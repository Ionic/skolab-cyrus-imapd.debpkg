#!/bin/sh
#
# autogen.sh glue for CMU Cyrus IMAP
# $Id: autogen.sh,v 1.16 2004/09/12 15:30:23 hmh Exp $
#
# Requires: automake 1.9, autoconf 2.57, dpkg-dev
set -e

# Refresh GNU autotools toolchain.
echo Running GNU autotools toolchain...
AUTOMAKEDIR=/usr/share/automake-1.9
[ -n "$AUTOMAKEDIR" ] &&
  for i in config.guess config.sub install-sh mkinstalldirs ; do
	test -r ${AUTOMAKEDIR}/${i} && {
		rm -f ${i} || true
		cp ${AUTOMAKEDIR}/${i} .
	}
	chmod 755 ${i}
  done

aclocal-1.9 -I cmulocal
autoheader
#automake --verbose --foreign --add-missing
autoconf

# For the Debian build
test -d debian && {
	# Kill executable list first
	#rm -f debian/executable.files

	# Make sure our executable and removable lists won't be screwed up
	#debclean && echo Cleaned buildtree just in case...

	# refresh list of executable scripts, to avoid possible breakage if
	# upstream tarball does not include the file or if it is mispackaged
	# for whatever reason.
	#echo Generating list of executable files...
	#rm -f debian/executable.files
	#find -type f -perm +111 ! -name '.*' -print  | sort > debian/executable.files

	# even in Debian builds, copy them in, don't link them
	rm -f config.sub config.guess
	cp /usr/share/misc/config.sub .
	cp /usr/share/misc/config.guess .

	# Remove any files in upstream tarball that we don't have in the Debian
	# package (because diff cannot remove files)
	# THIS CRAP IS NOT EMBEDDED SPACE-SAFE!
	version=`dpkg-parsechangelog | awk '/Version:/ { print $2 }' | sed -e 's/-[^-]\+$//'`
	source=`dpkg-parsechangelog | awk '/Source:/ { print $2 }' | tr -d ' '`
	#if test -r ../${source}_${version}.orig.tar.gz ; then
	#	echo Generating list of files that should be removed...
	#	rm -f debian/deletable.files
	#	touch debian/deletable.files.new
	#	mkdir debian/tmp
	#	cd debian/tmp
	#	tar -zxf ../../../${source}_${version}.orig.tar.gz
	#	# et/ we handle directly
	#	rm -fr */et/
	#	cd ../..
	#	for i in `find debian/tmp/ -type f ! -name '.*' -print | xargs` ; do
	#	  if test -r ${i} ; then
	#	     filename=`echo "${i}" | sed -e 's#.*debian/tmp/[^/]+/##'`
	#	     test -r "${filename}" || echo "${filename}" >>debian/deletable.files.new
	#	  fi
	#	done
	#	sort < debian/deletable.files.new > debian/deletable.files \
	#		&& rm debian/deletable.files.new
	#	rm -fr debian/tmp
	#else
	#	echo Emptying list of files that should be deleted...
	#	rm -f debian/deletable.files
	#	touch debian/deletable.files
	#fi
}

exit 0