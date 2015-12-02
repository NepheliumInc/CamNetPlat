#include "stdafx.h"

#include "humanreident.h"

#include "BlobDetection.h"
#include < time.h>

#define RWIDTH 320 //640 //800
#define RHEIGHT 240 //480 //600

#define RWIDTH2 800
#define RHEIGHT2 600

#define MIN_BLOB 10
#define MAX_BLOB 500

BlobDetection::BlobDetection()
{
	//pMOG2_g = gpu::MOG2_GPU(30);
	//pMOG2_g.history = 3000; //300;
	//pMOG2_g.varThreshold = 128; //64; //128; //64; //32;//; 
	//pMOG2_g.bShadowDetection = false; // true;//

	//gpurgb2 = vector< gpu::GpuMat>(3);
	//gpurgb = vector< gpu::GpuMat>(3);

	element = getStructuringElement(MORPH_RECT, Size(9, 9), Point(4, 4));
}


BlobDetection::~BlobDetection()
{
}

vector< vector< Point> > BlobDetection::detectContours(Mat frame, Ptr< BackgroundSubtractor>& pMOG2Pointer , Mat& fgMaskMOG2)
{
	vector< vector< Point> > result;

	Mat fgMaskMOG2X = fgMaskMOG2.clone(); 

	Mat ContourImg; 
	Ptr< BackgroundSubtractor> pMOG2 = pMOG2Pointer; 
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));


	//PreProcess
	blur(frame, frame, Size(4, 4));

	//Background subtraction
	pMOG2->operator()(frame, fgMaskMOG2X, -1);
	morphologyEx(fgMaskMOG2X, frame, CV_MOP_CLOSE, element);
	//threshold(frame, frame, 100, 180, CV_THRESH_BINARY);

	ContourImg = frame.clone();
	findContours(ContourImg,
		result, // a vector of contours
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_NONE); // all pixels of each contours


	fgMaskMOG2 = fgMaskMOG2X.clone();
	return result;
}
/*
vector<vector<Point>> BlobDetection::GPU_DetectContours(Mat o_frame, gpu::GpuMat o_frame_gpu, float& scaleX2, float& scaleY2)
{

	//scale and check processing time
	float scaleX = float(o_frame.size().width) / RWIDTH;
	float scaleY = float(o_frame.size().height) / RHEIGHT;
	scaleX2 = RWIDTH2 / float(RWIDTH);
	scaleY2 = RHEIGHT2 / float(RHEIGHT);

	unsigned long AAtime = 0, BBtime = 0;
	const clock_t begin_time = clock(); // by niro

	//get frame and upload to gpu
	o_frame_gpu.upload(o_frame);

	//resize
	gpu::resize(o_frame_gpu, r_frame_gpu, Size(RWIDTH, RHEIGHT)); //for blob labeling
	//gpu::resize(o_frame_gpu, r_frame2_gpu, Size(RWIDTH2, RHEIGHT2)); //for FREAK featrue 
	//r_frame_gpu = o_frame_gpu.clone();
	//r_frame2_gpu = o_frame_gpu.clone();
	//AAtime = getTickCount();
	//blur
	gpu::split(r_frame_gpu, gpurgb);
	gpu::blur(gpurgb[0], gpurgb2[0], Size(3, 3));
	gpu::blur(gpurgb[1], gpurgb2[1], Size(3, 3));
	gpu::blur(gpurgb[2], gpurgb2[2], Size(3, 3));
	gpu::merge(gpurgb2, r_blur_gpu);
	//mog
	pMOG2_g.operator()(r_blur_gpu, Mog_Mask_g, -1);
	Mog_Mask_g.download(Mog_Mask);
	//mopnology
	//gpu::morphologyEx(Mog_Mask_g, Mog_MaskMorpho_g, CV_MOP_CLOSE, element);
	gpu::morphologyEx(Mog_Mask_g, Mog_MaskMorpho_g, CV_MOP_DILATE, element);
	//binary
	gpu::threshold(Mog_MaskMorpho_g, r_binary_gpu, 128, 255, CV_THRESH_BINARY);
	//Blob Labeling
	//Find contour   
	Mat ContourImg;
	r_binary_gpu.download(ContourImg);
	//less blob delete   
	vector< vector< Point> > contours;
	findContours(ContourImg,
		contours, // a vector of contours   
		CV_RETR_EXTERNAL, // retrieve the external contours   
		CV_CHAIN_APPROX_NONE); // all pixels of each contours  

	vector< Rect > output;
	vector< vector< Point> >::iterator itc = contours.begin();

	///Display  
	//Mat showMat2_r;
	//r_frame2_gpu.download(showMat2_r);

	//Blob labeling
	while (itc != contours.end()) {

		//Create bounding rect of object   
		//rect draw on origin image   
		Rect mr = boundingRect(Mat(*itc));

		mr.x = mr.x * scaleX;
		mr.y = mr.y * scaleY;
		mr.width = mr.width * scaleX;
		mr.height = mr.height * scaleY;

		rectangle(o_frame, mr, CV_RGB(255, 0, 0), 2);
		++itc;
	}

	//processing time print
	//BBtime = getTickCount();
	//float pt = (BBtime - AAtime) / getTickFrequency();
	//float fpt = 1 / pt;
	//printf("gpu %.4lf / %.4lf \n", pt, fpt);
	float time = float(clock() - begin_time) / CLOCKS_PER_SEC;
	qDebug() << "Back ground Substraction Time in GPU" << time;// by niro

	//Display 
	//Mat showMat_r_blur;
	//Mat showBinary;
	//r_binary_gpu.download(showBinary);
	//imshow("binary2", showBinary);
	//Mog_Mask_g.download(Mog_Mask);
	//r_blur_gpu.download(showMat_r_blur);
	//imshow("blur", showMat_r_blur);
	//imshow("origin", showMat2_r);
	//imshow("mog_mask", Mog_Mask);
	/////////////////////////////////////////////////////////////////////////

	return contours;


}
*/
bool BlobDetection::isQualifyingContour(vector<Point> contour)
{ 
	bool result = false;
	int minimum_width = 30;//30;
	int maximum_width = 180;//100;
	int minimum_height = 30;// 30;
	double minimum_htow_ratio = 1.3;
	Rect roi = boundingRect(contour);
	double heightToWidthRatio = static_cast<double>(roi.height) / static_cast<double>(roi.width);
	if (	roi.width			>	minimum_width	&&
			roi.width			<	maximum_width	&&
			roi.height			>	minimum_height	&&
			heightToWidthRatio	>	minimum_htow_ratio
		)
	{
		result = true;
	}

	//second test
	// pointPolygonTest(InputArray contour, Point2f pt, bool measureDist)


	return result;
	

}
bool BlobDetection::isQualifyingContour(vector<Point> contour, vector<vector<Point>>cutOffRegions)
{
	bool result = false;
	int minimum_width = 30;//30;
	int maximum_width = 180;//100;
	int minimum_height = 30;// 30;
	double minimum_htow_ratio = 1.3;
	Rect roi = boundingRect(contour);
	double heightToWidthRatio = static_cast<double>(roi.height) / static_cast<double>(roi.width);
	if (roi.width			>	minimum_width	&&
		roi.width			<	maximum_width	&&
		roi.height			>	minimum_height	&&
		heightToWidthRatio	>	minimum_htow_ratio
		)
	{
		result = true;
	}

	//second test
	// pointPolygonTest(InputArray contour, Point2f pt, bool measureDist)
	//Performs a point - in - contour test.
	//contour – Input contour.
	//pt – Point tested against the contour.
	//measureDist – If true, the function estimates the signed distance from the point to the nearest contour edge.Otherwise, the function only checks if the point is inside a contour or not.
	//The function determines whether the point is inside a contour, outside, or lies on an edge(or coincides with a vertex).It returns positive(inside), negative(outside), or zero(on an edge) value, correspondingly.When measureDist = false, the return value is + 1, -1, and 0, respectively.Otherwise, the return value is a signed distance between the point and the nearest contour edge.
	//See below a sample output of the function where each image pixel is tested against the contour.


	return result;


}


