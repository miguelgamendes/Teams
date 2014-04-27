#ifndef SKILL_H_
#define SKILL_H_

#include <string>
#include <ostream>

class Skill
{
public:
	Skill();
	Skill(std::string name);

	bool operator==(const Skill& other);
	const std::string& getName() const;

private:
	std::string name;
};

std::ostream& operator<<(std::ostream& os, const Skill& skill);

#endif /* SKILL_H_ */
