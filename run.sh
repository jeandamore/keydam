#!/bin/sh

make clean
make
touch tmpfile

sudo ./main.exe $1 $2

csvfile=`find . -name "keydam*.csv" -newer tmpfile`
rm -f tmpfile

python ./extract_key_dynamics.py $csvfile