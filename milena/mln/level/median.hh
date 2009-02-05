// Copyright (C) 2007, 2008, 2009 EPITA Research and Development
// Laboratory (LRDE)
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

#ifndef MLN_LEVEL_MEDIAN_HH
# define MLN_LEVEL_MEDIAN_HH

/// \file mln/level/median.hh
///
/// Median filtering of an image.
///
/// \todo Add versions for fastest and semi-linear images.

# include <mln/core/concept/image.hh>
# include <mln/core/window.hh>
# include <mln/core/alias/dpoint2d.hh>

# include <mln/win/shift.hh>
# include <mln/win/diff.hh>
# include <mln/win/line.hh>

# include <mln/canvas/browsing/snake_fwd.hh>
# include <mln/accu/median_h.hh>
# include <mln/accu/transform_line.hh>


namespace mln
{

  namespace level
  {

    /*! Compute in \p output the median filter of image \p input by
     *  the window \p win.
     *
     * \param[in] input The image to be filtered.
     * \param[in] win The window.
     * \param[out] output The output image.
     *
     * \pre \p input and \p output have to be initialized.
     */
    template <typename I, typename W>
    mln_concrete(I)
    median(const Image<I>& input, const Window<W>& win);



# ifndef MLN_INCLUDE_ONLY

    namespace internal
    {

      template <typename I, typename W>
      void
      median_tests(const Image<I>& input, const Window<W>& win)
      {
	mln_precondition(exact(input).is_valid());
	mln_precondition(exact(win).is_valid());
	(void) input;
	(void) win;
      }

    } // end of namespace level::internal


    namespace impl
    {

      // Functors.


      template <typename I, typename W, typename O>
      struct median_t
      {
	typedef mln_psite(I)  P;
	typedef mln_dpsite(P) D;

	// i/o

	const I& input;
	const W& win;
	O& output;

	// aux data

	accu::median_h<mln_value(I)> med;
	P p;
	window<D>    win_fp, win_fm, win_bp, win_bm, win_dp, win_dm;
	mln_qiter(window<D>)   q_fp,   q_fm,   q_bp,   q_bm,   q_dp,   q_dm;

	// ctor

	inline
	median_t(const I& input_, const W& win_, O& output_)
	  :
	  // i/o
	  input(exact(input_)),
	  win(exact(win_)),
	  output(exact(output_)),
	  // aux data
	  med(),
	  p(),
	  win_fp(win - win::shift(win, left)),
	  win_fm(win::shift(win, left)  - win),
	  win_bp(win - win::shift(win, right)),
	  win_bm(win::shift(win, right) - win),
	  win_dp(win - win::shift(win, up)),
	  win_dm(win::shift(win, up)    - win),
	  q_fp(win_fp, p),  q_fm(win_fm, p),
	  q_bp(win_bp, p),  q_bm(win_bm, p),
	  q_dp(win_dp, p),  q_dm(win_dm, p)
	{
	}

	// parts

	inline
	void init()
	{
	  med.init();
	  p = input.domain().pmin() + up;
	  mln_qiter(W) q(win, p);
	  for_all(q) if (input.has(q))
            med.take(input(q));
	}

	inline
	void down()
	{
	  for_all(q_dm) if (input.has(q_dm))
	    med.untake(input(q_dm));
	  for_all(q_dp) if (input.has(q_dp))
	    med.take(input(q_dp));
	  output(p) = med.to_result();
	}

	inline
	void fwd()
	{
	  for_all(q_fm) if (input.has(q_fm))
	    med.untake(input(q_fm));
	  for_all(q_fp) if (input.has(q_fp))
	    med.take(input(q_fp));
	  output(p) = med.to_result();
	}

	inline
	void bkd()
	{
	  for_all(q_bm) if (input.has(q_bm))
	    med.untake(input(q_bm));
	  for_all(q_bp) if (input.has(q_bp))
            med.take(input(q_bp));
	  output(p) = med.to_result();
	}

      }; // end of median_t



      namespace generic
      {

	template <typename I, typename W>
	inline
	mln_concrete(I)
	median(const Image<I>& input, const Window<W>& win)
	{
	  trace::entering("level::impl::generic::median");

	  mlc_equal(mln_trait_image_quant(I),
		    trait::image::quant::low)::check();
	  internal::median_tests(input, win);

	  extension::adjust(input, win);

	  typedef mln_concrete(I) O;
	  O output;
	  initialize(output, input);
	  median_t<I,W,O> f(exact(input), exact(win), output);
	  canvas::browsing::snake_fwd(f);

	  trace::exiting("level::impl::generic::median");
	  return output;
	}

      } // end of namespace mln::level::impl::generic


      template <typename I,
		typename M, unsigned i, typename C>
      inline
      mln_concrete(I)
      median_line(const Image<I>& input, const win::line<M,i,C>& win)
      {
	trace::entering("level::impl::median_line");

	mlc_equal(mln_trait_image_quant(I),
		  trait::image::quant::low)::check();
	internal::median_tests(input, win);

	accu::median_h<mln_value(I)> a;
	mln_concrete(I) output = accu::transform_line(a, input, win.length(), i);

	trace::exiting("level::impl::median_line");
	return output;
      }


    } // end of namespace mln::level::impl



    namespace internal
    {

      template <typename I, typename W>
      inline
      mln_concrete(I)
      median_dispatch_wrt_win(const Image<I>& input, const Window<W>& win)
      {
	return impl::generic::median(input, win);
      }

      template <typename I,
		typename M, unsigned i, typename C>
      inline
      mln_concrete(I)
      median_dispatch_wrt_win(const Image<I>& input, const win::line<M,i,C>& win)
      {
	return impl::median_line(input, win);
      }


      template <typename I, typename W>
      inline
      mln_concrete(I)
      median_dispatch(const Image<I>& input, const Window<W>& win)
      {
	return median_dispatch_wrt_win(input, exact(win));
      }

    } // end of namespace level::internal


    // Facade.

    template <typename I, typename W>
    mln_concrete(I)
    median(const Image<I>& input, const Window<W>& win)
    {
      trace::entering("level::median");

      mlc_equal(mln_trait_image_quant(I),
		trait::image::quant::low)::check();

      internal::median_tests(input, win);
      mln_concrete(I) output;
      output = internal::median_dispatch(input, win);

      trace::exiting("level::median");
      return output;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::level

} // end of namespace mln


#endif // ! MLN_LEVEL_MEDIAN_HH
