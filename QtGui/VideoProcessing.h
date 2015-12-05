#include <opencv2\highgui\highgui.hpp>	// open cv
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>
#include "Models.h"
#include "graph.h"
#include "BlobDetection.h"
#include "svm__class.h"
#include "Logger.h"

// blob detection
// in	: *frame
// out	: contours

// human detection
// in	: *contours, *frame
// out	: filtered_contours

// kalman filtering

// comparison algo (get relevent contours)

using namespace std;
using namespace cv;


class VideoProcessing
{
public:
	VideoProcessing();
	int blobDetection(Mat frame, Ptr<BackgroundSubtractor> pMOG2, Mat mask, vector<models::Blob> *outBlobs, vector<Point> cutOffRegions, vector<vector<Point>>* blobsInCutoff);
	int GPU_BlobDetection(Mat frame, Ptr<BackgroundSubtractor> pMOG2, Mat mask, vector<models::Blob> *outBlobs, vector<Point> cutOffRegions, vector<vector<Point>>* blobsInCutoff);
	int humanDetection(vector<models::Blob> *blobs, Mat *frame, vector<models::HumanBlob> *outHumanBlobs, VideoCapture *cap, string link, SVM__Class* svmPointer, Connection* mySqlConnection, vector<string>* profilesInASecondToBeLoggInDB, vector<string>* currentProcessingSecond);
	void dataAssociation(
		vector<models::Blob> *blobs,
		vector<models::HumanBlob> *trackingHumanBlobs,
		vector<models::Blob> *outUnidentifiedBlobs,
		vector<models::MissingHumanBlob> *outMissingHumanBlobs);

	void checkInProfiles(
		vector<models::HumanBlob> *humanList,
		vector<models::HumanBlob> *possibleList,
		vector<models::MissingHumanBlob> *missingList,
		vector<models::HumanBlob> *trackingList);

	void initTrackingObject(vector<models::HumanBlob> *humanList, vector<models::HumanBlob> *trackingList);

	void kalmanCorrectAndPredict(vector<models::HumanBlob> *trackingList);

	void informAdjecentNodes(vector<graph::ExitPoint> *exitsList, vector<models::HumanBlob> *trackingList);

	~VideoProcessing();

private:
	Mat morpho_ele = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));
	BlobDetection blbDetect;
protected:

};