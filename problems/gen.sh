#!/usr/bin/env bash

# $1 is lang
# $2 is problem name
# $3 is problem link
dir_name=${2^^}
echo Creating dir with $dir_name
mkdir $dir_name
echo Creating README.md with $3 as link
cd $dir_name
echo '<'$3'>' >> README.md

echo Creating main file
touch $2.$1
