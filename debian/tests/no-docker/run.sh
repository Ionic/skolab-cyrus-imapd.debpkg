#! /bin/bash

set -x

START_DIR="$(pwd)"

groupadd -r saslauth || true
useradd -c "Cyrus IMAP Server" -d /var/lib/imap -g mail -G saslauth -s /bin/bash -r cyrus || true


mkdir /tmp/cass
chown cyrus /tmp/cass

cd "${START_DIR}"
chmod 755 entrypoint.sh testscript.sh
./entrypoint.sh
