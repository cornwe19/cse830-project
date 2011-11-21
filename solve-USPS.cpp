#include <iostream>
#include "Graph.h"
#include <list>
#include <set>
#include <algorithm>

using namespace std;

unsigned GetNumberOfVerticesTouched( list<Node*> *inclusions, Graph* graph )
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
            break;
         }
      }
   }

   return touchedNodes.size();
}

bool ListIsValidInGraph( list<Node*> *inclusions, Graph* graph )
{
   return GetNumberOfVerticesTouched( inclusions, graph ) == (unsigned)graph->NumVertices();
}

unsigned _bestAnswerSize;
list<Node*> *_bestAnswerSoFar;

void SolveUSPS( Graph* graph, int nextNode, list<Node*> *includedNodes )
{
   if( includedNodes->size() < _bestAnswerSize )
   {
      if( nextNode < graph->NumVertices() )
      {
         list<Node*> *listIfIncluded = new list<Node*>( *includedNodes );

         listIfIncluded->push_back( graph->GetNode( nextNode ) );

         SolveUSPS( graph, nextNode + 1, listIfIncluded );

         SolveUSPS( graph, nextNode + 1, includedNodes );
      }
      else if ( ListIsValidInGraph( includedNodes, graph ) )
      {
         _bestAnswerSize = includedNodes->size();
         _bestAnswerSoFar = includedNodes;
      }
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

	cout << graph->NumVertices() - _bestAnswerSize << ": ";
	
	list<Node*> result( graph->NumVertices() );
	list<Node*>::iterator it, resultIt;
	
	resultIt = set_difference( graph->GetAllNodes(), graph->GetAllNodes() + graph->NumVertices(),
									_bestAnswerSoFar->begin(), _bestAnswerSoFar->end(), result.begin() );
	
	for (it = result.begin(); it != resultIt; it++ )
	{
		cout << (*it)->GetId() << " ";
	}

	cout << endl;

	delete graph;
}

