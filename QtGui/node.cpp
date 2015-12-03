#include <iostream>
#include "graph.h"

using namespace graph;

Node::Node(){}

Node::Node(string _nodeId, string _videoLink, vector<ExitPoint> _exitPoints, int _startFrame)
{
	videoLink = _videoLink;
	nodeId = _nodeId;
	exitPoints = _exitPoints;
	startFrame = _startFrame;
}

Node::~Node(){}