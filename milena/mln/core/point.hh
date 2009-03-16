// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_CORE_POINT_HH
# define MLN_CORE_POINT_HH

/// \file mln/core/point.hh
///
/// Definition of the generic point class mln::point.

# include <mln/core/def/coord.hh>
# include <mln/core/concept/proxy.hh>
# include <mln/core/concept/gpoint.hh>
# include <mln/core/internal/coord_impl.hh>
# include <mln/fun/i2v/all_to.hh>

# include <mln/metal/bool.hh>
# include <mln/metal/is_not.hh>
# include <mln/algebra/vec.hh>
# include <mln/metal/converts_to.hh>
# include <mln/algebra/h_vec.hh>
# include <mln/util/yes.hh>


namespace mln
{

  /// \{ Forward declarations.
  template <typename G, typename C> struct  point;
  template <typename G, typename C> struct dpoint;
  namespace literal {
    struct zero_t;
    struct one_t;
    struct origin_t;
  }
  /// \}


  namespace convert
  {

    namespace over_load
    {

      template <typename G, typename C1, typename C2>
      void from_to_(const point<G,C1>& from, point<G,C2>& to);

    } // end of namespace mln::convert::over_load

  } // end of namespace mln::convert



  /// Generic point class.
  ///
  /// Parameters are \c n the dimension of the space and \c C the
  /// coordinate type in this space.
  template <typename G, typename C>
  struct point : public Gpoint< point<G,C> >,
		 public internal::mutable_coord_impl_< G::dim, C, point<G,C> >
  {
    // FIXME: Temporary hack.
    typedef point site;
    typedef point psite;


    /// \var dim
    /// Dimension of the space.
    /// \invariant dim > 0
    enum { dim = G::dim };

    /// Grid associated type.
    typedef G grid;

    /// Delta associated type.
    typedef dpoint<G,C> delta;

    /// DPsite associated type.
    typedef dpoint<G,C> dpsite;

    /// Coordinate associated type.
    typedef C coord;

    /// Algebra vector (vec) associated type.
    typedef algebra::vec<G::dim, float> vec;

    /// Algebra hexagonal vector (hvec) associated type.
    typedef algebra::h_vec<G::dim, float> h_vec;

    /// Read-only access to the \p i-th coordinate value.
    /// \param[in] i The coordinate index.
    /// \pre \p i < \c dim
    const C& operator[](unsigned i) const;

    /// Read-write access to the \p i-th coordinate value.
    /// \param[in] i The coordinate index.
    /// \pre \p i < \c dim
    C& operator[](unsigned i);


    /// Read-only access to the last coordinate.
    const C& last_coord() const;

    /// Read-write access to the last coordinate.
    C& last_coord();


    /// Constructor without argument.
    point();

    /// Constructor from an algebra vector.
    template <typename C2>
    point(const algebra::vec<dim,C2>& v);

    /// \{ Constructors with different numbers of arguments
    /// (coordinates) w.r.t. the dimension.
    explicit point(C ind);
    point(C row, C col);
    point(C sli, C row, C col);
    /// \}

    /// \{ Constructors/assignments with literals.
    point(const literal::origin_t&);
    point<G,C>& operator=(const literal::origin_t&);
    // Works only in 1D:
    point(const literal::zero_t&);
    point<G,C>& operator=(const literal::zero_t&);
    point(const literal::one_t&);
    point<G,C>& operator=(const literal::one_t&);
    /// \}

    /// Constructor; coordinates are set by function \p f.
    template <typename F>
    point(const Function_i2v<F>& f);

    /// Set all coordinates to the value \p c.
    void set_all(C c);

    /// Origin point (all coordinates are 0).
    static const point<G,C> origin;

    /// Shifting by \p dp.
    point<G,C>& operator+=(const delta& dp);

    /// Shifting by \p the inverse of dp.
    point<G,C>& operator-=(const delta& dp);

  /* FIXME: Seems highly non-generic!
     This (non documented change, even in ChangeLog) change was
     introduce by revision 1224, see
     https://trac.lrde.org/olena/changeset/1224#file2
     https://www.lrde.epita.fr/pipermail/olena-patches/2007-October/001592.html
  */
    operator algebra::vec<G::dim, float> () const;

    /// Explicit conversion towards mln::algebra::vec.
    vec to_vec() const;

    /// Transform to point in homogene coordinate system.
    h_vec to_h_vec() const;

    /// Point with all coordinates set to the maximum value.
    static const point<G,C>& plus_infty();

    /// Point with all coordinates set to the mininum value.
    static const point<G,C>& minus_infty();

  protected:
    algebra::vec<G::dim, C> coord_;
  };

