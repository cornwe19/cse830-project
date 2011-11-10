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
	
private:
	int _numVertices;
	Node** _nodes;
};

