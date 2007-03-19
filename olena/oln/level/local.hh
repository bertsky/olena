// Copyright (C) 2007 EPITA Research and Development Laboratory
//
// This file is part of the Olena Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License version 2 as published by the
// Free Software Foundation.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 51 Franklin Street, Fifth Floor,
// Boston, MA 02111-1307, USA.
//
// As a special exception, you may
// use this file as part of a free software library without
// restriction.  Specifically, if other files instantiate templates or
// use macros or inline functions from this file, or you compile this
// file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be
// covered by the GNU General Public License.  This exception does not
// however invalidate any other reasons why the executable file might
// be covered by the GNU General Public License.

#ifndef OLN_LEVEL_LOCAL_HH
# define OLN_LEVEL_LOCAL_HH

# include <oln/core/concept/image.hh>
# include <oln/core/concept/window.hh>
# include <oln/core/concept/accumulator.hh>


namespace oln
{

  namespace level
  {

    template <typename A, typename I>
    typename A::result
    local(const Accumulator<A>&    f,
	  const Image_with_Nbh<I>& input,
	  const oln_point(I)&      p);

    template <typename F, typename I, typename W>
    typename F::result
    local(const Accumulator<F>& f,
	  const Image<I>&       input,
	  const oln_point(I)&   p,
	  const Window<W>&      win);


# ifndef OLN_INCLUDE_ONLY

    namespace impl
    {

      // Generic version with neighborhood.

      template <typename A, typename I>
      typename A::result
      local_(const A&    f,
	     const Image_with_Nbh<I>& input,
	     const oln_point(I)&      p)
      {
	f.init();
	oln_niter(I) n(p, input.nbhood()); // FIXME: 2nd arg should be 'input'!
	for_all(n)
	  f(input(n));
	return f.value();
      }


      // FIXME: Generic version with nbh given as argument?


      // Generic version with window.

      template <typename F, typename I, typename W>
      typename F::result
      local_(const F& f,
	     const Image<I>&       input,
	     const oln_point(I)&   p,
	     const Window<W>&      win)
      {
	f.init();
	oln_qiter(W) q(p, win);
	for_all(q)
	  f(input(q));
	return f.value();
      }

    } // end of namespace oln::level::impl


    // Facades.

    template <typename A, typename I>
    typename A::result
    local(const Accumulator<A>&    f,
	  const Image_with_Nbh<I>& input,
	  const oln_point(I)&      p)
    {
      return impl::local_(exact(f), input, p);
    }

    template <typename F, typename I, typename W>
    typename F::result
    local(const Accumulator<F>& f,
	  const Image<I>&       input,
	  const oln_point(I)&   p,
	  const Window<W>&      win)
    {
      return impl::local_(exact(f), input, p, win);
    }

#endif // ! OLN_INCLUDE_ONLY

  } // end of namespace oln::level

} // end of namespace oln

#endif // ! OLN_LEVEL_LOCAL_HH
