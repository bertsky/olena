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

#ifndef MLN_TEST_PREDICATE_HH
# define MLN_TEST_PREDICATE_HH

/*! \file mln/test/predicate.hh
 *
 * \brief Test a predicate on the pixel values of an image.
 */

# include <mln/core/concept/image.hh>
# include <mln/core/concept/function.hh>
# include <mln/core/concept/site_set.hh>


namespace mln
{

  namespace test
  {

    /*! Test if all pixel values of \p ima verify the predicate \p
     *  f.
     *
     * \param[in] ima The image.
     * \param[in] f The predicate.
     */
    template <typename I, typename F>
    bool predicate(const Image<I>& ima, const Function_v2b<F>& f);


    /*! Test if all pixel values of \p lhs and \p rhs verify the
     *  predicate \p f.
     *
     * \param[in] lhs The image.
     * \param[in] rhs The image.
     * \param[in] f The predicate.
     */
    template <typename I, typename J, typename F>
    bool predicate(const Image<I>& lhs, const Image<J>& rhs, const Function_v2b<F>& f);


    /*! Test if all points of \p pset verify the predicate \p f.
     *
     * \param[in] pset The point set.
     * \param[in] f The predicate.
     */
    template <typename S, typename F>
    bool predicate(const Site_Set<S>& pset, const Function_p2b<F>& f);


# ifndef MLN_INCLUDE_ONLY

    namespace impl
    {

      template <typename I, typename F>
      inline
      bool predicate_(trait::image::speed::any, const I& ima, const F& f)
      {
	mln_piter(I) p(ima.domain());
	for_all(p)
	  if (! f(ima(p)))
	    return false;
	return true;
      }

      template <typename I, typename F>
      inline
      bool predicate_(trait::image::speed::fastest, const I& ima, const F& f)
      {
	mln_pixter(const I) pxl(ima);
	for_all(pxl)
	  if (! f(pxl.val()))
	    return false;
	return true;
      }

      template <typename I, typename J, typename F>
      inline
      bool predicate_(trait::image::speed::any,
		      trait::image::speed::any,
		      const I& lhs, const J& rhs, const F& f)
      {
	mln_piter(I) p(lhs.domain());
	for_all(p)
	  if (! f(lhs(p), rhs(p)))
	    return false;
	return true;
      }

      template <typename I, typename J, typename F>
      inline
      bool predicate_(trait::image::speed::fastest,
		      trait::image::speed::fastest,
		      const I& lhs, const J& rhs, const F& f)
      {
	mln_pixter(const I) pxl1(lhs);
	mln_pixter(const I) pxl2(rhs);
	for_all_2(pxl1, pxl2)
	  if (! f(pxl1.val(), pxl2.val()))
	    return false;
	return true;
      }

      template <typename S, typename F>
      inline
      bool predicate_(const Site_Set<S>& pset, const F& f)
      {
	mln_piter(S) p(exact(pset));
	for_all(p)
	  if (! f(p))
	    return false;
	return true;
      }

    } // end of namespace mln::test::impl


    // Facades.

    template <typename I, typename F>
    inline
    bool predicate(const Image<I>& ima, const Function_v2b<F>& f)
    {
      mln_precondition(exact(ima).has_data());
      return impl::predicate_(mln_trait_image_speed(I)(), exact(ima),
			      exact(f));
    }


    template <typename I, typename J, typename F>
    inline
    bool predicate(const Image<I>& lhs_, const Image<J>& rhs_, const Function_vv2b<F>& f)
    {
      const I& lhs = exact(lhs_);
      const J& rhs = exact(rhs_);

      mln_precondition(lhs.has_data());
      mln_precondition(rhs.has_data());
      mln_precondition(lhs.domain() == rhs.domain());

      return impl::predicate_(mln_trait_image_speed(I)(),
			      mln_trait_image_speed(J)(),
			      lhs, rhs,
			      exact(f));
    }

    template <typename S, typename F>
    inline
    bool predicate(const Site_Set<S>& pset, const Function_p2b<F>& f)
    {
      return impl::predicate_(exact(pset), exact(f));
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::test

} // end of namespace mln


#endif // ! MLN_TEST_PREDICATE_HH
