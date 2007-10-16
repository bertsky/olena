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

#ifndef MLN_DISPLAY_SHOW_HH
# define MLN_DISPLAY_SHOW_HH

/*! \file mln/display/show.hh
 *
 * \brief Display the temporary image which has just been saved with
 * given viewer (default xv).
 */

# include <mln/trait/image_from_mesh.hh>
# include <mln/core/image_if_value.hh>
# include <mln/core/image2d.hh>
# include <mln/display/save.hh>

# include <map>

namespace mln
{

  namespace display
  {

    template <typename I>
    void
    show(const Image<I>& input_, std::string cmd = "xv");

# ifndef MLN_INCLUDE_ONLY

    namespace impl
    {

      template <typename I>
      void
      show(const Image<I>& input_, std::string cmd)
      {
	const I& input = exact (input_);
	
	std::string s = cmd + " " + map_saved_image_tmp_[(void*)input.id_ ()] + " &";
	system (s.c_str ());
      }

    } // end of namespace mln::display::impl

    /// Facade.
    template <typename I>
    void
    show(const Image<I>& input_, std::string cmd = "xv")
    {
      return impl::show(input_, cmd);
    }

# endif // !MLN_INCLUDE_ONLY
    
  } // end of namespace mln::display
  
} // end of namespace mln


#endif //  ! MLN_DISPLAY_SHOW_HH
