#ifndef TESTER_CLASS_H
#define TESTER_CLASS_H

#include <QtCore\qstring.h>
#include <QtCore\qdiriterator.h>
#include <QtCore\qstring.h>
#include <QtCore\qstring.h>
#include <QtCore\qdebug.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class Tester_class
{
public:
	Tester_class();
	~Tester_class();

	void Tester_class::get_path();
	void Tester_class::hog_PeopelDetectorTest(String path);

private:
	
};

#endif // TESTER_CLASS_H