  namespace internal
  {

    /// subject_impl specialization (Proxy)
    /// \{

    template <typename P, typename E>
    struct subject_point_impl;

    template <typename G, typename C, typename E>
    struct subject_point_impl< point<G,C>, E >
    {
      typename point<G,C>::vec to_vec() const;
      operator algebra::vec<G::dim, float>() const;

    private:
      const E& exact_() const;
    };

    /// \}

  } // end of namespace mln::internal


  /// FIXME...
  template <typename G, typename C>
  const algebra::vec<point<G,C>::dim - 1, C>& cut_(const point<G,C>& p);

  template <typename C>
  const util::yes& cut_(const point<grid::tick,C>& p);


# ifndef MLN_INCLUDE_ONLY

  namespace convert
  {

    namespace over_load
    {

      template <typename G, typename C1, typename C2>
      inline
      void
      from_to_(const point<G,C1>& from, point<G,C2>& to)
      {
	mlc_converts_to(C1,C2)::check();
	to = point<G,C2>(from.to_vec());
      }

    } // end of namespace mln::convert::over_load

  } // end of namespace mln::convert


  template <typename G, typename C>
  inline
  const C& point<G,C>::operator[](unsigned i) const
  {
    assert(i < dim);
    return this->coord_[i];
  }

  template <typename G, typename C>
  inline
  C& point<G,C>::operator[](unsigned i)
  {
    assert(i < dim);
    return this->coord_[i];
  }

  template <typename G, typename C>
  inline
  const C&
  point<G,C>::last_coord() const
  {
    return this->coord_[dim - 1];
  }

  template <typename G, typename C>
  inline
  C&
  point<G,C>::last_coord()
  {
    return this->coord_[dim - 1];
  }


  // Constructors.

  template <typename G, typename C>
  inline
  point<G,C>::point()
  {
  }

  template <typename G, typename C>
  template <typename C2>
  inline
  point<G,C>::point(const algebra::vec<dim,C2>& v)
  {
    unsigned j = 0;
    //FIXME: to be improved.
    if (dim < 3)
      coord_ = v;
    else
    {
      for (unsigned i = dim - 2; i < dim; ++i)
	coord_[i] = v[j++];
      for (unsigned i = 2; i < dim; ++i, ++j)
	coord_[i-j] = v[j];
    }
  }

  template <typename G, typename C>
  inline
  point<G,C>::point(C ind)
  {
    metal::bool_<(dim == 1)>::check();
    coord_[0] = ind;
  }

  template <typename G, typename C>
  inline
  point<G,C>::point(C row, C col)
  {
    metal::bool_<(dim == 2)>::check();
    coord_[0] = row;
    coord_[1] = col;
  }

  template <typename G, typename C>
  inline
  point<G,C>::point(C sli, C row, C col)
  {
    metal::bool_<(dim == 3)>::check();
    coord_[0] = sli;
    coord_[1] = row;
    coord_[2] = col;
  }

  template <typename G, typename C>
  template <typename F>
  inline
  point<G,C>::point(const Function_i2v<F>& f_)
  {
    mlc_converts_to(mln_result(F), C)::check();
    const F& f = exact(f_);
    for (unsigned i = 0; i < dim; ++i)
      coord_[i] = static_cast<C>( f(i) );
  }

  template <typename G, typename C>
  inline
  point<G,C>::point(const literal::origin_t&)
  {
    coord_.set_all(0);
  }

  template <typename G, typename C>
  inline
  point<G,C>&
  point<G,C>::operator=(const literal::origin_t&)
  {
    coord_.set_all(0);
    return *this;
  }

  template <typename G, typename C>
  inline
  point<G,C>::point(const literal::zero_t&)
  {
    metal::bool_<(dim == 1)>::check();
    coord_[0] = 1;
  }

