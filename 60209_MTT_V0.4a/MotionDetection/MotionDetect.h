#pragma once
#include<opencv2/opencv.hpp>
//输入图像为配准后的图像对
class CMotionDetect
{
public:
	CMotionDetect(void):m_bMhiInit(false){}
	~CMotionDetect(void);
	void difference(const cv::Mat &_inputFrame1,const cv::Mat &_inputFrame2,cv::Mat &difference,int _ROIBound=20);
	void morphology(const cv::Mat &_difference,cv::Mat &_output,int _openScale,int _closeScale);
	void motionHistory(const cv::Mat &_difference,cv::Mat &segmentMask,std::vector<cv::Rect> &_orignRects);
private:
	bool m_bMhiInit;
	cv::Mat m_mhi;
};

