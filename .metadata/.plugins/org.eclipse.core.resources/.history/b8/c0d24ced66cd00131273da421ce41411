#include "Skill.h"

#include <string>

using namespace std;

Skill::Skill()
{
	skill = none;
}
Skill::Skill(type_t skill)
{
	this->skill = skill;
}

bool Skill::operator==(const Skill& other)
						{
	return this->skill == other.getType();
						}

Skill::type_t Skill::getType() const
{
	return skill;
}

ostream& operator<<(ostream& os, const Skill& skill)
{
	std::string skillsList[] =
	{
			"none", "AI", "DB", "DM", "IR"
	};

	return os << skillsList[skill.getType()];
}
