#include "Person.h"

#include <stdarg.h>

using namespace std;

Person::Person(std::string name, skills_t skills[]) {

	this->name = name;
	this->skills = vector<skills_t>(skills);
}

bool Person::checkSkill(skills_t skill) {

	for(unsigned int i = 0; i < skills.size(); i++)
		if(skill == skills[i])
			return true;

	return false;
}
