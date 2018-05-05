//RoomMap library testing code -- Aidan McDonald

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cerrno>
#include <cstring>
#include "roomMap.h"
#include "booking.h"

int main(int argv, char *argc[]) {
    Booking testBook;// = {"","","","",0,0,0,0,0};
    testBook.building = "Knott";
    testBook.location = "121B";
    testBook.f_name = "Aidan";
    testBook.l_name = "McDonald";
    testBook.num_people = 1;
    testBook.s_time = 2;
    testBook.book_len = 3;
    testBook.e_time = 2+3;
    testBook.capacity = 10;
    

    //Room testBlank={""}; Room otherBlank={""};
    //if(testBlank != otherBlank) return EXIT_FAILURE;

    
    RoomMap testMap;
    testMap.book(testBook);

    Booking newBook = {"Knot","314P","Aiden","McDonald",1,6,1,7,20};
    testMap.book(newBook);
   
    testMap.dump(std::cout);
    
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
