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

#ifndef MLN_CORE_CONCEPT_FUNCTION_HH
# define MLN_CORE_CONCEPT_FUNCTION_HH

/*! \file mln/core/concept/function.hh
 *
 * \brief Definition of several concepts of functions.
 */

# include <mln/core/concept/object.hh>


namespace mln
{


  /*! \brief Base class for implementation of function-objects.
   *
   * The parameter \a E is the exact type.
   */
  template <typename E>
  struct Function : public Object<E>
  {
    /*
      An operator() has to be provided.  Its signature depends
      on the particular function-object one considers.
     */
  protected:
    Function();
  };


  // Value -> Value.

  /// Base class for implementation of function-objects from value to
  /// value.
  template <typename E>
  struct Function_v2v : public Function<E>
  {
  protected:
    Function_v2v();
  };


  // Index -> Value.

  /// Base class for implementation of function-objects from index to
  /// value.
  template <typename E>
  struct Function_i2v : public Function_v2v<E>
  {
  protected:
    Function_i2v();
  };


  // Point -> Value.

  /// Base class for implementation of function-objects from point to
  /// value.
  template <typename E>
  struct Function_p2v : public Function_v2v<E>
  {
  protected:
    Function_p2v();
  };


  // Point -> bool.

  /// Base class for implementation of function-objects from point to
  /// bool.
  template <typename E>
  struct Function_p2b : public Function_p2v<E>
  {
    typedef bool result;
  protected:
    Function_p2b();
  };


  // Point -> Point.

  /// Base class for implementation of function-objects from point to
  /// point.
  template <typename E>
  struct Function_p2p : public Function_p2v<E>
  {
  protected:
    Function_p2p();
  };



# ifndef MLN_INCLUDE_ONLY

  template <typename E>
  Function<E>::Function()
  {
    typedef mln_result(E) result;
  }

  template <typename E>
  Function_v2v<E>::Function_v2v()
  {
  }

  template <typename E>
  Function_i2v<E>::Function_i2v()
  {
  }

  template <typename E>
  Function_p2v<E>::Function_p2v()
  {
  }

  template <typename E>
  Function_p2b<E>::Function_p2b()
  {
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_CORE_CONCEPT_FUNCTION_HH
