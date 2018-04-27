// roomMap.h: header file for roomMap object

#pragma once //May be unneccessary, depends on everyone else's header files
#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <unistd.h>
#include <stdexcept>
#include <unordered_map>

//#include "booking.h"
#include "circular_linked_list.cpp"

typedef std::hash<std::string>  StringHasher;

const double DEFAULT_LOAD_FACTOR = 0.6; //extern?
const size_t DEFAULT_TABLE_SIZE = 20; //extern?
//const Room NONE(); //Definition?






typedef struct {
        size_t times[48];
        std::string names[48];
        size_t cap;
} schedule;
typedef std::unordered_map<std::string, schedule> oldRmMap;

class Room{
    public:
        Room(); //Default constructor
        Room(std::string, size_t); //Normal constructor, sets room name and capacity
        Room(std::string, schedule &);
        ~Room(); //Destructor

        Room(const Room &); //Copy Constructor
        Room& operator= (const Room &); //Assignment Operator
        friend bool operator== (const Room &, const Room &); //Overloaded tests
        friend bool operator != (const Room &, const Room &);

        std::string roomNum; //Data elements
        size_t capacity;
        List times;

        bool book(Booking &); //Booking function
};


Room::Room() { //Default constructor
    roomNum = "9 3/4";
    capacity = 42;
    List temp; times = temp;    
}


Room::Room(std::string name, size_t holding) { //Custom constructor
    roomNum = name;
    capacity = holding;
    List temp; times = temp;
} 

Room::Room(std::string name, schedule &oldIn){
    roomNum = name;
    capacity = oldIn.cap;
    List temp(oldIn.times, oldIn.names);
    times = temp;
}

Room::~Room(){ //Destructor, modify this as necessary
    //delete &times;
}


Room::Room(const Room &r2){ //Copy constructor
    *this = r2;
}


Room& Room::operator= (const Room &r2){ //Overloaded assignment operator
    this->roomNum = r2.roomNum;
    this->capacity = r2.capacity;
    this->times = r2.times;
}


bool operator== (const Room &r1, const Room &r2) { //Overloaded comparison operator
    if(r1.roomNum != r2.roomNum || r1.capacity != r2.capacity) {
        return false;
    }
    else return true;
}


bool operator != (const Room &r1, const Room &r2) { //Overloaded comparison operator
    return !(r1 == r2);
}


bool Room::book(Booking &b){ //Booking function calls Michael's
    return times.reserve(&b); //Check syntax on this!!!!!
}












//extern struct Booking; //Seth's booking structure

class RoomMap {
public:
        RoomMap();                                      // default constructor
        RoomMap(size_t, double);        		// constructor
        RoomMap(oldRmMap);                              // .txt initialization constructor
        ~RoomMap();                                     // destructor

        bool book(Booking &entry); //Function to book a time in a room; calls insert as needed.
        const Room search(const std::string &key); //Pre-written function, returns either the room with the right key or NULL if that room's not in the table

        void            insert(const Room &input); //Standard insert / dump
        void            dump(std::ostream &os);

private:
        size_t          locate(const std::string &key); //Pre-written function, returns either the bucket corresponding to that key, the next open bucket, or the table size if the table is full
        void            resize(const size_t new_size); //All this is pre-written
        size_t          table_size;
        size_t          num_items;
        Room*           table;
        double          max_load_factor;
};

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
