#!/bin/bash

source functions.sh

#_cyrusclone
[ -d /srv/cassandane.git ] || _cassandaneclone
#_cyrusbuild
apt update
# FIXME: move libdbi-perl into Dockerfile.jessie
DEBIAN_FRONTEND=noninteractive apt install -y libdbi-perl

# FIXME: move libhttp-daemon-perl into Dockerfile.sid
DEBIAN_FRONTEND=noninteractive apt install -y libhttp-daemon-perl

# FIXME: install package from autopkgtest
DEBIAN_FRONTEND=noninteractive apt install -y cyrus-imapd

_updatejmaptestsuite

export CASSANDANEOPTS="Cyrus::ImapTest"
_cassandane
retval=$?
_report
exit ${retval}

