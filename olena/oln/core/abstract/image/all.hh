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

#ifndef OLN_CORE_ABSTRACT_IMAGE_ALL_HH
# define OLN_CORE_ABSTRACT_IMAGE_ALL_HH

# include <oln/core/abstract/image.hh>

# include <oln/core/abstract/image/hierarchies.hh>

// Hierarchy 1: image w.r.t. dimension.
# include <oln/core/abstract/image/dimension/hierarchy.hh>
// Hierarchy 2: image w.r.t. type of data.
# include <oln/core/abstract/image/type/hierarchy.hh>
// Hierarchy 3: image w.r.t. neighborhood.
# include <oln/core/abstract/image/neighborhood/hierarchy.hh>
// Hierarchy 4: image w.r.t. bounding box.
# include <oln/core/abstract/image/bbox/hierarchy.hh>
// Hierarchy 5: image w.r.t. point point-wise accessibility.
# include <oln/core/abstract/image/point_wise_accessibility/hierarchy.hh>
// Hierarchy 6: image w.r.t. data mutability.
# include <oln/core/abstract/image/mutability/hierarchy.hh>
// Hierarchy 7: image w.r.t. computability.
# include <oln/core/abstract/image/computability/hierarchy.hh>
// Hierarchy 8: image w.r.t. value-wise accessibility.
# include <oln/core/abstract/image/value_wise_accessibility/hierarchy.hh>

// (Hybrid) hierarchy 9: image w.r.t. classical features.
# include <oln/core/abstract/image/hybrid/classical.hh>

#endif // ! OLN_CORE_ABSTRACT_IMAGE_ALL_HH
