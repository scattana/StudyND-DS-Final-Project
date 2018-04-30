//RoomMap library testing code -- Aidan McDonald

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cerrno>
#include <cstring>
#include "roomMap.h"
#include "booking.h"

int main() {
    Booking testBook;//{"","","","",0,0,0,0,0};
    testBook.building = "Knott";
    testBook.location = "121B";
    testBook.f_name = "Aidan";
    testBook.l_name = "McDonald";
    testBook.num_people = 1;
    testBook.s_time = 2;
    testBook.book_len = 3;
    testBook.e_time = 2+3;
    testBook.capacity = 20;
    
    RoomMap testMap;
    testMap.book(testBook);

    Booking newBook = {"","315 K","Aidan","McDonald",1,2,3,5,6};
    testMap.book(newBook);
   
    testMap.dump(std::cout);
     
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp: