// Copyright (C) 2007 EPITA Research and Development Laboratory
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

/*! \file
 *
 * \brief Tests on mln::border::resize.
 */


#include <mln/core/image/image1d.hh>
#include <mln/debug/iota.hh>
#include <mln/value/int_u8.hh>
#include <mln/border/resize.hh>
#include <mln/debug/println_with_border.hh>
#include <mln/border/fill.hh>

using namespace mln;

int
main (void)
{
  unsigned border = 3;
  unsigned new_border = 6;

  std::cout << std::endl
	    << "Test 1d resize"
	    << std::endl
	    << std::endl;
  image1d<int> ima(6, border);
  debug::iota(ima);
  border::fill(ima, 8);


  std::cout << "before resize ("
	    << border
	    << ")"
	    << std::endl;
  debug::println_with_border(ima);
  std::cout << std::endl;


  border::resize (ima, new_border);
  std::cout << "after resize ("
	    << new_border
	    << ")"
	    << std::endl;
  debug::println_with_border(ima);
  std::cout << std::endl;
}
