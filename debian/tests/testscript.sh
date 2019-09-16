#!/bin/bash

source functions.sh

#_cyrusclone
_cassandaneclone
#_cyrusbuild
apt update
apt install -y cyrus-imapd
_updatejmaptestsuite
_cassandane
retval=$?
_report
exit ${retval}

