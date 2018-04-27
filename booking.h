#include <string>

struct Booking{
	string building;		// building name
	string location;		// space identifier within building (i.e. room)
	string f_name;			// first name of the person who made the booking
	string l_name;			// last name of person who made booking
	size_t num_people;		// number of people who will be using the space
	size_t s_time;			// start time of booking (0 = now)
	size_t book_len;		// duration in hours of booking (0-48)
	size_t e_time;			// end time of booking (assigned after input)
	size_t capacity;		// room's capacity (assigned after input)
};
