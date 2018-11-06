%global version_major  3
%global version_minor  17
%global version_patch  4

%global ffmpeg_ver_el6 2.6.3-9.3.el6
%global ffmpeg_ver_el7 2.6.3-10.4.el7
%global ptlib_ver_el6 2.17.4.65-2.1.el6
%global ptlib_ver_el7 2.17.4.65-2.1.el7
%global srtp_ver_el6 2.1.0-3.2.el6
%global srtp_ver_el7 2.1.0-4.3.el7

# Branch ID should be 0 for local builds/PRs
# Jenkins builds should use 1 for develop, 2 for master (release builds)
%{!?branch_id: %global branch_id 0}
%{!?opal_stage: %global opal_stage -alpha}

# Disable the separate debug package and automatic stripping, as detailed here:
# http://fedoraproject.org/wiki/How_to_create_an_RPM_package
%global _enable_debug_package 0
%global debug_package %{nil}
%global __os_install_post /usr/lib/rpm/brp-compress %{nil}

%if 0%{?rhel} <= 6
    %global _prefix /opt/bbcollab
%endif

Name:           bbcollab-libopal
Version:        %{version_major}.%{version_minor}.%{version_patch}.69
Release:        %{branch_id}%{?jenkins_release}%{?dist}
Summary:        OpalVOIP library

Group:          System Environment/Libraries
License:        MPL 1.0
URL:            http://www.opalvoip.org/
Source0:        zsdk-opal.src.tgz

%if 0%{?rhel} <= 6
BuildRequires:  bbcollab-gcc = 5.1.0-3.2.el6
BuildRequires:  bbcollab-ptlib-devel = %{ptlib_ver_el6}
BuildRequires:  bbcollab-ffmpeg-devel = %{ffmpeg_ver_el6}
BuildRequires:  libsrtp2-devel = %{srtp_ver_el6}
%else
BuildRequires:  devtoolset-7-gcc-c++
BuildRequires:  bbcollab-ptlib-devel = %{ptlib_ver_el7}
BuildRequires:  bbcollab-ffmpeg-devel = %{ffmpeg_ver_el7}
BuildRequires:  libsrtp2-devel = %{srtp_ver_el7}
%endif

BuildRequires:  opus-devel
BuildRequires:  speex-devel
BuildRequires:  libtheora-devel
BuildRequires:  libvpx-devel
BuildRequires:  which
BuildRequires:  x264-devel

# The PTLib so version does not tend to change, so relying on the automatic dependency
# generator may not trigger upgrades when needed. Add an explicit package dependency instead.
%if 0%{?rhel} >= 7
Requires:       bbcollab-ptlib = %{ptlib_ver_el7}
%endif

%description
OpalVOIP library

%package        devel
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
%if 0%{?rhel} <= 6
Requires:       bbcollab-ptlib-devel = %{ptlib_ver_el6}
Requires:       libsrtp2-devel = %{srtp_ver_el6}
%else
Requires:       bbcollab-ptlib-devel = %{ptlib_ver_el7}
Requires:       libsrtp2-devel = %{srtp_ver_el7}
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
%setup -q -c -n zsdk-opal


%build
%if 0%{?rhel} <= 6
PKG_CONFIG_PATH=/opt/bbcollab/lib64/pkgconfig:/opt/bbcollab/lib/pkgconfig
%else
source /opt/rh/devtoolset-7/enable
%endif
%configure --enable-localspeexdsp \
        --disable-h323 \
        --disable-iax2 \
        --disable-skinny \
        --disable-lid \
        --disable-t38 \
        --disable-sipim \
        --disable-script \
        --disable-mixer \
        --disable-presence \
        --disable-g.722.1 \
        --enable-cpp14 \
%if 0%{?rhel} <= 6
        CC=/opt/bbcollab/bin/gcc \
        CXX=/opt/bbcollab/bin/g++ \
        LD=/opt/bbcollab/bin/g++ \
%endif
        OPAL_MAJOR=%{version_major} \
        OPAL_MINOR=%{version_minor} \
        OPAL_STAGE=%{opal_stage} \
        OPAL_BUILD=%{version_patch}
make %{?_smp_mflags} REVISION_FILE= all


%install
%if 0%{?rhel} <= 6
PKG_CONFIG_PATH=/opt/bbcollab/lib64/pkgconfig:/opt/bbcollab/lib/pkgconfig
%else
source /opt/rh/devtoolset-7/enable
%endif
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%clean
rm -rf $RPM_BUILD_ROOT


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%{_libdir}/*.so.*
%{_libdir}/opal-%{version_major}.%{version_minor}.%{version_patch}

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

