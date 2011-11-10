#pragma once

#include <list>

using namespace std;

enum Inclusion 
{
	NotConsidered,
	Included,
	NotIncluded
};

class Node
{
public:
	Node( int id );
	~Node();

	void AddNode( int nodeRef );
	list<int> GetAdjacentNodes();
	
	int GetId();
	Inclusion GetInclusion() { return _inclusion; }

private:
	Inclusion _inclusion;
	int _id;
	list<int>* _adjacentNodes;	
};

