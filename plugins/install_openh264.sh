#!/bin/sh

set -e

if [ `whoami` != root ]; then
   echo "$0 must be run as root!"
   exit 1
fi

case `uname -sm` in
   Linux*x86_64 )
     PLATFORM=linux64
     EXT=so
   ;;
   Linux*x86 )
     PLATFORM=linux32
     EXT=so
   ;;
   Darwin*x86_64 )
     PLATFORM=osx64
     EXT=dylib
   ;;
   Darwin*x86 )
     PLATFORM=osx32
     EXT=dylib
   ;;
   * )
     echo Unknown platform `uname -sm`
     exit 2
   ;;
esac

LIBBASE=libopenh264
LIBFILE=${LIBBASE}-2.1.0-${PLATFORM}.5.$EXT
LIBDIR=${1-/usr/local/lib}

if [ \! -d $LIBDIR ]; then
   mkdir -p $LIBDIR
fi

cd $LIBDIR
rm -f ${LIBBASE}*
curl http://ciscobinary.openh264.org/$LIBFILE.bz2 | bunzip2 > $LIBFILE
ln -s $LIBFILE ${LIBBASE}.$EXT
ls -l $LIBDIR/${LIBBASE}*

