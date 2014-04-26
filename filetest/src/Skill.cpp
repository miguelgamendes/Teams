#include "Skill.h"

#include <string>

using namespace std;

Skill::Skill()
{
	skill = "";
}
Skill::Skill(std::string skill)
{
	this->skill = skill;
}

bool Skill::operator==(const Skill& other)
						{
	return this->skill == other.getType();
						}

void Skill::print(){
	std::cout << skill;
}

std::string Skill::getType() const
{
	return skill;
}

ostream& operator<<(ostream& os, const Skill& skill)
{
	return os << skill;
}
