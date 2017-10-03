#include "CoopLocatoinProcessor.h"
#include "VideoProcessor/VideoProcessor.h"						//视频处理类
#include "Detector/CMyDetector.h"								//检测器
#include "MultiTargetTracker/MultiTargetTracker.h"				//多目标跟踪器
#include "CooperativeLocation/CooperativeLocalization.h"		//协同定位
#include<iostream>
#include<sstream>
#include<fstream>
#include"Counter/TickCount.h"
//CLASS CSingleTaskProcessor
CSingleTaskProcessor::CSingleTaskProcessor():
m_video(NULL),m_detector(NULL),m_tracker(NULL),
m_bInitVideo(false),m_bInitDetector(false),m_bInitTracker(false)
{
	m_video=new VideoProcessor();
	m_detector=new CMyDetector();
	m_tracker=new CMultiTargetTracker();
}
CSingleTaskProcessor::~CSingleTaskProcessor()
{
	if(m_video)
		delete m_video;
	if(m_detector)
		delete m_detector;
	if(m_tracker)
		delete m_tracker;
}
void CSingleTaskProcessor::clear()
{
	m_bInitVideo=false;
	m_bInitDetector=false;
	m_bInitTracker=false;
	if(m_tracker){
		delete m_tracker;
		m_tracker=new CMultiTargetTracker();
	}
	
}
void CSingleTaskProcessor::initVideo(const std::string &_videoFilePath)
{
	if(m_video){
		if(m_video->load(_videoFilePath))
			m_bInitVideo=true;
	}
}
void CSingleTaskProcessor::initDetector(const std::string &_classifierFilePath)
{
	if(m_detector){
		m_detector->set(_classifierFilePath);
		m_bInitDetector=true;
	}
}
void CSingleTaskProcessor::initTracker(const std::string &_poseFilePath)
{
	if(m_tracker&&m_bInitVideo){
		m_tracker->setVO(_poseFilePath,m_video->frameSize(),setFovFromFile(_poseFilePath));
		m_bInitTracker=true;
	}
}
void CSingleTaskProcessor::processFrame(cv::Mat &_outputFrame)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	if(m_bInitTracker&&m_bInitDetector&&m_bInitVideo){
		m_video->process(_outputFrame);
		cv::Mat gray;
		cv::cvtColor(m_video->currentFrame(),gray,CV_BGR2GRAY);
		std::vector<cv::Rect>rects;
		m_detector->detect(gray,rects);
		detectionFilter(rects,30,80);
		m_tracker->update(m_video->frameID(),rects);
		for(int i=0;i!=m_tracker->getDetection().size();i++)
		{
			if(m_tracker->getDetection()[i].m_length>10&&
				m_tracker->getDetection()[i].m_pixID!=-1){
					cv::rectangle(_outputFrame,m_tracker->getDetection()[i].m_box,cv::Scalar(0,255,0),2);
					cv::putText(_outputFrame,to_string((_ULONGLONG)(m_tracker->getDetection()[i].m_pixID)),
						m_tracker->getDetection()[i].m_center,CV_FONT_NORMAL,1,cv::Scalar(0,255,0),1);
			}
		}
	}
	m_frameRate=1.0/counter.endCount();
	std::stringstream tempStream;
	tempStream.precision(4);
	tempStream<<"FrameID:  "<<m_video->frameID()<<"   FrameRate:  "<<m_frameRate;
	std::string temp=tempStream.str();
	if(m_video->frameSize().height>400){
		cv::putText(_outputFrame,temp,cv::Point(20,50),cv::FONT_HERSHEY_TRIPLEX,1.2,cv::Scalar(0,255,0),1,8,false);
	}
	else{
		cv::putText(_outputFrame,temp,cv::Point(10,30),cv::FONT_HERSHEY_TRIPLEX,0.6,cv::Scalar(0,255,0),1,8,false);
	}
}
double CSingleTaskProcessor::setFovFromFile(const std::string &_poseFilePath)
{
	if(!_poseFilePath.empty()){
		std::ifstream myFile(_poseFilePath);
		if(myFile.is_open()){
			std::string line;
			std::getline(myFile,line);
			std::string model="fov";
			std::size_t index=0;
			index=line.rfind(model);
			std::string strFov=line.substr(index+3,line.size());
			std::istringstream in(strFov);
			double temp=0;
			in>>temp;
			return temp;
		}
	}
	return 0;
}
//CLASS CCoopLocatoinProcessor
CCoopLocatoinProcessor::CCoopLocatoinProcessor(void):
m_task_1(NULL),m_task_2(NULL),m_coopLocator(NULL),m_mapper(NULL),m_timer(NULL),
m_bInitMapper(false),m_bIsRun(false)
{
	m_task_1=new CSingleTaskProcessor;
	m_task_2=new CSingleTaskProcessor;
	m_coopLocator=new CCooperativeLocalization;
	m_mapper=new CDrawMap;
	CMultiTargetTracker *trackers[]={m_task_1->getMTT(),m_task_2->getMTT()};
	m_coopLocator->init(trackers,2);
}

