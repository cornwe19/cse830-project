#pragma once

#include <list>

using namespace std;

// Simple node class tailored specifically for the solve-USPS problem
class Node
{
public:
	Node( int id );
	~Node();

	void AddNode( int nodeRef );
	list<int>* GetAdjacentNodes();
	
	int GetId();

	// Helper methods for sorting nodes in a graph
	static bool Compare( Node* a, Node* b );
	static bool NumVerticesDescending( Node* a, Node* b );

private:
	int _id;
	// Maintains a simple list of integers that represent node IDs in the graph
	list<int>* _adjacentNodes;	
};

