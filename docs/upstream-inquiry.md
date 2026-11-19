# Anfrage an Infomaniak (Marke und Logo)

Status: **freigegeben**. Infomaniak hat die Nutzung von Name und Icons am
2026-11-19 genehmigt — öffentlich im GitHub-Issue (Kommentar von
`FabianDevel`, der das Issue damit geschlossen hat) und zusätzlich per
E-Mail: https://github.com/Infomaniak/desktop-kDrive/issues/2706#issuecomment-7015038005

Die ursprüngliche Frist von 14 Tagen (2026-11-23) ist damit gegenstandslos.

## Antwort von Infomaniak

> Hello,
>
> First, thank you for your trademark inquiry and your willingness to
> contribute to our application.
>
> After validation from our compliance team, you may use the name and icon
> and proceed with your package, as long as you explicitly mention that:
>
> your .rpm package is unofficial,
> we do not offer support for it,
> you include the trademark notice.
> In fine, exactly what you described in this issue.
>
> Have a great day, and thanks again.

Damit sind drei Auflagen verbunden. Wo sie erfüllt sind:

| Auflage | Umsetzung |
|---|---|
| Paket ist inoffiziell | README („Dieses Paket ist nicht offiziell“), Spec-`Summary`/`%description` („Unofficial build“), Desktop-Eintrag („kDrive (unofficial)“), AppStream-Metainfo, COPR-Beschreibung |
| Kein Support durch Infomaniak | README, Spec-`%description`, AppStream-Metainfo, COPR-Beschreibung („not supported by Infomaniak“); Fehlermeldungen gehen an dieses Repo |
| Markenhinweis | „kDrive is a trademark of Infomaniak Network SA“ in README, Spec, AppStream-Metainfo, COPR-Beschreibung und `TRADEMARK_NOTICE.md` |

## Ursprüngliche Anfrage (2026-11-09)

Ziel: Einverständnis für Name „kDrive“ und die mitgelieferten App-Icons in
einem inoffiziellen Fedora-Paket.

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
