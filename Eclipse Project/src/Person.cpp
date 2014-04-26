#include "Person.h"

#include <stdarg.h>

using namespace std;

Person::Person(std::string name)
{
	this->name = name;
}

void Person::addSkill(Skill skill)
{
	skills.push_back(skill);
}

bool Person::operator==(const Person& other) const
{
	return this->name == other.getName();
}

string Person::getName() const
{
	return name;
}

const vector<Skill>& Person::getSkills() const
{
	return skills;
}

bool Person::checkSkill(Skill skill) const
{

	for(unsigned int i = 0; i < skills.size(); i++)
		if(skill == skills[i])
			return true;

	return false;
}

ostream& operator<<(std::ostream& os, const Person& person)
{
	os << person.getName() << ": ";

	vector<Skill> skills = person.getSkills();
	Person::SkillIt skill;
	for(skill = skills.begin(); skill != skills.end(); skill++)
		os << *skill << " ";

	return os;
}
