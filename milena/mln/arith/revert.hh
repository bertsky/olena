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

#ifndef MLN_ARITH_REVERT_HH
# define MLN_ARITH_REVERT_HH

/*! \file mln/arith/revert.hh
 *
 * \brief Point-wise revert (min -> max and max -> min) of images.
 *
 * \todo Add static assertion and save one iterator in in-place version.
 */

# include <mln/core/concept/image.hh>
# include <mln/value/props.hh>

// FIXME: Rely instead on mln/fun/v2v/revert.hh.
// FIXME: Revert on int value 0 does not give 0 (since min != - max; idem for float etc.)



namespace mln
{

  namespace arith
  {

    /*! Point-wise reversion of image \p input.
     *
     * \param[in] input the input image.
     * \param[out] output The result image.
     *
     * \pre \p output.domain == \p input.domain
     */
    template <typename I, typename O>
    void revert(const Image<I>& input, Image<O>& output);


    /*! Point-wise in-place reversion of image \p input.
     *
     * \param[in,out] input The target image.
     *
     * It performs: \n
     *   for all p of input.domain \n
     *     input(p) = min + (max - input(p))
     */
    template <typename I>
    void revert_inplace(Image<I>& input);


# ifndef MLN_INCLUDE_ONLY

    namespace impl
    {

      template <typename I, typename O>
      void revert_(const Image<I>& input_, Image<O>& output_)
      {
	const I& input = exact(input_);
	O& output = exact(output_);
	typedef mln_value(I) V;
	mln_piter(I) p(input.domain());
	for_all(p)
	  output(p) = mln_min(V) + (mln_max(V) - input(p));
      }

      template <typename I, typename O>
      void revert_(const Fastest_Image<I>& input, Fastest_Image<O>& output)
      {
	typedef mln_value(I) V;
	mln_pixter(const I) ip(exact(input));
	mln_pixter(O)       op(exact(output));
	for_all_2(ip, op)
	  op.val() = mln_min(V) + (mln_max(V) - ip.val());
      }

    } // end of namespace mln::arith::impl


    // Facades.

    template <typename I, typename O>
    void revert(const Image<I>& input, Image<O>& output)
    {
      mln_precondition(exact(output).domain() == exact(input).domain());
      impl::revert_(exact(input), exact(output));
    }

    template <typename I>
    void revert_inplace(Image<I>& input)
    {
      mln_precondition(exact(input).has_data());
      impl::revert_(exact(input), exact(input));
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::arith

} // end of namespace mln


#endif // ! MLN_ARITH_REVERT_HH
