// roomMap.cpp: Map of rooms that utilizes open addressing

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <unistd.h>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    std::chrono::duration<int,std::ratio<60*60*24>> one_day (1);
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
}


RoomMap::RoomMap(oldRmMap oldMap, time_t age){
    table_size = 0;
    max_load_factor = DEFAULT_LOAD_FACTOR;
    num_items = 0;
    table = nullptr;
    resize(DEFAULT_TABLE_SIZE);

    struct stat temp;
    if(stat("./data/schedule.txt", &temp) < 0) {
        for(auto it = oldMap.begin(); it != oldMap.end(); it++) delete it->second;
        return;
    }
    age = (time_t)temp.st_mtim.tv_sec;


    std::chrono::duration<int,std::ratio<60*60*24>> one_day (1);
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t lastUpdate = std::chrono::system_clock::to_time_t (today);
    int numHours = 0;
    numHours = (lastUpdate - age)/3600;

    for(auto it = oldMap.begin(); it != oldMap.end(); it++){
        List *NewList;
        if(numHours > 47)
            NewList = new List;
        else{
            NewList = new List(it->second->times);
            for(int c=0; c<numHours; c++)
                NewList->rotate();
        }
        Room *NewRoom = new Room{it->first, it->second->cap, NewList};
        toDelete.push_back(NewRoom);
        insert(*NewRoom);
        delete it->second;
    }
}

// deconstructor
RoomMap::~RoomMap(){
    for(size_t c=0; c<table_size; c++){
        if(table[c] != NONE) {
            delete table[c].times;
        }
    }
    int temp = toDelete.size();
    for(int c=0; c<temp; c++) delete toDelete[c];
    delete[] table;
}

size_t RoomMap::num_rooms(){
    return num_items; 
}

//Custom booking function- handles insertion as needed as well as booking
bool RoomMap::book(Booking &entry) {
    if(search(entry.location) == NONE) {
        List *NewList = new List;
        Room *NewRoom = new Room{entry.location, entry.capacity, NewList};
        toDelete.push_back(NewRoom);
        insert(*NewRoom);
    }
    return table[locate(entry.location)].times->reserve(&entry);
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
            os << table[i].roomNum << std::endl;
            os << table[i].capacity << std::endl;
            table[i].times->dump(os);
	}
    }
}

void RoomMap::listRooms(){
    for(size_t i=0; i<table_size; i++){
        if(table[i] != NONE){
            std::cout << table[i].roomNum << std::endl;
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
    table = new Room[new_size]();
    table_size = new_size;
    for(size_t c=0; c<new_size; c++){
        table[c] = NONE;
    }
    for(size_t i=0; i<old_size; i++){
	if(old_table[i] != NONE) insert(old_table[i]);
    }
    if(old_table) delete[] old_table;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
