#!/bin/bash
g++ -Wall -o spfa spfa.cpp
g++ -Wall -o dijkstra dijkstra.cpp
g++ -Wall -o bellmanford bellmanford.cpp
g++ -Wall -o genr genr.cpp
for i in {1..100}
do	
	./genr > input
	./dijkstra < input > out1
	./spfa < input > out2
	./bellmanford < input > out3
	if diff out1 out3 && diff out2 out3
	then
	   echo "pass testcase $i" 
	else
	   echo "fail testcase $i"
	   head -1 input
	fi
	sleep 0.1
done
rm input out1 out2 out3 genr dijkstra bellmanford spfa
