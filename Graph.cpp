#include "Graph.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Graph::Graph()
{
}

Graph::~Graph()
{
	if( _nodes != NULL )
	{
		delete [] _nodes;
		_nodes = NULL;
	}
}

void Graph::LoadFromFile( const char* fileName )
{
	fstream graphFile( fileName, fstream::in );

	unsigned numEdges;
	
	int edgeFrom, edgeTo;

	graphFile >> _numVertices >> numEdges;

	_nodes = new Node*[_numVertices];
	
	// Allocate nodes
	for( int i = 0; i < _numVertices; i++ )
	{
		_nodes[i] = new Node( i );
	}

	while( graphFile.good() )
	{
		graphFile >> edgeFrom;
		graphFile >> edgeTo;

		_nodes[edgeFrom]->AddNode( edgeTo );
		_nodes[edgeTo]->AddNode( edgeFrom );
	}

	sort( _nodes, _nodes + _numVertices, Node::NumVerticesDescending );

	// Turn this off in production
	for ( int i = 0; i < _numVertices; i++ )
	{
		//cout << i << endl;
		
		// Print node.
		cout << "Node #" << _nodes[i]->GetId() << ": [";
		list<int> adjacentNodes = _nodes[i]->GetAdjacentNodes();
		list<int>::iterator nodeIt;

		for (nodeIt = adjacentNodes.begin(); nodeIt != adjacentNodes.end(); nodeIt++ )
		{
			cout << " " << *nodeIt;
		}

		cout << "]" << endl;
	}
	// Turn this off in production
}

Node* Graph::GetNode( int index )
{
	return _nodes[index];
}

int Graph::NumVertices()
{
	return _numVertices;
}

Node** Graph::GetAllNodes()
{
	return _nodes;
}
