#!/bin/bash

# Testing script for studyND final project
# Tests both memory (using valgrind) and output against an expected
# output text file

# testing output...five total cases



# testing memory...
valgrind --leak-check=full ./studyND -n < input1 2>&1 | grep -e "ERROR SUMMARY: 0 errors" > /dev/null
status=$?
if [ $status = 0 ]; then
	echo "Memory Success"
else
	echo "Memory Failure"
fi
