#ifndef SKILL_H_
#define SKILL_H_

#include <ostream>

class Skill
{
public:
	enum type_t
	{
		none = 0,
		AI = 1,
		DB = 2,
		DM = 3,
		IR = 4
	};

public:
	Skill();
	Skill(type_t skill);

	bool operator==(const Skill& other);

	type_t getType() const;

private:
	type_t skill;
};

std::ostream& operator<<(std::ostream& os, const Skill& skill);

#endif /* SKILL_H_ */
