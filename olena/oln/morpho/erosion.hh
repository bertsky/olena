// Copyright (C) 2007 EPITA Research and Development Laboratory
//
// This file is part of the Olena Library.  This library is free
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

#ifndef	OLN_MORPHO_EROSION_HH
# define OLN_MORPHO_EROSION_HH

#include <oln/level/apply_local.hh>
#include <oln/border/fill.hh>
#include <oln/accumulator/max.hh>

namespace oln
{

  namespace morpho
  {

    // Fwd decl.

    template <typename I, typename W>
    oln_plain(I)
      erosion(const Image<I>& input, const Window<W>& win);


# ifndef OLN_INCLUDE_ONLY

    namespace impl
    {

      // Generic version.

      template <typename I, typename W>
      oln_plain(I)
      erosion_(const Image<I>& input, const Window<W>& win)
      {
	border::fill(input, oln_min(oln_value(I)));
	accumulator::min_<oln_value(I)> min;
	return level::apply_local(min, input, win);
      }

      template <typename I>
      oln_plain(I)
      erosion_on_set_(const Image<I>&,
		      const I& input)
      {
	border::fill(input, oln_min(oln_value(I)));
	accumulator::and_<oln_value(I)> accu_and;
	return level::apply_local(accu_and, input);
      }

      // FIXME: Add a fast version.


      // Impl facade.

      template <typename I>
      oln_plain(I) erosion_(const Image<I>& input)
      {
	return erosion_on_function_(exact(input), exact(input));
      }

      template <typename I>
      oln_plain(I) erosion_(const Binary_Image<I>& input)
      {
	return erosion_on_set_(exact(input), exact(input));
      }

    } // end of namespace oln::morpho::impl


    // Facade.

    template <typename I, typename W>
    oln_plain(I)
    erosion(const Image<I>& input, const Window<W>& win)
    {
      return impl::erosion_(exact(input), exact(win));
    }

# endif // ! OLN_INCLUDE_ONLY

  } // end of namespace oln::morpho

} // end of namespace oln


#endif // ! OLN_MORPHO_EROSION_HH
