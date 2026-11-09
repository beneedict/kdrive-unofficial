# kdrive-unofficial – Fedora-Paket für den kDrive-Desktop-Client

Inoffizieller RPM-Build von [Infomaniak desktop-kDrive](https://github.com/Infomaniak/desktop-kDrive)
für Fedora, gebaut mit COPR.

**Dieses Paket ist nicht offiziell und wird von Infomaniak nicht unterstützt.**
kDrive ist eine Marke der Infomaniak Network SA.

## Installation

```bash
sudo dnf copr enable beneedict/kdrive-unofficial
sudo dnf install kdrive-unofficial
```

Danach `kDrive (inoffiziell)` im App-Grid starten. Ohne die GNOME-Erweiterung
*AppIndicator* erscheint kein Tray-Symbol; das Programm läuft trotzdem weiter
und lässt sich über den App-Starter wieder öffnen. Das Paket empfiehlt die
Erweiterung (`gnome-shell-extension-appindicator`).

## Was anders ist als bei der AppImage

| Änderung | Grund |
|---|---|
| Bau gegen Qt 6, Poco, OpenSSL, SQLite und log4cplus aus Fedora | Sicherheitsupdates kommen vom Distributions-Repo, keine privaten Kopien |
| Sentry ersetzt durch eine No-Op-Bibliothek (`sentry-stub/`) | kein Absturzbericht an Infomaniak, kein `sentry-native`/Crashpad im Paket |
| Matomo-Nutzungsstatistik abgeschaltet | keine Daten an `analytics.infomaniak.com` |
| Autostart-Eintrag zeigt auf `kdrive-unofficial_client` statt auf eine AppImage | funktioniert ohne AppImage |
| Desktop-Datei, Icon und AppStream-Metainfo unter `/usr/share` | Integration in GNOME Software und das App-Grid |

Die Änderungen sind als Patches in `patches/` abgelegt und jeweils im
Patch-Kopf dokumentiert (GPLv3 §5(a)). Die vollständigen Quellen liegen im
jeweiligen SRPM bei, das COPR zu jedem Build veröffentlicht.

## Quellen und Lizenzen

- Upstream: GPL-3.0-or-later (`LICENSE`)
- `src/3rdparty/qtsingleapplication`, `qtlockedfile`: LGPL-2.1-only mit
  Qt-LGPL-Ausnahme 1.1 (deren Dateien werden nicht mitinstalliert, die
  Lizenztexte liegen im SRPM)
- `src/3rdparty/utf8proc`: MIT, `src/3rdparty/qt-piwik-tracker`: MIT,
  `src/3rdparty/keychain`: MIT
- `sentry-stub/`: MIT
- AppStream-Metainfo: MIT

Die Lizenztexte werden mit `%license` installiert.

## Selbst bauen

```bash
# Quellen holen (GitHub-Tarball und Submodule per Commit)
dnf install mock rpmdevtools
spectool -g -R kdrive-unofficial.spec   # legt die Quellen in ./ ab

# SRPM bauen und in mock bauen; läuft abgekoppelt weiter,
# auch wenn das Terminal geschlossen wird
./build-local.sh fedora-45-x86_64

# Ergebnis
cat build-status.log
ls /var/lib/mock/fedora-45-x86_64/result/*.rpm
```

`build-srpm.sh` sammelt Spec-Datei, Patches und die kleinen Zusatz-Tarballs
(`sentry-stub`, `cmake-modules`) in ein Staging-Verzeichnis und ruft
`rpmbuild -bs` auf. `build-local.sh` startet `mock` mit `setsid`, schreibt
das vollständige Log nach `build-<chroot>.log` und die Zusammenfassung nach
`build-status.log`.

COPR baut für `fedora-44`, `fedora-45` und `fedora-rawhide` auf x86_64.
Bei jedem neuen Upstream-Tag (`3.x.y`, nicht `w-*` oder `m-*`) wird die
Version in der Spec-Datei erhöht; der Merge löst über den Webhook einen
neuen COPR-Build aus.

## Fehler melden

Bitte im [Issue-Tracker dieses Repos](https://github.com/beneedict/kdrive-unofficial/issues),
nicht bei Infomaniak. Fehler, die auch in der offiziellen AppImage auftreten,
können zusätzlich upstream gemeldet werden.
