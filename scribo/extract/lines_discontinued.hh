// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

#ifndef SCRIBO_EXTRACT_PRIMITIVE_LINES_DISCONTINUED_HH
# define SCRIBO_EXTRACT_PRIMITIVE_LINES_DISCONTINUED_HH

/// \file scribo/primitive/lines/lines_discontinued.hh
///
/// Extract discontinued lines in a binary image.


# include <mln/core/concept/image.hh>
# include <mln/core/concept/window.hh>
# include <mln/core/concept/neighborhood.hh>
# include <mln/core/site_set/box.hh>

# include <mln/labeling/blobs.hh>
# include <mln/labeling/compute.hh>

# include <mln/morpho/rank_filter.hh>
# include <mln/morpho/dilation.hh>

# include <mln/accu/bbox.hh>

# include <mln/util/array.hh>
# include <mln/util/couple.hh>

# include <scribo/core/macros.hh>

namespace scribo
{

  namespace extract
  {

    namespace primitive
    {

      using namespace mln;


      /// Extract discontinued lines in a binary image.
      /*!
       * Based on a rank filter.
       *
       * \param[in]     input_	  A binary image.
       * \param[in]     nbh_	  The neighborhood used for labeling image
       *				  components.
       * \param[in,out] nlines	  The label type used for labeling.
       * \param[in]     win_	  A Window used to extract lines.
       * \param[in]     rank_k	  Rank used for filtering.
       * \param[in,out] line_bboxes line bounding boxes.
       *
       * \return An image in which lines are labeled.
       */
      template <typename I, typename N, typename V, typename W>
      mln_ch_value(I,V)
      lines_discontinued(const Image<I>& input_,
			 const Neighborhood<N>& nbh_, V& nlines,
			 const Window<W>& win_, unsigned rank_k,
			 util::array<box<mln_site(I)> >& line_bboxes);


      /// \overload
      template <typename I, typename N, typename V, typename W>
      mln_ch_value(I,V)
      lines_discontinued(const Image<I>& input_,
			 const Neighborhood<N>& nbh_, V& nlines,
			 const Window<W>& win_, unsigned rank_k);




# ifndef MLN_INCLUDE_ONLY


      namespace internal
      {

	template <typename I, typename N, typename V, typename W>
	void
	lines_discontinued_tests(const Image<I>& input,
				 const Neighborhood<N>& nbh, V& nlines,
				 const Window<W>& win, unsigned rank_k)
	{
	  mlc_equal(mln_value(I),bool)::check();
	  mlc_bool(mln_site_(I)::dim == 2)::check();
	  mlc_is_a(V, mln::value::Symbolic)::check();

	  mln_precondition(exact(input).is_valid());
	  mln_precondition(exact(nbh).is_valid());
	  mln_precondition(exact(win).is_valid());

	  (void) nlines;
	  (void) rank_k;
	}

    } // end of namespace scribo::primitive::internal



      template <typename I, typename N, typename V, typename W>
      inline
      mln_ch_value(I,V)
      lines_discontinued(const Image<I>& input_,
			 const Neighborhood<N>& nbh_, V& nlines,
			 const Window<W>& win_, unsigned rank_k)
      {
	trace::entering("scribo::primitive::lines_discontinued");

	internal::lines_discontinued_tests(input_, nbh_, nlines, win_, rank_k);

	const I& input = exact(input_);
	const N& nbh = exact(nbh_);
	const W& win = exact(win_);

	mln_ch_value(I,bool) filter = morpho::rank_filter(input, win, rank_k);
	mln_ch_value(I,V) output = labeling::blobs(filter, nbh, nlines);

	//FIXME: we would like to enlarge the component in the right direction,
	// in order to avoid rank filter side effects (smaller components).

	trace::exiting("scribo::primitive::lines_discontinued");
	return output;
      }




      template <typename I, typename N, typename V, typename W>
      inline
      mln_ch_value(I,V)
      lines_discontinued(const Image<I>& input_,
			 const Neighborhood<N>& nbh_, V& nlines,
			 const Window<W>& win_, unsigned rank_k,
			 util::array<box<mln_site(I)> >& line_bboxes)
      {
	trace::entering("scribo::primitive::lines_discontinued");

	internal::lines_discontinued_tests(input_, nbh_, nlines, win_, rank_k);

	const I& input = exact(input_);
	const N& nbh = exact(nbh_);
	const W& win = exact(win_);

	mln_ch_value(I,V)
	  output = lines_discontinued(input, nbh, nlines, win, rank_k);

	line_bboxes = labeling::compute(accu::meta::bbox(), output, nlines);
	mln_postcondition(line_bboxes.nelements() == nlines.next());

	//FIXME: is it correct?
	for_all_components(i, line_bboxes)
	{
	  line_bboxes[i].enlarge(W::dir, win.delta_() - rank_k);
	  line_bboxes[i].crop_wrt(input.domain());
	}

	trace::exiting("scribo::primitive::lines_discontinued");
	return output;
      }

# endif // ! MLN_INCLUDE_ONLY


    } // end of namespace scribo::extract::primitive

  } // end of namespace scribo::extract

} // end of namespace scribo

#endif // ! SCRIBO_EXTRACT_PRIMITIVE_LINES_DISCONTINUED_HH