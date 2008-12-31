// Copyright (C) 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_CORE_IMAGE_INSTANT_HH
# define MLN_CORE_IMAGE_INSTANT_HH

/*! \file mln/core/image/instant.hh
 *
 * \brief Definition of a morpher that prevent an image from sharing
 * his data.
 *
 * \todo Fix FIXME; see todo in image_identity...
 */

# include <mln/core/internal/image_identity.hh>
# include <mln/metal/is_not_const.hh>



namespace mln
{

  // Forward declaration.
  template <typename I> struct instant_;


  namespace trait
  {

    template <typename I>
    struct image_< instant_<I> > : image_< I > // Same as I except...
    {
      // ...this change.
      typedef trait::image::category::identity_morpher category;
    };

  } // end of namespace mln::trait



  namespace internal
  {

    /// Data structure for \c mln::instant_<I>.
    template <typename I>
    struct data< instant_<I> >
    {
      data(const I& ima);
      I ima_;
    };

  } // end of namespace mln::internal





  /*! \brief FIXME
   *
   */
  template <typename I>
  struct instant_

    : public mln::internal::image_identity< I, mln_pset(I), instant_<I> >,
      private mlc_is_not_const(I)::check_t
  {

    /// Skeleton.
    typedef tag::image_<I> skeleton; // Remove the "instant" envelope.

    /// Constructor.
    instant_(I& ima);

    /// Deferred initialization.
    void init_(I& ima);

    /// Remove the "instant" envelope.
    I& un_instant_();
    I& un_instant_() const;
  };



# ifndef MLN_INCLUDE_ONLY

  namespace internal
  {

    // internal::data< instant_<I> >

    template <typename I>
    inline
    data< instant_<I> >::data(const I& ima)
      : ima_(ima)
    {
    }

  } // end of namespace mln::internal


  // instant_<I>

  template <typename I>
  inline
  instant_<I>::instant_(I& ima)
  {
    mln_precondition(ima.is_valid());
    this->init_(ima);
    this->data_ = new internal::data< instant_<I> >(ima);
  }

  template <typename I>
  inline
  void
  instant_<I>::init_(I& ima)
  {
    mln_precondition(ima.is_valid());
    this->data_ = new internal::data< instant_<I> >(ima);
  }

  template <typename I>
  inline
  I&
  instant_<I>::un_instant_()
  {
    mln_precondition(this->is_valid());
    return this->data_->ima_;
  }

  template <typename I>
  inline
  I&
  instant_<I>::un_instant_() const
  {
    mln_precondition(this->is_valid());
    return const_cast<I&>(this->data_->ima_);
  }

# endif // ! MLN_INCLUDE_ONLY

} // end of namespace mln


#endif // ! MLN_CORE_IMAGE_INSTANT_HH
