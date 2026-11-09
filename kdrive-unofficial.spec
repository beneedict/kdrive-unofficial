%global         debug_package %{nil}
%global         _hardened_build 1

Name:           kdrive-unofficial
Version:        3.8.8
Release:        1%{?dist}
Summary:        Unofficial build of the Infomaniak kDrive desktop sync client
License:        GPL-3.0-or-later AND MIT AND Apache-2.0 AND BSD-2-Clause
URL:            https://github.com/Infomaniak/desktop-kDrive

# Upstream release tag 3.8.7 (GPL-3.0-or-later)
Source0:        %{url}/archive/refs/tags/%{version}/desktop-kDrive-%{version}.tar.gz
# Submodules of that tag, pinned by commit
Source1:        https://github.com/hrantzsch/keychain/archive/1865e69fe29e352cdafe613e878f572c907d39d7/keychain-1865e69fe29e.tar.gz
Source2:        https://github.com/JuliaStrings/utf8proc/archive/a1b99daa2a3393884220264c927a48ba1251a9c6/utf8proc-a1b99daa2a33.tar.gz
Source3:        https://github.com/pbek/qt-piwik-tracker/archive/c705cfd34109545e859b9915ddcc23f52f594258/qt-piwik-tracker-c705cfd34109.tar.gz
# Distribution packaging
Source4:        io.github.beneedict.kdrive_unofficial.metainfo.xml
Source5:        sentry-stub.tar.gz
Source6:        cmake-modules.tar.gz
# Fedora's log4cplus is built without UNICODE support, kDrive needs it
Source7:        https://github.com/log4cplus/log4cplus/releases/download/REL_2_1_2/log4cplus-2.1.2.tar.gz

Patch0:         0001-sentry-stub.patch
Patch1:         0002-disable-matomo.patch
Patch2:         0003-autostart-without-appimage.patch
Patch3:         0004-relax-sqlite-version.patch
Patch4:         0005-package-managed-updates.patch

# kDrive is built from source against the Qt 6 packages of Fedora
BuildRequires:  cmake
BuildRequires:  gcc-c++
BuildRequires:  gettext
BuildRequires:  make
BuildRequires:  ninja-build
BuildRequires:  pkgconfig
BuildRequires:  qt6-qtbase-devel
BuildRequires:  qt6-qtbase-gui
BuildRequires:  qt6-qt5compat-devel
BuildRequires:  qt6-qtsvg-devel
BuildRequires:  qt6-linguist
BuildRequires:  qt6-qttools-devel
BuildRequires:  poco-devel
BuildRequires:  xxhash-devel
BuildRequires:  libzip-devel
BuildRequires:  sqlite-devel
BuildRequires:  openssl-devel
BuildRequires:  libsecret-devel
BuildRequires:  libuuid-devel
BuildRequires:  zlib-devel
BuildRequires:  kf6-filesystem
BuildRequires:  shared-mime-info
BuildRequires:  desktop-file-utils
BuildRequires:  libappstream-glib
Requires:       hicolor-icon-theme
Requires:       shared-mime-info
# Without the AppIndicator extension GNOME shows no tray icon.  kDrive keeps
# running and the main window can be opened from the app grid, so this is only
# a recommendation.
Recommends:     gnome-shell-extension-appindicator

Provides:       bundled(log4cplus) = 2.1.2
Provides:       bundled(keychain) = 1865e69fe29e352cdafe613e878f572c907d39d7
Provides:       bundled(qt-piwik-tracker) = c705cfd34109545e859b9915ddcc23f52f594258

%description
kDrive Desktop synchronises files between the local computer and the kDrive
cloud storage of Infomaniak.

This is an unofficial build for Fedora.  It is compiled from the upstream
GPL-3.0-or-later sources and is not supported by Infomaniak.  kDrive is a
trademark of Infomaniak Network SA.

Differences from the upstream AppImage:
  * built against the system Qt 6, Poco, OpenSSL and SQLite libraries
  * crash reporting (Sentry) removed, no telemetry library is shipped
  * usage statistics (Matomo) disabled
  * the autostart entry points at the installed client instead of an AppImage
  * desktop integration is installed to /usr/share

%prep
%autosetup -p1 -n desktop-kDrive-%{version}
tar xf %{SOURCE1} --strip-components=1 -C src/3rdparty/keychain
tar xf %{SOURCE2} --strip-components=1 -C src/3rdparty/utf8proc
tar xf %{SOURCE3} --strip-components=1 -C src/3rdparty/qt-piwik-tracker
tar xf %{SOURCE5}
tar xf %{SOURCE6}
tar xf %{SOURCE7}

