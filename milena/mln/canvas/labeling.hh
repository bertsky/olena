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

#ifndef MLN_CANVAS_LABELING_HH
# define MLN_CANVAS_LABELING_HH

/// \file mln/canvas/labeling.hh
///
/// Connected component labeling of the object part in a binary image.
///
/// \todo Make the fastest version work.

# include <mln/core/concept/image.hh>
# include <mln/data/fill.hh>
# include <mln/literal/zero.hh>
# include <mln/convert/to_upper_window.hh>


namespace mln
{

  namespace canvas
  {

    // General version.
    template <typename I, typename N, typename F, typename L>
    mln_ch_value(I, L)
    labeling(const Image<I>& input, const Neighborhood<N>& nbh,
	     F& functor, L& nlabels);


# ifndef MLN_INCLUDE_ONLY

    // Tests.

    namespace internal
    {

      template <typename I, typename N, typename F, typename L>
      void
      labeling_tests(const Image<I>& input_, const Neighborhood<N>& nbh_,
		     const F& f, const L& nlabels)
      {
	const I& input = exact(input_);
	const N& nbh   = exact(nbh_);

	mln_precondition(input.is_valid());
	mln_precondition(nbh.is_valid());

	(void) input;
	(void) nbh;
	(void) f;
	(void) nlabels;
      }

    } // end of namespace mln::canvas::internal



    // Implementations.

    namespace impl
    {

      namespace generic
      {

	template <typename I>
	static inline
	mln_psite(I)
	find_root(I& parent, const mln_psite(I)& x)
	{
	  if (parent(x) == x)
	    return x;
	  else
	    return parent(x) = find_root(parent, parent(x));
	}

	template <typename I, typename N, typename F, typename L>
	mln_ch_value(I, L)
	labeling(const Image<I>& input_, const Neighborhood<N>& nbh_,
		 F& f, L& nlabels)
	{
	  trace::entering("canvas::impl::generic::labeling");

	  // FIXME: Test?!

	  const I& input = exact(input_);
	  const N& nbh   = exact(nbh_);

	  typedef typename F::S S;

	  // Local type.
	  typedef mln_psite(I) P;

	  // Auxiliary data.
	  mln_ch_value(I, bool) deja_vu;
	  mln_ch_value(I, P)    parent;

	  // Output.
	  mln_ch_value(I, L) output;

	  // Initialization.
	  {
	    initialize(deja_vu, input);
	    mln::data::fill(deja_vu, false);

	    initialize(parent, input);

	    initialize(output, input);
	    mln::data::fill(output, L(literal::zero));
	    nlabels = 0;

	    f.init(); // Client initialization.
	  }

	  // First Pass.
	  {
	    mln_fwd_piter(S) p(f.s);
	    mln_niter(N) n(nbh, p);
	    for_all(p) if (f.handles(p))
	      {
		// Make-Set.
		parent(p) = p;
		f.init_attr(p);

		for_all(n)
		  if (input.domain().has(n) && deja_vu(n))
		    {
		      if (f.equiv(n, p))
			{
			  // Do-Union.
			  P r = find_root(parent, n);
			  if (r != p)
			    {
			      parent(r) = p;
			      f.merge_attr(r, p);
			    }
			}
		      else
			f.do_no_union(n, p);
		    }
		deja_vu(p) = true;
	      }
	  }

	  // Second Pass.
	  {
	    mln_bkd_piter(S) p(f.s);
	    for_all(p) if (f.handles(p))
	      {
		if (parent(p) == p) // if p is root
		  {
		    if (f.labels(p))
		      {
			if (nlabels == mln_max(L))
			  {
			    trace::warning("labeling aborted!");
			    return output;
			  }
			output(p) = ++nlabels;
		      }
		  }
		else
		  output(p) = output(parent(p));
	      }
	  }

	  trace::exiting("canvas::impl::generic::labeling");
	  return output;
	}

      } // end of namespace mln::canvas::impl::generic

    } // end of namespace mln::canvas::impl



    // Dispatch.

    namespace internal
    {

      template <typename I, typename N, typename F, typename L>
      inline
      mln_ch_value(I, L)
      labeling_dispatch(const Image<I>& input, const Neighborhood<N>& nbh,
			F& functor, L& nlabels)
      {
	return impl::generic::labeling(input, nbh, functor, nlabels);
      }

    } // end of namespace mln::canvas::internal



    // Facade.

    template <typename I, typename N, typename F, typename L>
    inline
    mln_ch_value(I, L)
    labeling(const Image<I>& input, const Neighborhood<N>& nbh,
	     F& functor, L& nlabels)
    {
      trace::entering("canvas::labeling");

      internal::labeling_tests(input, nbh, functor, nlabels);

      mln_ch_value(I, L) output;
      output = internal::labeling_dispatch(input, nbh, functor, nlabels);

      trace::exiting("canvas::labeling");
      return output;
    }


# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::canvas

} // end of namespace mln


#endif // ! MLN_CANVAS_LABELING_HH
