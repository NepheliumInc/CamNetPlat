#ifndef BLOBDETECTION_H
#define BLOBDETECTION_H

#include "humanreident_global.h"

#include "opencv2/core/core.hpp"
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>

#include < opencv2\gpu\gpu.hpp>
#include < opencv2\legacy\legacy.hpp>

#include <QtCore\qstring.h>
#include <QtCore\qdebug.h>


using namespace cv;
using namespace std;
class HUMANREIDENT_EXPORT BlobDetection
{
public:

	vector<vector<Point>> detectContours(Mat frame, Ptr< BackgroundSubtractor>& pMOG2, Mat& fgMaskMOG2);
	//vector<vector<Point>> GPU_DetectContours(Mat o_frame, gpu::GpuMat o_frame_gpu, float& scaleX2, float& scaleY2);
	bool BlobDetection::isQualifyingContour(vector<Point> contour);
	vector<vector<Point>> detectEnclosingConvexHull(vector< vector< Point> >  contours);
	BlobDetection();
	~BlobDetection();


	Mat Mog_Mask;
	//gpu::GpuMat Mog_Mask_g, Mog_MaskMorpho_g;
	//gpu::MOG2_GPU pMOG2_g;


	////for 3channel blur
	//vector< gpu::GpuMat> gpurgb;
	//vector< gpu::GpuMat> gpurgb2;
	///////////////////////////////////////////////////////////////////////////
	Mat element;

	//gpu::GpuMat r_frame_gpu;
	//gpu::GpuMat r_frame2_gpu;
	//gpu::GpuMat rg_frame2_gpu;
	//gpu::GpuMat r_binary_gpu;
	//gpu::GpuMat r_blur_gpu;
	//gpu::GpuMat r_binary2_gpu;

};

#endif 

