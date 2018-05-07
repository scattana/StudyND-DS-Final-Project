#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <unordered_map>

size_t get_hour(){
    std::chrono::duration<int,std::ratio<60*60*24>> one_day (1);
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t (today);
    const char hr[3] = {ctime(&tt)[11], ctime(&tt)[12], '\0'};
    return (size_t)std::stoi(hr);
}

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

typedef struct {
        size_t times[48];
        std::string names[48];
        size_t cap;
} schedule;

typedef std::unordered_map<std::string, schedule> oldRmMap;
