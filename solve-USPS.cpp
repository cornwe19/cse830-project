#include <iostream>
#include "Graph.h"
#include <list>
#include <set>
#include <algorithm>

using namespace std;

void AddVerticesTouchedToSet( Node* currentNode, set<int> *touchedNodes )
{
   touchedNodes->insert(currentNode->GetId());

   list<int>::iterator edgeIt;
   for( edgeIt = currentNode->GetAdjacentNodes()->begin(); edgeIt != currentNode->GetAdjacentNodes()->end(); edgeIt++ )
   {
      touchedNodes->insert( *edgeIt );
   }
}

void AddVerticesTouchedToSet( int currentNode, set<int> *touchedNodes, Graph* graph )
{
   Node* current = graph->GetNode( currentNode );

   AddVerticesTouchedToSet( current, touchedNodes );
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

         if( !currentNode->IsPreIncluded() )
         {
            includedNodes->push_back( currentNode );
            set<int>* newSet = new set<int>( *touchedNodes );
            AddVerticesTouchedToSet( nextNode, newSet, graph );

            SolveUSPS( graph, nextNode + 1, includedNodes, newSet );

            includedNodes->pop_back();
         }

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

void PruneLeafNodes( Graph* graph, list<Node*> *includedNodes, set<int> *touchedNodes )
{
   // Assumes graph is sorted in descending order
   //  - Traverse graph from nodes with least degree first...
   int currentIndex = graph->NumVertices() - 1;
   Node* currentNode = graph->GetNode( currentIndex );
   while( currentNode->GetAdjacentNodes()->size() == 1 )
   {
      cout << "Pruning node at index " << currentIndex << endl;
      Node* adjacentNode = graph->GetNodeWithId( currentNode->GetAdjacentNodes()->front() );
      if( !adjacentNode->IsPreIncluded() )
      {
         adjacentNode->PreInclude();

         AddVerticesTouchedToSet( adjacentNode, touchedNodes );
         includedNodes->push_back( adjacentNode );
      }

      graph->RemoveNode( currentIndex );

      currentNode = graph->GetNode( --currentIndex );
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

	_bestAnswerSoFar = new list<Node*>();

	GetPolynomialTimeGoodAnswer( graph, _bestAnswerSoFar );
	_bestAnswerSize = _bestAnswerSoFar->size();
	cout << "Setting best answer size to " << _bestAnswerSize << endl;

	list<Node*>* includedNodes = new list<Node*>();
	set<int>* touchedNodes = new set<int>();

	//PruneLeafNodes( graph, includedNodes, touchedNodes );

	SolveUSPS( graph, 0, includedNodes, touchedNodes );

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

	delete includedNodes;
	delete touchedNodes;

	delete graph;
}

