#include<time.h>
#include "MotionDetect.h"

using namespace cv;

CMotionDetect::~CMotionDetect(void)
{
	
}
void CMotionDetect::difference(const cv::Mat &_inputFrame1,const cv::Mat &_inputFrame2,cv::Mat &_difference,int _ROIBound)
{
	Mat frame=_inputFrame1;
	Mat warpROI=_inputFrame1(Rect(_ROIBound,_ROIBound,frame.cols-_ROIBound*2,frame.rows-_ROIBound*2));
	Mat frameROI=_inputFrame2(Rect(_ROIBound,_ROIBound,frame.cols-_ROIBound*2,frame.rows-_ROIBound*2));
	_difference=Mat::zeros(cv::Size(frame.cols,frame.rows),CV_8UC1);
	Mat diffROI=_difference(Rect(_ROIBound,_ROIBound,frame.cols-_ROIBound*2,frame.rows-_ROIBound*2));
	absdiff(frameROI,warpROI,diffROI);
	Mat thresholds;
	cv::threshold(_difference,_difference,30,255,CV_THRESH_BINARY);
}
void CMotionDetect::morphology(const cv::Mat &_difference,cv::Mat &_output,int _openScale,int _closeScale)
{
	cv::Mat elementClose(_closeScale,_closeScale,CV_8U,cv::Scalar(1));
	cv::Mat close;
	cv::morphologyEx(_difference,close,cv::MORPH_CLOSE,elementClose);
	cv::Mat elementOpen(_openScale,_openScale,CV_8U,cv::Scalar(1));
	//cv::Mat open;
	cv::morphologyEx(close,_output,cv::MORPH_OPEN,elementOpen);
	
}
void CMotionDetect::motionHistory(const cv::Mat &_difference,cv::Mat &segmentMask,std::vector<cv::Rect> &_orignRects)
{
	double timestamp = (double)clock()/CLOCKS_PER_SEC;
	if(!m_bMhiInit)
	{
		m_mhi= cv::Mat(cv::Size(_difference.cols,_difference.rows),CV_32FC1);
		m_bMhiInit=true;
	}
	updateMotionHistory(_difference,m_mhi,timestamp,1);
	segmentMotion(m_mhi,segmentMask,_orignRects,timestamp,0.5);
}