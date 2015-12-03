#ifndef HOGDESCRIPTOR_CLASS_H
#define HOGDESCRIPTOR_CLASS_H

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
using namespace std;

class HogDescriptor_Class
{
public:
	HogDescriptor_Class();
	~HogDescriptor_Class();

	Mat HogDescriptor_Class::generateDescriptorMat(Mat img);
private:
	vector<float> descriptorsValues;
};

#endif // HOGDESCRIPTOR_CLASS_H
