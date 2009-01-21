// Copyright (C) 2007, 2008, 2009 EPITA Research and Development Laboratory (LRDE)
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


#include <mln/core/image/image2d.hh>

#include <mln/win/rectangle2d.hh>

#include <mln/io/pgm/load.hh>
#include <mln/io/pbm/save.hh>

#include <mln/value/int_u8.hh>
#include <mln/value/int_u16.hh>

# include <mln/core/alias/window2d.hh>

#include <mln/level/transform.hh>
#include <mln/binarization/threshold.hh>
#include <mln/estim/mean.hh>
#include <mln/morpho/hit_or_miss.hh>
#include <mln/morpho/dilation.hh>
#include <mln/morpho/opening.hh>

#include <mln/win/all.hh>

int main(int argc, const char * argv[])
{
  using namespace mln;
  using namespace value;

  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " in.pgm [other_files.pgm]" << std::endl;
    return 1;
  }

  for (int i = 1; i < argc; ++i)
    {
      typedef int_u8 int_t;

      border::thickness = 21;

      image2d<int_t> ima;
      io::pgm::load(ima, argv[i]);

      // Compute the mean
      int_t mean = estim::mean(ima);

      image2d<bool> imab = binarization::threshold(ima, mean-10);

      io::pbm::save(imab, "hop.pbm");
    
      window2d out = win::disk2d(25) - win::disk2d(22);
      win::disk2d in(4);


      std::string name(argv[i]);
      name.erase(name.length() - 4);
      io::pbm::save(morpho::hit_or_miss(imab, in, out), name.append("_hom.pbm"));
    }
}
