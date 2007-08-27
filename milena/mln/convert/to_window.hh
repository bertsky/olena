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

#ifndef MLN_CONVERT_TO_WINDOW_HH
# define MLN_CONVERT_TO_WINDOW_HH

/*! \file mln/convert/to_window.hh
 *
 * \brief Conversions to mln::window.
 */

# include <mln/core/concept/neighborhood.hh>
# include <mln/core/window.hh>
# include <mln/pw/image.hh>
# include <mln/pw/cst.hh>


namespace mln
{

  namespace convert
  {

    /// Convert a neighborhood \p nbh into a window.
    template <typename N>
    window<mln_dpoint(N)> to_window(const Neighborhood<N>& nbh);

    /// Convert a binary image \p ima into a window.
    template <typename I>
    window<mln_dpoint(I)> to_window(const Image<I>& ima);

    /// Convert a point set \p pset into a window.
    template <typename S, typename F>
    window<mln_dpoint(S)> to_window(const Point_Set<S>& pset);


# ifndef MLN_INCLUDE_ONLY

    template <typename N>
    window<mln_dpoint(N)> to_window(const Neighborhood<N>& nbh_)
    {
      const N& nbh = exact(nbh_);
      typedef mln_dpoint(N) D;
      typedef mln_point(D) P;
      window<D> win;
      mln_niter(N) n(nbh, P::zero);
      for_all(n)
	win.insert(n - P::zero);
      return win;
    }

    template <typename I>
    window<mln_dpoint(I)> to_window(const Image<I>& ima_)
    {
      const I& ima = exact(ima_);
      mln_precondition(ima.has_data());
      // FIXME: Check that ima is binary!
      typedef mln_dpoint(I) D;
      typedef mln_point(D) P;
      window<D> win;
      mln_piter(I) p(ima.domain());
      for_all(p)
	if (ima(p))
	  win.insert(p - P::zero);
      return win;
    }

    template <typename S, typename F>
    window<mln_dpoint(S)> to_window(const Point_Set<S>& pset)
    {
      return to_window(pw::cst(true) | pset);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::convert

} // end of namespace mln


#endif // ! MLN_CONVERT_TO_WINDOW_HH
