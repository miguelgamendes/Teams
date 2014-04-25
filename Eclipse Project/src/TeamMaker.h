#include "Graph.h"
#include "Person.h"

#include <vector>

class TeamMaker
{
public:
	TeamMaker();
	~TeamMaker();

	std::vector<Vertex<Person>*> calculatePrim(std::vector<Person::skills_t> requiredSkills);

private:
	bool checkAndRemoveSkill(std::vector<Person::skills_t>* requiredSkills, Person person);

private:
	Graph<Person>* persons;
};
