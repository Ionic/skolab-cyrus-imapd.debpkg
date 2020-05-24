#! /bin/bash

START_DIR="$(pwd)"

groupadd -r saslauth || true
useradd -c "Cyrus IMAP Server" -d /var/lib/imap -g mail -G saslauth -s /bin/bash -r cyrus || true

cd /srv
git config --global http.sslverify false
git clone https://github.com/cyrusimap/cyrus-docker.git cyrus-docker.git
git clone https://github.com/cyrusimap/cassandane.git cassandane.git
git clone https://github.com/cyrusimap/cyruslibs.git cyruslibs.git
git clone https://github.com/dovecot/core.git dovecot.git
# Use packaged UnicodeData.txt as it often 503's when downloading on
# arm64 armhf in Ubuntu's autopkgtest infrastructure
cp /usr/share/unicode/UnicodeData.txt dovecot.git/src/lib
cp /usr/share/unicode/auxiliary/WordBreakProperty.txt dovecot.git/src/lib-fts
cp /usr/share/unicode/PropList.txt dovecot.git/src/lib-fts

#wget https://github.com/dovecot/core/archive/2.3.8.tar.gz
#tar xzf 2.3.8.tar.gz
#mv core-2.3.8 dovecot.git
git clone https://github.com/cyrusimap/imaptest.git imaptest.git
git clone https://github.com/cyrusimap/CalDAVTester.git caldavtester.git

cpan Term::ReadLine
cpan Mail::IMAPTalk Net::CalDAVTalk Net::CardDAVTalk
cpan Convert::Base64 File::LibMagic;
cpan Net::LDAP::Constant
cpan Net::LDAP::Server
cpan Net::LDAP::Server::Test
cpan Math::Int64

# The following packages are required by JMAP Test Suite
cpan Test::Routine
cpan Test::Deep::JType
cpan Test::Deep::HashRec
cpan Test::Abortable
cpan JSON::Typist
cpan Email::MessageID
cpan MooseX::Role::Parameterized
cpan Process::Status
cpan Data::GUID
cpan JMAP::Tester
cpan Email::MIME
cpan Mail::IMAPClient
cpan Test::Routine

git clone https://github.com/fastmail/JMAP-TestSuite.git JMAP-TestSuite.git

cd /srv/JMAP-TestSuite.git
cpanm --installdeps .

cd /srv
git clone https://github.com/cyrusimap/Mail-JMAPTalk.git Mail-JMAPTalk.git
cd /srv/Mail-JMAPTalk.git
perl Makefile.PL
make
make test
make install

cd /srv/dovecot.git
git fetch
# NOTE: change this only after testing
git checkout -q 6264b51bcce8ae98efdcda3e55a765d7a13d15ed
./autogen.sh
./configure --enable-silent-rules
make -j 8

cd /srv/imaptest.git
git fetch
git checkout -q origin/cyrus
sh autogen.sh
./configure --enable-silent-rules --with-dovecot=/srv/dovecot.git
make -j 8
# # need to run it once as root to link up libs
# src/imaptest || true

mkdir /tmp/cass
chown cyrus /tmp/cass

cd "${START_DIR}"
chmod 755 entrypoint.sh testscript.sh
./entrypoint.sh
