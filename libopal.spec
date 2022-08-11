%global version_major  3
%global version_minor  19
%global version_patch  7
%global version_oem    5

# Branch ID should be 0 for local builds/PRs
# Jenkins builds should use 1 for develop, 2 for master (release builds)
%{!?branch_id:     %global branch_id     0}
%{!?version_stage: %global version_stage AlphaCode}

%global ffmpeg_version       4.3.1
%global ffmpeg_build         72
%global srtp_version         2.1.0
%global srtp_build           34
%global opus_version         1.3.1
%global opus_build           11
%global ptlib_version        2.19.4.18
%global ptlib_build          69

%global ffmpeg_full_version  %{ffmpeg_version}-2.%{ffmpeg_build}%{?dist}
%global srtp_full_version    %{srtp_version}-2.%{srtp_build}%{?dist}
%global opus_full_version    %{opus_version}-2.%{opus_build}%{?dist}
%if "%{?REPO}" == "mcu-develop"
%global ptlib_full_version   %{ptlib_version}
%else
%global ptlib_full_version   %{ptlib_version}-2.%{ptlib_build}%{?dist}
%endif


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

BuildRequires:  collab-ffmpeg-devel = %{ffmpeg_full_version}
BuildRequires:  collab-libsrtp2-devel = %{srtp_full_version}
BuildRequires:  collab-opus-devel = %{opus_full_version}
BuildRequires:  collab-ptlib-devel = %{ptlib_full_version}

BuildRequires:  which
BuildRequires:  speex-devel
BuildRequires:  libtheora-devel
BuildRequires:  libvpx-devel

Requires:       collab-ffmpeg = %{ffmpeg_full_version}
Requires:       collab-libsrtp2 = %{srtp_full_version}
Requires:       collab-opus = %{opus_full_version}
Requires:       collab-ptlib = %{ptlib_full_version}

%description
OpalVOIP library

%package        devel
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       collab-ffmpeg-devel = %{ffmpeg_full_version}
Requires:       collab-libsrtp2-devel = %{srtp_full_version}
Requires:       collab-ptlib-devel = %{ptlib_full_version}

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
%if "%{?dist}" == ".el7"
source /opt/rh/devtoolset-9/enable
%endif
%ifarch aarch64
%define arch_arg --enable-graviton2 --disable-x264
%endif
%if "%{?REPO}" == "mcu-release-tsan"
%define tsan_arg --enable-sanitize-thread
%endif
%if "%{?REPO}" == "mcu-release-asan"
%define asan_arg --enable-sanitize-address
%endif
sed -i \
    -e "s/MAJOR_VERSION.*/MAJOR_VERSION %{version_major}/" \
    -e "s/MINOR_VERSION.*/MINOR_VERSION %{version_minor}/" \
    -e "s/BUILD_TYPE.*/BUILD_TYPE %{version_stage}/"       \
    -e "s/PATCH_VERSION.*/PATCH_VERSION %{version_patch}/" \
    -e "s/OEM_VERSION.*/OEM_VERSION %{version_oem}/"       \
    version.h
./configure %{?arch_arg} %{?tsan_arg} %{?asan_arg} \
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
        --disable-silk \
        --prefix=%{_prefix} \
        --libdir=%{_libdir}
make %{?_smp_mflags} all


%install
%if "%{?dist}" == ".el7"
source /opt/rh/devtoolset-9/enable
%endif
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%clean
rm -rf $RPM_BUILD_ROOT


%post
%{_datadir}/opal/install_openh264.sh %{_libdir}
/sbin/ldconfig

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
