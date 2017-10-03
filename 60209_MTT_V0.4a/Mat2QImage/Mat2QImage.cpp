#include"Mat2QImage.h"
CMat2QImage::CMat2QImage():bConverted(false),imageSize(cvSize(0,0)),wndSize(cvSize(0,0))
{
	
}
bool CMat2QImage::importImage(const char *filename)
{
	if(filename)
	{
	orignImage=imread(filename,1);
	imageSize=orignImage.size();
	bConverted=false;
	return true;
	}
	else
	return false;
}
bool CMat2QImage::importImage(const cv::Mat &inputImage)//Not Clone
{
	//orignImage=inputImage.clone();
	orignImage=inputImage;
	imageSize=orignImage.size();
	bConverted=false;
	return true;
}
QImage* CMat2QImage::exportImage(const QSize &windowSize)
{
	wndSize.width=windowSize.width();
	wndSize.height=windowSize.height();
	convertImage=Mat(wndSize.width,wndSize.height,CV_8UC1);
	resize(orignImage,convertImage,wndSize);
	cvtColor(convertImage,convertImage,CV_BGR2RGB);
	outputImage=QImage((const unsigned char*)(convertImage.data),
                    convertImage.cols,convertImage.rows,
                    convertImage.cols*convertImage.channels(),
                    QImage::Format_RGB888);
	bConverted=true;
	return &outputImage;
}
CMat2QImage::~CMat2QImage()
{

}