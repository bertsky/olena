#! /bin/sh

# Copyright (C) 2007, 2009 EPITA Research and Development Laboratory
# (LRDE)
#
# This file is part of Olena.
#
# Olena is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation, version 2 of the License.
#
# Olena is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Olena.  If not, see <http://www.gnu.org/licenses/>.

## FIXME: Don't use `echo -n', as echo's options are not portable.
##
## http://www.gnu.org/software/autoconf/manual/html_node/Limitations-of-Builtins.html#Limitations-of-Builtins
##
## As an ugly workaround, use `printf' instead.  The right approach
## would be to only emit lines ended with newlines.
ECHO_N=printf

# Use the C locale to have a deterministic sort.
export LC_ALL=C

test $# -eq 3 || { echo "Usage: $0 <scanned dir> <output_dir> <disabled_tests>" && exit 1; }

scanned_dir=$1
output_dir=$2
disabled_tests=$3

## FIXME: We do not include these directories
##
##   mln/io/dicom
##   mln/io/fits
##   mln/io/magick
##   mln/io/tiff
##
## because they contain files depending on optional (external)
## libraries.  We should test them conditionally.
HEADERS=$(find $scanned_dir -type f -name "*.hh" \
  | sort \
  | sed -e 's/.*\/mln\/\(.*\)/mln\/\1/g' | sed 's/\.\.\/\.\.\///g' \
  | comm -23 - "$disabled_tests")

output="$output_dir/unit-tests.mk"

rm -f "$output"
rm -f mln_*.cc

# Build unit-tests.mk.
echo "## Generated by $0, do not modify." >"$output"
echo >>"$output"
$ECHO_N "check_PROGRAMS = " >>"$output"

for i in $HEADERS; do
    FILE_CC=`echo $i | sed 's/[/.]/_/g' | sed 's/_hh/\.cc/g'`

    # Build .cc.
    cat > $output_dir/$FILE_CC << EOF
// Unit test for $i.
// Generated by $0, do not modify.

// Include the file twice, so we detect missing inclusion guards.
#include <$i>
#include <$i>

int main()
{
  // Nothing.
}
EOF

    # Build unit-tests.mk.
    TARGET=`echo "${FILE_CC}" | sed 's/\.cc//'`
    echo " \\" >>"$output"
    $ECHO_N "${TARGET}" >>"$output"
done

# Build "$output".
echo "" >>"$output"
echo "" >>"$output"
for i in $HEADERS; do
    FILE_CC=`echo $i | sed 's/[/.]/_/g' | sed 's/_hh/\.cc/g'`
    NAME=`echo $FILE_CC | sed 's/\.cc//g'`
    echo "${NAME}_SOURCES = $FILE_CC" >>"$output"
done