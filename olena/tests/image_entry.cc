// Copyright (C) 2006 EPITA Research and Development Laboratory
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
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301 USA
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

/// Test oln::abstract::image_entry.

#include <oln/core/abstract/image_entry.hh>
#include <oln/core/abstract/image_dimension.hh>

namespace my
{
  // Fwd decl.
  class image;
}

namespace oln
{
  // Warning, this sugar might be removed in the future.
  stc_set_super(my::image, abstract::image_entry<my::image>);

  /// Virtual types associated to my::A.
  template<>
  struct vtypes<category::image, my::image>
  {
    // FIXME: Don't use the abstraction as a property, but the
    // corresponding grid instead.  The switch for image_dimension
    // (above image_entry) should plug the inheritance relationship to
    // the right image_dimension class using the sole grid information
    // (the grid can be seen here as a ``tag'').
    typedef stc::is_a<abstract::image1d> image_dimension_type;
  };
}

namespace my
{
  // A very simple 1D image.
  class image : public oln::set_super_type<image>::ret
  {
    typedef image self_type;
    typedef oln_type_of_(self_type, image_dimension) image_dimension_type;
  };
}

int
main()
{
  // Instantiate it, and check its dimension.
  my::image i;
  mlc::assert_< mlc_is_a_(my::image::image, oln::abstract::image1d) >::check();
}
