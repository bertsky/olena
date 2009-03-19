// Copyright (C) 2009 EPITA Research and Development Laboratory
// (LRDE)
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

#ifndef SCRIBO_TABLE_ERASE_HH
# define SCRIBO_TABLE_ERASE_HH

/// \file scribo/table/erase.hh
///
/// Erase the table lines in an image.

# include <mln/core/concept/image.hh>
# include <mln/core/site_set/box.hh>
# include <mln/core/routine/duplicate.hh>

# include <mln/util/array.hh>
# include <mln/util/couple.hh>

# include <scribo/core/erase_bboxes.hh>

namespace scribo
{

  namespace table
  {

    /// Erase table line bboxes from an image.
    ///
    /// \param[in]  line_bboxes   vertical and horizontal line bounding
    ///				  boxes.
    /// \param[in]  in		  A binary image from which the table line
    ///				  bboxes are extracted.
    ///
    ///
    ///	\return A copy of \p in where the table lines are removed.
    template <typename I>
    mln_concrete(I)
    erase(const Image<I>& in,
	  const util::couple<util::array< box<mln_site(I)> >,
			     util::array< box<mln_site(I)> > >& line_bboxes);



# ifndef MLN_INCLUDE_ONLY


    template <typename I>
    mln_concrete(I)
    erase(const Image<I>& in,
	  const util::couple<util::array< box<mln_site(I)> >,
			     util::array< box<mln_site(I)> > >& line_bboxes)
    {
      trace::entering("scribo::internal::erase_table");
      mlc_equal(mln_value(I),bool)::check();
      mln_precondition(exact(in).is_valid());

      I output = duplicate(in);

      erase_bboxes(output, line_bboxes.first());
      erase_bboxes(output, line_bboxes.second());

      trace::exiting("scribo::internal::erase_table");
      return output;
    }


# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace scribo::table

} // end of namespace scribo

#endif // ! SCRIBO_TABLE_ERASE_HH