%build
# Fedora's log4cplus-devel is compiled without UNICODE support, but kDrive
# logs wide strings.  Build a private static log4cplus with UNICODE=ON.
%cmake -S log4cplus-2.1.2 -B log4cplus-build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=$PWD/log4cplus-prefix \
  -DUNICODE=ON \
  -DLOG4CPLUS_ENABLE_DECORATED_LIBRARY_NAME=OFF \
  -DBUILD_SHARED_LIBS=OFF \
  -DLOG4CPLUS_BUILD_TESTING=OFF \
  -DLOG4CPLUS_BUILD_LOGGINGSERVER=OFF \
  -DWITH_ICONV=OFF \
  -DWITH_QT5=OFF
cmake --build log4cplus-build -- -j4
cmake --install log4cplus-build

%cmake \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=%{_prefix} \
  -DKDRIVE_THEME_DIR=$PWD/infomaniak \
  -DKDRIVE_SENTRY_STUB_DIR=$PWD/sentry-stub \
  -DKDRIVE_EXTRA_MODULE_PATH=$PWD/cmake-modules \
  -DKDRIVE_LOG4CPLUS_ROOT=$PWD/log4cplus-prefix \
  -DBUILD_UNIT_TESTS=OFF \
  -DBUILD_TESTING=OFF \
  -DCMAKE_SKIP_RPATH=ON \
  -DBUILD_SHARED_LIBS=OFF \
  -Wno-dev
%cmake_build -- -j4

%install
%cmake_install

# Lizenztexte mit eindeutigen Namen ablegen
licdir=%{buildroot}%{_licensedir}/%{name}
install -Dpm 0644 LICENSE                        $licdir/LICENSE.GPL-3.0-or-later
install -Dpm 0644 src/3rdparty/LICENSE.LGPL      $licdir/LICENSE.LGPL-2.1
install -Dpm 0644 src/3rdparty/LGPL_EXCEPTION.txt $licdir/LGPL_EXCEPTION.txt
install -Dpm 0644 src/3rdparty/keychain/LICENSE  $licdir/LICENSE.keychain
install -Dpm 0644 src/3rdparty/utf8proc/LICENSE.md $licdir/LICENSE.utf8proc
install -Dpm 0644 src/3rdparty/qt-piwik-tracker/LICENSE $licdir/LICENSE.qt-piwik-tracker
install -Dpm 0644 log4cplus-2.1.2/LICENSE        $licdir/LICENSE.log4cplus
install -Dpm 0644 log4cplus-2.1.2/COPYING        $licdir/COPYING.log4cplus
install -Dpm 0644 %{SOURCE4} %{buildroot}%{_metainfodir}/io.github.beneedict.kdrive_unofficial.metainfo.xml
# keychain is linked statically into the build, its development files
# must not end up in the package
rm -rf %{buildroot}%{_includedir}/keychain %{buildroot}%{_libdir}/libkeychain.so %{buildroot}%{_prefix}/lib/libkeychain.so %{buildroot}%{_prefix}/lib/libkeychain.a

%check
desktop-file-validate %{buildroot}%{_datadir}/applications/kDrive_client.desktop
appstream-util validate-relax --nonet %{buildroot}%{_metainfodir}/io.github.beneedict.kdrive_unofficial.metainfo.xml || :

%files
%license %{_licensedir}/%{name}/*
%doc README.md THIRD_PARTY_NOTICES.md
%{_bindir}/kDrive
%{_bindir}/kDrive_client
%{_bindir}/sync-exclude.lst
%{_datadir}/applications/kDrive_client.desktop
%{_metainfodir}/io.github.beneedict.kdrive_unofficial.metainfo.xml
%{_datadir}/icons/hicolor/*/apps/kdrive-win.png
%{_datadir}/kDrive_client

%changelog
* Tue Nov 10 2026 Benedikt Nimmervoll <beneedict@users.noreply.github.com> - 3.8.8-1
- Update to kDrive 3.8.8.1.
- New patch: no update check against Infomaniak, updates are delivered by dnf.
* Mon Nov 09 2026 Benedikt Nimmervoll <beneedict@users.noreply.github.com> - 3.8.7-1
- Initial package for kDrive 3.8.7.
- Build against the Fedora system libraries.
- Sentry stub instead of sentry-native, Matomo tracking disabled.
- Autostart entry fixed for non-AppImage installations.
- Update check replaced by package-managed updates (dnf).
