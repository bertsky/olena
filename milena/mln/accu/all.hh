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

#ifndef MLN_ACCU_ALL_HH
# define MLN_ACCU_ALL_HH

/*! \file mln/accu/all.hh
 *
 * \brief File that includes all accumulator types.
 *
 * \todo Update accumulators s.a. count so that they are like min_/min.
 *
 * \todo Propagate those updates to mln/estim/.
 */


namespace mln
{

  /// Namespace of accumulators.
  namespace accu
  {
    /// Implementation namespace of accumulator namespace.
    namespace impl {}
    /// Internal namespace of accumulators.
    namespace internal {}
  }

}


# include <mln/accu/bbox.hh>
# include <mln/accu/count.hh>
# include <mln/accu/histo.hh>
# include <mln/accu/max.hh>
# include <mln/accu/mean.hh>
# include <mln/accu/median_h.hh>
# include <mln/accu/min.hh>
# include <mln/accu/min_h.hh>
# include <mln/accu/min_max.hh>
# include <mln/accu/nil.hh>
# include <mln/accu/pair.hh>
# include <mln/accu/sum.hh>


#endif // ! MLN_ACCU_ALL_HH
