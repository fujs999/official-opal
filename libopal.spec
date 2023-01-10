%global version_major  3
%global version_minor  19
%global version_patch  7
%global version_oem    6

%global ffmpeg_version 4.4.3
%global opus_version   1.3.1
# Note: at release, ptlib_version should be set to a full version, e.g. 2.19.4.18-2.73%{?dist}
%global ptlib_version  2.19.4.19-2.3%{?dist}


# Branch ID should be 0 for local builds/PRs
# Jenkins builds should use 1 for develop, 2 for master (release builds)
%{!?branch_id:     %global branch_id     0}
%{!?version_stage: %global version_stage AlphaCode}

# Disable the separate debug package and automatic stripping, as detailed here:
# http://fedoraproject.org/wiki/How_to_create_an_RPM_package
%global _enable_debug_package 0
%global debug_package %{nil}
%global __os_install_post /usr/lib/rpm/brp-compress %{nil}

# Fudge the auto-requires script to avoid a dependency on OpenH264
# See https://fedoraproject.org/wiki/PackagingDrafts/FilteringAutomaticDependencies
%define _use_internal_dependency_generator 0
%define __find_requires %{SOURCE1}


Name:           collab-libopal
Version:        %{version_major}.%{version_minor}.%{version_patch}.%{version_oem}
Release:        %{branch_id}%{?jenkins_release}%{?dist}
Summary:        OpalVOIP library

Group:          System Environment/Libraries
License:        MPL 1.0
URL:            http://www.opalvoip.org/
Source0:        source.tgz
Source1:        filter-requires.sh

BuildRequires:  collab-ffmpeg-devel = %{ffmpeg_version}
BuildRequires:  collab-ptlib-devel = %{ptlib_version}
BuildRequires:  libsrtp2-devel
%if 0%{?el7}
# needs a version hint to ensure it picks up our own build
BuildRequires:  opus-devel = %{opus_version}
%else
BuildRequires:  opus-devel
%endif

BuildRequires:  which
BuildRequires:  speex-devel
BuildRequires:  libtheora-devel
BuildRequires:  libvpx-devel

# Since auto-requires is disabled, we have to explicitly list runtime requirements
Requires:       collab-ffmpeg = %{ffmpeg_version}
Requires:       collab-ptlib = %{ptlib_version}
Requires:       libsrtp2
%if 0%{?el7}
Requires:       opus = %{opus_version}
%else
Requires:       opus
%endif

Requires:       speex
Requires:       libtheora
Requires:       libvpx

%description
OpalVOIP library

%package        devel
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       collab-ffmpeg-devel = %{ffmpeg_version}
Requires:       collab-ptlib-devel = %{ptlib_version}
Requires:       libsrtp2-devel
%if 0%{?el7}
Requires:       opus-devel = %{opus_version}
%else
Requires:       opus-devel
%endif

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%package        static
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       %{name}-devel = %{version}-%{release}

%description    static
The %{name}-static package contains static libraries for
developing applications that use %{name}.


%prep
%setup -q -c -n opal


%build
%if 0%{?el7}
source /opt/rh/devtoolset-9/enable
%endif
sed -i \
    -e "s/MAJOR_VERSION.*/MAJOR_VERSION %{version_major}/" \
    -e "s/MINOR_VERSION.*/MINOR_VERSION %{version_minor}/" \
    -e "s/BUILD_TYPE.*/BUILD_TYPE %{version_stage}/"       \
    -e "s/PATCH_VERSION.*/PATCH_VERSION %{version_patch}/" \
    -e "s/OEM_VERSION.*/OEM_VERSION %{version_oem}/"       \
    version.h
%configure \
%ifarch aarch64
    --enable-graviton2 \
    --disable-x264 \
%endif
%if 0%{?_with_tsan:1}
    --enable-sanitize-thread \
%endif
%if 0%{?_with_asan:1}
    --enable-sanitize-address \
%endif
    --enable-cpp14 \
    --enable-localspeexdsp \
    --disable-h323 \
    --disable-iax2 \
    --disable-skinny \
    --disable-lid \
    --disable-t38 \
    --disable-bfcp \
    --disable-sipim \
    --disable-script \
    --disable-mixer \
    --disable-presence \
    --disable-g.722.1 \
    --disable-g.722.2 \
    --disable-isac \
    --disable-iLBC \
    --disable-silk
%make_build all


%install
%if 0%{?el7}
source /opt/rh/devtoolset-9/enable
%endif
rm -rf $RPM_BUILD_ROOT
%make_install
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%clean
rm -rf $RPM_BUILD_ROOT


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%{_libdir}/*.so.*
%{_libdir}/opal-%{version_major}.%{version_minor}.%{version_patch}-%{version_oem}
%{_datadir}/opal
%{_bindir}/conopal

%files devel
%defattr(-,root,root,-)
%{_includedir}/opal
%{_libdir}/*.so
%{_libdir}/pkgconfig/*.pc
%{_datadir}/opal

%files static
%defattr(-,root,root,-)
%{_libdir}/*.a


%changelog
* Fri Dec 02 2016 Gavin Llewellyn <gavin.llewellyn@blackboard.com> - 3.17.1-1
- Initial RPM release
