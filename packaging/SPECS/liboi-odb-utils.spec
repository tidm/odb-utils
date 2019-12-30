%define name liboi-odb-utils
%define version 7.0.1
%define release 3

Name:           %{name}
Version:        %{version}
Release:        %{release}%{?dist}
License:        LGPLv3
URL:            http://gitlab.tosanidm.net/oi/odb_utils
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Summary:        Operational Intelligence ODB Utilities
Group:          Development/Libraries

BuildRequires: gcc-c++
BuildRequires: libtool
BuildRequires: make

Requires:       liboi-exception >= 7.0
Requires:       liboi-common >= 7.2
Requires:       libodb >= 2.4
Requires:       libodb-oracle >= 2.4

%package devel
Summary:        Development files for using ${name}
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       pkgconfig
Requires:       liboi-exception-devel >= 7.0
Requires:       liboi-common-devel >= 7.2
Requires:       libodb-devel >= 2.4
Requires:       libodb-oracle-devel >= 2.4
Provides:       %{name}-devel = %{version}-%{release}


%description
TIDM Operational Intelligence ODB Utilities

%description devel
This package contain development files for ${name}. It should be installed
if you want to develop programs that will use the ${name} library.

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_libdir}/*.so.*
%exclude %{_libdir}/*.a*
%exclude %{_libdir}/*.la*
%exclude %{_libdir}/pkgconfig/*
%exclude %{_includedir}/*

%files devel
%{_libdir}/*.so
%{_libdir}/*.a*
%{_libdir}/*.la*
%{_libdir}/pkgconfig/*
%{_includedir}/*
%exclude %{_libdir}/*.so.*

%changelog
* Sun Dec 29 2019 Soroush Rabiei <rabiei@tidm.ir> 7.0-3
- Remove ODB Boost dependency (release 3)

* Sat Dec 07 2019 Hessam Khoshniat <khoshniat@tidm.ir> 7.0-2
- library version upgraded (release 2)

* Sat Sep 29 2018 Soroush Rabiei <rabiei@tidm.ir> 7.0-1
- Initial package for oi-odb-utils library (release 1)
