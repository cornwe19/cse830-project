#include <iostream>
#include "Graph.h"
#include <list>
#include <set>
#include <algorithm>

using namespace std;

void AddVerticesTouchedToSet( int currentNode, set<int> *touchedNodes, Graph* graph )
{
   Node* current = graph->GetNode( currentNode );

   touchedNodes->insert(current->GetId());

   list<int>::iterator edgeIt;
   for( edgeIt = current->GetAdjacentNodes()->begin(); edgeIt != current->GetAdjacentNodes()->end(); edgeIt++ )
   {
      touchedNodes->insert( *edgeIt );
   }
}

bool ListIsValidInGraph( set<int> *touchedNodes, Graph* graph )
{
   return touchedNodes->size() == (unsigned)graph->NumVertices();
}

bool CanAttainLegalAnswer( set<int> *touchedNodes, Graph* graph, int nodeIndex )
{
   bool answerCanBeLegal = true;

   if( nodeIndex >= 0 )
   {
      int numNodesLeftToProcess = graph->NumVertices() - nodeIndex;
      int numNodesPossibleToHit = numNodesLeftToProcess * graph->GetMaxDegree( nodeIndex );

      answerCanBeLegal = ( touchedNodes->size() + numNodesPossibleToHit ) >= (unsigned)graph->NumVertices();
   }

   return answerCanBeLegal;
}

unsigned _bestAnswerSize;
list<Node*> *_bestAnswerSoFar;

void SolveUSPS( Graph* graph, int nextNode, list<Node*> *includedNodes, set<int> *touchedNodes )
{
   if( includedNodes->size() < _bestAnswerSize && CanAttainLegalAnswer( touchedNodes, graph, nextNode ) )
   {
      if( nextNode < graph->NumVertices() )
      {
         includedNodes->push_back( graph->GetNode( nextNode ) );
         set<int>* newSet = new set<int>( *touchedNodes );
         AddVerticesTouchedToSet( nextNode, newSet, graph );

         SolveUSPS( graph, nextNode + 1, includedNodes, newSet );

         includedNodes->pop_back();

         SolveUSPS( graph, nextNode + 1, includedNodes, touchedNodes );
      }
      else if ( ListIsValidInGraph( touchedNodes, graph ) )
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

	SolveUSPS( graph, 0, new list<Node*>(), new set<int>() );

	cout << "found solution with " << _bestAnswerSize << " vertices" << endl;

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

