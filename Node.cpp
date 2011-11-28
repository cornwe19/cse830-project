#include "Node.h"

Node::Node( int id ) 
{
	_consideration = NotConsidered;
	_id = id;
	_adjacentNodes = new list<int>();
}

Node::~Node()
{
	if( _adjacentNodes != NULL )
	{
		delete _adjacentNodes;
		_adjacentNodes = NULL;
	}
}

void Node::AddNode( int nodeRef )
{
	_adjacentNodes->push_back( nodeRef );	
}

list<int>* Node::GetAdjacentNodes()
{
	return _adjacentNodes;
}

int Node::GetId()
{
	return _id;
}

bool Node::NumVerticesDescending( Node* a, Node* b )
{
   return a->GetAdjacentNodes()->size() > b->GetAdjacentNodes()->size();
}
