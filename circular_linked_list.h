//circular_linked_list.h

#pragma once
#include "booking.h"
#include <iostream>
#include <string>

const size_t NTIMES = 48;

class List {
	public:
		List();
		List(size_t times[NTIMES]);
		~List();
		size_t rotate();
		bool isFull(Booking *b);
		bool reserve(Booking *b);
		void dump(std::ostream &s);
	private:
		struct Node{
			size_t                  people;
			Node                    *next;
		};
		Node *head;
};
