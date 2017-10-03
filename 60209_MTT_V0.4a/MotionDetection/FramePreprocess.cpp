#include "FramePreprocess.h"


void CFramePreprocess::setBlur(bool _bSet,BLUR _type,cv::Size _size,double _sigma)
{
	m_setBlur=_bSet;
	m_blurType=_type;
	m_blurSize=_size;
	m_blurSigma=_sigma;
}
void CFramePreprocess::setResize(bool _bSet,cv::Size _size)
{
	m_setResize=_bSet;
	m_Resize=_size;
}
void CFramePreprocess::setCvtColor(bool _bCvtGray)
{
	m_setCvtColor=_bCvtGray;
}
void CFramePreprocess::process(cv::Mat &_inputFrame,cv::Mat &_outputFrame)
{
	cv::Mat frameTemp;
	frameTemp=_inputFrame.clone();
	if(m_setResize)
		cv::resize(frameTemp,frameTemp,m_Resize);
	if(m_setCvtColor)
		cv::cvtColor(frameTemp,frameTemp,CV_BGR2GRAY);
	if(m_setBlur)
		if(m_blurType==GAUSSIAN)
		{
			cv::GaussianBlur(frameTemp,frameTemp,m_blurSize,m_blurSigma);
		}
		else ;
	_outputFrame=frameTemp.clone();
}