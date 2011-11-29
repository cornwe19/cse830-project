#include <iostream>
#include "Graph.h"
#include <list>
#include <set>
#include <algorithm>

using namespace std;

// Includes any vertices a node touches into the set of touched nodes
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

// Makes sure every node on the graph has been touched (neighbored or included)
bool ListIsValidInGraph( set<int> *touchedNodes, Graph* graph )
{
   return touchedNodes->size() == (unsigned)graph->NumVertices();
}

// Pre-check to see if it's even possible to get a legal answer with the current set of nodes
bool CanAttainLegalAnswer( set<int> *touchedNodes, Graph* graph, int nodeIndex )
{
   // Dont check anything if we have a valid set of included nodes
   if( ListIsValidInGraph( touchedNodes, graph ) )
   {
      return true;
   }

   // Try including every node left and see if we get a legal answer
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

// Recursive branching function
void SolveUSPS( Graph* graph, int nextNode, list<Node*> *includedNodes, set<int> *touchedNodes )
{
   // Check bounding and branching conditions to determine if we should abort current branch
   if( includedNodes->size() < _bestAnswerSize && CanAttainLegalAnswer( touchedNodes, graph, nextNode ) )
   {
      // Check if we have a complete set of nodes
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
      // If set is complete and valid, set the new best answer
      else if ( ListIsValidInGraph( touchedNodes, graph ) )
      {
         _bestAnswerSize = includedNodes->size();
         delete _bestAnswerSoFar;
         _bestAnswerSoFar = new list<Node*>( *includedNodes );
      }
   }
}

// Greedy include highest degree nodes to set an initial bound answer
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

	// Print the results
	list<Node*> result( graph->NumVertices() );
	list<Node*>::iterator it, resultIt;

	cout << graph->NumVertices() - _bestAnswerSize << " : ";

	// Since we maintained a list of the nodes included, take the set difference between all the
	// nodes in the graph and the list we best answer we ended up with. **Note requires best answer
	// be sorted for efficiency in stl difference algorithm.
	_bestAnswerSoFar->sort( Node::Compare );
	resultIt = set_difference( graph->GetAllNodes(), graph->GetAllNodes() + graph->NumVertices(),
									_bestAnswerSoFar->begin(), _bestAnswerSoFar->end(), result.begin(), Node::Compare );

	for (it = result.begin(); it != resultIt; it++ )
	{
		cout << (*it)->GetId() << " ";
	}

	cout << endl;

	delete graph;
}

