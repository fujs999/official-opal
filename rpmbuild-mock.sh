#!/bin/sh
# Build script for local testing of RPM build process; not used by Jenkins

set -e

if ! which mock > /dev/null; then
    echo You must install mock first: sudo yum install -y mock
    exit 1
fi

if ! which spectool > /dev/null; then
    echo You must install spectool first: sudo yum install -y rpmdevtools
    exit 1
fi

# Remove any existing output
rm -rf rpmbuild

# Build the source RPM
mkdir -p rpmbuild/SOURCES
tar -czf rpmbuild/SOURCES/zsdk-opal.src.tgz --exclude-vcs --exclude=rpmbuild .
mock --root=mcu-atrpms-epel-6-x86_64.cfg $@ --buildsrpm --spec bbcollab-libopal.spec --sources rpmbuild/SOURCES --resultdir rpmbuild/SRPMS

# Build the final RPMs
mock --root=mcu-atrpms-epel-6-x86_64.cfg $@ --resultdir rpmbuild/RPMS rpmbuild/SRPMS/bbcollab-libopal-*.el6.src.rpm

