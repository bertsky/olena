// Copyright (C) 2007, 2008, 2009 EPITA Research and Development
// Laboratory (LRDE)
//
// This file is part of the Milena Library.  This library is free
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

/// \file
///
/// Tests on mln::line_graph_image with morphological filters.

#include <mln/core/alias/point2d.hh>

/// Required for line graph images.
#include <mln/core/image/vertex_image.hh>
#include <mln/fun/i2v/array.hh>
#include <mln/util/line_graph.hh>
#include <mln/util/graph.hh>
#include <mln/util/site_pair.hh>
#include <mln/make/vertex_image.hh>

#include <mln/morpho/erosion.hh>
#include <mln/morpho/dilation.hh>

static const unsigned dil_ref[] = { 12, 14, 13, 14, 13 };
static const unsigned ero_ref[] = { 11, 10, 10, 12, 11 };

int main()
{
  using namespace mln;

  /*--------.
  | Graph.  |
  `--------*/

  /* The graph and its corresponding line graph are as follows:

            0 1 2 3 4               0 1 2 3 4
         .-----------	         .-----------
         |		         |
       0 |  0       2	       0 |  *       *
       1 |    \   / |	       1 |    0   1 |
       2 |      1   |	       2 |      *   4
       3 |       \  |	       3 |       2  |
       4 |        3-4	       4 |        *3*

  */

  // Graph.
  util::graph g;

  // Populate the graph with vertices.
  g.add_vertices(5);

  // Populate the graph with edges.
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(1, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 2);

  /// Create the corresponding line graph.
  /// Edges are now considered as vertices.
  util::line_graph<util::graph> lg(g);

  // Points associated to the line graph vertices (edges in the graph).
  typedef util::site_pair<point2d> P;
  typedef fun::i2v::array<P> fsite_t;
  fsite_t sites(5);
  sites(0) = P(point2d(0,0), point2d(2,2)); // Site associated to vertex 0.
  sites(1) = P(point2d(2,2), point2d(0,4)); // Site associated to vertex 1.
  sites(2) = P(point2d(2,2), point2d(4,3)); // Site associated to vertex 2.
  sites(3) = P(point2d(4,3), point2d(4,4)); // Site associated to vertex 3.
  sites(4) = P(point2d(0,4), point2d(4,4)); // Site associated to vertex 4.

  /*-------------------.
  | Line graph image.  |
  `-------------------*/

  // Line graph values.
  typedef fun::i2v::array<unsigned> viota_t;
  viota_t iota(lg.v_nmax());
  for (unsigned i = 0; i < iota.size(); ++i)
    iota(i) = 10 + i;

  typedef vertex_image< P, unsigned, util::line_graph<util::graph> > ima_t;
  ima_t ima = make::vertex_image(lg, sites, iota);


  /*-------------------------------.
  | Processing line graph images.  |
  `-------------------------------*/

  ima_t::win_t win;
  unsigned i = 0;

  ima_t ima_dil = morpho::dilation(ima, win);
  // Manual iteration over the domain of IMA_DIL.
  mln_piter_(ima_t) p_dil(ima_dil.domain());
  for_all (p_dil)
    mln_assertion(dil_ref[i++] == ima_dil(p_dil));

  ima_t ima_ero = morpho::erosion(ima, win);
  // Manual iteration over the domain of IMA_ERO.
  mln_piter_(ima_t) p_ero(ima_ero.domain());
  i = 0;
  for_all (p_ero)
    mln_assertion(ero_ref[i++] == ima_ero(p_ero));
}
