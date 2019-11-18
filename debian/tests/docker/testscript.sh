#!/bin/bash

source functions.sh

#_cyrusclone
[ -d /srv/cassandane.git ] || _cassandaneclone
#_cyrusbuild
apt-get update

DEBIAN_FRONTEND=noninteractive apt-get install -y cyrus-imapd

_updatejmaptestsuite

export CASSANDANEOPTS="Cyrus::ImapTest"
_cassandane
retval=$?
_report
exit ${retval}

