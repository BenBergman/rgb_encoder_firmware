#!/bin/sh

GVF=include/version.h
DEF_VER="unknown_ver"

LF='
'

# First try git-describe, then default.
if test -d .git -o -f .git &&
	VN=$(git describe --match "v[0-9]*" --abbrev=7 HEAD 2>/dev/null) &&
	case "$VN" in
		*$LF* ) (exit 1) ;;
		v[0-9]* )
			git update-index -q --refresh
			test -z "$(git diff-index --name-only HEAD --)" ||
				VN="$VN-dirty" ;;
	esac
then
	VN=$(echo "$VN" | sed -e 's/-/./g');
else
	VN="$DEF_VER"
fi


echo "
#ifndef VERSION_H
#define VERSION_H

#define RGB_ENCODER_FIRMWARE_VERSION \"$VN\"

#endif
" > $GVF
