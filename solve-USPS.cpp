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
   if( ListIsValidInGraph( touchedNodes, graph ) )
   {
      return true;
   }

   bool answerCanBeLegal = false;

   set<int>* completeSet = new set<int>( *touchedNodes );
   for( int i = nodeIndex; i < graph->NumVertices(); i++ )
   {
      AddVerticesTouchedToSet( i, completeSet, graph );
      if( completeSet->size() == (unsigned)graph->NumVertices() )
      {
         answerCanBeLegal = true;
         break;
      }
   }

   return answerCanBeLegal;
}

unsigned _bestAnswerSize;
list<Node*> *_bestAnswerSoFar;

void SolveUSPS( Graph* graph, int nextNode, list<Node*> *includedNodes, set<int> *touchedNodes )
{
   if( includedNodes->size() < _bestAnswerSize && CanAttainLegalAnswer( touchedNodes, graph, nextNode ) )
   {
      if( nextNode < graph->NumVertices() && !ListIsValidInGraph(touchedNodes, graph) )
      {
         Node* currentNode = graph->GetNode( nextNode );

         includedNodes->push_back( currentNode );
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

void GetPolynomialTimeGoodAnswer( Graph* graph, list<Node*> *nodeListToFill )
{
	set<int> touchedNodes;
	int currentNodeIndex = 0;
	nodeListToFill->clear();

	while( true )
	{
		Node* currentNode = graph->GetNode( currentNodeIndex );
		list<int>* currentAdjacentNodes = currentNode->GetAdjacentNodes();
		list<int>::iterator it;

		nodeListToFill->push_back( currentNode );

		for( it = currentAdjacentNodes->begin(); it != currentAdjacentNodes->end(); it++ )
		{
			touchedNodes.insert( *it );
			if( touchedNodes.size() == (unsigned)graph->NumVertices() )
			{
				return;
			}
		}

		currentNodeIndex++;
	}
}

void PrintInclusions( Graph* graph )
{
   for( int i = 0; i < graph->NumVertices(); i++ )
   {
      Node* node = graph->GetNode( i );
      cout << node->GetId() << ":" << node->GetConsideration() << " ";
   }
   cout << endl;
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

	_bestAnswerSoFar = new list<Node*>();

	GetPolynomialTimeGoodAnswer( graph, _bestAnswerSoFar );
	_bestAnswerSize = _bestAnswerSoFar->size();

	SolveUSPS( graph, 0, new list<Node*>(), new set<int>() );

	cout << graph->NumVertices() - _bestAnswerSize << " : ";
	
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

