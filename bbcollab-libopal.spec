%global version_major  3
%global version_minor  17
%global version_patch  4

Name:           bbcollab-libopal
Version:        %{version_major}.%{version_minor}.%{version_patch}.3
Release:        0%{?jenkins_release}%{?dist}
Summary:        OpalVOIP library

Group:          System Environment/Libraries
License:        MPL 1.0
URL:            http://www.opalvoip.org/
Source0:        zsdk-opal.src.tgz

BuildRequires:  bbcollab-gcc = 5.1.0
BuildRequires:  bbcollab-ptlib-devel = 2.17.4.3
BuildRequires:  bbcollab-ffmpeg-devel = 2.6.3
BuildRequires:  opus-devel
BuildRequires:  speex-devel
BuildRequires:  libsrtp-devel = 1.4.4
BuildRequires:  libtheora-devel
BuildRequires:  libvpx-devel
BuildRequires:  x264-devel

%description
OpalVOIP library

%package        devel
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       bbcollab-ptlib-devel = 2.17.4.3
Requires:       libsrtp-devel = 1.4.4

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
PKG_CONFIG_PATH=/opt/bbcollab/lib64/pkgconfig:/opt/bbcollab/lib/pkgconfig
./configure --prefix=/opt/bbcollab \
        --exec-prefix=/opt/bbcollab \
        --bindir=/opt/bbcollab/bin \
        --sbindir=/opt/bbcollab/sbin \
        --sysconfdir=/opt/bbcollab/etc \
        --datadir=/opt/bbcollab/share \
        --includedir=/opt/bbcollab/include \
        --libdir=/opt/bbcollab/lib64 \
        --libexecdir=/opt/bbcollab/libexec \
        --localstatedir=/opt/bbcollab/var \
        --sharedstatedir=/opt/bbcollab/var/lib \
        --mandir=/opt/bbcollab/share/man \
        --infodir=/opt/bbcollab/share/info \
        --enable-localspeexdsp \
        --enable-rtpfec \
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
        CC=/opt/bbcollab/bin/gcc \
        CXX=/opt/bbcollab/bin/g++ \
        LD=/opt/bbcollab/bin/g++ \
        OPAL_MAJOR=%{version_major} \
        OPAL_MINOR=%{version_minor} \
        OPAL_BUILD=%{version_patch}
make %{?_smp_mflags} all


%install
PKG_CONFIG_PATH=/opt/bbcollab/lib64/pkgconfig:/opt/bbcollab/lib/pkgconfig
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%clean
rm -rf $RPM_BUILD_ROOT


# No need to call ldconfig, as we're not installing to the default dynamic linker path
#%post -p /sbin/ldconfig

#%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
/opt/bbcollab/lib64/*.so.*
/opt/bbcollab/lib64/opal-%{version_major}.%{version_minor}.%{version_patch}

%files devel
%defattr(-,root,root,-)
/opt/bbcollab/include/opal
/opt/bbcollab/lib64/*.so
/opt/bbcollab/lib64/pkgconfig/*.pc
/opt/bbcollab/share/opal

%files static
%defattr(-,root,root,-)
/opt/bbcollab/lib64/*.a


%changelog
* Fri Dec 02 2016 Gavin Llewellyn <gavin.llewellyn@blackboard.com> - 3.17.1-1
- Initial RPM release

