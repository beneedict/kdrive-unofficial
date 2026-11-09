#!/bin/sh
# Build the source RPM for kdrive-unofficial.
#
# Upstream sources are downloaded with spectool, the local packaging files
# and the generated helper tarballs are staged next to them.  rpmbuild
# resolves Source/Patch entries relative to _sourcedir, so everything has
# to live in one directory.
set -eu

here=$(cd "$(dirname "$0")" && pwd)
stage=$(mktemp -d)
trap 'rm -rf "$stage"' EXIT

# Local files referenced by the spec
cp "$here"/io.github.beneedict.kdrive_unofficial.metainfo.xml "$stage"/
cp "$here"/*.patch "$stage"/
tar czf "$stage/sentry-stub.tar.gz" -C "$here" sentry-stub
tar czf "$stage/cmake-modules.tar.gz" -C "$here" cmake-modules

# Upstream sources (Source0..3 and the log4cplus tarball).  spectool only
# downloads missing files, so a local cache in sources/ is reused.
spectool -g -R \
    --define "_sourcedir $stage" \
    "$here/kdrive-unofficial.spec" >/dev/null

mkdir -p "$here/srpms"
rpmbuild -bs \
    --define "_sourcedir $stage" \
    --define "_srcrpmdir $here/srpms" \
    "$here/kdrive-unofficial.spec"

echo "SRPM: $(ls -t "$here"/srpms/*.src.rpm | head -n1)"
