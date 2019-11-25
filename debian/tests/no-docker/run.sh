#! /bin/bash

export DEBIAN_FRONTEND=noninteractive
START_DIR="$(pwd)"

# do no install suggests or recommands
echo 'APT::Install-Recommends "false";' > /etc/apt/apt.conf.d/docker-no-recommends
echo 'APT::Install-Suggests "false";' >> /etc/apt/apt.conf.d/docker-no-recommends 

# install requirements
apt-get update
apt-get -y install \
    apt-utils \
    autoconf \
    automake \
    autotools-dev \
    bash-completion \
    bison \
    build-essential \
    check \
    clang \
    cmake \
    comerr-dev \
    cpanminus \
    doxygen \
    debhelper \
    flex \
    g++ \
    git \
    gperf \
    graphviz \
    groff \
    texi2html \
    texinfo \
    heimdal-dev \
    help2man \
    libanyevent-perl \
    libbsd-dev \
    libbsd-resource-perl \
    libclone-perl \
    libconfig-inifiles-perl \
    libcunit1-dev \
    libdatetime-perl \
    libdb-dev \
    libdbi-perl \
    libdigest-sha-perl \
    libencode-imaputf7-perl \
    libfile-chdir-perl \
    libfile-slurp-perl \
    libglib2.0-dev \
    libhttp-daemon-perl \
    libio-socket-inet6-perl \
    libio-stringy-perl \
    libjson-perl \
    libjson-xs-perl \
    libldap2-dev \
    libmagic-dev \
    libmilter-dev \
    default-libmysqlclient-dev \
    libnet-server-perl \
    libnews-nntpclient-perl \
    libpath-tiny-perl \
    libpam0g-dev \
    libpcre3-dev \
    libsasl2-dev \
    libsnmp-dev \
    libsqlite3-dev \
    libssl-dev \
    libstring-crc32-perl \
    libtest-deep-perl \
    libtest-deep-type-perl \
    libtest-most-perl \
    libtest-unit-perl \
    libtool \
    libunix-syslog-perl \
    liburi-perl \
    libxml-generator-perl \
    libxml-xpath-perl \
    libxml2-dev \
    libwrap0-dev \
    libxapian-dev \
    libzephyr-dev \
    lsb-base \
    net-tools \
    pandoc \
    perl \
    php-cli \
    php-curl \
    pkg-config \
    po-debconf \
    python-docutils \
    python-sphinx \
    python-pygments \
    python3-pygments \
    rsync \
    sudo \
    sphinx-common \
    tcl-dev \
    transfig \
    uuid-dev \
    vim \
    wamerican \
    wget \
    xutils-dev \
    zlib1g-dev

groupadd -r saslauth
useradd -c "Cyrus IMAP Server" -d /var/lib/imap -g mail -G saslauth -s /bin/bash -r cyrus

apt-get -y install cyrus-imapd

cd /srv
git config --global http.sslverify false
git clone https://github.com/cyrusimap/cyrus-docker.git cyrus-docker.git
git clone https://github.com/cyrusimap/cassandane.git cassandane.git
git clone https://github.com/cyrusimap/cyruslibs.git cyruslibs.git
git clone https://github.com/dovecot/core.git dovecot.git
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
