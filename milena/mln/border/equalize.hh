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

#ifndef MLN_BORDER_EQUALIZE_HH
# define MLN_BORDER_EQUALIZE_HH

/*! \file mln/border/equalize.hh
 *
 * \brief Define a function that equalizes the thickness of an image
 * virtual border.
 */

# include <mln/border/resize.hh>


namespace mln
{

  namespace border
  {

    /*! Equalize the virtual (outer) border of images \p ima1 and \p
     *  ima2 so that their size is equal and is at least \p min_thickness.
     *
     * \param[in,out] ima1 The first image whose border is to be equalizeed.
     * \param[in,out] ima2 The second image whose border is to be equalizeed.
     * \param[in] min_thickness The expected border minimum thickness of both images.
     *
     * \pre \p ima has to be initialized.
     *
     * \warning If both image borders already have the same thickness
     * and if this thickness is larger than \p min_thickness, this
     * routine is a no-op.
     */
    template <typename I, typename J>
    void equalize(const Image<I>& ima1, const Image<J>& ima2,
		  unsigned min_thickness);



# ifndef MLN_INCLUDE_ONLY

    template <typename I, typename J>
    void equalize(const Image<I>& ima1_, const Image<J>& ima2_,
		  unsigned min_thickness)
    {
      trace::entering("border::equalize");
      mlc_is(mln_trait_image_border(I), trait::image::border::some)::check();
      mlc_is(mln_trait_image_border(J), trait::image::border::some)::check();
      const I& ima1 = exact(ima1_);
      const J& ima2 = exact(ima2_);
      mln_precondition(ima1.has_data() && ima2.has_data());

      unsigned b1 = border::get(ima1), b2 = border::get(ima2);
      if (! (b1 == b2 && b2 >= min_thickness))
	// Something has to be done.
	{
	  if (b1 < min_thickness && b2 < min_thickness)
	    // Both images have to be border-resized.
	    {
	      border::resize(ima1, min_thickness);
	      border::resize(ima2, min_thickness);
	    }
	  else
	    // A single image has to be border-resized with
	    // the other image thickness.
	    if (b1 < min_thickness)
	      {
		mln_assertion(b2 >= min_thickness);
		border::resize(ima1, b2);
	      }
	    else
	      {
		mln_assertion(b2 < min_thickness);
		mln_assertion(b1 >= min_thickness);
		border::resize(ima2, b1);
	      }
	}

      mln_postcondition(border::get(ima1) == border::get(ima2) &&
			border::get(ima1) >= min_thickness &&
			border::get(ima2) >= min_thickness);
      trace::exiting("border::equalize");
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::border

} // end of namespace mln


#endif // ! MLN_BORDER_EQUALIZE_HH
