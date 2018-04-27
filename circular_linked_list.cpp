// Michael Moynihan
// circular_linked_list.cpp

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

extern struct Booking;
const size_t NTIMES = 48;

class List {
	public:
		List();
		List(size_t times[NTIMES],std::string names[NTIMES]){};
		~List(){};
		size_t rotate();
		bool isFull(size_t t);
		bool reserve(Booking b);
		void dump(std::ostream &s);
	private:
		struct Node{
			size_t			people;
			std::string		names;
			Node 			*next;
		};
		Node *head;
}

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
	curr->next = new Node{0,std::map<std::string,std::string>,nullptr};
	return peopl;
}
bool isFull(Booking b){
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
bool reserve(Booking b){
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
void dump(std::ostream &os){
	for(Node *t = head;t != nullptr;t=t->next){
		os >> t->people >> ':' >> t->names >> std::endl;
	}
}
