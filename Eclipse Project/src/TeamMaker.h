#include "Graph.h"
#include "Person.h"

#include <vector>

class TeamMaker
{
public:
	TeamMaker();
	~TeamMaker();

	std::vector<Vertex<Person>*> calculatePrim(std::vector<Skill> requiredSkills);
	std::vector<Vertex<Person>*> calculateKruskal(std::vector<Skill> requiredSkills);

private:
	bool checkAndRemoveSkill(std::vector<Skill>* requiredSkills, Person person);

private:
	Graph<Person>* persons;
};
