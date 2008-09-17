// Copyright (C) 2005, 2008 EPITA Research and Development Laboratory (LRDE)
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
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.
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

#ifndef MLN_UTIL_GREATER_POINT_HH
# define MLN_UTIL_GREATER_POINT_HH

# include <mln/core/concept/image.hh>


namespace mln {

  namespace util {

    /** \brief A ``greater than'' functor comparing points w.r.t. the
        values they refer to in an image.

        This functor used in useful to implement ordered queues of
        points.  */
    template <typename I>
    class greater_point
    {
    public:
      typedef mln_psite(I) point;

      greater_point(const Image<I>& ima);

      /// Is \a x greater than \a y?
      bool operator()(const point& x, const point& y);

    private:
      const I& ima_;
    };


    /// Helper to build a mln::util::greater_point.
    /* FIXME: To be moved into mln/make/?  */
    template <typename I>
    greater_point<I>
    make_greater_point(const Image<I>& ima);


# ifndef MLN_INCLUDE_ONLY

    template <typename I>
    greater_point<I>::greater_point(const Image<I>& ima)
      : ima_ (exact(ima))
    {
    }

    template <typename I>
    bool
    greater_point<I>::operator()(const mln_psite(I)& x, const mln_psite(I)& y)
    {
      return ima_(x) > ima_(y);
    }


    template <typename I>
    greater_point<I>
    make_greater_point(const Image<I>& ima)
    {
      return greater_point<I>(ima);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::util

} // end of namespace mln

#endif // ! MLN_UTIL_GREATER_POINT_HH
