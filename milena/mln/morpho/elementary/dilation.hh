// Copyright (C) 2008, 2009 EPITA Research and Development Laboratory
// (LRDE)
//
// This file is part of the Milena Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License version 2 as published by the
// Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 51 Franklin Street, Fifth Floor,
// Boston, MA 02111-1307, USA.
//
// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

#ifndef MLN_MORPHO_ELEMENTARY_DILATION_HH
# define MLN_MORPHO_ELEMENTARY_DILATION_HH

/// \file

# include <mln/morpho/elementary/like_ero_fun.hh>
# include <mln/morpho/elementary/like_ero_set.hh>


namespace mln
{

  namespace morpho
  {

    namespace elementary
    {


      template <typename I, typename N>
      mln_concrete(I)
      dilation(const Image<I>& input, const Neighborhood<N>& nbh);


# ifndef MLN_INCLUDE_ONLY

      namespace internal
      {

	// Dispatch.

	template <typename I, typename N>
	mln_concrete(I)
	dilation_dispatch(trait::image::kind::any,
			  const Image<I>& input, const Neighborhood<N>& nbh)
	{
	  return like_ero_fun(accu::meta::stat::max(), f_accu(), input, nbh);
	}

	template <typename I, typename N>
	mln_concrete(I)
	dilation_dispatch(trait::image::kind::logic,
			 const Image<I>& input, const Neighborhood<N>& nbh)
	{
	  bool val[] =
	    {
	      0, // ext_value
	      1, // do_duplicate
	      0, // on_input_p
	      1, // on_input_n
	      1, // output_p
	    };
	  return like_ero_set(val, input, nbh);
	}

	template <typename I, typename N>
	mln_concrete(I)
	dilation_dispatch(const Image<I>& input, const Neighborhood<N>& nbh)
	{
	  return dilation_dispatch(mln_trait_image_kind(I)(),
				  input, nbh);
	}

      } // end of namespace mln::morpho::elementary::internal


      // Facade.

      template <typename I, typename N>
      mln_concrete(I)
      dilation(const Image<I>& input, const Neighborhood<N>& nbh)
      {
	trace::entering("morpho::elementary::dilation");

	mln_precondition(exact(input).is_valid());
	mln_precondition(exact(nbh).is_valid());

	mln_concrete(I) output = internal::dilation_dispatch(input, nbh);

	mln_postcondition(output >= input);
	trace::exiting("morpho::elementary::dilation");
	return output;
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::morpho::elementary

  } // end of namespace mln::morpho

} // end of namespace mln


#endif // ! MLN_MORPHO_ELEMENTARY_DILATION_HH
