#include "Team.h"

#include "graphviewer.h"
#include <algorithm>

struct vertex_person_equals
{
	Vertex<Person>* v;

	vertex_person_equals(Vertex<Person>* v) : v(v) {}

	bool operator()(Vertex<Person>* v)
	{
		return this->v->getInfo() == v->getInfo();
	}
};

Team::~Team()
{
	vector<Vertex<Person>*>::iterator member;
	for (member = members.begin(); member != members.end(); member++)
	{
		if (*member)
		{
			delete *member;
			*member = 0;
		}
	}
}

bool Team::addMember(Vertex<Person>* member)
{
	vector<Vertex<Person>*>::const_iterator location;
	location = find_if(members.begin(), members.end(), vertex_person_equals(member));

	if (location != members.end())
		return false;

	Vertex<Person>* newMember = new Vertex<Person>(*member);
	members.push_back(newMember);

	return true;
}

void Team::addEdge(const Edge<Person>& edge)
{
	Vertex<Person>* source = edge.getSource();
	Vertex<Person>* dest = edge.getDest();

	addMember(source);
	addMember(dest);

	edges.push_back(edge);
}

void Team::visualize()
{
	GraphViewer* gv = new GraphViewer (600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<Person>*>::const_iterator member;
	for(member = members.begin(); member != members.end(); member++)
	{
		Person person = (*member)->getInfo();

		gv->addNode(person);
		gv->setVertexLabel(person.getID(), (string)person);
		cout << (string)person;
	}

	for(unsigned int id = 0; id < edges.size(); id++)
	{
		unsigned int v1 = edges[id].getSource()->getInfo().getID();
		unsigned int v2 = edges[id].getDest()->getInfo().getID();

		gv->addEdge(id, v1, v2, EdgeType::UNDIRECTED);
		gv->setEdgeWeight(id, edges[id].getWeight());
	}

	gv->rearrange();
}

const vector<Vertex<Person>*>& Team::getMembers() const
{
	return members;
}
const vector<Edge<Person> >& Team::getEdges() const
{
	return edges;
}

ostream& operator<<(ostream& os, const Team& team)
{
	vector<Vertex<Person>*>::const_iterator member;
	vector<Edge<Person> >::const_iterator edge;

	vector<Vertex<Person>*> members = team.getMembers();
	vector<Edge<Person> > edges = team.getEdges();

	os << endl << "Vertices:" << endl;
	for (member = members.begin(); member != members.end(); member++)
		os << "\t " << (*member)->getInfo() << endl;

	os << endl << "Edges:" << endl;
	for (edge = edges.begin(); edge != edges.end(); edge++)
		os << "\t " << edge->getWeight() << "\t " << edge->getSource()->getInfo() << " <-> " << edge->getDest()->getInfo() << endl;

	os << endl << endl;

	return os;
}
