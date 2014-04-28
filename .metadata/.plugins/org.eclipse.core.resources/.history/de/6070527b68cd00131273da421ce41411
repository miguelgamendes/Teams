#include <iostream>
#include <vector>
#include "Person.h"
#include "FileOps.h"

int main(){
	std::cout << "Program started." << std::endl;

	std::vector<Person> people;
	loadPeople(people);

	std::cout << "OUTPUT:" << std::endl;
	for(unsigned int i = 0; i < people.size(); i++){
		std::cout << i << std::endl;
		people[i].print();
	}

	return 0;
}
