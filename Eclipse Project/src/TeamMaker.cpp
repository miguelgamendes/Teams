#include "TeamMaker.h"

#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include "graphviewer.h"

using namespace std;

TeamMaker::TeamMaker()
{
	// Constructor for testing purposes:
	persons = new Graph<Person>();
	Skill AI("AI");
	Skill DB("DB");
	Skill DM("DM");
	Skill IR("IR");

	Person jack = Person("Jack");
	jack.addSkill(IR);
	persons->addVertex(jack);

	Person susan = Person("Susan");
	susan.addSkill(DB);
	persons->addVertex(susan);

	Person thomas = Person("Thomas");
	thomas.addSkill(AI);
	thomas.addSkill(DB);
	thomas.addSkill(DM);
	persons->addVertex(thomas);

	Person jessie = Person("Jessie");
	jessie.addSkill(DB);
	persons->addVertex(jessie);

	Person john = Person("John");
	john.addSkill(AI);
	john.addSkill(DM);
	persons->addVertex(john);


	// Jack Edges
	persons->addEdge(jack, susan, 2);
	persons->addEdge(jack, thomas, 7);
	persons->addEdge(jack, jessie, 6);
	persons->addEdge(jack, john, 1);

	// Susan Edges
	persons->addEdge(susan, thomas, 6);
	persons->addEdge(susan, jessie, 6);
	persons->addEdge(susan, john, 1);

	// Thomas Edges
	persons->addEdge(thomas, jessie, 4);
	persons->addEdge(thomas, john, 7);

	// Jessie Edges
	persons->addEdge(jessie, john, 5);

	vector<Skill> requiredSkills = vector<Skill>(4);
	requiredSkills[0] = AI;
	requiredSkills[1] = DB;
	requiredSkills[2] = DM;
	requiredSkills[3] = IR;

	calculateKruskal(requiredSkills);
}

TeamMaker::TeamMaker(const string& filename)
{
	loadData(filename);
}

TeamMaker::~TeamMaker()
{
	if (persons)
	{
		delete persons;
		persons = NULL;
	}

	if(team)
	{
		delete team;
		team = NULL;
	}
}

void TeamMaker::loadData(const string& filename)
{
	if (persons)
		delete persons;

	persons = new Graph<Person>();

	ifstream inputFile(filename.c_str());

	cout << "Checking file..." << endl;

	if (!inputFile){
		cerr << "ERROR: File not found." << endl;
		exit(1);
	}

	cout << "Loading file..." << endl;

	string line;

	while (!inputFile.eof()){
		string name;
		vector<Skill> skills;
		unsigned int lineIndex = 0;
		getline(inputFile, line);

		cout << "Getting name..." << endl;
		//get name
		for (unsigned int i = 0; i < line.size(); i++){
			if (line.at(i) == ';'){
				name = line.substr(0, i);
				lineIndex = i + 1;
				break;
			}
		}

		cout << "Getting skills..." << std::endl;
		//get skills
		for (unsigned int i = lineIndex; i < line.size(); i++){
			//add skill at ';'
			if (line.at(i) == ';'){
				skills.push_back(Skill(line.substr(lineIndex, i - lineIndex)));
				lineIndex = i + 1;
			}
			//add last skill on line
			if (i == line.size() - 1){
				skills.push_back(Skill(line.substr(lineIndex, i - lineIndex + 1)));
			}
		}

		cout << "Adding person..." << endl;

		persons->addVertex(Person(name, skills));
	}

	cout << "File's loaded" << endl;
}

