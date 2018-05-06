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
#include "roomMap.cpp"			// For the new library syste, include both of these .h files
#include "booking.h"
using namespace std;


// utility function prototypes
int printBuildings();							// from file loc in Public
Booking newBooking(size_t);						// makes&returns new booking
string lower_str(string);						// returns lowercase string
void printBooking(Booking);						// prints formatted booking
int printRooms(string temp);					// prints rooms in spec bldg
string returnRoom(size_t n, string temp);		// from numeric identifier
string formatTime(size_t);						// in 12-hour format
void system(unordered_map<string, Booking>&);	// reservation system w/HM
size_t get_hour();								// from system_clock
size_t get_capacity(string, size_t);			// from spec. bldg, room
void receipt(Booking);							// outputs booking->txt file

// ----------------------------------------------------------------------------
//            UTILITY FUNCTIONS FOR studyND MAIN EXECUTION
// ----------------------------------------------------------------------------

// Usage function - called when "-h" command line option is set
// or with improper usage
int usage(string progname, int status){
	cout << "\n-----------------------------------------------" << endl;
	cout << "Usage: " << progname << " [OPTIONS]\n\n\t";
	cout << "Command line options:\n\n\t-h\t\tDisplay this usage message\n";
	cout << "\t-n\t\tMake New Study Booking\n";
	cout << "\t-v BUILDING\tView study spaces and bookings for a specific building" << endl;
	cout << "\nCurrent supported buildings:" << endl;
	printBuildings();
	cout << "\n-----------------------------------------------\n" << endl;
	return status;
}



// Opens and prints list of currently-supported buildings in our database
int printBuildings(){
	const char *file_path = "/afs/nd.edu/user24/scattana/Public/buildings.txt";
	FILE *buildings;
	buildings = fopen(file_path,"r");
	// If file doesn't open, return errror message and exit w/failure
	if(!buildings){
		fprintf(stderr, "Could not open file %s: %s\n", file_path, strerror(errno));
		return -1;		// failure
	}
	// If file *does* open, print list of buildings, then close file
	char temp[BUFSIZ];
	cout << endl;		// blank line for formatting purposes
	while(fgets(temp, BUFSIZ, buildings)) printf("\t%s", temp);
	cout << endl;		// formatting
	fclose(buildings);
	return 0;			// success
}

// Makes and returns a new Booking based on user input
Booking newBooking(size_t current_hour){
	int stat = 0;		// success by default
	string temp;
	// do-while loop prints instructions once, and repeats while "view" is specified
	do{
		cout << "\nWelcome to the studyND study space manager\n";
		cout << "The current hour is: " << formatTime(get_hour()) << endl;
		cout << "To make a new booking, please enter BUILDING NAME:\n";
		cout << "\t-to view a list of currently-supported buildings, type \"view\"\n";
		cout << "\t-to exit, type \"exit\"\n";
		getline(cin, temp);	// get input from user
		if(lower_str(temp)=="view") stat = printBuildings();
		if(lower_str(temp)=="exit"){
			stat = -1;		// failure
			Booking booking;
			booking.status = stat;
			return booking;
		}
	}
	while(lower_str(temp)=="view");

	// Make list of buildings from file and store as unordered_set for fast retreival
	unordered_set<string> mySet;
	FILE *buildings;
	const char *file_path = "/afs/nd.edu/user24/scattana/Public/buildings.txt";
	buildings = fopen(file_path,"r");
	if(!buildings){
		fprintf(stderr, "Could not open file %s: %s\n", file_path, strerror(errno));
		stat = -1;		// failure
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
		stat = printBuildings();		// success or failure
		getline(cin, temp);
		found = mySet.find(lower_str(temp));
		if(lower_str(temp)=="exit") exit(0);
	}

	// If we get to this point, building was found, so store it in struct:
	Booking booking;
	booking.building = lower_str(temp);

	// Now, get and find space location within a particular building:
	cout << "\nSpace locations available in " << lower_str(temp) << ":\n";
	stat = printRooms(lower_str(temp));
	cout << "\nPlease enter the number (below) of the space location you wish to reserve:\n";
	//getline(cin, temp);
	size_t num;
	cin >> num;
	string rm = returnRoom(num, lower_str(temp));
	booking.location = lower_str(rm);

	// Get and assign capacity from room location to Booking struct
	booking.capacity = get_capacity(booking.building, num);
	if(booking.capacity == 0) stat = -1;

	// Get and store time of reservation
	cout << "\nThe current hour is: " << formatTime(get_hour()) << endl;
	cout << "\nHow many hours in advance would you look to book (0-48)?\n";
	cout << "(enter a time in hour increments; '0' = NOW)\n";
	cin >> booking.s_time;			// get start time
	booking.s_time += get_hour();	// add to current hour
	cout << "\nHow many hours would you like your booking to last?\n";
	cout << "(enter in hour increments)\n";
	cin >> booking.book_len	;		// get end time
	booking.e_time = booking.s_time + booking.book_len;		// assign e_time


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
	cout << "\nThank you! Here are the details for your booking:\n" << endl;
	printBooking(booking);
	cout << "\nWould you like to confirm your booking? (y/n) ";
	string c;
	getline(cin, c);
	while(!(lower_str(c)=="y" || lower_str(c)=="n")){
		cout << "\nPlease type either 'y' or 'n' or type \"q\" to exit: ";
		getline(cin, c);
		if(lower_str(c)=="q"){
			stat = -1;
			booking.status = stat;
			return booking;
		}
	}

	if(lower_str(c)=="n"){
		cout << "\nYour booking was not confirmed. Leaving studyND\n" << endl;
		stat = -1;
	}
	else cout << "\nYour booking was confirmed! Thank you for using studyND\n" << endl;

	// assign status to booking and return
	booking.status = stat;

	// now reverse the adding current hour to s_time of the Booking struct
	// in order to pass to circular_linked_list later on:
	booking.s_time -= get_hour();
	booking.e_time -= get_hour();

	return booking;
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
	cout << "\tCapacity of room: " << b.capacity << endl;
}

