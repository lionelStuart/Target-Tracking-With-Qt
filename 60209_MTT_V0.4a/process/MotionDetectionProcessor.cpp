#include "MotionDetectionProcessor.h"
#include"Counter/TickCount.h"
#include<iostream>
#include<sstream>
#include<fstream>
CMotionDetectionProcessor::CMotionDetectionProcessor(void):
m_md(NULL)
{
	if(!m_md)m_md=new MyMD;
	m_maskImage=cv::Mat(10,10,CV_8UC1);
}

CMotionDetectionProcessor::~CMotionDetectionProcessor(void)
{
	if(m_md)delete m_md;
}
void CMotionDetectionProcessor::process(const cv::Mat &_input,cv::Mat &_output)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	m_md->process(_input,m_detectRects,m_maskImage);
	for(int i=0;i!=m_detectRects.size();i++){
		cv::rectangle(_output,m_detectRects[i],cv::Scalar(0,255,0));
	}
	m_frameRate=1.0/counter.endCount();
	std::stringstream tempStream;
	tempStream.precision(4);
	tempStream<<"FrameID:  "<<getParents()->frameID()<<"   FrameRate:  "<<m_frameRate;
	std::string temp=tempStream.str();
	if(getParents()->frameSize().height>400){
		cv::putText(_output,temp,cv::Point(20,30),cv::FONT_HERSHEY_TRIPLEX,0.6,cv::Scalar(0,255,0),1,8,false);
	}
	else{
		cv::putText(_output,temp,cv::Point(10,15),cv::FONT_HERSHEY_TRIPLEX,0.3,cv::Scalar(0,255,0),1,8,false);
	}
}
