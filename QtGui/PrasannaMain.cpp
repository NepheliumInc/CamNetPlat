#include "tester_class.h"
#include "svm__class.h"

int main(int argc, char* argv[])
{
	bool result=false; 
	SVM__Class svm_cam1;	
	//svm_cam1.positiveTrainingSet("F:\\FYP related contents\\Training Data\\classified_data_box\\preparation_data\\human_r");
	//svm_cam1.negativeTrainingSet("F:\\FYP related contents\\Training Data\\classified_data_box\\preparation_data\\not_human_r");
	//svm_cam1.train_svm();
	//svm_cam1.train_svmAndSave("camera6.xml");
	svm_cam1.load_svm("camera6.xml");
	result= svm_cam1.predict_Singlesvm("C:\\Users\\Prasanna\\Desktop\\group_blobJPG.JPG");
	qDebug() << "************ From main result: " << result << "***************";
	//svm_cam1.testingSet("F:\\FYP related contents\\Training Data\\classified_data_box\\svm_data");

	//svm_cam1.show_predictionReport();
	

	qDebug() << "Programme exited succesfully";
	return 0;

}