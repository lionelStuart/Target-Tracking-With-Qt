#include "trackProcessor.h"
#include"Counter/TickCount.h"
trackProcessor::trackProcessor(void):
m_tracker(NULL),m_trackingBox(0,0,0,0),m_bInited(false)
{
	m_tracker=new CMyTracker();
}
trackProcessor::~trackProcessor(void)
{
	if(m_tracker)
		delete m_tracker;
}
void trackProcessor::init(const std::string &_trackingType,const cv::Rect &_rect)
{
	setRect(_rect);
	selectTrackingType(_trackingType);
}
void trackProcessor::setRect(const cv::Rect &_rect)
{
	m_bInited=false;
	m_trackingBox=cv::Rect(0,0,0,0);
	if(_rect.width!=0&&_rect.height!=0)
	m_trackingBox=_rect;
}
void trackProcessor::selectTrackingType(const std::string &_trackingType)
{
	if(_trackingType=="CT"){
		m_tracker->create(TRACKER_TYPE_CT);
	}
	if(_trackingType=="Hash"){
		m_tracker->create(TRACKER_TYPE_HASH);
	}
	if(_trackingType=="KCF"){
		m_tracker->create(TRACKER_TYPE_KCF);
	}
	if(_trackingType=="PF"){
		m_tracker->create(TRACKER_TYPE_PF);
	}
	if(_trackingType=="STC"){
		m_tracker->create(TRACKER_TYPE_STC);
	}
	if(_trackingType=="STRUCK"){
		m_tracker->create(TRACKER_TYPE_STRUCK);
	}
}
void trackProcessor::process(const cv::Mat &_input,cv::Mat &_output)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	if(!m_bInited)
	{
		if(m_trackingBox.width!=0&&m_trackingBox.height!=0)
		{
			m_tracker->init(_input,m_trackingBox);
			m_bInited=true;
		}
	}
	else
	{
		m_tracker->tracking(_input,m_trackingBox);
		drawEvent(_output,m_trackingBox);
	}
	m_frameRate=1.0/counter.endCount();
}
void trackProcessor::drawEvent(cv::Mat &_image,cv::Rect &_box)
{
	cv::rectangle(_image,_box,cv::Scalar::all(200));
	stringstream tempStream;
	tempStream<<"FrameID:  "<<getParents()->frameID()
		<<"  Target   X:  "<<_box.x<<" Y:  "<<_box.y<<" W:  "<<_box.width<<" H:  "<<_box.height;
	std::string temp=tempStream.str();
	tempStream.str("");
	tempStream.precision(3);
	tempStream<<"FrameRate: "<<m_frameRate;
	std::string temp2=tempStream.str();
	if(getParents()->frameSize().height>400){
		cv::putText(_image,temp,cv::Point(20,30),FONT_HERSHEY_TRIPLEX,0.6,cv::Scalar(0,255,0),1,8,false);
		cv::putText(_image,temp2,cv::Point(20,60),FONT_HERSHEY_TRIPLEX,0.6,cv::Scalar(0,255,0),1,8,false);
	}
	else{
		cv::putText(_image,temp,cv::Point(10,15),FONT_HERSHEY_TRIPLEX,0.3,cv::Scalar(0,255,0),1,8,false);
		cv::putText(_image,temp2,cv::Point(10,30),FONT_HERSHEY_TRIPLEX,0.3,cv::Scalar(0,255,0),1,8,false);
	}
	
	
}