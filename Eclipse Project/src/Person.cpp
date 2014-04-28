#include "Person.h"

#include <sstream>
#include <stdarg.h>

using namespace std;

unsigned int Person::nPersons = 0;

Person::Person(std::string name)
{
	this->name = name;
	this->nPersons++;
	this->id = this->nPersons;
}

Person::Person(std::string name, std::vector<Skill> skills) : name(name){
	for(unsigned int i = 0; i < skills.size(); i++){
		(this->skills).push_back(skills[i]);
	}

	this->nPersons++;
	this->id = this->nPersons;
}

void Person::addSkill(Skill skill)
{
	skills.push_back(skill);
}

bool Person::operator==(const Person& other) const
{
	return this->name == other.getName();
}

unsigned int Person::getID() const
{
	return id;
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

Person::operator string() const
{
	stringstream ss;
	ss << *this;
	return ss.str();
}
Person::operator int() const
{
	return id;
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
