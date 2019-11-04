#!/bin/bash
g++ -Wall -o undo undo_q.cpp 
g++ -Wall -o jury jury2b.cpp
g++ -Wall -o gen gen.cpp
cpass=0
cfail=0
for i in {1..1000}
do	
	./gen > input
	./undo < input > out1
	./jury < input > out2
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
rm input out1 out2 undo jury gen
