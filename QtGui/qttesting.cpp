#include "qttesting.h"

QtTesting::QtTesting(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	vector<QLabel*> uiLblVector{ ui.lblCamera1, ui.lblCamera2, ui.lblCamera3, ui.lblCamera4, ui.lblCamera5, ui.lblCamera6, ui.lblCamera7, ui.lblCamera8 };

	graph::Graph _graph = graph::Graph();
	_graph.initGraph();

	vector<graph::Node> nodes = _graph.getAllNodes();

	for (vector<graph::Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		ThreadForNode* thread = new ThreadForNode();
		thread->nodeId = it->nodeId;
		thread->videoLink = it->videoLink;
		thread->exitPoints = it->exitPoints;
		nodeToThreadMap[it->nodeId] = thread;
	}

	for (map<string, ThreadForNode*>::iterator it = nodeToThreadMap.begin(); it != nodeToThreadMap.end(); it++)
	{
		connect(it->second, SIGNAL(sendFrameToMain(QImage, ThreadForNode*)),
			this, SLOT(recieveFrameFromThreads(QImage, ThreadForNode*)));
	}

	for (int i = 0; i < uiLblVector.size(); i++)
	{
		this->lblMap[nodes[i].nodeId] = uiLblVector[i];
	}

	this->threadCount = nodes.size();

	for (map<string, ThreadForNode*>::iterator it = nodeToThreadMap.begin(); it != nodeToThreadMap.end(); it++)
	{
		it->second->start();
	}



	/*ThreadForNode* thread1 = new ThreadForNode();
	ThreadForNode* thread2 = new ThreadForNode();

	connect(thread1, SIGNAL(sendFrameToMain(QImage, ThreadForNode*)), this, SLOT(recieveFrameFromThreads(QImage, ThreadForNode*)));
	connect(thread2, SIGNAL(sendFrameToMain(QImage, ThreadForNode*)), this, SLOT(recieveFrameFromThreads(QImage, ThreadForNode*)));

	thread1->nodeId = "C001";
	thread2->nodeId = "C002";

	this->lblMap["C001"] = ui.lblCamera1;
	this->lblMap["C002"] = ui.lblCamera2;

	thread1->videoLink = "C:/AdaptiveCameraNetworkPack/Videos/PRG6.avi";
	thread2->videoLink = "C:/AdaptiveCameraNetworkPack/Videos/PRG29.avi";

	thread1->start();
	thread2->start();*/
}

QtTesting::~QtTesting()
{

}


void QtTesting::recieveFrameFromThreads(QImage outImage, ThreadForNode* thread)
{
	int x = outImage.byteCount();
	if (completedThreadMap.count(thread->nodeId) == 0)
	{
		frameMap[thread->nodeId] = outImage;
		completedThreadMap[thread->nodeId] = thread;
	}
	if (completedThreadMap.size() == threadCount)
	{
		for (map<string, QImage>::const_iterator i = frameMap.begin(); i != frameMap.end(); i++)
		{
			lblMap[i->first]->setPixmap(QPixmap::fromImage(frameMap[i->first]));
		}
		for (map<string, ThreadForNode*>::const_iterator i = completedThreadMap.begin(); i != completedThreadMap.end(); i++)
		{
			i->second->acknowledged = true;
		}
		completedThreadMap.clear();
		frameMap.clear();
	}
}