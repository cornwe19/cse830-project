#include "Graph.h"

#include <stdlib.h>
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
		_initialOrderNodes = NULL;
	}
}

void Graph::LoadFromFile( const char* fileName )
{
	fstream graphFile( fileName, fstream::in );

	unsigned numEdges;
	
	int edgeFrom, edgeTo;

	graphFile >> _numVertices >> numEdges;

	_nodes = new Node*[_numVertices];
	_initialOrderNodes = new Node*[_numVertices];
	
	// Allocate nodes
	for( int i = 0; i < _numVertices; i++ )
	{
		_nodes[i] = new Node( i );
		_initialOrderNodes[i] = _nodes[i];
	}

	while( graphFile.good() )
	{
	   char charEdgeFrom[10], charEdgeTo[10];
		graphFile.getline( charEdgeFrom, 10, ' ' );
		graphFile.getline( charEdgeTo, 10 );

		edgeFrom = atoi( charEdgeFrom );
		edgeTo = atoi( charEdgeTo );

		_nodes[edgeFrom]->AddNode( edgeTo );
		_nodes[edgeTo]->AddNode( edgeFrom );
	}

	sort( _nodes, _nodes + _numVertices, Node::NumVerticesDescending );

	// Turn this off in production
	//PrintNodes();
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
	return _initialOrderNodes;
}

// NOTE: Assumes nodes are sorted descending by edges on reading in
int Graph::GetMaxDegree( int nodeBeingProcessed /* = 0 */ )
{
   int maxDegree = 0;
   if( nodeBeingProcessed < _numVertices )
   {
      maxDegree = _nodes[nodeBeingProcessed]->GetAdjacentNodes()->size();
   }

   return maxDegree;
}

void Graph::PrintNodes()
{
	for ( int i = 0; i < _numVertices; i++ )
	{
		// Print node.
		cout << "Node #" << _nodes[i]->GetId() << ": [";
		list<int>* adjacentNodes = _nodes[i]->GetAdjacentNodes();
		list<int>::iterator nodeIt;

		for (nodeIt = adjacentNodes->begin(); nodeIt != adjacentNodes->end(); nodeIt++ )
		{
			cout << " " << *nodeIt;
		}

		cout << "]" << endl;
	}
}

