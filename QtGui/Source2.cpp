#include <stdio.h>
#include <iostream>

#include <Windows.h> // threading purpose
#include <process.h>

#include <opencv2\highgui\highgui.hpp>	// open cv
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include "BlobDetection.h"
#include "QtCore\qdebug.h"

using namespace std;
using namespace cv;

#define drawCross( img, center, color, d )\
	line(img, Point(center.x - d, center.y - d), Point(center.x + d, center.y + d), color, 1, CV_AA, 0); \
	line(img, Point(center.x + d, center.y - d), Point(center.x - d, center.y + d), color, 1, CV_AA, 0);

struct Blobs
{
	vector<Point> contour;
	Point2f massCenter;
};

vector<Blobs> getBlobs(string link, double m_sec_start, double m_sec_end)
{
	VideoCapture cap(link);
	Mat frame;
	vector<Blobs> returnObj;

	if (!(cap.read(frame)))
	{
		cerr << "Problem opening video source" << endl;
	}

	double fps = cap.get(CV_CAP_PROP_FPS);
	double timegapForOneFrame = 1000 / fps;
	m_sec_start -= timegapForOneFrame;

	cap.set(CV_CAP_PROP_POS_MSEC, m_sec_start);
	double currentTime = m_sec_start;

	Mat fgMaskMOG2;
	Ptr<BackgroundSubtractor> pMOG2 = new BackgroundSubtractorMOG2(300, 32, true);
	Mat morpho_ele = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));
	BlobDetection blbDetect;

	Moments mu;
	Point2f mc;
	int waitKeyKey = 0;
	cvNamedWindow("Video", CV_WINDOW_NORMAL);
	cvSetWindowProperty("Video", CV_WND_PROP_AUTOSIZE, CV_WINDOW_NORMAL);
	cvSetWindowProperty("Video", CV_WND_PROP_ASPECTRATIO, CV_WINDOW_KEEPRATIO);
	cvResizeWindow("Video", 1400, 800);
	string timeX;
	int minutes;
	int seconds;
	int mili;
	while (waitKey(10) != 27 && cap.grab())
	{

		cap.read(frame);
		currentTime = cap.get(CV_CAP_PROP_POS_MSEC);
		if (m_sec_end != NULL)
			if (m_sec_end <= currentTime)
				break;

		// blob detection
		vector<vector<Point>> contours;
		contours = blbDetect.detectContours(frame, pMOG2, fgMaskMOG2);
		string lblMC;
		
		// setting retrun obj
		for each (vector<Point> con in contours)
		{
			if (!(blbDetect.isQualifyingContour(con)))
			{
				continue;
			}
			mu = moments(con, false);
			mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
			Blobs b{ con, mc };
			returnObj.push_back(b);
			Rect mr = boundingRect(Mat(con));
			rectangle(frame, mr, CV_RGB(255, 0, 0), 1);
			drawCross(frame, mc, Scalar(0, 255, 0), 5);
			lblMC = "X: " + to_string(mc.x) + " - Y: " + to_string(mc.y) + "";
			minutes = (int)(currentTime / (1000*60));
			int secondsBuffer = (int)((currentTime - minutes * 60 * 1000)/1000);


			if (secondsBuffer != seconds)
			{
				seconds = secondsBuffer;
				mili = currentTime - (minutes * 60 * 1000 + seconds * 1000);
				timeX = to_string(minutes);

				if (seconds < 10)
				{
					timeX += ".0";
				}
				else
				{
					timeX += ".";
				}
				timeX += to_string(seconds);

				/*
				if (mili < 10)
				{
					timeX += ".000";
				}
				else if (mili < 100)
				{
					timeX += ".00";
				}
				else
				{
					timeX += ".0";
				}
				timeX += to_string(mili);
				*/

				string output = "23 ==_== " + timeX + " " + to_string((int)mc.x) + "," + to_string((int)mc.y);

				qDebug() << qPrintable(QString::fromStdString(output));
				putText(frame, lblMC, mc, CV_FONT_HERSHEY_SIMPLEX, 0.6, Scalar(128, 0, 10), 2);
			}
			
			
		}
		putText(frame, timeX, Point(0, 20), CV_FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 2);
		
		
		imshow("Video", frame);
		

		if (waitKey(1500) == 32)
 			if (waitKey(600000) == 13);
	}

	return returnObj;

} 

int mainTFF(int argc, char* argv[])
{
	string link = "C:\\AdaptiveCameraNetworkPack\\Videos\\PRG23.avi";
	double sec_start = 182;
	double m_sec_start = sec_start*1000, m_sec_end = NULL;

	vector<Blobs> blobs = getBlobs(link, m_sec_start, m_sec_end);

	system("pause");
	return 0;

}