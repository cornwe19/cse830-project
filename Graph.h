#pragma once

#include <list>

#include "Node.h"

using namespace std;

// Simple graph class tailored specifically for the solve-USPS problem
class Graph
{
public:
	Graph();
	~Graph();

	void LoadFromFile( const char* fileName );
	Node* GetNode( int index );
	int NumVertices();
	Node** GetAllNodes();
	int GetMaxDegree( int numNodesProcessed = 0 );
	
private:
	int _numVertices;
	Node** _nodes;
	Node** _initialOrderNodes;

	// **For debugging purposes only**
	void PrintNodes();
};

