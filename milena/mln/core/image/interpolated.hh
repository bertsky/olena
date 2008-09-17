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

#ifndef MLN_CORE_IMAGE_INTERPOLATED_HH
# define MLN_CORE_IMAGE_INTERPOLATED_HH

/*! \file mln/core/image/interpolated.hh
 *
 * \brief Definition of a morpher that makes an image become readable
 * with floating coordinates.
 */

# include <cmath>

# include <mln/core/internal/image_identity.hh>
# include <mln/algebra/vec.hh>
# include <mln/value/set.hh>

namespace mln
{

  // Fwd decl.
  template <typename I> struct interpolated;

  namespace internal
  {

    /// Data structure for \c mln::interpolated<I>.
    template <typename I>
    struct data< interpolated<I> >
    {
      data(I& ima);

      I ima_;
    };

  } // end of namespace mln::internal

  /*! \brief Morpher that makes underlaying image being accessed with floating coordinate.
   *
   */
  template <typename I>
  struct interpolated :
    public mln::internal::image_identity< I, mln_pset(I), interpolated<I> >
  {

    typedef mln::internal::image_identity< I, mln_pset(I),
					   interpolated<I> > super_;

    /// Point_Site associated type.
    typedef mln_psite(I) psite;

    /// Value associated type.
    typedef mln_value(I) value;

    /// Return type of read-write access.
    typedef mln_lvalue(I) lvalue; // FIXME: Depends on lvalue presence in I.

    /// Return type of read-only access.
    typedef mln_rvalue(I) rvalue;

    /// Skeleton.
    typedef interpolated< tag::image_<I> > skeleton;


    /// Constructors.
    interpolated(I& ima);
    interpolated();

    /// Initialize an empty image.
    void init_(I& ima);


    /// Test if this image has been initialized.
    bool has_data() const;

    /// Test if a pixel value is accessible at \p p.
    using super_::has;

    /// Test if a pixel value is accessible at \p v.
    bool has(const mln::algebra::vec<I::point::dim, float>& v) const;

    /// Read-only access of pixel value at point site \p p.
    /// Mutable access is only OK for reading (not writing).
    using super_::operator();

    mln_value(I) operator()(const mln::algebra::vec<I::point::dim, float>& v) const;


  };



# ifndef MLN_INCLUDE_ONLY

  namespace internal
  {

    // internal::data< interpolated<I,S> >

    template <typename I>
    inline
    data< interpolated<I> >::data(I& ima)
      : ima_(ima)
    {
    }

  } // end of namespace mln::internal

  template <typename I>
  inline
  interpolated<I>::interpolated(I& ima)
  {
    mln_precondition(ima.has_data());
    init_(ima);
  }

  template <typename I>
  inline
  interpolated<I>::interpolated()
  {
  }

  template <typename I>
  inline
  void
  interpolated<I>::init_(I& ima)
  {
    mln_precondition(ima.has_data());
    this->data_ = new internal::data< interpolated<I> >(ima);
  }

  template <typename I>
  inline
  bool interpolated<I>::has_data() const
  {
    mln_invariant(this->data_->ima_.has_data());
    return true;
  }

  template <typename I>
  inline
  bool interpolated<I>::has(const mln::algebra::vec<I::point::dim, float>& v) const
  {
    mln_psite(I) p;
    for (unsigned i = 0; i < I::point::dim; ++i)
      p[i] = static_cast<int>(round(v[i]));
    return this->data_->ima_.has(p);
  }

  template <typename I>
  inline
  mln_value(I)
  interpolated<I>::operator()(const mln::algebra::vec<I::point::dim, float>& v) const
  {
    mln_psite(I) p;
    for (unsigned i = 0; i < I::point::dim; ++i)
      p[i] = static_cast<int>(round(v[i]));
    mln_assertion(this->data_->ima_.has(p));
    return this->data_->ima_(p);
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_CORE_IMAGE_INTERPOLATED_HH
