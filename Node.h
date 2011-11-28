#pragma once

#include <list>

using namespace std;

enum Consideration
{
	NotConsidered,
	Considered
};

class Node
{
public:
	Node( int id );
	~Node();

	void AddNode( int nodeRef );
	list<int>* GetAdjacentNodes();
	
	int GetId();
	Consideration GetConsideration() { return _consideration; }
	void SetConsideration( Consideration consideration ) { _consideration = consideration; }

	static bool NumVerticesDescending( Node* a, Node* b );

private:
   Consideration _consideration;
	int _id;
	list<int>* _adjacentNodes;	
};

