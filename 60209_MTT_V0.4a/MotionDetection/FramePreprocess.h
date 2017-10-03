#pragma once
#include<opencv2/opencv.hpp>

enum BLUR { GAUSSIAN, NONE };

class CFramePreprocess
{
public:

	CFramePreprocess():m_setBlur(false),m_setResize(false),m_setCvtColor(false){}
	void setBlur(bool _bSet,const BLUR _type=NONE,cv::Size _size=cv::Size(0,0),double _sigma=0);
	void setResize(bool _bSet,cv::Size _size=cv::Size(0,0));
	void setCvtColor(bool _bCvtGray);
	void process(cv::Mat &_inputFrame,cv::Mat &_outputFrame);
private:
	bool m_setBlur;
	bool m_setResize;
	bool m_setCvtColor;
	BLUR m_blurType;
	cv::Size m_blurSize;
	double m_blurSigma;
	cv::Size m_Resize;
};

