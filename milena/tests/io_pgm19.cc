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

/*! \file tests/pbm_load.cc
 *
 * \brief Test on mln::io::pbm::load.
 */

#include <mln/core/image2d.hh>

#include <mln/value/int_u8.hh>

#include <mln/io/pgm/load.hh>
#include <mln/io/pgm/save.hh>

#include <mln/level/transform.hh>
#include <mln/level/compare.hh>


  using namespace mln;

struct to19bits : mln::Function_v2v<to19bits>
{

  typedef value::int_u<19> result;
  result operator()(value::int_u8 v) const
  {
    result ret(v * 524288);
    return ret;
  }
};

struct to8bits : mln::Function_v2v<to8bits>
{

  typedef value::int_u8 result;
  result operator()(value::int_u<19> v) const
  {
    result ret(v / 524288);
    return ret;
  }
};

int main()
{
  using namespace mln;
  using value::int_u8;
  using value::int_u;
  typedef value::int_u<19> int_u19;

  border::thickness = 52;

  image2d<int_u8>
    lena = io::pgm::load<int_u8>("../img/lena.pgm");
  image2d<int_u19> out(lena.domain());

  level::transform(lena, to19bits(), out);

  io::pgm::save(out, "out19.pgm");

  image2d<int_u19>
    lena2 = io::pgm::load<int_u19>("out19.pgm");
   image2d<int_u8> out2(lena.domain());

   level::transform(lena2, to8bits(), out2);

   io::pgm::save(out2, "out8.pgm");

   assert(out2 == lena);

}
