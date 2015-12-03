#include "hogdescriptor_class.h"

HogDescriptor_Class::HogDescriptor_Class()
{


}

Mat HogDescriptor_Class::generateDescriptorMat(Mat img){

	HOGDescriptor hogd(
		Size(64, 128),	//window Size of image
		Size(16, 16),	//blocksize
		Size(8, 8),		//blockStride,
		Size(8, 8),		//cellSize,
		9,				//nbins,
		0,				 //derivAper,//derivAperture bool
		-1,				 //winSigma,
		0,				//histogramNormType, 0 means L2Hys L2HysTheshold =0.2
		0.2,			//L2HysThresh,
		0				//gammal correction,
		//nlevels=64
		);
	Size winStride(8, 8);
	Size padding(0, 0);

	hogd.compute(img, descriptorsValues, Size(8, 8), Size(0, 0));

	Mat descriptorsValues_mat = Mat(descriptorsValues);
	if (!descriptorsValues_mat.isContinuous()){
		std::cout << "ERROR : descriptorsValuesMat NOT CONTINUOUS------------: " << endl;		
	}
	return descriptorsValues_mat.reshape(0, 1);
}

HogDescriptor_Class::~HogDescriptor_Class()
{

}
