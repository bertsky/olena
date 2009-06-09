// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
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
/// Test on mln::transform::influence_zone_front.

#include <mln/core/image/image2d.hh>
#include <mln/core/alias/neighb2d.hh>
#include <mln/make/w_window2d_int.hh>
#include <mln/value/int_u8.hh>
#include <mln/debug/println.hh>

#include <mln/transform/influence_zone_front.hh>


int main()
{
  using namespace mln;
  using value::int_u8;

  int_u8 vals[] =
    { 1, 1, 0, 0, 0, 0, 3,
      1, 1, 1, 0, 0, 0, 0, 
      0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 2, 0,
      0, 0, 0, 0, 2, 2, 0,
      0, 0, 0, 0, 0, 0, 0 };
  image2d<int_u8> input = make::image2d(vals);

  int ws[] = { 0, 9, 0, 9, 0,
	       9, 6, 4, 6, 9,
	       0, 4, 0, 4, 0,
	       9, 6, 4, 6, 9,
	       0, 9, 0, 9, 0 };

  image2d<int_u8> output;
  output = transform::influence_zone_front(input,
					   c4(), make::w_window2d_int(ws));
  debug::println(output);
}
