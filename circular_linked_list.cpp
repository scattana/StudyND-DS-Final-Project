// Michael Moynihan
// circular_linked_list.cpp

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <map>

const size_t NTIMES = 48;
const char *DATA_FILE = "registration_data.txt";

class List {
	public:
		List(string room){};
		void load();
		size_t rotate();
		bool isFull(time_t t);
		size_t getSpace(time_t t);
		bool reserve(time_t t, size_t nPeople);
		void store();
	private:
		struct Node{
			size_t	people;
			std::map<std::string,std::string> names;
			Node 	*next;
		};
		Node *head;
}

List::List(size_t times[NTIMES],std::vector< std::map<std::string,std::string> > names){
	head->people = times[0];
	//head->names = 
	//for(size_t i = 0;i < 
/*	std::time_t t = std::time(0);
	std::tm *now = std::localtime(&t);
	start_time = t;
	ifstream data;
	data.open(DATA_FILE);
	string line;
	while(std::cin >> line){
		if(!line.substr(6,room.length()).compare(room)){
			break;
		}
	}
	if(!line){
		std::cout << "Error finding study room\n";
		exit(1);
	}
	size_t pos = 0;
	std::string delim = ";";

	// Delete space entry
	pos = line.find(delim);
	s.erase(0, pos+delim.length());

	// Get day entry
	pos = line.find(delim);
	size_t oldDay = (size_t) stoi(s.substr(4,pos));
	s.erase(0, pos+delim.length());

	// Get hour entry
	pos = line.find(delim);
	size_t oldHour = (size_t) stoi(s.substr(5,pos));
	s.erase(0, pos+delim.length());

	// Get capacity
	pos = line.find(delim);
	size_t capacity =(size_t) stoi(s.substr(9,pos));
	s.erase(0, pos+delim.length());

	// Figure out difference in time
	if(oldDay > start_time.mt_mday){ // If we changed month or day.
	time_t old_time;
	
	size_t diff_hours = 

	// Get reservations*/
}
