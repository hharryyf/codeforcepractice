#!/bin/bash
g++ -Wall -o c1 connectedoff.cpp 
g++ -Wall -o c2 connectedon.cpp
g++ -Wall -o gen gen.cpp
cpass=0
cfail=0
for i in {1..1000}
do	
	./gen > input
	./c1 < input > out1
	./c2 < input > out2
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
rm input out1 out2 c1 c2 gen