// Utility function to format time output
string formatTime(size_t t){
	string mod;
	if((int)t % 24 < 12) mod = "AM";
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

// Utility function that gets the current time using system_clock (C++11)
// and returns a size_t corresponding to the current hour
size_t get_hour(){
 	chrono::duration<int,ratio<60*60*24>> one_day (1);
    chrono::system_clock::time_point today = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t (today);
    const char hr[3] = {ctime(&tt)[11], ctime(&tt)[12], '\0'};
    return (size_t)stoi(hr);
}

// Utility function to print the rooms and capacities for a specified building
int printRooms(string temp){
	cout << endl;		// formatting
	// open file
	ifstream ifs;
	if(temp=="cushing") ifs.open("/afs/nd.edu/user24/scattana/Public/cushing.txt", ifstream::in);
	else if(temp=="fitzpatrick") ifs.open("/afs/nd.edu/user24/scattana/Public/fitzpatrick.txt", 
	ifstream::in);
	else if(temp=="duncan student center") ifs.open("/afs/nd.edu/user24/scattana/Public/duncan.txt", ifstream::in);
	else if(temp=="stinson-remick") ifs.open("/afs/nd.edu/user24/scattana/Public/stinson.txt", ifstream::in);
	else{
		cout << "Building " << temp << " was not found. Leaving studyND" << endl;
		return -1;
	}
	string loc, cap;
	int rmNum = 1;
	cout << "\tNumber\tLocation:\t\t\tCapacity" << endl;
	cout << "\t------\t--------\t\t\t--------" << endl;
	while(getline(ifs, loc)){
		if(loc != "")
			cout << "\t" << rmNum << "\t" << loc;
		getline(ifs, cap);
		cout << "\t\t" << cap << "\n";
		rmNum++;
	}
	// close the file
	ifs.close();
	return 0;
}

// Utility function to return the space location name for a specified space
// location identifier (number)
string returnRoom(size_t n, string temp){
	// open file
	ifstream ifs;
	if(temp=="cushing") ifs.open("/afs/nd.edu/user24/scattana/Public/cushing.txt", ifstream::in);
	else if(temp=="fitzpatrick") ifs.open("/afs/nd.edu/user24/scattana/Public/fitzpatrick.txt", ifstream::in);
	else if(temp=="duncan student center") ifs.open("/afs/nd.edu/user24/scattana/Public/duncan.txt", ifstream::in); 
	else if(temp=="stinson-remick") ifs.open("/afs/nd.edu/user24/scattana/Public/stinson.txt", ifstream::in);
	else{
		cout << "Building " << temp << " was not found. Leaving studyND" << endl;
		return "";
	}
	string temp2;
	int count = 1;
	while(count < n){
		getline(ifs, temp2);	// get and discard location name
		getline(ifs, temp2); 	// get and discard capacity
		count++;				// increment to next line
	}
	// after while loop runs, read one more line to get correct location:
	getline(ifs, temp2);
	return temp2;
}

// Utility function to return capacity of specified room from file
size_t get_capacity(string temp, size_t loc){
	// open file
	ifstream ifs;
	if(temp=="cushing") ifs.open("/afs/nd.edu/user24/scattana/Public/cushing.txt", ifstream::in);
	else if(temp=="fitzpatrick") ifs.open("/afs/nd.edu/user24/scattana/Public/fitzpatrick.txt", ifstream::in);
	else if(temp=="duncan student center") ifs.open("/afs/nd.edu/user24/scattana/Public/duncan.txt", ifstream::in); 
	else if(temp=="stinson-remick") ifs.open("/afs/nd.edu/user24/scattana/Public/stinson.txt", ifstream::in);
	else{
		cout << "Building " << temp << " was not found. Leaving studyND" << endl;
		return 0;
	}
	string name;
	size_t counter = 1;
	while(counter != loc*2){
		getline(ifs, name);
		counter++;
	}
	getline(ifs, name);		// temp will now hold correct capacity
	return (size_t)(stoi(name));
}


// Utility function to "print" a receipt of a booking to a text file
// in the user's current directory
void receipt(Booking b){
	ofstream out("studyND-booking-info.txt");
	out << "YOUR studyND BOOKING MADE AT HOUR: " << formatTime(get_hour()) << endl;
	out << "-------------------------------------------" << endl;
	out << "Name: " << b.f_name << " " << b.l_name << endl;
	out << "Location: " << b.building << " " << b.location << endl;
	out << "Time: " << formatTime(b.s_time + get_hour()) << " to " << formatTime(b.e_time + get_hour()) << endl;
	out << "Number of people: " << b.num_people << endl;
	out << "Location capacity: " << b.capacity << endl;
	out << "\n" << endl;
	out.close();
}


// -----------------------------------------------
//               MAIN FUNCTION
// -----------------------------------------------

int main(int argc, char* argv[]){
	// FIRST STEP: load booking data (current reservation schedule)
	unordered_map<string, RoomMap *> myMap;

	// -----------------------------------------
	// now parse command line options
	size_t hour;
	bool booked = false;
	// parse command line options
	if(argc == 1) return usage(argv[0], 1);
	if(strcmp(argv[1],"-h")==0) return usage(argv[0], 0);
	int argind = 1;
	for(argind; argind < argc; argind++){
		// -n option means make new reservation
		if(strcmp(argv[argind], "-n")==0){
			booked = true;
		}
		else if(strcmp(argv[argind], "-v")==0) cout << "CALL viewBookings()" << endl;
		else usage(argv[0], 1);	// improper usage; call "usage" with status 1
	}
	// if a booking is desired, make booking and output to file:
	if(booked){
		Booking b = newBooking(hour);
		if(b.status != 0) return EXIT_FAILURE;

		// try to add new <building, RoomMap> entry to the unordered_map
		// if the key already exists, call "book" function on the building
		// and pass Booking object. If the key doesn't exist, map "building"
		// to a new RoomMap object, then call "book" with the booking object
		auto found = myMap.find(b.building);
		if(found== myMap.end()){		// key was not found
			RoomMap *r = new RoomMap;
			myMap.insert(pair<string, RoomMap *>(b.building, r));
			myMap[b.building]->book(b);
		}
		else{							// key was found
			myMap[b.building]->book(b);
		}

		myMap[b.building]->dump(cout);
		// print "receipt" of booking to text file in current directory
		receipt(b);
		for(auto c = myMap.begin(); c != myMap.end(); c++) delete c->second;
	}

	return EXIT_SUCCESS;
}
