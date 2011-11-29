#include "Node.h"

#include <iostream>

using namespace std;

Node::Node( int id ) 
{
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

bool Node::Compare( Node* a, Node* b)
{
   return a->GetId() < b->GetId();
}
