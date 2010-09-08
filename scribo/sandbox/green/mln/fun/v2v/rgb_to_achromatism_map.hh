// Copyright (C) 2007 EPITA Research and Development Laboratory (LRDE)
// Copyright (C) 2008 EPITA Research and Development Laboratory (LRDE)
// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

#ifndef  MLN_FUN_V2V_RGB_TO_ACHROMATISM_MAP_HH
# define MLN_FUN_V2V_RGB_TO_ACHROMATISM_MAP_HH

# include <mln/math/abs.hh>
# include <mln/math/max.hh>

# include <mln/value/rgb.hh>


/// \file
///
/// \brief Convert rgb value to achromatism map.

namespace mln
{

  namespace fun
  {

    namespace v2v
    {

      /// \brief Convert rgb value to achromatism map.
      ///
      /// Convert rgb value to binary achromastism map using the
      /// rebuilded Millet phd formulae [millet.phd.2008.pdf]. The
      /// idea is to look at the minimum and maximum of the channels
      /// and to return the difference.
      ///
      /// \ingroup modfunv2v

      template <unsigned n>
      struct rgb_to_achromatism_map :
	Function_v2v< rgb_to_achromatism_map<n> >
      {
	typedef value::rgb<n>   argument;
	typedef value::int_u<n> result;

	result operator()(const argument& v) const
	{
	  result max = math::max(math::max(v.red(),v.green()),v.blue());
	  result min = math::min(math::min(v.red(),v.green()),v.blue());
	  result ret = max - min;

	  return ret;
	}
      };

    } // end of namespace mln::fun::v2v

  } // end of namespace mln::fun

} // end of namespace mln

#endif // ! MLN_FUN_V2V_RGB_TO_ACHROMATISM_MAP_HH
