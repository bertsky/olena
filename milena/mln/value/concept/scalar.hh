// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
// (LRDE)
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

#ifndef MLN_VALUE_CONCEPT_SCALAR_HH
# define MLN_VALUE_CONCEPT_SCALAR_HH

/// \file
///
/// Define a generic class for scalar values.

# include <mln/core/concept/value.hh>
# include <mln/literal/one.hh>


namespace mln
{

  namespace value
  {

    // Fwd decl.
    template <typename E> struct Scalar;


    // Category flag type.
    template <>
    struct Scalar<void>
    {
      typedef Value<void> super;
    };

    template <typename E>
    struct Scalar : public Value<E>
    {
      typedef Scalar<void> category;
    };

  } // end of namespace mln::value



  /// Pre-incrementation for any scalar type.
  template <typename S>
  S& operator++(value::Scalar<S>& rhs);

  /// Pre-decrementation for any scalar type.
  template <typename S>
  S& operator--(value::Scalar<S>& rhs);


# ifndef MLN_INCLUDE_ONLY

  template <typename S>
  inline
  S& operator++(value::Scalar<S>& rhs)
  {
    mlc_converts_to(literal::one_t, S)::check();
    return exact(rhs) += S(literal::one);
  }

  template <typename S>
  inline
  S& operator--(value::Scalar<S>& rhs)
  {
    mlc_converts_to(literal::one_t, S)::check();
    return exact(rhs) -= S(literal::one);
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_VALUE_CONCEPT_SCALAR_HH
