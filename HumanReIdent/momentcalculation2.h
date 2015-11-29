#ifndef MOMENTCALCULATION2_H
#define MOMENTCALCULATION2_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "MomentStructures2.h"
#include <humanreident_global.h>
#include <QtCore\qmath.h>


using namespace cv;
class HUMANREIDENT_EXPORT MomentCalculation2
{


public:
	MomentCalculation2();
	~MomentCalculation2();
	MomentAverage getAverageColourInConvexRegion(Mat image, Mat imageMask, Region *region);
	MomentStandardDeviation getStandardDeviationInConvexRegion(Mat image, Mat imageMask, Region *region, MomentAverage *momentAverage);
	MomentSkewness getSkewnessnInConvexRegion(Mat image, Mat imageMask, Region *region, MomentAverage *momentAverage);
	double getDistanceBetweenBlobs(Blob *controlBlob, Blob *testingBlob);
	Blob getMomentsInaBlob(Mat boxImage, Mat cmaskImage, string blobId = NULL, string profileId = NULL);

	struct HumanProportions{
		int height = 14;
		int head = 2;
		int gait = 5;
		int leg = 7;
	};
private:
	
};

#endif // MOMENTCALCULATION2_H
