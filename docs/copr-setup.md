# COPR-Einrichtung

Stand: **2026-11-19 eingerichtet.** GitHub-Repo und COPR-Projekt sind
öffentlich: https://copr.fedorainfracloud.org/coprs/beneedict/kdrive-unofficial/

Voraussetzungen:

- COPR-Token in `~/.config/copr`
- GitHub-Repo `beneedict/kdrive-unofficial` (öffentlich)

## 1. Projekt anlegen

```bash
copr-cli create kdrive-unofficial \
    --chroot fedora-44-x86_64 \
    --chroot fedora-45-x86_64 \
    --chroot fedora-rawhide-x86_64 \
    --description "Unofficial build of the Infomaniak kDrive desktop client. \
Not supported by Infomaniak. kDrive is a trademark of Infomaniak Network SA." \
    --instructions "sudo dnf copr enable beneedict/kdrive-unofficial
sudo dnf install kdrive-unofficial"
```

## 2. SCM-Paket mit `make srpm`

```bash
copr-cli add-package-scm kdrive-unofficial \
    --name kdrive-unofficial \
    --clone-url https://github.com/beneedict/kdrive-unofficial.git \
    --commit main \
    --spec kdrive-unofficial.spec \
    --method make_srpm \
    --webhook-rebuild on
```

`--method make_srpm` nutzt `.copr/Makefile` aus dem Repo; dort werden die
Quellen per `spectool` geladen und die Hilfs-Tarballs erzeugt.

## 3. Webhook (Rebuild nach Push)

```bash
# erzeugt ein neues Token und gibt es aus
copr-cli new-webhook-secret kdrive-unofficial
```

Die Webhook-URL hat die Form

```
https://copr.fedorainfracloud.org/webhooks/github/<token>/beneedict/kdrive-unofficial/
```

Eingetragen in GitHub unter *Settings → Webhooks* (Ereignis: `push`,
Content-Type `application/json`) bzw. per API:

```bash
gh api repos/beneedict/kdrive-unofficial/hooks -X POST \
    -f name=web -F active=true -f "events[]=push" \
    -f "config[url]=https://copr.fedorainfracloud.org/webhooks/github/<token>/beneedict/kdrive-unofficial/" \
    -f "config[content_type]=json" -f "config[insecure_ssl]=0"
```

Das Token steht nicht in `copr-cli get-package`; es ist nur über
`new-webhook-secret` (neu erzeugen) oder die COPR-Weboberfläche sichtbar.

## 4. Erster Build

```bash
copr-cli build-package kdrive-unofficial --name kdrive-unofficial
```

Build [11362240](https://copr.fedorainfracloud.org/coprs/build/11362240)
war am 2026-11-19 für Fedora 44, 45 und Rawhide erfolgreich.

## 5. Veröffentlichung

Die Markenfreigabe liegt vor (Infomaniak, 2026-11-19, siehe
`docs/upstream-inquiry.md`). Die drei Auflagen — inoffiziell, kein Support,
Markenhinweis — sind in README, Spec, Desktop-Eintrag und COPR-Beschreibung
erfüllt. GitHub-Repo und COPR-Projekt wurden am 2026-11-19 öffentlich
geschaltet:

```bash
gh repo edit beneedict/kdrive-unofficial --visibility public --accept-visibility-change-consequences
```

Danach sind COPR-Projekt und Repo öffentlich; die README nennt weiterhin
den inoffiziellen Status und die Markenhinweise.
