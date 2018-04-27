// room.h: Implementation of a "room" class / object

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <unistd.h>
#include <stdexcept>

extern class List; //Update this as needed based on Michael's code
extern typedef schedule;


class Room{
    public:
        Room(); //Default constructor
        Room(std::string, size_t); //Normal constructor, sets room name and capacity
        Room(std::string, size_t, size_t[48], std::string[48]);
        ~Room(); //Destructor

        Room(const Room &); //Copy Constructor
        Room& operator= (const Room &); //Assignment Operator
        friend bool operator== (const Room &, const Room &); //Overloaded tests
        friend bool operator != (const Room &, const Room &);

        std::string roomNum; //Data elements
        size_t capacity;
        List times;

        bool book(size_t, size_t); //Booking function
};


Room::Room() { //Default constructor
    roomNum = "9 3/4";
    capacity = 42;
    List temp(); times = temp;    
}


Room::Room(std::string name, size_t holding) { //Custom constructor
    roomNum = name;
    capacity = holding;
    List temp(); times = temp;
} 

Room::Room(std::string name, schedule &oldIn){
    roomNum = name;
    capacity = oldIn.cap;
    List temp(oldIn.times, oldIn.names);
    times = temp;
}

Room::~Room(){ //Destructor, modify this as necessary
    delete timeTable;
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


bool Room::book(size_t time, size_t nPeople){ //Booking function calls Michael's
    return times.add(time, nPeople); //Check syntax on this!!!!!
}


// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
