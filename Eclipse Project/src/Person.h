#ifndef PERSON_H_
#define PERSON_H_

#include <vector>
#include <string>

class Person
{
public:
	enum skills_t
	{
		none = 0,
		IR = 1,
		DB = 2,
		AI = 3,
		DM = 4
	};


public:
	Person(std::string name, skills_t skills[]);

	bool checkSkill(skills_t skill);

private:
	std::string name;
	std::vector<skills_t> skills;
};


#endif /* PERSON_H_ */
