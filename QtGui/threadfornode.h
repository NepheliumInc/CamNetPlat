#ifndef THREADFORNODE_H
#define THREADFORNODE_H

//#include <QObject>
#include "QtCore\qobject.h"
#include "QtCore\qthread.h"
#include "qimage.h"
#include "qdebug.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "VideoProcessing.h"

using namespace models;
using namespace cv;

class MessagePasser;

class ThreadForNode : public QThread
{
	Q_OBJECT

public:
	ThreadForNode();
	~ThreadForNode();
	void run();
	void updateProfileList(ProfileTransferObj profile);
	void waitForAcknowledge();

	string videoLink; // temp
	string nodeId;
	vector<graph::ExitPoint> exitPoints;
	bool acknowledged;

signals:
	void sendFrameToMain(QImage outImage, ThreadForNode* thread);
	void sendProfileToNode(ProfileTransferObj profile, ThreadForNode* nodeThread);

private:
	MessagePasser* msgPasser;
	Mat frame;
};

#endif // THREADFORNODE_H
