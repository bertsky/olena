// Copyright (C) 2009 EPITA Research and Development Laboratory
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

#ifndef MLN_DEBUG_SUPERPOSE_HH
# define MLN_DEBUG_SUPERPOSE_HH

/// \file
///
/// Superpose two images.

# include <mln/core/concept/image.hh>
# include <mln/core/image/dmorph/image_if.hh>
# include <mln/value/rgb8.hh>
# include <mln/data/fill.hh>
# include <mln/data/convert.hh>
# include <mln/pw/all.hh>
# include <mln/literal/colors.hh>

namespace mln
{

  namespace debug
  {

    /// Superpose two images.
    ///
    /// \param[in] input_	An image. Its value type must be convertible
    ///				toward value::rgb8 thanks to a conversion
    ///				operator or convert::from_to.
    /// \param[in] object_	A binary image. Objects used for superposition
    ///				are set to 'true'.
    /// \param[in] object_color The color used to draw the objects in
    ///				\p object_.
    ///
    /// @pre \p input_ and \p object_ must have the same domain.
    ///
    /// \result A color image.
    //
    template <typename I, typename J>
    mln_ch_value(I,value::rgb8)
    superpose(const Image<I>& input_, const Image<J>& object_,
	      const value::rgb8& object_color);


    /// \overload
    template <typename I, typename J>
    mln_ch_value(I,value::rgb8)
    superpose(const Image<I>& input, const Image<J>& object);



# ifndef MLN_INCLUDE_ONLY

    template <typename I, typename J>
    mln_ch_value(I,value::rgb8)
    superpose(const Image<I>& input_, const Image<J>& object_,
	      const value::rgb8& object_color)
    {
      trace::entering("debug::superpose");

      const I& input = exact(input_);
      const J& object = exact(object_);

      mlc_equal(mln_value(J), bool)::check();
      mln_precondition(input.is_valid());
      mln_precondition(object.is_valid());
      mln_precondition(input.domain() == object.domain());

      mln_ch_value(I,value::rgb8) output = data::convert(value::rgb8(), input);
      data::fill((output | pw::value(object)).rw(), object_color);

      trace::exiting("debug::superpose");
      return output;
    }

    template <typename I, typename J>
    mln_ch_value(I,value::rgb8)
    superpose(const Image<I>& input, const Image<J>& object)
    {
      return superpose(input, object, literal::red);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::debug

} // end of namespace mln

#endif // ! MLN_DEBUG_SUPERPOSE_HH
