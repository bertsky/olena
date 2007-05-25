// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 EPITA
// Research and Development Laboratory
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

#ifndef OLN_IO_SAVE_PGM_HH
# define OLN_IO_SAVE_PGM_HH

# include <iostream>
# include <fstream>

# include <oln/core/2d/image2d.hh>


namespace oln
{

  namespace io
  {

    void save_pgm(const image2d<unsigned char>& ima, const std::string& filename)
    {
      std::ofstream file(filename.c_str());
      if (not file)
	{
	  std::cerr << "error: cannot open file '" << filename
		    << "'!";
	  abort();
	}
      file << "P5" << std::endl;
      file << "# olena" << std::endl;
      file << ima.ncols() << ' ' << ima.nrows() << std::endl;
      file << "255" << std::endl;
      int col = ima.min_col();
      size_t len = ima.ncols() * sizeof(unsigned char);
      for (int row = ima.min_row(); row <= ima.max_row(); ++row)
	file.write((char*)(&(ima.at(row, col))), len);
    }

  } // end of namespace oln::io

} // end of namespace oln


#endif // ! OLN_IO_SAVE_PGM_HH
