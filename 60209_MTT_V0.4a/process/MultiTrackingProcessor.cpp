#include "MultiTrackingProcessor.h"
#include "Detector/CMyDetector.h"
#include "MultiTargetTracker/MultiTargetTracker.h"
#include"Counter/TickCount.h"
#include<iostream>
#include<sstream>
#include<fstream>
CMultiTrackingProcessor::CMultiTrackingProcessor(void)
	:m_detector(NULL),m_tracker(NULL),m_minSize(MTT_DEFAULT_MINSIZE),
	m_maxSize(MTT_DEFAULT_MAXSIZE)
{
	m_detector=new CMyDetector();
	m_tracker=new CMultiTargetTracker();
}


CMultiTrackingProcessor::~CMultiTrackingProcessor(void)
{
	if(m_detector)
		delete m_detector;
	if(m_tracker)
		delete m_tracker;
}
void CMultiTrackingProcessor::process(const cv::Mat &_input,cv::Mat &_output)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	if(m_bInited){
		m_detectRects.clear();
		m_detector->detect(_input,m_detectRects);
		detectionFilter(m_detectRects,m_minSize,m_maxSize);
		m_tracker->update(getParents()->frameID(),m_detectRects);
		const std::vector<CDetectionBox> &detection=m_tracker->getDetection();
		for(int i=0;i!=detection.size();i++)
		{
			if(detection[i].m_pixID!=-1&&detection[i].m_length>10)
			{
				rectangle(_output,detection[i].m_box,cv::Scalar::all(80),2);
				putText(_output,to_string((_ULonglong)detection[i].m_pixID),detection[i].m_center,CV_FONT_NORMAL,1,cv::Scalar(0,255,0));
			}
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
void CMultiTrackingProcessor::init(const std::string &_classifierFilePath)
{
	if(m_detector){
		m_detector->set(_classifierFilePath);
		m_bInited=true;
	}
}
void CMultiTrackingProcessor::clear()
{
	m_bInited=false;
	m_minSize=MTT_DEFAULT_MINSIZE;
	m_maxSize=MTT_DEFAULT_MAXSIZE;
	if(m_tracker){
		delete m_tracker;
		m_tracker=new CMultiTargetTracker();
	}
}
void CMultiTrackingProcessor::setDetectionFilter(int _minSize/* =-1 */,int _maxSize/* =-1 */)
{
	if(_minSize!=-1&&_minSize<m_maxSize){
		m_minSize=_minSize;
	}
	if(_maxSize!=-1&&_maxSize>m_minSize){
		m_maxSize=_maxSize;
	}
}
