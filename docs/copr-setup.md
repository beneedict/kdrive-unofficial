# COPR-Einrichtung (noch nicht ausgeführt)

Voraussetzungen:

- COPR-Token in `~/.config/copr`
- GitHub-Repo `beneedict/kdrive-unofficial` (existiert, derzeit privat)

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

## 3. Webhook (optional, für Rebuild nach Merge)

```bash
copr-cli get-package kdrive-unofficial --name kdrive-unofficial
# Webhook-URL steht in der Ausgabe unter "webhook_rebuild"
```

In GitHub unter *Settings → Webhooks* eintragen, Ereignis: Push.

## 4. Erster Build

```bash
copr-cli build-package kdrive-unofficial --name kdrive-unofficial
```

## 5. Veröffentlichen

Freigabe liegt vor (Infomaniak, 2026-11-19, siehe
`docs/upstream-inquiry.md`). Die drei Auflagen — inoffiziell, kein Support,
Markenhinweis — sind in README, Spec und COPR-Beschreibung erfüllt:

```bash
gh repo edit beneedict/kdrive-unofficial --visibility public --accept-visibility-change-consequences
```

Danach sind COPR-Projekt und Repo öffentlich; die README nennt weiterhin
den inoffiziellen Status und die Markenhinweise.
