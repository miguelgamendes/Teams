#include "Person.h"

bool Person::checkSkill(skills_t skill) {
	return false;
}

bool Person::operator==(skills_t skill)
{
	for(unsigned int i = 0; i < skills.size(); i++)
		if(skill == skills[i])
			return true;

	return false;
}
