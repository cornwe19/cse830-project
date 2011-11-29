#pragma once

#include <list>

using namespace std;

class Node
{
public:
	Node( int id );
	~Node();

	void AddNode( int nodeRef );
	list<int>* GetAdjacentNodes();
	
	int GetId();
	bool IsPreIncluded() { return _preIncluded; }
	void PreInclude() { _preIncluded = true; }

	static bool NumVerticesDescending( Node* a, Node* b );

private:
   bool _preIncluded;
	int _id;
	list<int>* _adjacentNodes;	
};

