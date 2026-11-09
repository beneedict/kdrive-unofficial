# Anfrage an Infomaniak (Marke und Logo)

Status: **abgeschickt am 2026-11-09** (direkt an Infomaniak) und zusätzlich als
GitHub-Issue: https://github.com/Infomaniak/desktop-kDrive/issues/2706
Frist: **2026-11-23** (14 Tage). Antwort oder Fristablauf entscheidet über
die Veröffentlichung im COPR.

Ziel: Einverständnis für Name „kDrive“ und die mitgelieferten App-Icons in
einem inoffiziellen Fedora-Paket.

---

**Subject: Unofficial Fedora COPR package of kDrive Desktop – trademark question**

Hello Infomaniak team,

I would like to provide an unofficial RPM package of kDrive Desktop for Fedora
via COPR, built from the GPL-3.0-or-later sources on GitHub against Fedora's
system libraries.

- The package is clearly labeled as unofficial and not supported by
  Infomaniak, with a trademark notice ("kDrive is a trademark of Infomaniak
  Network SA").
- All sources, patches and the spec file are public (SRPM + GitHub).
  Patches: crash reporting (Sentry) replaced by a no-op stub, Matomo tracking
  disabled, autostart entry fixed for installations without an AppImage,
  SQLite version check relaxed for Fedora 44.
- Bug reports are directed to our repository, not to your support.
- The application icons from `infomaniak/theme` are redistributed unchanged
  under the GPL-3.0-or-later licence of the repository.

Are you fine with us using the name "kDrive" and the bundled application icons
in this package? If you prefer a different name or icon set, we will adapt.
We are also happy to upstream generic Linux fixes (e.g. the autostart entry
outside an AppImage, and a CMake option to build without sentry-native).

Best regards,
Benedikt Nimmervoll
https://github.com/beneedict/kdrive-unofficial
