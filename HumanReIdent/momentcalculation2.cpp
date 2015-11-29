#include "stdafx.h"
#include "momentcalculation2.h"
#include "momentstructures2.h"

MomentCalculation2::MomentCalculation2()
{

}

MomentCalculation2::~MomentCalculation2()
{

}

double MomentCalculation2::getDistanceBetweenBlobs(Blob *controlBlob, Blob *testingBlob)
{
	double total = 0;
	vector<Region> controlRegions = controlBlob->getAllRegions();
	vector<Region> testingRegions = testingBlob->getAllRegions();
	double cHueCoef = 0.7, cSatCoef = 0.2, cValCoef = 0.1;
	double rHeadCoef = 0.1, rTorsCoef = 0.5, rLegCoef = 0.4;
	std::map<int, double> regionMap;
	regionMap[0] = rHeadCoef, regionMap[1] = rTorsCoef, regionMap[2] = rLegCoef;
	double totalDistanceSquared = 0;



	MomentAverage* cRAve;
	MomentAverage* tRAve;
	MomentStandardDeviation* cRStdDev;
	MomentStandardDeviation* tRStdDev;
	MomentSkewness* cRSkew;
	MomentSkewness* tRSkew;
	for (int rId = 0; rId < 3; rId++)
	{
		cRAve = controlRegions[rId].getAverageMoment(); //c = control , R = Region
		tRAve = testingRegions[rId].getAverageMoment(); //t = testing
		double rAveDistance = cHueCoef*qPow(cRAve->channel0 - tRAve->channel0, 2) +
			cSatCoef*qPow(cRAve->channel1 - tRAve->channel1, 2) +
			cValCoef*qPow(cRAve->channel2 - tRAve->channel2, 2);

		cRStdDev = controlRegions[rId].getStandardDeviationMoment(); //c = control , R = Region
		tRStdDev = testingRegions[rId].getStandardDeviationMoment(); //t = testing
		double rStandardDev = cHueCoef*(double)qPow(cRStdDev->channel0 - tRStdDev->channel0, 2) +
			cSatCoef*(double)qPow(cRStdDev->channel1 - tRStdDev->channel1, 2) +
			cValCoef*(double)qPow(cRStdDev->channel2 - tRStdDev->channel2, 2);

		cRSkew = controlRegions[rId].getSkewnessMoment(); //c = control , R = Region
		tRSkew = testingRegions[rId].getSkewnessMoment(); //t = testing
		double rSkewNess = cHueCoef*(double)qPow(cRSkew->channel0 - tRSkew->channel0, 2) +
			cSatCoef*(double)qPow(cRSkew->channel1 - tRSkew->channel1, 2) +
			cValCoef*(double)qPow(cRSkew->channel2 - tRSkew->channel2, 2);

		totalDistanceSquared += regionMap[rId] * (rAveDistance + rStandardDev + rSkewNess);
	}
	totalDistanceSquared = qSqrt(totalDistanceSquared);
	delete	cRAve;
	delete	tRAve;
	delete	cRStdDev;
	delete	tRStdDev;
	delete	cRSkew;
	delete	tRSkew;
	return totalDistanceSquared;
}

Blob MomentCalculation2::getMomentsInaBlob(Mat boxImage, Mat cmaskImage, string blobId,string profileId){


	cvtColor(boxImage, boxImage, CV_BGR2HSV);
	//Average
	HumanProportions prop;

	int boxHeight = boxImage.rows;
	double ratio = (double)boxHeight / (double)prop.height;
	int region1Height = (int)(((double)prop.head) * ratio);
	int region2Height = (int)(((double)prop.gait) * ratio);
	int region3Height = (int)(((double)prop.leg)	* ratio);

	string placement = "Top";
	Region region1(placement, 0, 0, region1Height, boxImage.cols);
	MomentCalculation2 mcalc;
	MomentAverage momentAverage1 = mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region1);
	MomentStandardDeviation momentStandardDeviation1 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region1, &momentAverage1);
	MomentSkewness momentSkewness1 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region1, &momentAverage1);
	region1.setMoments(&momentAverage1, &momentStandardDeviation1, &momentSkewness1);


	placement = "Middle";
	Region region2(placement, 0, 0, region2Height, boxImage.cols);
	MomentAverage momentAverage2 = mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region2);
	MomentStandardDeviation momentStandardDeviation2 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region2, &momentAverage2);
	MomentSkewness momentSkewness2 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region2, &momentAverage2);
	region2.setMoments(&momentAverage2, &momentStandardDeviation2, &momentSkewness2);

	placement = "Bottum";
	Region region3(placement, 0, 0, region3Height, boxImage.cols);
	MomentAverage momentAverage3 = mcalc.getAverageColourInConvexRegion(boxImage, cmaskImage, &region3);
	MomentStandardDeviation momentStandardDeviation3 = mcalc.getStandardDeviationInConvexRegion(boxImage, cmaskImage, &region3, &momentAverage3);
	MomentSkewness momentSkewness3 = mcalc.getSkewnessnInConvexRegion(boxImage, cmaskImage, &region3, &momentAverage3);
	region3.setMoments(&momentAverage3, &momentStandardDeviation3, &momentSkewness3);


	Blob blob(blobId, boxImage.rows, boxImage.cols);
	blob.human_id_actual = profileId;
	blob.addRegion(&region1);
	blob.addRegion(&region2);
	blob.addRegion(&region3);

	return blob;
}

