#include "TeamMaker.h"

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
	persons->addEdge(susan, jack, 2);
	persons->addEdge(susan, thomas, 6);
	persons->addEdge(susan, jessie, 6);
	persons->addEdge(susan, john, 1);

	// Thomas Edges
	persons->addEdge(thomas, jack, 7);
	persons->addEdge(thomas, susan, 6);
	persons->addEdge(thomas, jessie, 4);
	persons->addEdge(thomas, john, 7);

	// Jessie Edges
	persons->addEdge(jessie, jack, 6);
	persons->addEdge(jessie, susan, 6);
	persons->addEdge(jessie, thomas, 4);
	persons->addEdge(jessie, john, 5);

	// John Edges
	persons->addEdge(john, jack, 1);
	persons->addEdge(john, susan, 1);
	persons->addEdge(john, thomas, 7);
	persons->addEdge(john, jessie, 5);


	vector<Skill> requiredSkills = vector<Skill>(4);
	requiredSkills[0] = Skill(Skill::IR);
	requiredSkills[1] = Skill(Skill::DB);
	requiredSkills[2] = Skill(Skill::AI);
	requiredSkills[3] = Skill(Skill::DM);

	calculatePrim(requiredSkills);
}

TeamMaker::~TeamMaker()
{
	if(persons)
	{
		delete persons;
		persons = NULL;
	}
}

vector<Vertex<Person>*> TeamMaker::calculatePrim(vector<Skill> requiredSkills)
{
	list<Person> buffer;
	vector<Vertex <Person>* > heap;
	vector<Vertex <Person>* > vertexSet = persons->getVertexSet();

	for (unsigned int v = 0; v < vertexSet.size(); v++)
	{
		Vertex<Person>* ver = vertexSet[v];

		ver->setPath(NULL);
		ver->setDist(INT_INFINITY);
		ver->setVisited(false);
	}

	Vertex<Person> * start = vertexSet[0];

	start->setDist(0);
	start->setPath(NULL);

	heap.push_back(start);
	push_heap(heap.begin(), heap.end(), vertex_greater_than<Person>());

	while (!heap.empty())
	{
		pop_heap(heap.begin(), heap.end(), vertex_greater_than<Person>());
		Vertex<Person> * u = heap.back();
		heap.pop_back();

		u->setVisited(true);

		vector<Edge<Person> > adj = u->getAdj();
		for (unsigned int a = 0; a < adj.size(); a++)
		{
			Vertex<Person> * v = adj[a].getDest();

			if (!v->getVisited())
			{
				if (v->getDist() == INT_INFINITY)
				{
					heap.push_back(v);
					push_heap(heap.begin(), heap.end(), vertex_greater_than<Person>());
				}

				if (v->getDist() > adj[a].getWeight())
				{
					v->setDist(adj[a].getWeight());

					if(checkAndRemoveSkill(&requiredSkills, v->getInfo()))
						v->setPath(u);
				}
			}
		}
	}

	vector<Vertex<Person>* > res = vector<Vertex<Person>* >(vertexSet.size());
	for(unsigned int v = 0; v < vertexSet.size(); v++)
	{
		res[v] = vertexSet[v];
		cout << res[v]->getInfo() << " <- ";
		if(res[v]->getPath() != NULL)
			cout << res[v]->getPath()->getInfo();
		cout << endl;
	}

	return res;
}

bool TeamMaker::checkAndRemoveSkill(vector<Skill>* requiredSkills, Person person)
{
	vector<Skill>::iterator skill;
	for(skill = requiredSkills->begin(); skill != requiredSkills->end(); skill++)
	{
		if(person.checkSkill(*skill))
		{
			requiredSkills->erase(skill);
			return true;
		}
	}

	return false;
}