vector<BlobId> BlobDetection::matchProfilesWithBlobs(vector< vector< Point> > contours, string absoluteTime, string cameraNode){
	HumanHits hh;
	vector<BlobId> profiledBlobs;
	vector<Profile> profilesExisting = hh.getAllProfilesInSecond(absoluteTime, cameraNode);

	//Start comparing blob with existing profile
	int counter = 0;
	for (vector< Point> contour : contours)
	{
		//Find centre of blob
		Moments mom = moments(contour, false);
		Point2f currentCentrePoint = Point2f(mom.m10 / mom.m00, mom.m01 / mom.m00);

		//Map blob to profile, if not found set to UNKNOWN
		double minDistance = -1;
		string minProfile = "UNKNOWN";
		for (int profileCount = 0; profileCount < profilesExisting.size(); profileCount++)
		{
			Profile savedProfile = profilesExisting[profileCount];
			double distance = sqrt(
				(currentCentrePoint.x - savedProfile.centreX)*(currentCentrePoint.x - savedProfile.centreX)
				+
				(currentCentrePoint.y - savedProfile.centreY)*(currentCentrePoint.y - savedProfile.centreY)
				);
			if (minDistance = -1 || minDistance > distance)
			{
				minDistance = distance;
				minProfile = savedProfile.profileId;
				profilesExisting.erase(profilesExisting.begin() + profileCount);
			}

		}
		BlobId blobId;
		blobId.Id = minProfile;
		blobId.surroundingContours = contour;
		blobId.centreX = currentCentrePoint.x;
		blobId.centreY = currentCentrePoint.y;
		profiledBlobs.push_back(blobId);
		counter++;
	}



	return profiledBlobs;
}


vector< vector< Point> > BlobDetection::detectEnclosingConvexHull(vector<vector<Point>> contours)
{
	vector< vector< Point> > hull;
	return hull;
}