MomentAverage MomentCalculation2::getAverageColourInConvexRegion(Mat image, Mat imageMask, Region *region)
{
	int pixelCount = 0;
	int startRow	= region->startRow;
	int endRow		= region->endRow;
	int startCol	= region->startCol;
	int endCol		= region->endCol;
	int tot0 = 0;
	int tot1 = 0;
	int tot2 = 0;
	double av0 = 0;
	double av1 = 0;
	double av2 = 0;
	for (int i = startRow; i < endRow; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			int mask = imageMask.at<uchar>(i, j);
			if (mask == 0){
				continue;
			}
			else{
				pixelCount++;

				tot0 += image.at<cv::Vec3b>(i, j)[0];
				tot1 += image.at<cv::Vec3b>(i, j)[1];
				tot2 += image.at<cv::Vec3b>(i, j)[2];

			}
		}
	}
	if (pixelCount != 0)
	{
		av0 = (double)tot0 / (double)pixelCount;
		av1 = (double)tot1 / (double)pixelCount;
		av2 = (double)tot2 / (double)pixelCount;

	}
	else
	{
		qFatal("Cannot Divide By Zero : Unknown Error");
	}
	
	MomentAverage momentAverage(av0, av1, av2);

	return momentAverage;


}

MomentStandardDeviation MomentCalculation2::getStandardDeviationInConvexRegion(Mat image, Mat imageMask, Region *region, MomentAverage *momentAverage)
{
	int pixelCount = 0;
	int startRow	= region->startRow;
	int endRow		= region->endRow;
	int startCol	= region->startCol;
	int endCol		= region->endCol;

	double av0 = momentAverage->channel0;
	double av1 = momentAverage->channel1;
	double av2 = momentAverage->channel2;

	double varSquareTot0 = 0;
	double varSquareTot1 = 0;
	double varSquareTot2 = 0;

	for (int i = startRow; i < endRow; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			int mask = imageMask.at<uchar>(i, j);
			if (mask == 0){
				continue;
			}
			else{
				pixelCount++;

				double original0 = image.at<cv::Vec3b>(i, j)[0];
				double original1 = image.at<cv::Vec3b>(i, j)[1];
				double original2 = image.at<cv::Vec3b>(i, j)[2];

				varSquareTot0 += pow(av0 - original0, 2);
				varSquareTot1 += pow(av1 - original1, 2);
				varSquareTot2 += pow(av2 - original2, 2);

			}
		}
	}

	double stdDev0 = varSquareTot0 / pixelCount;
	double stdDev1 = varSquareTot1 / pixelCount;
	double stdDev2 = varSquareTot2 / pixelCount;

	stdDev0 = pow(stdDev0, 0.5);
	stdDev1 = pow(stdDev0, 0.5);
	stdDev2 = pow(stdDev0, 0.5);
	MomentStandardDeviation momentStandardDeviation(stdDev0, stdDev1, stdDev2);

	return momentStandardDeviation;

}

MomentSkewness MomentCalculation2::getSkewnessnInConvexRegion(Mat image, Mat imageMask, Region *region, MomentAverage *momentAverage)
{
	int pixelCount = 0;
	int startRow	= region->startRow;
	int endRow		= region->endRow;
	int startCol	= region->startCol;
	int endCol		= region->endCol;

	double av0 = momentAverage->channel0;
	double av1 = momentAverage->channel1;
	double av2 = momentAverage->channel2;

	int tot0 = 0;
	int tot1 = 0;
	int tot2 = 0;

	double varCubeTot0 = 0;
	double varCubeTot1 = 0;
	double varCubeTot2 = 0;
	for (int i = startRow; i < endRow; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			int mask = imageMask.at<uchar>(i, j);
			if (mask == 0){
				continue;
			}
			else{
				pixelCount++;

				double original0 = image.at<cv::Vec3b>(i, j)[0];
				double original1 = image.at<cv::Vec3b>(i, j)[1];
				double original2 = image.at<cv::Vec3b>(i, j)[2];


				varCubeTot0 += pow(av0 - original0, 3);
				varCubeTot1 += pow(av1 - original1, 3);
				varCubeTot2 += pow(av2 - original2, 3);

			}
		}
	}
	double skew0 = varCubeTot0 / pixelCount;
	double skew1 = varCubeTot1 / pixelCount;
	double skew2 = varCubeTot2 / pixelCount;
	skew0 = cbrt(skew0);
	skew1 = cbrt(skew1);
	skew2 = cbrt(skew2);
	MomentSkewness momentSkewness(skew0, skew1, skew2);

	return momentSkewness;
}
