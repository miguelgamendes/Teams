#ifndef TEAM_MAKER_H_
#define TEAM_MAKER_H_

#include "Graph.h"
#include "Person.h"
#include "Team.h"

#include <vector>

class TeamMaker
{
public:
	TeamMaker();
	~TeamMaker();

	Team* calculateKruskal(std::vector<Skill> requiredSkills);

private:
	void keepEdgesWithSkill(std::vector<Skill>* requiredSkills, std::vector<Edge<Person> >* edges);

	bool checkSkill(std::vector<Skill>* requiredSkills, const Person& person);
	void removeSkill(std::vector<Skill>* requiredSkills, const Person& person);

	bool isOnTeam(std::vector<Vertex<Person>*>* team, const Person& person);

private:
	Graph<Person>* persons;
};

#endif