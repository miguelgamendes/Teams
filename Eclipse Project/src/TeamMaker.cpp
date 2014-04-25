#include "TeamMaker.h"

using namespace std;

TeamMaker::TeamMaker()
{
	persons = new Graph<Person>();

	persons->addVertex(new Person("Jack", ));
}

TeamMaker::~TeamMaker()
{
	if(persons)
	{
		delete persons;
		persons = NULL;
	}
}

vector<Vertex<Person>*> TeamMaker::calculatePrim(vector<Person::skills_t> requiredSkills) {

	list<Person> buffer;
	vector<Vertex <Person>* > heap;
	vector<Vertex <Person>* > vertexSet = persons->getVertexSet();

	for (unsigned int v = 0; v < vertexSet.size(); v++) {
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

	while (!heap.empty()) {

		pop_heap(heap.begin(), heap.end(), vertex_greater_than<Person>());
		Vertex<Person> * u = heap.back();
		heap.pop_back();

		u->setVisited(true);

		vector<Edge<Person> > adj = u->getAdj();
		for (unsigned int a = 0; a < adj.size(); a++) {
			Vertex<Person> * v = adj[a].getDest();

			if (!v->getVisited()) {

				if (v->getDist() == INT_INFINITY) {
					heap.push_back(v);
					push_heap(heap.begin(), heap.end(), vertex_greater_than<Person>());
				}

				// TODO Check skill here
				if (v->getDist() > adj[a].getWeight() && checkAndRemoveSkill(&requiredSkills, v->getInfo())) {
					v->setDist(adj[a].getWeight());
					v->setPath(u);
				}
			}
		}
	}

	vector<Vertex<Person>* > res;

	for (unsigned int v = 0; v < vertexSet.size(); v++) {
		res.push_back(vertexSet[v]);
	}

	return res;
}

bool TeamMaker::checkAndRemoveSkill(vector<Person::skills_t>* requiredSkills, Person person)
{
	vector<Person::skills_t>::iterator skill;
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
