#!/bin/sh

rm b.txt
find "$1" -type f | while read path; do
	sha1sum "$path" >> b.txt
done

freq_digests=$( cat b.txt | cut -d' ' -f1 | sort | uniq -c | sort -n )
echo "$freq_digests" | awk '$1 > 1 { print $0 }' | while read freq_digest; do
	echo 'The same'
	digest=$( echo "$freq_digest" | cut -d' ' -f2 )
	grep "$digest" b.txt | cut -d' ' -f3-
done
