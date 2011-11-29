#pragma once

#include <list>

#include "Node.h"

using namespace std;

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
	void RemoveNode( int index );
	Node* GetNodeWithId( int id ) { return _initialOrderNodes[id]; }
	
private:
	int _numVertices;
	Node** _nodes;
	Node** _initialOrderNodes;

	void PrintNodes();
};

