#include "threadfornode.h"
#include "messagepasser.h"

ThreadForNode::ThreadForNode()
{
	msgPasser = new MessagePasser();
	acknowledged = true;
	connect(
		this, SIGNAL(sendProfileToNode(ProfileTransferObj, ThreadForNode*)), 
		msgPasser, SLOT(passMessage(ProfileTransferObj, ThreadForNode*))
		);
}

ThreadForNode::~ThreadForNode()
{

}

void ThreadForNode::run()
{
	VideoCapture cap(videoLink);

	//vector<graph::ExitPoint> exitPoints = currentNodePtr->exitPoints;
	vector<Blob> blobs, unidentifiedBlobs;
	vector<HumanBlob> humanBlobs, trackingHumanBlobs, possibleProfileList;
	vector<MissingHumanBlob> missingHumanBlobs;

	VideoProcessing _vProcessing = VideoProcessing();
	Mat fgMaskMOG2;
	Ptr<BackgroundSubtractor> pMOG2 = new BackgroundSubtractorMOG2(300, 32, true);

	if (!cap.isOpened())
	{
		qDebug() << "Error loding video '" << QString::fromStdString(videoLink) << "'";
	}
	cap.set(CV_CAP_PROP_POS_FRAMES, 9000);
	while (cap.read(frame))
	{
		// ////////////////// //
		// process begin here //
		// ////////////////// //

		//blobs.clear();
		//unidentifiedBlobs.clear();
		//humanBlobs.clear();

		//// blob detection
		//if (_vProcessing.blobDetection(frame, pMOG2, fgMaskMOG2, &blobs) == 0)
		//{
		//	waitForAcknowledge();
		//	QImage outImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
		//	emit sendFrameToMain(outImage, this);
		//	this->acknowledged = false;
		//	continue;	// If no blobs detected continue while
		//}
		//if (trackingHumanBlobs.empty())	// if no human blobs tracked yet
		//{
		//	unidentifiedBlobs = blobs;	// all blobs are unindentified
		//}
		//else	// if there are human blobs tracked in previous frames
		//{
		//	_vProcessing.dataAssociation(&blobs, &trackingHumanBlobs, &unidentifiedBlobs, &missingHumanBlobs);
		//}

		//if (!(unidentifiedBlobs.empty()))
		//{
		//	_vProcessing.humanDetection(&unidentifiedBlobs, &frame, &humanBlobs);
		//}

		//if (!(humanBlobs.empty()))
		//{
		//	_vProcessing.checkInProfiles(&humanBlobs, &possibleProfileList, &missingHumanBlobs, &trackingHumanBlobs);
		//}

		//if (!(humanBlobs.empty()))
		//{
		//	_vProcessing.initTrackingObject(&humanBlobs, &trackingHumanBlobs);
		//}

		//if (!(trackingHumanBlobs.empty()))
		//{
		//	_vProcessing.kalmanCorrectAndPredict(&trackingHumanBlobs);
		//	//_vProcessing.informAdjecentNodes(&exitPoints, &trackingHumanBlobs);
		//	//_vProcessing.UpdateCentralProfiles(&trackingHumanBlobs);
		//}







		//// get the moments
		//vector<Moments> mu(human_blobs.size());
		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	mu[i] = moments(human_blobs[i], false);
		//}

		//// get the mass centers:
		//vector<Point2f> mc(human_blobs.size());
		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		//}

		//for (size_t i = 0; i < mc.size(); i++)
		//{
		//	int selectedContourId = getReleventContour(mc[i]);

		//	Point measurePre(trackingObjectMap[selectedContourId].getLastPoint());
		//	vector<Point> pointsVector = trackingObjectMap[selectedContourId].addCenterPoint(mc[i]);
		//	Point measureCurrent(trackingObjectMap[selectedContourId].getLastPoint());

		//	drawCross(frame, measureCurrent, Scalar(0, 255, 0), 5);

		//	Mat prediction = trackingObjectMap[selectedContourId].kalmanPredict();
		//	Point kalmanPredict(prediction.at<float>(0), prediction.at<float>(1));

		//	Mat corrected = trackingObjectMap[selectedContourId].kalmanCorrect(mc[i]);
		//	Point kalmanCorrected(corrected.at<float>(0), corrected.at<float>(1));
		//	
		//	drawCross(frame, kalmanPredict, Scalar(0, 0, 255), 5);
		//	//drawCross(frame, kalmanCorrected, Scalar(0, 255, 255), 5);

		//	stringstream lbl;
		//	lbl << "Blob_" << selectedContourId;
		//	putText(frame, lbl.str(), measureCurrent, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 2);

		//	for (int i = pointsVector.size() - 1; i != 0; i--)
		//	{
		//		line(frame, pointsVector[i], pointsVector[i - 1], Scalar(200, 220, 80), 3);
		//	}
		//}

		//vector<vector<Point> > blobs_poly(human_blobs.size());
		//vector<Rect> boundRect(human_blobs.size());
		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	approxPolyDP(Mat(human_blobs[i]), blobs_poly[i], 3, true);
		//	boundRect[i] = boundingRect(Mat(blobs_poly[i]));
		//}

		//for (size_t i = 0; i < human_blobs.size(); i++)
		//{
		//	rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 0), 2, 8, 0);// scalar is for Bounding Box
		//}

		//  end process here  //

		
		waitForAcknowledge();
		if (cap.get(CV_CAP_PROP_POS_FRAMES) == cap.get(CV_CAP_PROP_FRAME_COUNT))
		{
			frame = Mat::zeros(1, 1, CV_64F);
			putText(frame, "END OF FILE!", Point(frame.rows / 2, frame.cols / 2), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 2);
			QImage outImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
			emit sendFrameToMain(outImage, this);
			emit sendFinishedToMain();
			break;
		}
		QImage outImage((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
		emit sendFrameToMain(outImage, this);
		this->acknowledged = false;
	}

	qDebug() << "finished.";
}

void ThreadForNode::updateProfileList(ProfileTransferObj profile)
{

}


void ThreadForNode::waitForAcknowledge()
{
	if (!acknowledged)
	{
		mutex->lock();
			isNotShown->wait(mutex);
		mutex->unlock();
	}
	//while (!acknowledged);

}