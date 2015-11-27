#include <iostream>
#include "graph.h"

using namespace graph;

Node::Node(){}

Node::Node(string _nodeId, string _videoLink, vector<ExitPoint> _exitPoints)
{
	videoLink = _videoLink;
	nodeId = _nodeId;
	exitPoints = _exitPoints;
}

Node::~Node(){}