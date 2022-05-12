#!/bin/bash

# Quick and dirty script to re-create the patches directory from commits.

set -e

# First, parse options.
typeset from="${1:?'Expected start commit as mandatory first parameter.'}"
typeset to="${2:-HEAD}"

# Translate both to SHA. This has the added side-effect that we don't
# inadvertently also process the removal commit we're going to create next.
from="$(git 'rev-parse' '--verify' '--end-of-options' "${from}")"
to="$(git 'rev-parse' '--verify' '--end-of-options' "${to}")"

if [ ! -e 'debian/patches' ]; then
  printf 'No debian/patches directory found relative to cwd, this is unsupported, exiting.' >&2
  exit '1'
fi

# Then, remove everything in debian/patches/.
git 'rm' 'debian/patches/'*
git 'commit' -m 'debian/patches: pre-regeneration removal.'

# We'll need the directory again.
mkdir '-p' 'debian/patches'

# Now rebuild it by going through the rev list and doing the real magic.
typeset commit=''
for commit in $(git rev-list --reverse "${from}^..${to}"); do
  printf 'Processing commit %s ...\n' "${commit}"

  typeset body="$(git 'show' '-p' '--diff-merges=off' '--stat' '--format=%B' "${commit}")"
  : printf 'Body: '"'"'%s'"'"'\n' "${body}"

  typeset -i start='1'
  typeset oldIFS="${IFS}"
  typeset line=''
  typeset file=''
  IFS=$'\n'
  printf '%s\n' "${body}" | while read -r line; do
    if [ '1' -eq "${start}" ]; then
      file="${line}patch"

      # Add to series file.
      printf '%s\n' "${file}" >> 'debian/patches/series'

      # Clear file, just for good measure.
      : > "debian/patches/${file}"

      # Okay, now make sure that this is followed by a blank line.
      start='2'
    elif [ '2' -eq "${start}" ]; then
      if [ -n "${line}" ]; then
        printf 'No empty line after patch name, invalid format, exiting.\n' >&2
        exit '2'
      else
        start='3'
      fi
    else
      # Pass-through.
      printf '%s\n' "${line}" >> "debian/patches/${file}"
    fi
  done
  IFS="${oldIFS}"

  : printf '\n'
done

# Commit the changes.
git 'add' 'debian/patches'
git 'commit' -m 'debian/patches: regenerate from commits.'

# And lastly, remove the commits in-between.
git 'rebase' "${to}" --onto "${from}^"
