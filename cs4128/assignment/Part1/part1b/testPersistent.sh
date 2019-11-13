#!/bin/bash
g++ -Wall -o pt2 HJTrangetree.cpp 
g++ -Wall -o jury2 jury2.cpp
g++ -Wall -o gen getPersistent.cpp
cpass=0
cfail=0
for i in {1..100}
do	
	./gen > input
	time ./pt2 < input > out1
	time ./jury2 < input > out2
	if diff out1 out2
	then
	   echo "pass testcase $i" 
	   head -1 input
	   ((cpass++))
	else
	   echo "fail testcase $i"
	   head -1 input
	   ((cfail++))
	fi
	sleep 0.1
done
echo "pass $cpass, fail  $cfail"
rm input out1 out2 gen jury2 pt2

