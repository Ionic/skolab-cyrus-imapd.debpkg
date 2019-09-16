#!/bin/bash

source functions.sh

#_cyrusclone
_cassandaneclone
#_cyrusbuild
apt update
DEBIAN_FRONTEND=noninteractive apt install -y cyrus-imapd libdbi-perl
_updatejmaptestsuite
_cassandane
retval=$?
_report
exit ${retval}

