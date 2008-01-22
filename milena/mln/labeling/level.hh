// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_LABELING_LEVEL_HH
# define MLN_LABELING_LEVEL_HH

/*! \file mln/labeling/level.hh
 *
 * \brief Connected component labeling of the image objects at a given
 * level.
 */

# include <mln/core/concept/image.hh>
# include <mln/core/concept/neighborhood.hh>
# include <mln/canvas/labeling.hh>
# include <mln/level/fill.hh>

// The 'fastest' specialization is in:
# include <mln/labeling/level.spe.hh>



namespace mln
{

  namespace labeling
  {

    /* FIXME: The neighborhood shall not be passed as argument, but
       bound to the input image.  We can also optionnaly provide a
       version of this function for regular-grid-based images where
       the neighborhood is replaced by a (user-provided) window.  */

    /*! Connected component labeling of the image objects at a given
     * level.
     *
     * \param[in]  input    The input image.
     * \param[in]  val      The level to consider for the labeling.
     * \param[in]  nbh      The neighborhood.
     * \param[out] nlabels  The number of labels.
     * \return              The label image.
     */
    template <typename I, typename N, typename L>
    mln_ch_value(I, L)
    level(const Image<I>& input, const mln_value(I)& val,
	  const Neighborhood<N>& nbh, L& nlabels);


# ifndef MLN_INCLUDE_ONLY

    namespace impl
    {

      // Generic functor.

      template <typename I_, typename N_, typename L_>
      struct level_functor
      {
	typedef mln_psite(I_) P;

	// requirements from mln::canvas::labeling:

	typedef I_ I;
	typedef N_ N;
	typedef L_ L;
        typedef mln_pset(I) S;

	const I& input;
	const N& nbh;
        const S& s;

	bool handles(const P& p) const         { return input(p) == val; }
	bool equiv(const P& n, const P&) const { return input(n) == val; }

 	void init()                          {}
	bool labels(const P&) const          { return true;  }
	void do_no_union(const P&, const P&) {}
	void init_attr(const P&)             {}
	void merge_attr(const P&, const P&)  {}

	// end of requirements

	const mln_value(I_)& val;

	level_functor(const I_& input, const mln_value(I_)& val, const N_& nbh)
	  : input(input),
	    nbh(nbh),
	    s(input.domain()),
	    val(val)
	{}
      };


      // Generic implementation.

      namespace generic
      {

	template <typename I, typename N, typename L>
	mln_ch_value(I, L)
	  level_(const I& input, const mln_value(I)& val, const N& nbh,
		 L& nlabels)
	{
	  trace::entering("labeling::impl::generic::level_");

	  typedef level_functor<I,N,L> F;
	  F f(input, val, nbh);
	  canvas::labeling<F> run(f);
	  
	  nlabels = run.nlabels;
	  // FIXME: Handle run.status

	  trace::exiting("labeling::impl::generic::level_");
	  return run.output;
	}

      } // end of namespace mln::labeling::impl::generic


    } // end of namespace mln::labeling::impl



    // Facade.

    template <typename I, typename N, typename L>
    mln_ch_value(I, L)
      level(const Image<I>& input, const mln_value(I)& val,
	    const Neighborhood<N>& nbh, L& nlabels)
    {
      trace::entering("labeling::level");
      mln_precondition(exact(input).has_data());

      mln_ch_value(I, L) output =
	impl::level_(mln_trait_image_speed(I)(),
		     exact(input), val, exact(nbh), nlabels);

      trace::exiting("labeling::level");
      return output;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::labeling

} // end of namespace mln


#endif // ! MLN_LABELING_LEVEL_HH
