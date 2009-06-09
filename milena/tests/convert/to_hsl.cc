// Copyright (C) 2009 EPITA Research and Development Laboratory
// (LRDE)
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
/// Tests on mln::convert::from_to_ for hsl<H,S,L>.

#include <mln/core/image/image2d.hh>
#include <mln/value/hsl.hh>
#include <mln/value/rgb8.hh>
#include <mln/convert/to.hh>


int main()
{
  using namespace mln;

//   value::rgb8 c1(3,3,3);
//   value::hsl_f c2 = convert::to<value::hsl_f>(c1);
// //  mln_assertion(c2 == hsl_f(0,0,3)); //FIXME: wrong result.

//   value::hsl_f c3(3,3,3);
//   c1 = convert::to<value::rgb8>(c3);
// //  mln_assertion(c1 == rgb8(2,4,0)); //FIXME: wrong result.

}
