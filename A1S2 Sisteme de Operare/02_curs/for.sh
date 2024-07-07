#!/bin/bash
for A in world life dude bye; do
	echo Hello $A
done
echo Arg count: $#
for A in $@; do
	echo Arg: $A
done
