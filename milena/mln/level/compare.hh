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

#ifndef MLN_LEVEL_COMPARE_HH
# define MLN_LEVEL_COMPARE_HH

/*! \file mln/level/compare.hh
 *
 * \brief Comparison operators between the pixel values of images.
 */

# include <mln/core/concept/image.hh>
# include <mln/fun/vv2b/eq.hh>
# include <mln/fun/vv2b/le.hh>
# include <mln/fun/vv2b/lt.hh>
# include <mln/test/predicate.hh>


namespace mln
{

  /*! Point-wise test if the pixel values of \p lhs are equal to the
   *  pixel values of \p rhs.
   *
   * \param[in] lhs A first image.
   * \param[in] rhs A second image.
   *
   * \pre lhs.domain == rhs.domain
   */
  template <typename L, typename R>
  bool operator == (const Image<L>& lhs, const Image<R>& rhs);


  /*! Point-wise test if the pixel values of \p lhs are point-wise
   *  less than the pixel values of \p rhs.
   *
   * \param[in] lhs A first image.
   * \param[in] rhs A second image.
   *
   * \pre lhs.domain == rhs.domain
   */
  template <typename L, typename R>
  bool operator < (const Image<L>& lhs, const Image<R>& rhs);


  /*! Point-wise test if the pixel values of \p lhs are point-wise
   *  less than or equal to the pixel values of \p rhs.
   *
   * \param[in] lhs A first image.
   * \param[in] rhs A second image.
   *
   * \pre lhs.domain == rhs.domain
   */
  template <typename L, typename R> // required!
  bool operator <= (const Image<L>& lhs, const Image<R>& rhs);



# ifndef MLN_INCLUDE_ONLY

  template <typename L, typename R>
  inline
  bool operator == (const Image<L>& lhs_, const Image<R>& rhs_)
  {
    typedef fun::vv2b::eq<mln_value(L), mln_value(R)> F;

    const L& lhs = exact(lhs_);
    const R& rhs = exact(rhs_);
    mln_precondition(lhs.domain() == rhs.domain());

    return test::predicate(lhs_, rhs_, F());
  }

  template <typename L, typename R>
  inline
  bool operator < (const Image<L>& lhs_, const Image<R>& rhs_)
  {
    typedef fun::vv2b::lt<mln_value(L), mln_value(R)> F;

    const L& lhs = exact(lhs_);
    const R& rhs = exact(rhs_);
    mln_precondition(lhs.domain() == rhs.domain());

    return test::predicate(lhs_, rhs_, F());
  }

  template <typename L, typename R> // required!
  inline
  bool operator <= (const Image<L>& lhs_, const Image<R>& rhs_)
  {
    typedef fun::vv2b::le<mln_value(L), mln_value(R)> F;

    const L& lhs = exact(lhs_);
    const R& rhs = exact(rhs_);
    mln_precondition(lhs.domain() == rhs.domain());

    return test::predicate(lhs_, rhs_, F());
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_LEVEL_COMPARE_HH
