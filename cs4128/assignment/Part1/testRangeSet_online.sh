#!/bin/bash
g++ -Wall -o RangeSetQuery RangeSetQuery_smarter.cpp 
g++ -Wall -o pt RangeSetQuery_online.cpp
g++ -Wall -o gen genRangeSet_online.cpp
cpass=0
cfail=0
for i in {1..1000}
do	
	./gen > input
	./RangeSetQuery < input > out1
	./pt < input > out2
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
rm input out1 out2 gen pt RangeSetQuery
