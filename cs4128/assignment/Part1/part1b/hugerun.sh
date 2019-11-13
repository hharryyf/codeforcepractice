#!/bin/bash
g++ -Wall -o pt2 jury2.cpp 
g++ -Wall -o gen getPersistent.cpp
cpass=0
cfail=0
for i in {1..1000}
do	
	./gen > input
	echo "testcase $i"
	head -1 input
	time ./pt2 < input > out1
done
rm input out1 gen pt2

