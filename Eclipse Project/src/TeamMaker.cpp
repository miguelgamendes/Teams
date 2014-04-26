#include "TeamMaker.h"

#include <algorithm>
#include <conio.h>

using namespace std;

TeamMaker::TeamMaker()
{
	persons = new Graph<Person>();

	Person jack = Person("Jack");
	jack.addSkill(Skill(Skill::IR));
	persons->addVertex(jack);

	Person susan = Person("Susan");
	susan.addSkill(Skill(Skill::DB));
	persons->addVertex(susan);

	Person thomas = Person("Thomas");
	thomas.addSkill(Skill(Skill::AI));
	thomas.addSkill(Skill(Skill::DB));
	thomas.addSkill(Skill(Skill::DM));
	persons->addVertex(thomas);

	Person jessie = Person("Jessie");
	jessie.addSkill(Skill(Skill::DB));
	persons->addVertex(jessie);

	Person john = Person("John");
	john.addSkill(Skill(Skill::AI));
	john.addSkill(Skill(Skill::DM));
	persons->addVertex(john);


	// Jack Edges
	persons->addEdge(jack, susan, 2);
	persons->addEdge(jack, thomas, 7);
	persons->addEdge(jack, jessie, 6);
	persons->addEdge(jack, john, 1);

	// Susan Edges
	//persons->addEdge(susan, jack, 2);
	persons->addEdge(susan, thomas, 6);
	persons->addEdge(susan, jessie, 6);
	persons->addEdge(susan, john, 1);

	// Thomas Edges
	//persons->addEdge(thomas, jack, 7);
	//persons->addEdge(thomas, susan, 6);
	persons->addEdge(thomas, jessie, 4);
	persons->addEdge(thomas, john, 7);

	// Jessie Edges
	//persons->addEdge(jessie, jack, 6);
	//persons->addEdge(jessie, susan, 6);
	//persons->addEdge(jessie, thomas, 4);
	persons->addEdge(jessie, john, 5);

	// John Edges
	/*persons->addEdge(john, jack, 1);
	persons->addEdge(john, susan, 1);
	persons->addEdge(john, thomas, 7);
	persons->addEdge(john, jessie, 5);*/


	vector<Skill> requiredSkills = vector<Skill>(4);
	requiredSkills[0] = Skill(Skill::IR);
	requiredSkills[1] = Skill(Skill::DB);
	requiredSkills[2] = Skill(Skill::AI);
	requiredSkills[3] = Skill(Skill::DM);

	/*vector<Vertex<Person>*> res = persons->calculatePrim();
	for(unsigned int v = 0; v < res.size(); v++)
	{
	cout << res[v]->getInfo() << " <- ";
	if(res[v]->getPath() != NULL)
	cout << res[v]->getPath()->getInfo();
	cout << endl;
	}*/

	Team* team = calculateKruskal(requiredSkills);

	cout << *team;
	_getch();

	delete team;
}

TeamMaker::~TeamMaker()
{
	if (persons)
	{
		delete persons;
		persons = NULL;
	}
}

Team* TeamMaker::calculateKruskal(std::vector<Skill> requiredSkills)
{
	Team* team = new Team();
	vector<Edge<Person> > edgeHeap = persons->getEdges();

	while (!requiredSkills.empty())
	{
		keepEdgesWithSkill(&requiredSkills, &edgeHeap);

		make_heap(edgeHeap.begin(), edgeHeap.end(), edge_greater_than<Person>());
		pop_heap(edgeHeap.begin(), edgeHeap.end(), edge_greater_than<Person>());
		Edge<Person> nextEdge = edgeHeap.back();
		edgeHeap.pop_back();

		Vertex<Person>* source = nextEdge.getSource();
		if (!source->getVisited())
		{
			removeSkill(&requiredSkills, source->getInfo());
			source->setVisited(true);
		}

		Vertex<Person>* dest = nextEdge.getDest();
		if (!dest->getVisited())
		{
			removeSkill(&requiredSkills, dest->getInfo());
			dest->setVisited(true);
			dest->setPath(source);
		}

		team->addEdge(nextEdge);
	}

	return team;
}

struct edgeWithoutSkill
{
	const vector<Skill>& skills;

	edgeWithoutSkill(const vector<Skill>& skills) : skills(skills) {}

	bool operator()(const Edge<Person>& edge)
	{
		Person source = edge.getSource()->getInfo();
		Person dest = edge.getDest()->getInfo();
		bool sourceSkillFound = edge.getSource()->getVisited();
		bool destSkillFound = edge.getDest()->getVisited();

		vector<Skill>::const_iterator skill;
		for (skill = skills.begin(); skill != skills.end() && !sourceSkillFound; skill++)
		{
			if (source.checkSkill(*skill))
				sourceSkillFound = true;
		}

		for (skill = skills.begin(); skill != skills.end() && !destSkillFound; skill++)
		{
			if (dest.checkSkill(*skill))
				destSkillFound = true;
		}

		return !(sourceSkillFound && destSkillFound);
	}
};

void TeamMaker::keepEdgesWithSkill(vector<Skill>* requiredSkills, vector<Edge<Person> >* edges)
{
	vector<Edge<Person> >::iterator edgeEnd;

	edgeEnd = remove_if(edges->begin(), edges->end(), edgeWithoutSkill(*requiredSkills));
	edges->erase(edgeEnd, edges->end());
}

bool TeamMaker::checkSkill(vector<Skill>* requiredSkills, const Person& person)
{
	vector<Skill>::iterator skill;
	for (skill = requiredSkills->begin(); skill != requiredSkills->end(); skill++)
	if (person.checkSkill(*skill))
		return true;

	return false;
}

void TeamMaker::removeSkill(vector<Skill>* requiredSkills, const Person& person)
{
	vector<Skill>::iterator skill;
	vector<Skill>::iterator skillEnd;
	vector<Skill> skills = person.getSkills();
	for (skill = skills.begin(); skill != skills.end(); skill++)
		skillEnd = remove(requiredSkills->begin(), requiredSkills->end(), *skill);

	requiredSkills->erase(skillEnd, requiredSkills->end());
}

bool TeamMaker::isOnTeam(std::vector<Vertex<Person>*>* team, const Person& person)
{
	vector<Vertex<Person>*>::iterator member;
	for (member = team->begin(); member != team->end(); member++)
	if ((*member)->getInfo() == person)
		return true;

	return false;
}
