#!/bin/bash

# Testing script for studyND final project
# Tests both memory (using valgrind) and output against an expected
# output text file



# testing memory...
# ------------------
valgrind --leak-check=full ./studyND -n < ./scripts/input1 2>&1 | grep -e "ERROR SUMMARY: 0 errors" > /dev/null
status=$?
if [ $status = 0 ]; then
	echo "Memory Success"
else
	echo "Memory Failure"
fi


# testing output...
# ------------------
rm data/schedule.txt		# start with clean slate, no dependencies
# now create 5 sample bookings with multiple edge cases
./studyND -n < ./scripts/input1 > /dev/null 2>&1
./studyND -n < ./scripts/input2 > /dev/null 2>&1
./studyND -n < ./scripts/input3 > /dev/null 2>&1
./studyND -n < ./scripts/input4 > /dev/null 2>&1
./studyND -n < ./scripts/input5 > /dev/null 2>&1

# test for differences between expected output and generated schedule.txt
./studyND -v < ./scripts/sample | tail -n 48 > temp
diff temp ./scripts/output
status=$?
if [ $status = 0 ]; then
	echo "Output Success"
else
	echo "Memory Failure"
fi

# remove temp files
rm temp
rm ./data/schedule.txt

