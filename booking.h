#pragma once
#include <string>

struct Booking{
	std::string building;	// building name
	std::string location;	// space identifier within building (i.e. room)
	std::string f_name;		// first name of the person who made the booking
	std::string l_name;		// last name of person who made booking
	size_t num_people;		// number of people who will be using the space
	size_t s_time;			// start time of booking (0 = now)
	size_t book_len;		// duration in hours of booking (0-48)
	size_t e_time;			// end time of booking (assigned after input)
	size_t capacity;		// room's capacity (assigned after input)
	int status;				// status used to create booking struct, in main
};
