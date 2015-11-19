//
//  ProBlobDetection.cpp
//  OpencvTut
//
//  Created by Dehan on 4/20/15.
//  Copyright (c) 2015 nephelium. All rights reserved.
//
#include <iostream>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <QtWidgets/QApplication>

#include <QtCore\QFileInfo>
#include <QtWidgets\qlabel.h>
#include <fstream>
#include <sys/stat.h>
#include <QtCore\QCoreApplication>
#include <QtCore\qdir.h>
#include <QtCore\QDebug>
#include <QtCore\QString>
#include <stdlib.h>


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>

#include "BlobDetection.h"

#include <stdio.h>
#include <time.h>
using namespace cv;
using namespace std;
void getDiffInVideo();
void drawHist();
Mat drawHist(Mat greyImage);
Mat src;
Mat dst;
Mat resizedFrame;
Mat processedFrame;
Mat edgeDetected;

Mat savedImage;
Mat savedHist;
RNG rng(12345);

///Removes any dir if exists
void make_directory(QString path);

void make_directory(QString path){

	QDir directory(path);
	if (!directory.exists())
	{
		qDebug() << "Creating " << directory << "directory";
		directory.mkpath(path);
	}
	else
	{
		qDebug() << path << " already exists";
		directory.setNameFilters(QStringList() << "*.*");
		directory.setFilter(QDir::Files);
		foreach(QString dirFile, directory.entryList())
		{
			directory.remove(dirFile);
		}
	}
}

//global variables
Mat frame; //current frame

int frameCounter = 0;
int mainHR()
{
	BlobDetection blb;
	
	//blb.
	/* The behavior of mkdir is undefined for anything other than the "permission" bits */
	QString path = "C:\\Projects\\Output";
	QString path_correct = "C:\\Projects\\Output\\file1\\correct";
	QString path_non = "C:\\Projects\\Output\\file1\\non";
	make_directory(path_correct);
	make_directory(path_non);
	//make_directory(path);

	Mat frame; //current frame
	Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
	//Mat TestImg;
	Ptr< BackgroundSubtractor> pMOG2; //MOG2 Background subtractor

	pMOG2 = new BackgroundSubtractorMOG2(300, 32, true);//300,0.0);
	
	Ptr< BackgroundSubtractor> pMOG2Pointer; //MOG2 Background subtractor
	pMOG2Pointer = new BackgroundSubtractorMOG2(300, 32, true);//300,0.0);

	string fileName = "C:\\Projects\\PRG6.avi";
	VideoCapture stream1(fileName);  

	//morphology element
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));
	bool flag = true;


	
	float loopCounter = 1;
	float averageTime = 0;
	int skippedFrames = 0;
	int count = 0;
	for (int i = 0; i < skippedFrames; i++)
	{
		stream1.grab();

	}
	while (true) {


		clock_t t = clock();
		if (!(stream1.read(frame))) 
			break;

		vector< vector< Point> > contours;
		BlobDetection blbDetect;
		resize(frame, frame, Size(frame.size().width, frame.size().height));
		Mat originalFrame = frame.clone();

		contours = blbDetect.detectContours(frame,pMOG2Pointer, fgMaskMOG2);
		Rect roi;
		vector<vector<Point> >hulls;
		vector< vector< Point> > filteredContours;

	
		while (contours.size() != 0)
		{
			vector<Point> contour = contours[contours.size() - 1];
			if (blbDetect.isQualifyingContour(contour))
			{
				vector<Point> tempHull;
				convexHull(Mat(contour), tempHull, false);
				hulls.push_back(tempHull);
				filteredContours.push_back(contour);
			}
			contours.pop_back();
		}

		//Draw the hull borders and fill in white to create the "hullDrawing" mask 
		Mat hullDrawing(frame.size(), CV_8UC3);
		floodFill(hullDrawing, Point(), Scalar(255, 255, 255));
		for (int i = 0; i< filteredContours.size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			drawContours(hullDrawing, hulls, i, color, 1, 8, vector<Vec4i>(), 0, Point());

		}
		floodFill(hullDrawing, Point(), Scalar(0, 0, 0));
		cvWaitKey(1);

		for (int i = 0; i < filteredContours.size(); i++)
		{
			roi = boundingRect(filteredContours[i]);
			Mat imageHullCrop;
			//Copy the relevant pixels
			//representation of the hull drawing 
			originalFrame.copyTo(imageHullCrop, hullDrawing); // 'image' is the image you used to compute the contours.

			//Crop the region of interest
			Mat convexBlob = imageHullCrop(roi);
			Mat convexBlobMask = hullDrawing(roi);
			Mat rectBlob = originalFrame(roi);

			namedWindow("convexBlob", CV_WINDOW_KEEPRATIO);
			namedWindow("convexBlMask", CV_WINDOW_KEEPRATIO);
			namedWindow("rectBlob", CV_WINDOW_KEEPRATIO);

			imshow("convexBlob", convexBlob);
			imshow("convexBlMask", convexBlobMask);
			imshow("rectBlob", rectBlob);
			cvWaitKey(1);
			time_t seconds;
			time(&seconds);
			stringstream ss;
			ss << seconds;
			string ts = ss.str();
			double heightToWidthRatio = static_cast<double>(roi.height) / static_cast<double>(roi.width);
			if (roi.width > 30 && roi.width < 100 && roi.height>30)
			{
				if (heightToWidthRatio > 1.3)
				{
					string number = "";

					if (count < 10){
						number = "000"+  to_string(count);

					}
					else if (count < 100){
						number = "00" + to_string(count);
					}
					else if (count < 1000){
						number = "0" + to_string(count);
					}
					else{
						number = to_string(count);
					}
					string pathConvex = "C:\\Projects\\Output\\file1\\correct\\img_convex_" + number + ".jpg";
					string pathConvexMask = "C:\\Projects\\Output\\file1\\correct\\cmask\\img_cmask_" + number + ".jpg";
					string pathBox = "C:\\Projects\\Output\\file1\\correct\\box\\img_box_" + number + ".jpg";
					string pathFrame = "C:\\Projects\\Output\\file1\\correct\\frame\\img_frame_" + number + ".jpg";

					count++;
					imwrite(pathConvex, convexBlob);
					imwrite(pathConvexMask, convexBlobMask);
					imwrite(pathBox, rectBlob);
					imwrite(pathFrame, originalFrame);
					
				}
				else{
					imwrite("C:\\Projects\\Output\\file1\\non\\" + ts + to_string(i) + ".jpg", convexBlob);


				}
			}

		}
	}
	return 0;
}

Mat drawHist(Mat greyImage)
{////
	float colourFrequency2[256] = {}; 
	for (int i = 0; i < greyImage.rows; i++){
		for (int j = 0; j < greyImage.cols; j++){
			int pixel = greyImage.at<uchar>(i, j);
			colourFrequency2[pixel] += 1;
		}
	}

	float max = 0.0;
	for (int i = 0; i < 256; i++){
		if (max < colourFrequency2[i]){
			max = colourFrequency2[i];
		}
	}
	Mat histogram2(310, 260, CV_8UC3, Scalar(255, 255, 255));

	int hist2[256] = {};
	float maxd = max;
	for (int i = 0; i < 256; i++){
		hist2[i] = cvRound(double(colourFrequency2[i] / maxd) * 300.0);
		Point pt1 = Point(i, 300 - hist2[i]);
		Point pt2 = Point(i, 300);
		line(histogram2, pt1, pt2, Scalar(0, 0, 0), 1, 8, 0);
	}

	return histogram2;

}