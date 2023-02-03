#!/bin/bash -x
for x in `ls *.c`
do
	./compile.sh $x
	./a.out
	gcc -g $x
	./a.out
done
