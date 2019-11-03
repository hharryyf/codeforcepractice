#!/bin/bash
g++ -Wall -o undo undo.cpp 
g++ -Wall -o jury1 jury1.cpp
g++ -Wall -o gen2a gen2a.cpp
cpass=0
cfail=0
for i in {1..1000}
do	
	./gen2a > input
	./undo < input > out1
	./jury1 < input > out2
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
rm input out1 out2 undo jury1 gen2a
