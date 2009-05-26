//						       		-*- C++ -*-
// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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
// License.
// reasons why the executable file might be covered by the GNU General
// Public License.

/// \file concat.ixx
/// \brief Macros concatenating their arguments.
///
/// These macros are useful to wrap strings containing commas and
/// passed as arguments other macros.  For instance, to pass the
/// argument <tt>Bar<int, float></tt> to a macro
/// <tt>instantiate_foo</tt> taking a single argument, use this:
///
/// \code
/// instantiate_foo(concat2(Bar<int, float>))
/// \endcode

#define concat2(A, B) A, B
#define concat3(A, B, C) A, B, C
#define concat4(A, B, C, D) A, B, C, D