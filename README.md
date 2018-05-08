# StudyND-DS-Final-Project
A software program to reserve and manage study locations across the University of Notre Dame.
Implemented in C/C++ with bash testing scripts and a Makefile

USER INFORMATION (building + running the project)
--------------------------------------------------
* To compile and build all files, download all project files into the same 
directory and run `make`. This will generate a `studyND` executable
* To test program output and memory, run `make test`. This will execute a 
shell script that checks valgrind for memory errors and checks sample inputs 
against expected output
* To remove the studyND executable, run `make clean`
* To view usage instructions for studyND, run `studyND -h` and follow the 
provided instructions

INDIVIDUAL CONTRIBUTIONS AND TEAM STRUCTURE
--------------------------------------------------
* Aidan: implemented RoomMap, the custom open addressing hash map; worked 
with I/O for loading and saving reservation state; implemented view option 
for studyND main driver; helped develop booking.h structure
* Michael: implemented circular linked list custom class; worked with I/O 
loading and saving for reservation state; wrote scripts for debugging and 
parsing reservation information
* Seth: implemented the studyND main driver and the new booking capability, 
using Aidan's and Michael's custom classes to map buildings to a Booking 
struct; helped write the Makefile and wrote the shell script for memory and 
output testing; wrote the utility functions in studyND to manage I/O from 
user and from data files
* Team structure: after writing the initial pieces (i.e. main driver and two 
custom data structures), the team debugged together/in-personfor most of the 
project. Smaller tasks were accepted and completed on a need-be basis, and 
generally completed by the individual whose previous contributions most 
strongly related to the task at hand.



FILE INFORMATION
--------------------------------------------------
	
### studyND.cpp
	Main driver for studyND project. C++ implementation. Contains functions 
	for command line argument parsing, viewing building usage and bookings, 
	and making new bookings. Uses an unordered_map as well as a custom 
	RoomMap hash map to manage study reservations. Loads and saves the state 
	of all reservations upon opening and closing, basing its modifications on 
	the system access time returned by the `stat` system call.
	
### roomMap.cpp
	A custom hash map implemented with open addressing and linear probing. 
	Used to map buildings to a circular linked list object 
	(custom-implementation) which manage revolving study reservations.
	
### roomMap.h
	Header file for the RoomMap class. Defines the public and private methods 
	and data fields.
	
### booking.h
	Header file that contains the Booking struct, which is used to create a 
	new booking (study reservation) with fields pertaining to the desired 
	building, room, reservation maker, reservation capacity, etc. The 
	booking.h file also contains several utility functions called in 
	roomMap.cpp and studyND.cpp
	
### circular_linked_list.cpp
	Custom-implementation of a circular linked list object, which has 48 
	slots for each room to be reserved and rotates automatically based on 
	access time and the system clock.
	
### circular_list_list.h
	Header file for circular_linked_list class
	
### scripts
	A folder containing a test script for memory and output as well as sample 
	input/output files used to verify these tests
	
### data
	A folder containing room and building data for currently-supported 
	buildings at Notre Dame (i.e. locations currently in our system)
	
### Makefile
	Makefile used to automatically build and test the studyND program. 
	Includes targets to build, test and clean studyND
	


