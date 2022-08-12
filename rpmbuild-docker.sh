#!/bin/sh

set -e

PACKAGENAME=collab-libopal
TARGET_OS=${1:-el7}
CMD=${2:-./rpmbuild.sh}

docker build -f $TARGET_OS.Dockerfile --build-arg SPECFILE=libopal.spec -t $PACKAGENAME-$TARGET_OS-build .
docker run -it --rm --mount type=bind,src=$PWD,dst=/host -w /host $PACKAGENAME-$TARGET_OS-build $CMD
