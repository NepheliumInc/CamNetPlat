#include "tester_class.h"

Tester_class::Tester_class()
{

}

void Tester_class::get_path()
{
	QString index = "F:\\FYP related contents\\Training Data\\classified_data_box\\preparation_data\\human_r";
	QDirIterator imgIt(index, QDir::Files);
	QString  absolute_path;
	while (true)
	{
		if (!imgIt.hasNext())
			break;
		//qDebug() << 
		imgIt.next();
		QFileInfo fileInfo = imgIt.fileInfo();
		QString box_file_Name = fileInfo.fileName();
		absolute_path = fileInfo.absoluteFilePath();
		//fileInfo.
		qDebug() << absolute_path;
		std::string path = absolute_path.toStdString();
				
		cv::Mat image;
		image = cv::imread(path, CV_LOAD_IMAGE_COLOR);
		cv::imshow("Image", image);


	}
	cv::waitKey(4000);
	qDebug() << "Completed succesfully";
}

void Tester_class::hog_PeopelDetectorTest(String path){
		Mat img = imread(path);
		HOGDescriptor hog;
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
		namedWindow("people detector", 1);
		vector<Rect> found, found_filtered;
		double t = (double)getTickCount();
		// run the detector with default parameters. to get a higher hit-rate
	
		// (and more false alarms, respectively), decrease the hitThreshold and
	
		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
		hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
		t = (double)getTickCount() - t;
		printf("tdetection time = %gms\n", t*1000. / cv::getTickFrequency());
		size_t i, j;
	
		for (i = 0; i < found.size(); i++)
		{
			Rect r = found[i];
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			if (j == found.size())
				found_filtered.push_back(r);
		}
	
		for (i = 0; i < found_filtered.size(); i++)
		{
			Rect r = found_filtered[i];
			// the HOG detector returns slightly larger rectangles than the real objects.
			// so we slightly shrink the rectangles to get a nicer output.
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}
		imshow("people detector", img);
		cvWaitKey(0);

}

Tester_class::~Tester_class()
{

}
