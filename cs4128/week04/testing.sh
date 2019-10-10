counter=1
while [ $counter -le 5 ]
do
	g++ -Wall -o genr genr.cpp
	./genr > testing
	./E < testing > out1
	./Ejury < testing > out2
	if diff out1 out2
	then cat testing 
	fi
	((counter++))
done




