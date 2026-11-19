# Prüfergebnisse

## COPR-Build 3.8.8-2 (2026-11-19)

Build [11362240](https://copr.fedorainfracloud.org/coprs/build/11362240)
war für alle drei Chroots erfolgreich:

| Chroot | Ergebnis | RPM |
|---|---|---|
| `fedora-44-x86_64` | erfolgreich | `kdrive-unofficial-3.8.8-2.fc44.x86_64.rpm` |
| `fedora-45-x86_64` | erfolgreich | `kdrive-unofficial-3.8.8-2.fc45.x86_64.rpm` |
| `fedora-rawhide-x86_64` | erfolgreich (fc46) | `kdrive-unofficial-3.8.8-2.fc46.x86_64.rpm` |

Geprüft am heruntergeladenen Fedora-45-RPM:

- `/usr/share/doc/kdrive-unofficial/TRADEMARK_NOTICE.md` ist enthalten.
- Der Desktop-Eintrag heißt `kDrive (unofficial)` bzw. `kDrive (inoffiziell)`.
- `%description` nennt den inoffiziellen Status, den fehlenden Support und
  den Markenhinweis.

Der Build dauerte rund 13 Minuten.

## Lokale Prüfung 3.8.8-1

Stand: 2026-11-10, lokal mit `mock` gebaut (`build-local.sh`).

### Builds

| Chroot | Ergebnis | RPM |
|---|---|---|
| `fedora-44-x86_64` | erfolgreich, `%check` grün | `kdrive-unofficial-3.8.8-1.fc44.x86_64.rpm` |
| `fedora-45-x86_64` | erfolgreich, `%check` grün | `kdrive-unofficial-3.8.8-1.fc45.x86_64.rpm` |
| `fedora-rawhide-x86_64` | erfolgreich (fc46, Qt 6.12, OpenSSL 4.0) | `kdrive-unofficial-3.8.8-1.fc46.x86_64.rpm` |

Jeweils ca. 13–15 Minuten Bauzeit auf 4 Threads, inklusive des privat
gebauten `log4cplus` mit `UNICODE=ON`.

## Installationstest in leerem Chroot

Für alle drei Chroots geprüft (`rpm -ivh --nodeps`):

- `ldd /usr/bin/kDrive` und `/usr/bin/kDrive_client`: keine fehlenden
  Bibliotheken
- `desktop-file-validate /usr/share/applications/kDrive_client.desktop`: OK
- `appstream-util validate-relax`: OK (Fedora 45)
- Installation und Deinstallation ohne Fehler

## Rauchtest (Fedora 45)

```
$ QT_QPA_PLATFORM=offscreen timeout 8 /usr/bin/kDrive
kDrive server starting
rc=124          # läuft weiter, wie erwartet

$ QT_QPA_PLATFORM=offscreen timeout 8 /usr/bin/kDrive_client
kDrive client starting
rc=124
```

## Datenschutzprüfung

- Keine Laufzeitabhängigkeit auf `libsentry`:
  `readelf -d /usr/bin/kDrive | grep libsentry` → leer
- Keine Sentry-DSN-Zeichenketten in den Binaries (vom LTO entfernt, weil der
  Stub die Aufrufe zu No-Ops macht)
- `sentry_init` ist als definierte Funktion im Binary enthalten (Stub,
  Symbole werden von Fedora gestrippt)
- Matomo ist über `matomoDisabled = true` abgeschaltet; der Konfigurationswert
  `MATOMO_URL` steht noch im Client-Binary, es wird aber kein Request
  ausgelöst (`sendVisit`/`sendEvent` kehren vor dem Senden zurück)

## Offen

- Fedora 44: SQLite 3.51 statt 3.53, per Patch `0004` freigegeben
- Markenfrage geklärt: Infomaniak hat Name und Icons am 2026-11-19
  freigegeben (`docs/upstream-inquiry.md`). COPR-Projekt, GitHub-Repo und
  Build 3.8.8-2 sind veröffentlicht (`docs/copr-setup.md`).

## Update-Verhalten (3.8.8.1)

- `0005-package-managed-updates.patch` ist im Build enthalten.
- Der Client startet mit Version `3.8.8.1` (siehe
  `~/.local/state/kDrive/logs/*_kDrive_client.log.0`).
- Es erscheint kein Hinweis mehr auf eine AppImage; der Updater meldet
  `UpToDate`, ohne den Infomaniak-Endpunkt abzufragen.
