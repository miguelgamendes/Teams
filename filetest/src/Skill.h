#ifndef SKILL_H_
#define SKILL_H_

#include <iostream>
#include <string>
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
	Skill(std::string skill);

	bool operator==(const Skill& other);

	void print();
	std::string getType() const;

private:
	std::string skill;
};

std::ostream& operator<<(std::ostream& os, const Skill& skill);

#endif /* SKILL_H_ */
