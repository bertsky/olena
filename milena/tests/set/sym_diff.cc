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

/*! \file tests/set/sym_diff.cc
 *
 * \brief Tests on mln::set::sym_diff.
 */

#include <mln/set/sym_diff.hh>
#include <mln/core/dpoint2d.hh>

int main()
{
  using namespace mln;

  {
    window<dpoint2d> win1;
    win1
      .insert( 2, 7)
      .insert( 2, 1)
      .insert(-4, 0)
      .insert( 0, 0)
      .insert( 1, 1)
      .insert( 6, 5);
    window<dpoint2d> win2;
    win2
      .insert( 2, 7)
      .insert(-2, 1)
      .insert(-4, 0)
      .insert( 1,-1)
      .insert( 6, 5);
    window<dpoint2d> win3 = set::sym_diff(win1, win2);
    mln_assertion(win3.has(dpoint2d( 2, 1)));
    mln_assertion(win3.has(dpoint2d( 0, 0)));
    mln_assertion(win3.has(dpoint2d( 1, 1)));
    mln_assertion(!win3.has(dpoint2d( 2, 7)));
    mln_assertion(win3.has(dpoint2d(-2, 1)));
    mln_assertion(!win3.has(dpoint2d(-4, 0)));
    mln_assertion(win3.has(dpoint2d( 1,-1)));
    mln_assertion(!win3.has(dpoint2d( 6, 5)));
  }

  {
    p_set<point2d> pst1;
    pst1
      .insert(point2d( 2, 7))
      .insert(point2d( 2, 1))
      .insert(point2d(-4, 0))
      .insert(point2d( 0, 0))
      .insert(point2d( 1, 1))
      .insert(point2d( 6, 5));
    p_set<point2d> pst2;
    pst2
      .insert(point2d( 2, 7))
      .insert(point2d(-2, 1))
      .insert(point2d(-4, 0))
      .insert(point2d( 1,-1))
      .insert(point2d( 6, 5));
    p_set<point2d> pst3 = set::sym_diff(pst1, pst2);
    mln_assertion(pst3.has(point2d( 2, 1)));
    mln_assertion(pst3.has(point2d( 0, 0)));
    mln_assertion(pst3.has(point2d( 1, 1)));
    mln_assertion(!pst3.has(point2d( 2, 7)));
    mln_assertion(pst3.has(point2d(-2, 1)));
    mln_assertion(!pst3.has(point2d(-4, 0)));
    mln_assertion(pst3.has(point2d( 1,-1)));
    mln_assertion(!pst3.has(point2d( 6, 5)));
  }
}
