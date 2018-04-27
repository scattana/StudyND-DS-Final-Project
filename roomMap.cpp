// roomMap.cpp: Map of rooms that utilizes open addressing

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <unistd.h>
#include <stdexcept>

//#include "room.h"
#include "roomMap.h"

//Room Object Methods:

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


// Methods --------------------------------------------------------------------
const Room NONE;

// default constructor (use DEFAULT values)
RoomMap::RoomMap(){
	table_size = 0;
	max_load_factor = DEFAULT_LOAD_FACTOR;
	num_items = 0;
        table = nullptr;
	resize(DEFAULT_TABLE_SIZE);
}

// parameter-based constructor
RoomMap::RoomMap(size_t t_size, double l_factor){
	table_size = 0;
	max_load_factor = l_factor;
	num_items = 0;
        table = nullptr;
	resize(t_size);
}


RoomMap::RoomMap(oldRmMap oldMap){
    table_size = 0;
    max_load_factor = DEFAULT_LOAD_FACTOR;
    num_items = 0;
    table = nullptr;
    resize(DEFAULT_TABLE_SIZE);
    
    for(auto it = oldMap.begin(); it != oldMap.end(); it++){
        Room NewRoom(it->first, it->second);
        insert(NewRoom);
    }
}

// deconstructor
RoomMap::~RoomMap(){
    delete[] table;
}

//Custom booking function- handles insertion as needed as well as booking
bool RoomMap::book(Booking &entry) {
    if(search(entry.location) == NONE) {
        Room NewRoom(entry.location, entry.capacity);
        insert(NewRoom);
    }

    return table[locate(entry.location)].book(entry);    
}

//Pre-written insert function
void RoomMap::insert(const Room &input) {
    double curr_load_factor = (double)num_items/(double)table_size;

    if(curr_load_factor >= max_load_factor){
	resize(table_size*2);
    }
    size_t bucket = locate(input.roomNum);
    if(bucket == table_size){
	resize(table_size*2); // if no empty buckets found
    }
    else if (table[bucket].roomNum != input.roomNum){
	num_items++; // increment the number of UNIQUE items in the table
    }
    table[bucket] = input;
}

//Pre-written search function
const Room RoomMap::search(const std::string &key) {
    size_t bucket = locate(key);
    if (table[bucket].roomNum == key)
        return table[bucket];
    else
        return NONE;
}


// dump in appropriate format to stream
void RoomMap::dump(std::ostream &os) {
    for(size_t i=0; i<table_size; i++){
	if(table[i] != NONE){
            os << table[i].roomNum << std::endl; //Modify this to dump table info as well?
            /*
	    switch(flag){
		case DUMP_KEY:	     os << table[i].first << std::endl; break;
		case DUMP_VALUE:     os << table[i].second << std::endl; break;
		case DUMP_KEY_VALUE: os << table[i].first << "\t" << table[i].second << std::endl; break;
		case DUMP_VALUE_KEY: os << table[i].second << "\t" << table[i].first << std::endl; break;
	    } */
	}
    }
}

size_t  RoomMap::locate(const std::string &key) {
    // hashing should take place here. If the given key has a non-empty
    // bucket, return that bucket. If the given key does not exist, return
    // the next empty bucket.
    StringHasher hash;		// define hashing type function
    size_t bucket = hash(key) % table_size;
    if(table[bucket].roomNum == key) return bucket;
    else{
	size_t count = 0;
	while(count < table_size){
	    if(table[bucket] == NONE) return bucket; // return next empty bucket
	    if(table[bucket].roomNum == key) return bucket;
	    count++;
	    bucket = (bucket+1)%table_size;
	}
	return table_size;	// sentinel to indicate 'locate' could not find
	                        // an empty bucket, so 'insert' should call 'resize'
    }
}

// called by "insert" when (1) no empty entries in the table, or (2) when
// current load factor exceeds max load factor
void RoomMap::resize(const size_t new_size) {
    auto old_table = table;
    auto old_size = table_size;
    table = new Room[new_size];
    table_size = new_size;
    // copy old values from table to new table
    for(size_t i=0; i<old_size; i++){
	if(old_table[i] != NONE) insert(old_table[i]);
    }
    //delete[] old_table;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
