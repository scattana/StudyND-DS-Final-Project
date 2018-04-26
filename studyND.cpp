//------------------------------------------------------------------------
//	studyND.cpp
//		a study space booking and usage system for common study locations
//		at the University of Notre Dame. For more info, see README.md
//
//	Seth Cattanach, Aidan McDonald, Michael Moynihan
//	Data Structures Spring 2018 Final Project
//------------------------------------------------------------------------

#include <iostream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <stdio.h>
#include <cerrno>
#include <cstring>
using namespace std;

// "Booking" struct (each "booking" contains the data for one "study reservation"
struct Booking{
	string building;
	string location;
	string f_name;
	string l_name;
	int num_people;
	int s_time;
	int e_time;
	int capacity;
};


// utility function prototypes
string lower_str(string);
void printBooking(Booking);
string formatTime(int);
void system(unordered_map<string, Booking>&);



// Opens and prints list of currently-supported buildings in our database
void printBuildings(){
	const char *file_path = "./buildings.txt";
	FILE *buildings;
	buildings = fopen(file_path,"r");
	// If file doesn't open, return errror message and exit w/failure
	if(!buildings){
		fprintf(stderr, "Could not open file %s: %s\n", file_path, strerror(errno));
		exit(EXIT_FAILURE);
	}
	// If file *does* open, print list of buildings, then close file
	char temp[BUFSIZ];
	cout << endl;		// blank line for formatting purposes
	while(fgets(temp, BUFSIZ, buildings)) printf("\t%s", temp);
	fclose(buildings);
}

// Makes and returns a new Booking based on user input
Booking newBooking(){
	string temp;
	// do-while loop prints instructions once, and repeats while "view" is specified
	do{
		cout << "\nWelcome to the studyND study space manager\n";
		cout << "To make a new booking, please enter BUILDING NAME:\n";
		cout << "\t-to view a list of currently-supported buildings, type \"view\"\n";
		cout << "\t-to exit, type \"exit\"\n";
		getline(cin, temp);	// get input from user
		if(lower_str(temp)=="view") printBuildings();
		if(lower_str(temp)=="exit") exit(0);
	}
	while(temp=="view" || temp=="View" || temp=="VIEW");

	// Make list of buildings from file and store as unordered_set for fast retreival
	unordered_set<string> mySet;
	FILE *buildings;
	const char *file_path = "./buildings.txt";
	buildings = fopen(file_path,"r");
	if(!buildings){
		fprintf(stderr, "Could not open file %s: %s\n", file_path, strerror(errno));
		exit(EXIT_FAILURE);
	}
	char hold[BUFSIZ];
	while(fgets(hold, BUFSIZ, buildings)){
		mySet.insert(lower_str((string)strtok(hold,"\n")));
	}
	fclose(buildings);

	// try to find specified building. If not found, print list of supported
	// buildings and try again
	auto found = mySet.find(lower_str(temp));
	while(found == mySet.end()){		// not found
		cout << "\n\"" << temp << "\" was not found." << endl;
		cout << "Please enter a building from the list below, ";
		cout << "or type \"exit\" to exit the program: " << endl;
		printBuildings();
		getline(cin, temp);
		found = mySet.find(lower_str(temp));
		if(lower_str(temp)=="exit") exit(0);
	}

	// If we get to this point, building was found, so store it in struct:
	Booking booking;
	booking.building = lower_str(temp);

	// Now, get and find space location within a particular building:
	cout << "\nPlease enter the location within " << temp << ":\n";
	getline(cin, temp);
	booking.location = temp;

	// Get and store time of reservation
	cout << "\nPlease enter a start time for your reservation:\n";
	cout << "Enter a time in hour increments and using military (24-hour) time,\n";
	cin >> booking.s_time;		// get start time
	cout << "\nPlease enter an end time for your reservation:\n";
	cout << "Enter a time in hour increments and using military (24-hour) time,\n";
	cout << "(end time must be on the same day as your start time)" << endl;
	cin >> booking.e_time;		// get end time


	// get and store first name
	cout << "\nPlease enter your first name:\n";
	cin >> temp;
	booking.f_name = temp;

	// get and store last name
	cout << "\nPlease enter your last name:\n";
	cin >> temp;
	booking.l_name = temp;

	// get and store number of people
	cout << "\nHow many people will be using this location?\n";
	cin >> booking.num_people;

	// confirm booking
	cout << "Thank you! Here are the details for your booking:\n" << endl;
	printBooking(booking);
	cout << "\nWould you like to confirm your booking? (y/n) ";
	char c;
	cin >> c;
	while(!(tolower(c)=='y' || tolower(c)=='n')){
		cout << "Please type either 'y' or 'n' or type \"q\" to exit: ";
		cin >> c;
		if(tolower(c)=='q') exit(0);
	}
	if(tolower(c)=='n'){
		cout << "\nYour booking was not confirmed. Leaving studyND\n" << endl;
		exit(0);
	}
	else cout << "\nYour booking was confirmed! Thank you for using studyND\n" << endl;

	return booking;
}

void usage(string progname, int status){
	cout << "\n-----------------------------------------------" << endl;
	cout << "Usage: " << progname << " [OPTIONS]\n\n\t";
	cout << "Command line options:\n\n\t-h\t\tDisplay this usage message\n";
	cout << "\t-n\t\tMake New Study Booking\n";
	cout << "\t-v BUILDING\tView study spaces and bookings for a specific building" << endl;
	cout << "\nCurrent supported buildings:" << endl;
	printBuildings();
	cout << "\n-----------------------------------------------\n" << endl;
	exit(status);
}


int main(int argc, char* argv[]){
	// parse command line options
	bool manual = true;
	if(argc == 1) usage(argv[0], 1);
	if(strcmp(argv[1],"-h")==0) usage(argv[0], 0);
	int argind = 1;
	for(argind; argind < argc; argind++){
		// -n option means make new reservation
		if(strcmp(argv[argind], "-n")==0) Booking myBooking = newBooking();
		else if(strcmp(argv[argind], "-v")==0) cout << "CALL viewBookings()" << endl;
		else usage(argv[0], 1);	// improper usage; call "usage" with status 1
	}
	return EXIT_SUCCESS;
}


// Utility function "lower_str" returns lowercase copy of string parameter
string lower_str(string x){
	for(int i=0; i < x.size(); i++) x[i] = tolower(x[i]);
	return x;
}



// Utility function "printBooking" prints booking details to stdout
void printBooking(Booking b){
	cout << "\tName: " << b.f_name << " " << b.l_name << endl;
	cout << "\tLocation: " << b.building << " " << b.location << endl;
	cout << "\tTime: " << formatTime(b.s_time) << " to " << formatTime(b.e_time) << endl;
	cout << "\tNumber of people: " << b.num_people << endl;
}

// Utility function to format time output
string formatTime(int t){
	string mod;
	if((int)t / 12 == 0) mod = "AM";
	else mod = "PM";
	int hour = t;	// truncate decimal
	hour = (int)t % 12;
	if(hour==0) hour = 12;
	// concatenate in proper 12-hour time format:
	return (to_string(hour) + ":" + "00" + " " + mod);
}


// "system" modifies (by reference) the hash table of reservations
void system(unordered_map<string, Booking> &booking){
	
}
