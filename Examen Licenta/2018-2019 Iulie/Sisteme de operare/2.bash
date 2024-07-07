#!/usr/bin/env bash
while [ -n "$1" ]; do
	if [ -d $1 ]; then
		for F in `find $1 -type f`; do
			if file $F | grep -q -v text; then
				echo "Eroare: $F"
				continue
			fi
			sed "s/^$2//" $F > $F.text
		done
		shift
		shift
	else
		shift
	fi
done
