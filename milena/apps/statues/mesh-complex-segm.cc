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

/// \file apps/statues/mesh-complex-segm.cc
/// \brief A program performing a WST-based segmentation of the
/// surface of the (triangle) mesh of a statue, using a complex-based
/// image.

#include <cstdlib>
#include <cmath>

#include <utility>
#include <iostream>

#include <mln/core/image/complex_image.hh>
#include <mln/core/image/complex_neighborhoods.hh>

#include <mln/morpho/closing_area.hh>
#include <mln/morpho/meyer_wst.hh>

#include <mln/literal/white.hh>

#include <mln/io/off/load.hh>
#include <mln/io/off/save.hh>



int main(int argc, char* argv[])
{
  if (argc != 4)
    {
      std::cerr << "usage: " << argv[0] << " input.off lambda output.off"
		<< std::endl;
      exit(1);
    }

  std::string input_filename = argv[1];
  unsigned lambda = atoi(argv[2]);
  std::string output_filename = argv[3];

  /*----------------.
  | Complex image.  |
  `----------------*/

  // Image type.
  typedef mln::float_2complex_image3df ima_t;
  // Dimension of the image (and therefore of the complex).
  static const unsigned D = ima_t::dim;
  // Geometry of the image.
  typedef mln_geom_(ima_t) G;

  ima_t input;
  mln::io::off::load(input, input_filename);

  // Values on edges.

  /* FIXME: To be improved: instead of computing the curvature on
     edges from a mean of the curvature on adjacent polygons, compute
     it directly from the curvature on vertices.  We should probably
     integrate Trimesh's curvature computation into Milena.  */
  mln::p_n_faces_fwd_piter<D, G> e(input.domain(), 1);
  typedef mln::complex_higher_neighborhood<D, G> adj_polygons_nbh_t;
  adj_polygons_nbh_t adj_polygons_nbh;
  mln_niter_(adj_polygons_nbh_t) p(adj_polygons_nbh, e);
  // Iterate on edges (1-faces).
  for_all(e)
  {
    float s = 0.0f;
    unsigned n = 0;
    for_all(p)
    {
      s += input(p);
      ++n;
    }
    input(e) = s / n;
    // An edge should be adjacent to two polygons at most.
    mln_invariant(n <= 2);
  }

  /*-----------------.
  | Simplification.  |
  `-----------------*/

  /// Adjancent edges are connected by shared polygons.
  typedef
    mln::complex_higher_dim_connected_n_face_neighborhood<D, G>
    adj_edges_nbh_t;
  adj_edges_nbh_t adj_edges_nbh;

  ima_t closed_input(input.domain());
  mln::morpho::closing_area(input, adj_edges_nbh, lambda, closed_input);

  /*------.
  | WST.  |
  `------*/

  /* FIXME: Note that the WST is either doing too much work, since we
     have not constrained the domain of the image to 1-faces only.

     It would be great if we could use something like this:

         closed_input | mln::p_faces<1, D, G>(closed_input.domain())

      as input of the WST.  */

  // Compute the WST on edges.
  typedef unsigned wst_val_t;
  wst_val_t nbasins;
  typedef mln::unsigned_2complex_image3df wst_ima_t;
  wst_ima_t wshed =
    mln::morpho::meyer_wst(closed_input, adj_edges_nbh, nbasins);
  std::cout << "nbasins = " << nbasins << std::endl;

  // Label polygons (i.e., propagate labels from edges to polygons).
  for_all(e)
    if (wshed(e) != 0)
      for_all(p)
	wshed(p) = wshed(e);

  /*---------.
  | Output.  |
  `---------*/

  mln::rgb8_2complex_image3df output(wshed.domain());
  mln::data::fill(output, mln::literal::white);

  // FIXME: Use a colorize functor instead.
  // Choose random colors for each basin number.
  std::vector<mln::value::rgb8> basin_color (nbasins + 1);
  for (unsigned i = 0; i <= nbasins; ++i)
    basin_color[i] = mln::value::rgb8(random() % 256,
				      random() % 256,
				      random() % 256);
  mln_piter_(ima_t) f(wshed.domain());
  for_all(f)
    output(f) = basin_color[wshed(f)];

  mln::io::off::save(output, output_filename);
}
