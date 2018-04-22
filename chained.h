

#pragma once

// chained.cpp: Separate Chaining Map
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

/*extern class Linked_List;

struct Node {
	int ,
	std::string second
}*/

typedef std::pair<std::string, std::string> Entry;
typedef std::hash<std::string>              StringHasher;
const Entry  NONE;
const double DEFAULT_LOAD_FACTOR = 0.9;
const size_t DEFAULT_TABLE_SIZE  = 1<<10;
const size_t DUMP_KEY = 0;
const size_t DUMP_VALUE = 1;
const size_t DUMP_KEY_VALUE = 2;
const size_t DUMP_VALUE_KEY = 3;

class ChainedMap{
	public:
		ChainedMap(size_t tableSize, double ldFactor){
			size = 0;
			nEntries = 0;
			loadFactor = ldFactor;
			resize(tableSize);
		}
		ChainedMap(){
			size = 0;
			nEntries = 0;
			loadFactor = DEFAULT_LOAD_FACTOR;
			resize(DEFAULT_TABLE_SIZE);
		}
		~ChainedMap(){
			delete[] table;
		}
		void            insert(const std::string &key, const std::string &value){
			StringHasher hfunc;
			table[hfunc(key)%size][key] = value;
			nEntries++;
			if((double) nEntries/size >= loadFactor)
				resize(size*2);
		};
		const Entry     search(const std::string &key){
			StringHasher hfunc;
			auto find = table[hfunc(key)%size].find(key);
			return find==table[hfunc(key)%size].end()?NONE:Entry(key,find->second);
		};
		void            dump(std::ostream &os, DumpFlag flag){
			for (size_t i = 0;i < size;i++) {
				for(auto it = table[i].begin();it != table[i].end();it++){
					switch (flag) {
						case DUMP_KEY:      os << it->first  << std::endl; break;
						case DUMP_VALUE:    os << it->second << std::endl; break;
						case DUMP_KEY_VALUE:os << it->first  << "\t" << it->second << std::endl; break;
						case DUMP_VALUE_KEY:os << it->second << "\t" << it->first  << std::endl; break;
					}
				}
			}
		};
	private:
		void            resize(const size_t new_size){
			std::map<std::string,std::string> *new_table = new std::map<std::string,std::string> [new_size];
			std::map<std::string,std::string> *old_table = table;
			table = new_table;
			size_t old_size = size;
			size = new_size;
			if(old_size > 0){
				for(size_t i = 0;i < old_size;i++)
					for(auto it = old_table[i].begin();it != old_table[i].end();it++)
						insert(it->first, it->second);
				delete[] old_table;
			}
		};
		size_t			size;
		size_t			nEntries;
		double			loadFactor;
		std::map<std::string, std::string> *table;
};
