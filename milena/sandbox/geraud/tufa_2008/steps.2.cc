// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
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

/// \file sandbox/geraud/tufa/steps.cc

#include <mln/core/image/image2d.hh>
#include <mln/value/int_u8.hh>
#include <mln/io/pgm/load.hh>
#include <mln/debug/println.hh>

#include <mln/core/site_set/p_array.hh>
#include <mln/level/sort_psites.hh>
#include <mln/core/alias/neighb2d.hh>
#include <mln/morpho/tree/data.hh>

#include <mln/accu/count.hh>
#include <mln/util/set.hh>

#include <mln/labeling/regional_minima.hh>
#include <mln/morpho/tree/compute_attribute_image.hh>
#include <mln/morpho/closing_area.hh>
#include <mln/level/fill.hh>


namespace mln
{

  template <typename I>
  void println_par(const I& par)
  {
    int nr = par.nrows(), nc = par.ncols();
    for (int r = 0; r < nr; ++r)
      {
	for (int c = 0; c < nc; ++c)
	  if (par.at(r,c) == point2d(r,c))
	    std::cout << "(    ) ";
	  else
	    std::cout << par.at(r,c) << ' ';
	std::cout << std::endl;
      }
  }

  template <typename P>
  inline
  mln_value(P) find_root__(P& par, const mln_value(P)& x)
  {
    if (par(x) == x)
      return x;
    else
      return par(x) = find_root__(par, par(x));
  }


  template <typename I, typename A, typename N>
  mln_ch_value(I, util::set<unsigned>)
    compute_labels(const I& f, const A& a, const N& nbh,
		   unsigned n_objects,
		   bool echo = false)
  {
    if (echo)
      debug::println("f =", f);

    typedef p_array<mln_psite(I)> S;
    S s = level::sort_psites_increasing(a);
    // s maps increasing attributes.

    mln_ch_value(I, mln_site(I)) par;
    mln_ch_value(I, bool) deja_vu;
    mln_ch_value(I, util::set<unsigned>) labels;
    unsigned nbassins, current_n;

    // Initialization.
    {
      mln_piter(A) p(f.domain());

      // parent
      initialize(par, f);
      for_all(p)
	par(p) = p;

      // deja_vu
      initialize(deja_vu, f);
      level::fill(deja_vu, false);

      // labels
      mln_ch_value(I, unsigned) regmin = labeling::regional_minima(a, nbh,
								   nbassins);
      if (n_objects >= nbassins)
	{
	  std::cerr << "The number of expected objects is higher than the number of regional minima!" << std::endl;
	  std::abort();
	}

      if (echo)
	debug::println("regmin(f) =", regmin);

      initialize(labels, f);
      for_all(p)
	if (regmin(p) != 0) // p in a reg min of the attribute image
	  labels(p).insert(regmin(p));
    }

    current_n = nbassins;

    // First pass.
    {
      mln_site(I) r;
      mln_fwd_piter(S) p(s);
      mln_niter(N) n(nbh, p);
      for_all(p)
	{
	  for_all(n)
	    if (a.domain().has(n) && deja_vu(n))
	      {
		r = find_root__(par, n);
		if (r != p)
		  {
		    par(r) = p; // Union.

		    if (labels(r).is_empty())
		      // No-op.
		      ;
		    else
		      if (labels(p).is_empty())
			labels(p) = labels(r);
		      else
			if (labels(p) == labels(r))
			  // No-op.
			  ;
			else
			  {
			    labels(p).insert(labels(r));
			    --current_n;
			    if (current_n == n_objects && echo)
			      {
				// Filtering.
				mln_concrete(I) g;
				initialize(g, f);
				mln_bkd_piter(S) p(s);
				for_all(p)
				  if (par(p) == p)
				    g(p) = f(p);
				  else
				    g(p) = g(par(p));
				debug::println("g =", g);

				// Testing.
				unsigned n_result;
				mln_ch_value(I, unsigned) g_regmin;
				g_regmin = labeling::regional_minima(g, nbh, n_result);
				debug::println("regmin(g) =", g_regmin);

				mln_invariant(n_result == n_objects);
			      }
			  }		    
		  }
	      }
	  deja_vu(p) = true;
	}
    }

    mln_invariant(current_n == 1); // All labels are merged into a single set.

    return labels;
  }


} // mln


void usage(char* argv[])
{
  std::cerr << "usage: " << argv[0] << " input.pgm n echo" << std::endl;
  std::cerr << "n: number of expected objects (n > 0)" << std::endl;
  std::cerr << "echo: 0 (silent) or 1 (verbose)" << std::endl;
  std::cerr << "merge using sets of labels from regional minima and save the highest label image" << std::endl;
  std::abort();
}


int main(int argc, char* argv[])
{
  using namespace mln;
  using value::int_u8;

  if (argc != 4)
    usage(argv);

  typedef image2d<int_u8> I;
  I f;
  // input image
  io::pgm::load(f, argv[1]);

  // n
  int n = std::atoi(argv[2]);
  if (n <= 0)
    usage(argv);

  // echo
  int echo = std::atoi(argv[3]);
  if (echo != 0 && echo != 1)
    usage(argv);

  typedef p_array<point2d> S;
  S s = level::sort_psites_decreasing(f);

  // Children go towards lower levels so leafs are regional minima.
  // We get a min-tree so that we can perform morphological closings. 

  morpho::tree::data<I,S> t(f, s, c4());
  accu::count< util::pix<I> > attr;

  image2d<unsigned> a = morpho::tree::compute_attribute_image(attr, t);


  image2d< util::set<unsigned> > labels = compute_labels(f, a, c4(), n, echo);
  if (echo)
    debug::println("labels =", labels);

  {
    image2d<unsigned> lab(f.domain());
    mln_piter_(I) p(f.domain());
    for_all(p)
      {
	mln_assertion(! labels(p).is_empty());
	lab(p) = labels(p).last_element();
      }
    if (echo)
      debug::println("max of labels (clearly NOT the objects image!) =", lab);

    // We can observe that we do NOT get objects this way...
  }

}
