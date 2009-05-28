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

#ifndef SCRIBO_TEXT_GROUPING_INTERNAL_FIND_LEFT_LINK_HH
# define SCRIBO_TEXT_GROUPING_INTERNAL_FIND_LEFT_LINK_HH

/// \file scribo/text/grouping/internal/find_left_link.hh
///
/// Find the left neighbor of a line of text if exists.

# include <mln/core/concept/image.hh>

# include <mln/math/abs.hh>

# include <mln/util/array.hh>

# include <scribo/util/text.hh>
# include <scribo/text/grouping/internal/update_link_array.hh>

//FIXME: not generic.
# include <mln/core/alias/dpoint2d.hh>

namespace scribo
{

  namespace text
  {

    namespace grouping
    {

      namespace internal
      {

	/// Find the left neighbor of a line of text if exists.
	///
	/// \param objects An image of objects.
	/// \param left_link The left neighbors.
	/// \param current_comp A text line id.
	/// \param dmax The maximum lookup distance.
	/// \param c The lookup start point.
	template <typename L>
	void
	find_left_link(const object_image(L)& objects,
		       mln::util::array<unsigned>& left_link,
		       unsigned current_comp,
		       int dmax,
		       const mln_site(L)& c);

# ifndef MLN_INCLUDE_ONLY

	template <typename L>
	void
	find_left_link(const object_image(L)& objects,
		       mln::util::array<unsigned>& left_link,
		       unsigned current_comp,
		       int dmax,
		       const mln_site(L)& c)
	{
	  ///FIXME: the following code is not generic...
	  /// First site on the right of the central site
	  mln_site(L) p = c + left;

	  while (objects.domain().has(p) // Not outside image domain
		&& (objects(p) == literal::zero // Is the background
		  || objects(p) == current_comp // Is the current component
		  || left_link[objects(p)] == current_comp) // Creates a loop
	      && math::abs(p.col() - c.col()) < dmax) // Not to far
	    --p.col();

	  update_link_array(objects, left_link, p, c, current_comp, dmax);
	}

# endif // MLN_INCLUDE_ONLY

      } // end of namespace scribo::text::grouping::internal

    } // end of namespace scribo::text::grouping

  } // end of namespace scribo::text

} // end of namespace scribo


#endif // ! SCRIBO_TEXT_GROUPING_INTERNAL_FIND_LEFT_LINK_HH
