#!/bin/bash

TRIALS=10000
TIME="0"
for (( c=1; c<=$TRIALS ; c++ ))
do
	START=$(date +%s.%N)
	`../studyND -n < input1 2&>1 /dev/null`
	END=$(date +%s.%N)
	TIME=$(echo "$END - $START + $TIME" | bc)
	if [ $c -eq 1 ] || [ $c -eq 10 ] || [ $c -eq 100 ] || [ $c -eq 1000 ] || [ $c -eq 10000 ]
	then
		echo "The time for $c trials is $TIME s."
	fi
done
