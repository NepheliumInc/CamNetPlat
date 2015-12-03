#include "svm__class.h"


SVM__Class::SVM__Class()
{

	Mat positive_float(1,1,CV_32FC1,1.0);
	Mat negative_float(1, 1, CV_32FC1, -1.0);
	this->negative_f = negative_float;
	this->positive_f = positive_float;

}

void SVM__Class::positiveTrainingSet(QString path){
	//QString path = "F:\\FYP related contents\\Training Data\\classified_data_box\\preparation_data\\human_r";
	fileIterator(path, &training_Descriptor, &positive_training_count,'p');
}

void SVM__Class::positiveTrainingSet(QString path, int number){		//overloaded mtd to take limited number of files
}

void SVM__Class::negativeTrainingSet(QString path){
	fileIterator(path, &training_Descriptor, &negative_training_count, 'n');
}


void SVM__Class::negativeTrainingSet(QString path, int number){		//overloaded mtd to take limited number of files
}

void SVM__Class::testingSet(Mat imagte_toPredict){
	
}

void SVM__Class::testingSet(QString path){		//overloaded mtd to take limited number of files
	fileIterator(path, &testing_Descriptor, &total_testing_count, 't');
	predict_svm();
}

void SVM__Class::train_svm(){
	
	params.svm_type = CvSVM::C_SVC; 
	params.kernel_type = CvSVM::POLY; // CvSVM::LINEAR; // CvSVM::POLY
	params.degree = 1.4;
	//params.gamma = 3;// change n check // Parameter gamma of a kernel function 
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6); 	// run for maximum 100 iterations//10
	params.C = 0.02;
	
	//print_Mat(&training_lable);

	svm.train(training_Descriptor, training_lable, Mat(), Mat(), params);
}

void SVM__Class::train_svmAndSave(string filename){
	train_svm();
	string FileMeasure = filename;
		int TempNumOne = FileMeasure.size();
	char Filename[100];
	for (int a = 0; a <= TempNumOne; a++)
	{
		Filename[a] = FileMeasure[a];
	}
	
	svm.save(Filename);
}

void SVM__Class::load_svm(string filename){
	string FileMeasure = filename;
	int TempNumOne = FileMeasure.size();
	char Filename[100];
	for (int a = 0; a <= TempNumOne; a++)
	{
		Filename[a] = FileMeasure[a];
	}
	svm.load(Filename);
}

void SVM__Class::predict_svm(){
	svm.predict(testing_Descriptor, testing_result);
	predicted_results = testing_result.reshape(1, 1);
}

bool SVM__Class::predict_Singlesvm(string filepath){
	Mat image;
	Mat resizedImage;
	Mat resizedGrayImage;
	Mat descriptor;
	Size resizeForHog(64, 128);
	Mat result;
	bool predicted_result = false;

	image = imread(filepath, CV_LOAD_IMAGE_COLOR);

	cv::resize(image, resizedImage, resizeForHog);
	cv::cvtColor(resizedImage, resizedGrayImage, CV_BGR2GRAY);
	//imshow("Image", resizedGrayImage); 
	HogDescriptor_Class hd;
	Mat mx = hd.generateDescriptorMat(resizedGrayImage);
	descriptor.push_back(mx);
	svm.predict(descriptor, result);
	float val = result.at<float>(0, 0);
	if (val == -1.0){
		predicted_result = false;
		qDebug() << "------------------------------------------ it is not human";
	}
	else if (val == 1.0)
	{
		predicted_result = true;
		qDebug() << "------------------------------------------ Human!!!!!!!!";
	}
	return predicted_result;
}

bool SVM__Class::predict_SingleSVMfromMat(Mat image){
	Mat resizedImage;
	Mat resizedGrayImage;
	Mat descriptor;
	Size resizeForHog(64, 128);
	Mat result;
	bool predicted_result = false;	

	cv::resize(image, resizedImage, resizeForHog);
	cv::cvtColor(resizedImage, resizedGrayImage, CV_BGR2GRAY);
	//imshow("Image", resizedGrayImage); 
	HogDescriptor_Class hd;
	Mat mx = hd.generateDescriptorMat(resizedGrayImage);
	descriptor.push_back(mx);
	svm.predict(descriptor, result);
	float val = result.at<float>(0, 0);
	if (val == -1.0){
		predicted_result = false;
		qDebug() << "------------------------------------------ it is not human";
	}
	else if (val == 1.0)
	{
		predicted_result = true;
		qDebug() << "------------------------------------------ Human!!!!!!!!";
	}
	return predicted_result;
}

void SVM__Class::show_predictionReport(){
	for (int r = 0; r < predicted_results.size().width; r++){
		if (predicted_results.at<float>(r) == 1.0){
			predicted_postive_count++;
		}
		else{
			predicted_negative_count++;

			cout << " negative : " << r << endl;
			//negatives_images[neg_img_count] = r;
			//neg_img_count++;
		}
		//cout << "testMat_lable" << i << "  : " << testMat_lable.at<int>(i) << endl;

	}
	qDebug() << "Positive count : " << positive_training_count << "\tNegative count : " << negative_training_count;
	qDebug() << "Testing Positive count : " << total_testing_count;
	qDebug() << "Training set height : " << training_Descriptor.size().height << "width : " << training_Descriptor.size().width;


	qDebug() << "positive : " << predicted_postive_count << endl;
	qDebug() << "negative : " << predicted_negative_count << endl;


	float accuracy = ((double)predicted_postive_count * 100) / ((double)predicted_postive_count + (double)predicted_negative_count);
	qDebug() << "accuracy is" << " : " << accuracy << "%" << endl;
}

void SVM__Class::fileIterator(QString filepath, Mat *descriptor, int *counter, char lable){
	QDirIterator imgIt(filepath, QDir::Files);
	QString  absolute_path;
	Size resizeForHog(64, 128);
	

	while (true)
	{
		if (!imgIt.hasNext())
			break;

		imgIt.next();
		QFileInfo fileInfo = imgIt.fileInfo();
		QString box_file_Name = fileInfo.fileName();
		absolute_path = fileInfo.absoluteFilePath();

		//qDebug() << absolute_path;
		std::string path = absolute_path.toStdString();

		Mat image;
		Mat resizedImage;
		Mat resizedGrayImage;

		image = imread(path, CV_LOAD_IMAGE_COLOR);

		cv::resize(image, resizedImage, resizeForHog);
		cv::cvtColor(resizedImage, resizedGrayImage, CV_BGR2GRAY);
		//imshow("Image", resizedGrayImage); 
		HogDescriptor_Class hd;
		Mat mx = hd.generateDescriptorMat(resizedGrayImage);
		(*descriptor).push_back(mx);
		
		if (lable== 'p'){
			training_lable.push_back(positive_f);
		}
		else if (lable == 'n'){
			training_lable.push_back(negative_f);
		}
		else if (lable == 't'){
			testing_result.push_back(positive_f);
		}	

		(*counter)++;
	}
	//__debugbreak();
}

void SVM__Class::print_Mat(Mat *mat_toprint){
	for (int i = 0; i < (*mat_toprint).rows; i++)
	{
		string line = "";
		for (int j = 0; j < (*mat_toprint).cols; j++)
		{
			float val = (*mat_toprint).at<float>(i, j);
			line += to_string(val) + ", ";

		}
		qDebug() << QString::fromStdString(line);
	}
}


SVM__Class::~SVM__Class()
{

}
