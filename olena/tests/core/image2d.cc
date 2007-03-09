// Copyright (C) 2006, 2007 EPITA Research and Development Laboratory
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

/// Test oln::image2d.

#include <cassert>
// FIXME: We should not include oln/basics2d.hh, but
// oln/core/2d/image2d.hh (and oln/core/2d/neigh2d.hh ?).
#include <oln/core/2d/image2d.hh>
#include <oln/level/fill.hh>

int
main()
{
  // Fill a 2D image using its iterator.
  oln::image2d<char> ima1(3, 3);
  oln::image2d<char>::piter p1(ima1.points());
  for_all(p1)
    ima1(p1) = 1;

  // Fill a 2D image using a classic loop.
  oln::image2d<int> ima2(ima1.points());
  for (unsigned i = 0; i < 3; ++i)
    for (unsigned j = 0; j < 3; ++j)
      ima2.at(i, j) = 2;

  // Fill a 2D image using the routine oln::level::fill.
  oln::image2d<long> ima3(ima1.points());
  oln::level::fill(ima3, 3);


  // Add the three images.
  oln::image2d<long> sum(ima1.points());
  oln::image2d<long>::piter p(sum.points());
  for_all(p)
    sum(p) = ima1(p) + ima2(p) + ima3(p);
  // And check the sum.
  for_all(p)
    assert(sum(p) == 6);
}