CCoopLocatoinProcessor::~CCoopLocatoinProcessor(void)
{
	if(m_task_1)
		delete m_task_1;
	if(m_task_2)
		delete m_task_2;
	if(m_coopLocator)
		delete m_coopLocator;
	if(m_mapper)
		delete m_mapper;
	if(m_timer)
		delete m_timer;
}
void CCoopLocatoinProcessor::clear()
{
	m_bInitMapper=false;
	m_bIsRun=false;
	if(m_task_1)
		m_task_1->clear();
	if(m_task_2)
		m_task_2->clear();
	if(m_coopLocator){
		delete m_coopLocator;
		m_coopLocator=new CCooperativeLocalization();
		CMultiTargetTracker *trackers[]={m_task_1->getMTT(),m_task_2->getMTT()};
		m_coopLocator->init(trackers,2);
	}
	if(m_mapper){
		delete m_mapper;
		m_mapper=new CDrawMap();
	}
}
void CCoopLocatoinProcessor::initTimer()
{
	if(!m_timer)
	m_timer=new QTimer();
	connect(m_timer,SIGNAL(timeout()),this,SLOT(run()));
	m_timer->start(20);
}
void CCoopLocatoinProcessor::initMapper(const std::string &_mapPath,double _GeoMapWidth/* =-1 */,double _GeoMapHeight/* =-1 */)
{
	if(_GeoMapHeight!=-1&&_GeoMapWidth!=-1&&!_mapPath.empty()&&m_coopLocator){
			m_map=cv::imread(_mapPath);
			m_coopLocator->set_draw(m_map,_GeoMapWidth,_GeoMapHeight);
			m_mapper->setParam(m_map,_GeoMapWidth,_GeoMapHeight);//可以不要m_mapper
			m_bInitMapper=true;
	}
}
bool CCoopLocatoinProcessor::isInited()
{
	if(!m_task_1||!m_task_2)return false;
	return (m_task_1->videoIsInited())&&(m_task_1->detectorIsInited())&&(m_task_1->trackerIsInited())&&
		(m_task_2->videoIsInited())&&(m_task_2->detectorIsInited())&&(m_task_2->trackerIsInited())&&
		mapperIsInited();
}
void CCoopLocatoinProcessor::run()
{
	if(isInited()&&m_bIsRun){
		if(m_task_1->getVideo()->frameID()<m_task_1->getVideo()->frameCount()&&
			m_task_2->getVideo()->frameID()<m_task_2->getVideo()->frameCount()){
				m_mapOut=m_map.clone();
				m_task_1->processFrame(m_output_1);
				m_task_2->processFrame(m_output_2);
				m_coopLocator->update(m_task_1->getVideo()->frameID());
				drawSyncIDInUAV(m_output_1,m_output_2);
				m_coopLocator->draw(m_mapOut);
				emit display();
		}	
	}
}
void CCoopLocatoinProcessor::drawSyncIDInUAV(cv::Mat &_input_1,cv::Mat &_input_2)
{
	std::vector<matchedTrajectories>&ptrMatchedTrajectories=m_coopLocator->getMatchedTrajectoried();
	for(int i=0;i!=ptrMatchedTrajectories.size();i++){
		if(ptrMatchedTrajectories[i].m_ptrTrajectories[0])
			putText(_input_1,to_string((_ULONGLONG)i),ptrMatchedTrajectories[i].getPixelCoordinateByChannel(0),CV_FONT_NORMAL,1,cv::Scalar::all(255));
		if(ptrMatchedTrajectories[i].m_ptrTrajectories[1])
			putText(_input_2,to_string((_ULONGLONG)i),ptrMatchedTrajectories[i].getPixelCoordinateByChannel(1),CV_FONT_NORMAL,1,cv::Scalar::all(255));
	}
}
double CCoopLocatoinProcessor::setWidthFromFile(const std::string &_uavPoseFile)
{
	if(!_uavPoseFile.empty()){
		std::ifstream myFile(_uavPoseFile);
		if(myFile.is_open()){
			std::string line;
			std::getline(myFile,line);
			std::string model="Geo_W";
			std::size_t index=0;
			index=line.rfind(model);
			std::string strFov=line.substr(index+model.size(),line.size());
			std::istringstream in(strFov);
			double temp=0;
			in>>temp;
			return temp;
		}
	}
	return 0;
}
double CCoopLocatoinProcessor::setHeightFromFile(const std::string &_uavPoseFile)
{
	if(!_uavPoseFile.empty()){
		std::ifstream myFile(_uavPoseFile);
		if(myFile.is_open()){
			std::string line;
			std::getline(myFile,line);
			std::string model="Geo_H";
			std::size_t index=0;
			index=line.rfind(model);
			std::string strFov=line.substr(index+model.size(),line.size());
			std::istringstream in(strFov);
			double temp=0;
			in>>temp;
			return temp;
		}
	}
	return 0;
}
void showFrame(const cv::Mat & _image,QLabel *_window)
{
	CMat2QImage m_mat2QImage;
	m_mat2QImage.importImage(_image);
	_window->setPixmap(QPixmap::fromImage(*m_mat2QImage.exportImage(_window->size())));
	_window->show();
}


