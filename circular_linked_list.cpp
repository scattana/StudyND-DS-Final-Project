// Michael Moynihan
// circular_linked_list.cpp

#include "booking.h"
#include "circular_linked_list.h"
#include <iostream>
#include <string>

List::List(){
	head = new Node{0,"",nullptr};
	Node *curr = head;
	for(int i = 1;i < NTIMES;i++){
		Node *temp = new Node{0,"",nullptr};
		curr->next = temp;
		curr = curr->next;
	}
}
List::List(size_t times[NTIMES],std::string names[NTIMES]){
	head = new Node{times[0],names[0],head};
	Node *curr = head;
	for(size_t i = 1;i < NTIMES;i++){
		Node *temp = new Node{times[i],names[i],nullptr};
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
	curr->next = new Node{0,"",nullptr};
	return people;
}
bool List::isFull(Booking *b){
	Node *curr = head;
	for(size_t i = 0;i < b->s_time;i++){
		if(!curr->next) return true;
		curr = curr->next;
	}
	for(size_t i = 0;i < b->book_len;i++){
		if(!curr->next || curr->people+b->num_people > b->capacity) return true;
		curr = curr->next;
	}
	return false;
}

bool List::reserve(Booking *b){
	if(!isFull(b)){
		Node *curr = head;
		for(size_t i = 0;i < b->s_time;i++)
			curr = curr->next;
		for(size_t i = 0;i < b->book_len;i++){
			curr->people += b->num_people;
			for(size_t j = 0;j < b->num_people;j++)
				curr->names = curr->names+","+b->f_name+" "+b->l_name;
		}
		return true;
	}
	return false;
}
void List::dump(std::ostream &os){
	for(Node *t = head;t != nullptr;t=t->next){
		os << t->people << ':' << t->names << std::endl;
	}
}
