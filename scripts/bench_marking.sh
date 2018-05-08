#!/bin/bash

TRIALS=10000
TIME="0"
BUILDINGS=(Fitzpatrick Cushing DuStu Stinson-Remick)
for (( c=1; c<=$TRIALS ; c++ ))
do
	`touch temp.txt`
	`echo ${BUILDINGS[$((RANDOM % 4))]} > temp.txt`
	`echo $((1+RANDOM%2)) >> temp.txt`
	`echo $((RANDOM%48)) >> temp.txt`
	`echo $((RANDOM%5)) >> temp.txt`
	`echo "Shreya" >> temp.txt`
	`echo "Kumar" >> temp.txt`
	`echo $((1+RANDOM%10)) >> temp.txt`
	`echo "y" >> temp.txt`
	START=$(date +%s.%N)
	`../studyND -n < temp.txt 2&>1 /dev/null`
	END=$(date +%s.%N)
	TIME=$(echo "$END - $START + $TIME" | bc)
	if [ $c -eq 1 ] || [ $c -eq 10 ] || [ $c -eq 100 ] || [ $c -eq 1000 ] || [ $c -eq 10000 ]
	then
		echo "The time for $c trials is $TIME s."
	fi
	`rm temp.txt`
done
