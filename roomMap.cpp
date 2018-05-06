// roomMap.cpp: Map of rooms that utilizes open addressing

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <unistd.h>
#include <stdexcept>
#include "circular_linked_list.cpp"
#include "roomMap.h"

//Room Object Methods:
const Room NONE{"", 0};


bool Room::operator== (const Room &r2) const { //Overloaded comparison operator
    if(this->roomNum != r2.roomNum || this->capacity != r2.capacity) {
        return false;
    }
    else return true;
}

bool Room::operator != (const Room &r2) const { //Overloaded comparison operator
    if(roomNum != r2.roomNum || capacity != r2.capacity) {
        //std::cout << roomNum << "|" << r2.roomNum << std::endl;
        return true;
    }
    else return false;
}


// Methods --------------------------------------------------------------------
//const Room NONE{"9 3/4", 42};

// default constructor (use DEFAULT values)
RoomMap::RoomMap(){
        //std::cout << "In default constructor\n";
	table_size = 0;
	max_load_factor = DEFAULT_LOAD_FACTOR;
	num_items = 0;
        table = nullptr;
        //std::cout << "Right before resize\n";
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
        List *NewList = new List(it->second.times, it->second.names);
        Room *NewRoom = new Room{it->first, it->second.cap, NewList};
        insert(*NewRoom);
    }
}

// deconstructor
RoomMap::~RoomMap(){
    //std::cout << "In map deconstructor " << table_size << std::endl;
    for(size_t c=0; c<table_size; c++){
        //std::cout << "Looping\n";
        if(table[c] != NONE) {std::cout << "Found an item\n"; delete table[c].times;}
    }
    delete[] table;
    //std::cout << "Ran delete command\n";
}

//Custom booking function- handles insertion as needed as well as booking
bool RoomMap::book(Booking &entry) {
    //std::cout << "In Booking\n";
    if(search(entry.location) == NONE) {
        std::cout << "Need to make a new room\n";
        List *NewList = new List;
        Room *NewRoom = new Room{entry.location, entry.capacity, NewList};
        //std::cout << "Made new room\n";
        insert(*NewRoom);
        //std::cout << "About to finish if loop\n";
    }
    
    //std::cout << table[locate(entry.location)].roomNum << std::endl;
    //table[locate(entry.location)].times.dump(std::cout);

    std::cout << "Found in bucket " << locate(entry.location) << std::endl;

    return table[locate(entry.location)].times->reserve(&entry);
    //return table[locate(entry.location)].book(entry);    
}

//Pre-written insert function
void RoomMap::insert(const Room &input) {
    double curr_load_factor = (double)num_items/(double)table_size;

    if(curr_load_factor >= max_load_factor){
	resize(table_size*2);
    }
    //std::cout << "In insert, before locate\n";
    size_t bucket = locate(input.roomNum);
    if(bucket == table_size){
        //std::cout << "No empty buckets found\n";
	resize(table_size*2); // if no empty buckets found
    }
    else if (table[bucket].roomNum != input.roomNum){
	num_items++; // increment the number of UNIQUE items in the table
    }
    table[bucket] = input;
    std::cout << "Inserted in bucket " << bucket << std::endl;
}

//Pre-written search function
const Room RoomMap::search(const std::string &key) {
    //std::cout << "In search\n";
    size_t bucket = locate(key);
    //std::cout << "Past locate\n";
    if(bucket >= table_size)
        return NONE;
    else if (table[bucket].roomNum == key)
        return table[bucket];
    else
        return NONE;
}


// dump in appropriate format to stream
void RoomMap::dump(std::ostream &os) {
    for(size_t i=0; i<table_size; i++){
	if(table[i] != NONE){
            os << table[i].roomNum << ", capacity: " << table[i].capacity << std::endl;
            table[i].times->dump(os);
            os << std::endl;
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
    std::cout << "Resizing table\n";
    auto old_table = table;
    auto old_size = table_size;
    table = new Room[new_size]();
    table_size = new_size;
    //std::cout << "Made new table\n";
    for(size_t c=0; c<new_size; c++){
        table[c] = NONE;
    }
    // copy old values from table to new table
    for(size_t i=0; i<old_size; i++){
	if(old_table[i] != NONE) insert(old_table[i]);
    }
    if(old_table) delete[] old_table;
    //std::cout << "Finished resize\n";
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
