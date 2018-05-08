// Michael Moynihan
// circular_linked_list.cpp

#include "booking.h"
#include "circular_linked_list.h"
#include <iostream>
#include <string>

List::List(){
	//std::cout << "In list constructor\n";
	//delete[] tempArr;
	//int * c = new int;
	head = new Node{0,nullptr};
	Node *curr = head;
	for(int i = 1;i < NTIMES;i++){
		Node *temp = new Node{0,nullptr};
		curr->next = temp;
		curr = curr->next;
	}
	//head->people = 1; head->names = "default";
}
List::List(size_t times[NTIMES]){
	head = new Node{times[0],head};
	Node *curr = head;
	for(size_t i = 1;i < NTIMES;i++){
		Node *temp = new Node{times[i],nullptr};
		curr->next = temp;
		curr = curr->next;
	}
}
List::~List(){
	//std::cout << "In list deconstructor\n";
	if(!head) return;
	Node *prev = head;
	Node *curr = head;
	while(curr != nullptr){
		prev = curr;
		curr = curr->next;
		delete prev;
	}
}
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
bool List::isFull(Booking *b){
	Node *curr = head;
	for(size_t i = 0;i < b->s_time;i++){
		if(!curr->next) {
			//std::cout << "Trying to schedule more than 48 hours from now\n";
			return true;
		}
		curr = curr->next;
	}
	for(size_t i = 0;i < b->book_len;i++){
		if(!curr->next || curr->people+b->num_people > b->capacity) {
			/*if(!curr->next)
				std::cout << "Booking ends too late\n";
			else
				std::cout << "Room too full!\n";
			*/
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool List::reserve(Booking *b){
	//std::cout << "Reserving space in room " << b->location << std::endl;
	//dump(std::cout);
	if(!isFull(b)){
		Node *curr = head;
		//std::cout << "Starting time: " << b->s_time << std::endl;
		for(size_t i = 0;i < b->s_time;i++){
			curr = curr->next;
		}
		for(size_t i = 0;i < b->book_len;i++){
			curr->people += b->num_people;
			curr = curr->next;
		}
		return true;
	}
	else {
		//std::cout << "Calendar's full!\n";
	}
	return false;
}
void List::dump(std::ostream &os){
	for(Node *t = head;t != nullptr;t=t->next){
		os << t->people << std::endl;
	}
}
