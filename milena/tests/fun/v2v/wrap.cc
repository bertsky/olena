// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

#include <mln/fun/v2v/wrap.hh>

#include <mln/value/int_u8.hh>
#include <mln/value/label_16.hh>


int main()
{
  using namespace mln;

  fun::v2v::wrap<value::int_u8> f;

  value::label_16
    l0   = 0,
    l1   = 1,
    l255 = 255,
    l256 = 256,
    l510 = 510,
    l511 = 511;

  mln_assertion(f(l0)	== 0u);
  mln_assertion(f(l1)	== 1u);
  mln_assertion(f(l255) == 255u);
  mln_assertion(f(l256) == 1u);
  mln_assertion(f(l510) == 255u);
  mln_assertion(f(l511) == 1u);
}
