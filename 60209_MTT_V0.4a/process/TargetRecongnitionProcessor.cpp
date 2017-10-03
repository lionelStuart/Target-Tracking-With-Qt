#include "TargetRecongnitionProcessor.h"
#include "Detector/CMyDetector.h"
#include"Counter/TickCount.h"
#include<iostream>
#include<sstream>
#include<fstream>
CTargetRecongnitionProcessor::CTargetRecongnitionProcessor(void):
m_detector(NULL),m_bInited(false),m_minSize(0),m_maxSize(TARGETMAXSIZE)
{
	m_detector=new CMyDetector();
}

CTargetRecongnitionProcessor::~CTargetRecongnitionProcessor(void)
{
	if(m_detector)
		delete m_detector;
}
void CTargetRecongnitionProcessor::process(const cv::Mat &_input,cv::Mat &_output)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	if(m_bInited){
		m_rects.clear();
		std::vector<cv::Rect> tempRects;
		m_detector->detect(_input,tempRects);
		for(int i=0;i!=tempRects.size();i++){
			if(tempRects[i].width>m_minSize&&tempRects[i].width<m_maxSize){
				m_rects.push_back(tempRects[i]);
			}
		}
		for(int i=0;i!=m_rects.size();i++){
			cv::rectangle(_output,m_rects[i],cv::Scalar(0,255,0));
		}
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
void CTargetRecongnitionProcessor::init(const std::string &_classifierFilePath)
{
	if(m_detector){
		m_detector->set(_classifierFilePath);
		m_bInited=true;
	}
}
void CTargetRecongnitionProcessor::setFilterSize(int _minWidth/* =-1 */,int _maxWidth/* =-1 */)
{
	if(_maxWidth!=-1&&_maxWidth>0&&m_minSize<_maxWidth){
		m_maxSize=_maxWidth;
	}
	if(_minWidth!=-1&&_minWidth>0&&_minWidth<m_maxSize){
		m_minSize=_minWidth;
	}
}
void CTargetRecongnitionProcessor::clear()
{
	m_bInited=false;
}
