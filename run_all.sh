#!/bin/bash -x
for x in `ls *.c`
do
	./compile.sh $x
	./a.out
	gcc-13 -g $x
	./a.out
done
