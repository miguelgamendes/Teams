#include "Skill.h"

#include <string>

using namespace std;

Skill::Skill()
{
}
Skill::Skill(string name)
{
	this->name = name;
}

bool Skill::operator==(const Skill& other)
{
	return this->name == other.getName();
}

const string& Skill::getName() const
{
	return name;
}

ostream& operator<<(ostream& os, const Skill& skill)
{
	return os << skill.getName();
}
