#ifndef TEAM_H_
#define TEMA_H_

#include "Graph.h"
#include "Person.h"

#include <vector>
#include <ostream>

class Team
{
public:
	~Team();

	bool addMember(Vertex<Person>* member);
	void addEdge(const Edge<Person>& edge);

	const std::vector<Vertex<Person>*>& getMembers() const;
	const std::vector<Edge<Person> >& getEdges() const;

private:
	std::vector<Vertex<Person>*> members;
	std::vector<Edge<Person> > edges;
};

std::ostream& operator<<(std::ostream& os, const Team& team);

#endif
