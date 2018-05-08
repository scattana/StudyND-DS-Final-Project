// roomMap.h: header file for roomMap object

#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <unistd.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "booking.h"
#include "circular_linked_list.h"

typedef std::hash<std::string>  StringHasher;

const double DEFAULT_LOAD_FACTOR = 0.6; //extern?
const size_t DEFAULT_TABLE_SIZE = 20; //extern?

/*typedef struct {
        size_t times[48];
        std::string names[48];
        size_t cap;
} schedule;
typedef std::unordered_map<std::string, schedule> oldRmMap;
*/
struct Room{
    std::string roomNum;
    size_t capacity;
    List *times;

    bool operator==(const Room &r2) const;
    bool operator!=(const Room &r2) const;
};


class RoomMap {
public:
        RoomMap();                                      // default constructor
        RoomMap(size_t, double);        		// constructor
        RoomMap(oldRmMap, time_t);                      // .txt initialization constructor
        ~RoomMap();                                     // destructor

        bool book(Booking &entry); //Function to book a time in a room; calls insert as needed.
        const Room search(const std::string &key); //Pre-written function, returns either the room with the right key or NULL if that room's not in the table

        void            insert(const Room &input); //Standard insert / dump
        void            dump(std::ostream &os);
        void            listRooms();

        size_t          num_rooms();

private:
        size_t          locate(const std::string &key); //Pre-written function, returns either the bucket corresponding to that key, the next open bucket, or the table size if the table is full
        void            resize(const size_t new_size); //All this is pre-written
        size_t          table_size;
        size_t          num_items;
        Room*           table;
        double          max_load_factor;
        std::vector<Room *> toDelete;
};

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