  template <typename G, typename C>
  inline
  point<G,C>&
  point<G,C>::operator=(const literal::zero_t&)
  {
    metal::bool_<(dim == 1)>::check();
    coord_[0] = 1;
    return *this;
  }

  template <typename G, typename C>
  inline
  point<G,C>::point(const literal::one_t&)
  {
    metal::bool_<(dim == 1)>::check();
    coord_[0] = 1;
  }

  template <typename G, typename C>
  inline
  point<G,C>&
  point<G,C>::operator=(const literal::one_t&)
  {
    metal::bool_<(dim == 1)>::check();
    coord_[0] = 1;
    return *this;
  }

  template <typename G, typename C>
  inline
  void point<G,C>::set_all(C c)
  {
    coord_.set_all(c);
  }

  template <typename G, typename C>
  const point<G,C> point<G,C>::origin = all_to(0);

  template <typename G, typename C>
  inline
  point<G,C>&
  point<G,C>::operator+=(const delta& dp)
  {
    for (unsigned i = 0; i < dim; ++i)
      coord_[i] = static_cast<C>(coord_[i] + dp[i]);
    return *this;
  }

  template <typename G, typename C>
  inline
  point<G,C>&
  point<G,C>::operator-=(const delta& dp)
  {
    for (unsigned i = 0; i < dim; ++i)
      coord_[i] -= dp[i];
    return *this;
  }

  template <typename G, typename C>
  inline
  point<G,C>::operator algebra::vec<G::dim, float> () const
  {
    return to_vec();
  }

  template <typename G, typename C>
  inline
  typename point<G,C>::vec
  point<G,C>::to_vec() const
  {
    //FIXME: to be improved.
    if (dim > 2)
    {
      algebra::vec<G::dim, float> tmp;
      unsigned j = 0;
      for (unsigned i = dim - 2; i < dim; ++i)
	tmp[j++] = coord_[i];
      for (unsigned i = 2; i < dim; ++i, ++j)
	tmp[j] = coord_[i-j];

      return tmp;
    }

    return coord_;
  }

  template <typename G, typename C>
  inline
  typename point<G,C>::h_vec
  point<G,C>::to_h_vec() const
  {
    algebra::h_vec<G::dim, float> tmp;

    //FIXME: to be improved.
    if (dim == 1)
      tmp[0] = coord_[0];
    else
    {
      unsigned j = 0;
      for (unsigned i = dim - 2; i < dim; ++i)
	tmp[j++] = coord_[i];

      for (unsigned i = 2; i < dim; ++i, ++j)
	tmp[j] = coord_[i-j];

      tmp[G::dim] = 1;
    }

    return tmp;
  }


  template <typename G, typename C>
  inline
  const point<G,C>&
  point<G,C>::plus_infty()
  {
    static const point<G,C> the_(all_to(mln_max(C)));
    return the_;
  }

  template <typename G, typename C>
  inline
  const point<G,C>&
  point<G,C>::minus_infty()
  {
    static const point<G,C> the_(all_to(mln_min(C)));
    return the_;
  }

  namespace internal
  {

    template <typename G, typename C, typename E>
    inline
    const E&
    subject_point_impl< point<G,C>, E >::exact_() const
    {
      return internal::force_exact<const E>(*this);
    }

    template <typename G, typename C, typename E>
    inline
    typename point<G,C>::vec
    subject_point_impl< point<G,C>, E >::to_vec() const
    {
      return exact_().get_subject().to_vec();
    }

    template <typename G, typename C, typename E>
    inline
    subject_point_impl< point<G,C>, E >::operator algebra::vec<G::dim, float>() const
    {
      return exact_().get_subject();
    }

  } // end of namespace mln::internal

  template <typename G, typename C>
  inline
  algebra::vec<point<G,C>::dim - 1, C>
  cut_(const point<G,C>& p)
  {
    return *(algebra::vec<point<G,C>::dim - 1, C>*)(& p.to_vec());
  }

  template <typename C>
  inline
  const util::yes&
  cut_(const point<grid::tick,C>& p)
  {
    util::yes* the_;
    return *the_;
  }

# endif // ! MLN_INCLUDE_ONLY


} // end of namespace mln


#endif // ! MLN_CORE_POINT_HH
