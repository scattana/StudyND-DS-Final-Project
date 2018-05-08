// Michael Moynihan
// circular_linked_list.cpp

/********** Includes **********/

#include "booking.h"
#include "circular_linked_list.h"
#include <iostream>
#include <string>

/********** Constructors **********/

// Default constructor.  Creates an empty linked list with 48 elements
List::List(){
	head = new Node{0,nullptr};
	Node *curr = head;
	for(int i = 1;i < NTIMES;i++){
		Node *temp = new Node{0,nullptr};
		curr->next = temp;
		curr = curr->next;
	}
}

// Overloaded constructor.  Creates a linked list with 48 elements and data based on input
List::List(size_t times[NTIMES]){
	head = new Node{times[0],head};
	Node *curr = head;
	for(size_t i = 1;i < NTIMES;i++){
		Node *temp = new Node{times[i],nullptr};
		curr->next = temp;
		curr = curr->next;
	}
}

/********** Destructors **********/

// Destructor.  Deletes all nodes of the linked list.
List::~List(){
	if(!head) return;
	Node *prev = head;
	Node *curr = head;
	while(curr != nullptr){
		prev = curr;
		curr = curr->next;
		delete prev;
	}
}

/********** Methods **********/

// Rotates the linked list.  Takes the head, gets its value, and removes it.  Adds another empty element at the end.
size_t List::rotate(){
	Node *popped = head;
	head = head->next;
	size_t people = popped->people;
	delete popped;
	Node *curr = head;
	while(curr->next != nullptr)
		curr = curr->next;
	curr->next = new Node{0,nullptr};
	return people;
}

// Checks if a reservation can be made.
bool List::isFull(Booking *b){
	Node *curr = head;
	for(size_t i = 0;i < b->s_time;i++){
		if(!curr->next)
			return true;
		curr = curr->next;
	}
	for(size_t i = 0;i < b->book_len;i++){
		if(!curr->next || curr->people+b->num_people > b->capacity)
			return true;
		curr = curr->next;
	}
	return false;
}

// Makes a reservation.
bool List::reserve(Booking *b){
	if(!isFull(b)){
		Node *curr = head;
		for(size_t i = 0;i < b->s_time;i++){
			curr = curr->next;
		}
		for(size_t i = 0;i < b->book_len;i++){
			curr->people += b->num_people;
			curr = curr->next;
		}
		return true;
	}
	return false;
}

// Dumps contents to specified output stream.
void List::dump(std::ostream &os){
	for(Node *t = head;t != nullptr;t=t->next){
		os << t->people << std::endl;
	}
}
