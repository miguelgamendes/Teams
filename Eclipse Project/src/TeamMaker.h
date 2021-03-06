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
	TeamMaker(const std::string& filename);

	~TeamMaker();

	void loadData(const std::string& filename);
	const Team& calculateKruskal(std::vector<Skill> requiredSkills);

	void visualize();

	const Team& getTeam() const;

private:
	bool addEdge(const std::string& source, const std::string& dest, unsigned int weight);

	void keepEdgesWithSkill(std::vector<Skill>* requiredSkills, std::vector<Edge<Person> >* edges);

	bool checkSkill(std::vector<Skill>* requiredSkills, const Person& person);
	void removeSkill(std::vector<Skill>* requiredSkills, const Person& person);

private:
	Graph<Person>* persons;
	Team* team;
};

#endif