const Team& TeamMaker::calculateKruskal(std::vector<Skill> requiredSkills)
{
	// Creates the team:
	Team* team = new Team();

	// Gets all the graph edges:
	vector<Edge<Person> > edgeHeap = persons->getEdges();

	while (!requiredSkills.empty())
	{
		// Removes all the edges with persons which do not meet the required skills:
		keepEdgesWithSkill(&requiredSkills, &edgeHeap);

		// Sorts elements in a heap after the removal:
		make_heap(edgeHeap.begin(), edgeHeap.end(), edge_greater_than<Person>());

		// Gets the edge with less weight and removes it from the heap:
		pop_heap(edgeHeap.begin(), edgeHeap.end(), edge_greater_than<Person>());
		Edge<Person> nextEdge = edgeHeap.back();
		edgeHeap.pop_back();

		// Gets the source of the edge:
		Vertex<Person>* source = nextEdge.getSource();
		if (!source->getVisited())
		{
			// Removes the person's skills from the vector of skills:
			removeSkill(&requiredSkills, source->getInfo());

			// Flagging the person, so that we know one is already on the team:
			source->setVisited(true);
		}

		// Gets the destination of the edge:
		Vertex<Person>* dest = nextEdge.getDest();
		if (!dest->getVisited())
		{
			// Removes the person's skills from the vector of skills:
			removeSkill(&requiredSkills, dest->getInfo());

			// Flagging the person, so that we know one is already on the team:
			dest->setVisited(true);
		}

		// Adds both persons to the team and links them:
		team->addEdge(nextEdge);
	}

	this->team = team;
	return *team;
}

bool TeamMaker::addEdge(const std::string& source, const std::string& dest, unsigned int weight)
{
	vector<Vertex<Person>*>::const_iterator vertex;
	Vertex<Person>* vSource = 0;
	Vertex<Person>* vDest = 0;

	vector<Vertex<Person>*> vertexSet = persons->getVertexSet();

	// Searching for vSource
	for(vertex = vertexSet.begin(); vertex != vertexSet.end() && !vSource; vertex++)
	{
		if((*vertex)->getInfo().getName() == source)
			vSource = *vertex;
	}

	// Searching for vDest
	for(vertex = vertexSet.begin(); vertex != vertexSet.end() && !vDest; vertex++)
	{
		if((*vertex)->getInfo().getName() == dest)
			vDest = *vertex;
	}

	// If one or both of the Vertex weren't found:
	if(!vSource || !vDest)
		return false;

	persons->addEdge(vSource->getInfo(), vDest->getInfo(), weight);

	return true;
}

void TeamMaker::visualize()
{
	vector<Vertex<Person>*>::const_iterator vertex;

	vector<Vertex<Person>*> vertexSet = persons->getVertexSet();
	vector<Edge<Person> > edges = persons->getEdges();

	GraphViewer* gv = new GraphViewer (600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	for(vertex = vertexSet.begin(); vertex != vertexSet.end(); vertex++)
	{
		Person person = (*vertex)->getInfo();

		gv->addNode(person.getID());
		gv->setVertexLabel(person.getID(), (string)person);
	}

	for(unsigned int id = 0; id < edges.size(); id++)
	{
		unsigned int v1 = edges[id].getSource()->getInfo().getID();
		unsigned int v2 = edges[id].getDest()->getInfo().getID();

		gv->addEdge(id, v1, v2, EdgeType::UNDIRECTED);
		gv->setEdgeWeight(id, edges[id].getWeight());
	}

	gv->rearrange();

	// Animation

}

const Team& TeamMaker::getTeam() const
{
	return *team;
}

struct edgeWithoutSkill
{
	const vector<Skill>& skills;

	edgeWithoutSkill(const vector<Skill>& skills) : skills(skills) {}

	/**
	 * Checks for edges to be removed.
	 *
	 * All the edges in which both persons do not have any of the required skills are removed.
	 * It keeps the edges where one of the vertices is a member, and the other a potential
	 * skilled member.
	 */
	bool operator()(const Edge<Person>& edge)
	{
		// Gets the source and destination of the edge:
		Person source = edge.getSource()->getInfo();
		Person dest = edge.getDest()->getInfo();

		// Finds out if the source or destination are members of the team:
		bool sourceSkillFound = edge.getSource()->getVisited();
		bool destSkillFound = edge.getDest()->getVisited();

		// If both persons already do part of the team:
		if(sourceSkillFound && destSkillFound)
			return true;

		// Searches for a skilled person:
		vector<Skill>::const_iterator skill;
		for (skill = skills.begin(); skill != skills.end() && !sourceSkillFound; skill++)
		{
			// If the source has a required skill:
			if (source.checkSkill(*skill))
				sourceSkillFound = true;
		}

		for (skill = skills.begin(); skill != skills.end() && !destSkillFound; skill++)
		{
			// If the destination has a required skill:
			if (dest.checkSkill(*skill))
				destSkillFound = true;
		}

		// If both source and dest are flagged as true, then the edge is not removed:
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
	// Checking for a skill in the person:
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
