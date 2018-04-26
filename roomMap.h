// roomMap.h: header file for roomMap object

#pragma once //May be unneccessary, depends on everyone else's header files
#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <unistd.h>
#include <stdexcept>

#include "room.h"

typedef std::hash<std::string>  StringHasher;

const double DEFAULT_LOAD_FACTOR = 0.6; //extern?
const size_t DEFAULT_TABLE_SIZE = 20; //extern?
const Room NONE(); //Definition?

class RoomMap {
public:
        RoomMap();                                      // default constructor
        RoomMap(size_t, double);        		// constructor
        ~RoomMap();                                     // destructor

        bool book(const std::string &key, const size_t &max, const size_t &time, const size_t &nPeople); //Function to book a time in a room; calls insert as needed.
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