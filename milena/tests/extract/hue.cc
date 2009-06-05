// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

# include <mln/core/image/image2d.hh>
# include <mln/extract/hue.hh>
# include <mln/value/hsl.hh>
# include <mln/core/var.hh>

int main()
{
  using namespace mln;
  using value::hsl_f;

  typedef image2d<hsl_f> I;
  I ima(2,2);
  point2d p(1,1);
  ima(p) = value::hsl_f(200, 230, 240);

  fun_image< meta::hue<hsl_f>, I > ima_hue = extract::hue(ima);

  mln_assertion(ima(p).hue() == ima_hue(p));

  ima_hue(p) = 0;

  mln_assertion(ima_hue(p) == 0u);
}

