#include "MultiLocationProcessor.h"
#include "Detector/CMyDetector.h"
#include "MultiTargetTracker/MultiTargetTracker.h"
#include"Trajectory\TrajectoryManager.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include"Counter/TickCount.h"
MultiLocationProcessor::MultiLocationProcessor(void)
	:m_detector(NULL),m_tracker(NULL),m_imgSize(cv::Size(0,0)),
	m_classifierFilePath(""),m_uavPoseFilePath(""),m_bTrackerInited(false),//,m_minSize(MTT_DEFAULT_MINSIZE),
	m_bMapperInited(false),//m_maxSize(MTT_DEFAULT_MAXSIZE)
	m_geoMapHeight(0),m_geoMapWidth(0),
	m_mapFilePath(""),m_mapper(NULL),m_fov(0)
{
	m_detector=new CMyDetector();
	m_tracker=new CMultiTargetTracker();
	m_mapper=new CDrawMap();
}
MultiLocationProcessor::~MultiLocationProcessor(void)
{
	if(m_detector)
		delete m_detector;
	if(m_tracker)
		delete m_tracker;
	if(m_mapper)
		delete m_mapper;
}
void MultiLocationProcessor::setDetectionFilter(int _minSize/* =-1 */,int _maxSize/* =-1 */)
{
	//if(_minSize!=-1&&_minSize<m_maxSize){
	//	m_minSize=_minSize;
	//}
	//if(_maxSize!=-1&&_maxSize>m_minSize){
	//	m_maxSize=_maxSize;
	//}
}
void MultiLocationProcessor::initTracker(const std::string &_classifierFilePath/* ="" */,const std::string &_uavPoseFilePath/* ="" */,const cv::Size img_size)
{
	if(!_classifierFilePath.empty()){
		m_classifierFilePath=_classifierFilePath;
	}
	if(!_uavPoseFilePath.empty()){
		m_uavPoseFilePath=_uavPoseFilePath;
	}
	if(img_size.width&&img_size.height){
		m_imgSize=img_size;
	}
	if(!m_uavPoseFilePath.empty()&&!m_classifierFilePath.empty()&&m_imgSize.width&&m_imgSize.height){
		m_detector->set(m_classifierFilePath);
		m_fov=setFovFromFile(m_uavPoseFilePath);
		m_tracker->setVO(m_uavPoseFilePath,m_imgSize,m_fov);
		initMapper("",setWidthFromFile(m_uavPoseFilePath),setHeightFromFile(m_uavPoseFilePath));
		m_bTrackerInited=true;
	}
}
void MultiLocationProcessor::initMapper(const std::string &_mapFilePath/* ="" */,double _GeoMapWidth/* =0 */,double _GeoMapHeight/* =0 */)
{
	if(!_mapFilePath.empty())
		m_mapFilePath=_mapFilePath;
	if(_GeoMapHeight>0&&_GeoMapWidth>0){
		m_geoMapHeight=_GeoMapHeight;
		m_geoMapWidth=_GeoMapWidth;
	}
	if((!m_mapFilePath.empty())&&m_geoMapHeight>0&&m_geoMapWidth>0){
		m_map=cv::imread(m_mapFilePath);
		m_trajectoryMap=m_map;
		m_mapper->setParam(m_map,m_geoMapWidth,m_geoMapHeight);
		m_bMapperInited=true;
	}
}
double MultiLocationProcessor::setFovFromFile(const std::string &_poseFilePath)
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
double MultiLocationProcessor::setWidthFromFile(const std::string &_uavPoseFile)
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
double MultiLocationProcessor::setHeightFromFile(const std::string &_uavPoseFile)
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
void MultiLocationProcessor::process(const cv::Mat &_input,cv::Mat &_output)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	if(isInited()){
		m_detectRects.clear();
		m_detector->detect(_input,m_detectRects);
		//detectionFilter(m_detectRects,m_minSize,m_maxSize);
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
		m_trajectoryMap=m_map.clone();
		m_mapper->drawTrajectories(m_trajectoryMap,m_tracker->getTrajectories());
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
void MultiLocationProcessor::clear()
{
	m_classifierFilePath.clear();
	m_uavPoseFilePath.clear();
	m_mapFilePath.clear();
	m_imgSize.width=0;
	m_imgSize.height=0;
	m_geoMapHeight=0;
	m_geoMapWidth=0;
	m_fov=0;
	m_bTrackerInited=false;
	m_bMapperInited=false;
	if(m_tracker){
		delete m_tracker;
		m_tracker=new CMultiTargetTracker();
	}
}



