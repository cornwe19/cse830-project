#include <iostream>
#include "Graph.h"
#include <list>
#include <set>

using namespace std;

bool ListIsValidInGraph( list<Node*> *inclusions, Graph* graph )
{
	set<int> touchedNodes;
	
	list<Node*>::iterator it;
	for( it = inclusions->begin(); it != inclusions->end(); it++ )
	{
		touchedNodes.insert( (*it)->GetId() );
		
		list<int> current = (*it)->GetAdjacentNodes();
		list<int>::iterator edgeIt;
		for( edgeIt = current.begin(); edgeIt != current.end(); edgeIt++ )
		{
			touchedNodes.insert( *edgeIt );
			if( touchedNodes.size() == (unsigned)graph->NumVertices() )
			{
				return true;
			}
		}
	}

	return false;
}

unsigned _bestAnswerSize;
list<Node*> *_bestAnswerSoFar;

void SolveUSPS( Graph* graph, int nextNode, list<Node*> *includedNodes )
{
   if( nextNode < graph->NumVertices() )
   {
		list<Node*> *listIfIncluded = new list<Node*>( *includedNodes );

		listIfIncluded->push_back( graph->GetNode( nextNode ) );
	 
		SolveUSPS( graph, nextNode + 1, listIfIncluded );

		SolveUSPS( graph, nextNode + 1, includedNodes );
	} 
	else if( ListIsValidInGraph( includedNodes, graph ) && includedNodes->size() < _bestAnswerSize )
	{
		_bestAnswerSize = includedNodes->size();
		_bestAnswerSoFar = includedNodes;
	}
}

int main( int argc, char** argv )
{
	char* fileName = NULL; 
	if ( argc < 2 )
	{
		cerr << "Usage: " << argv[0] << " <test-file> " << endl;
		return -1;
	}
	
	fileName = argv[1];

	Graph* graph = new Graph();
	graph->LoadFromFile( fileName );

	_bestAnswerSize = graph->NumVertices();

	SolveUSPS( graph, 0, new list<Node*>() );

	list<Node*>::iterator it;
	for ( it = _bestAnswerSoFar->begin(); it != _bestAnswerSoFar->end(); it++ )
	{
		cout << (*it)->GetId() << ", ";
	}

	cout << endl;

	delete graph;
}

