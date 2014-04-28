#ifndef PERSON_H_
#define PERSON_H_

#include "Skill.h"

#include <iostream>
#include <vector>
#include <string>
#include <ostream>

class Person
{
public:
	typedef std::vector<Skill>::const_iterator SkillIt;

public:
	Person(std::string name);
	Person(std::string name, std::vector<Skill> skills);

	void addSkill(Skill skill);

	bool operator==(const Person& other) const;
	operator std::string() const;
	operator int() const;

	unsigned int getID() const;
	std::string getName() const;
	const std::vector<Skill>& getSkills() const;

	bool checkSkill(Skill skill) const;

private:
	static unsigned int nPersons;

	unsigned int id;
	std::string name;
	std::vector<Skill> skills;
};

std::ostream& operator<<(std::ostream& os, const Person& person);


#endif /* PERSON_H_ */
