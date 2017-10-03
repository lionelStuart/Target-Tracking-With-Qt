#include "myUAVMonoVO\MyUavVO.h"
#include"Trajectory\TrajectoryManager.h"
#include"Tracker\MyTracker.h"
#include "MonoLocationProcessor.h"
#include"Counter/TickCount.h"
#include<iostream>
#include<sstream>
#include<fstream>
using namespace myUAV;
MonoLocationProcessor::MonoLocationProcessor(void):
    m_tracker(NULL),m_trackingBox(0,0,0,0),m_bTrackerInited(false),
	m_locator(NULL),m_mapper(NULL),m_uavPoseFile(""),
	m_cameraImgSize(cv::Size(0,0)),m_fov(0.0),m_bVOInited(false),
	m_mapFilePath(""),m_geoMapHeight(0.0),m_geoMapWidth(0.0),
	m_groundTruthFilePath(""),m_bMapperInited(false),
	m_calTrajectoryPtr(NULL),m_realTrajectoryPtr(NULL),
	m_trajectoryManager(NULL)
{
	m_tracker=new CMyTracker();
	m_locator=new CMyUavVO();
	m_mapper=new CDrawMap();
	m_trajectoryManager=new CTrajectoryManager();
}
MonoLocationProcessor::~MonoLocationProcessor(void)
{
	if(m_tracker)
		delete m_tracker;
	if(m_locator)
		delete m_locator;
	if(m_mapper)
		delete m_mapper;
	if(m_trajectoryManager)
		delete m_trajectoryManager;
}
void MonoLocationProcessor::initVO(const std::string &_poseFilePath/* ="" */,double _fov/*=0*/,const cv::Size &_imgSize/* =cv::Size */,const std::string &_groundTruthFile/*=""*/)
{
	if(!_poseFilePath.empty())
		m_uavPoseFile=_poseFilePath;
	if(_imgSize.width>0&&_imgSize.height>0)
	m_cameraImgSize=_imgSize;
	if(_fov>0)
		m_fov=_fov;
	if(!_groundTruthFile.empty())
		m_groundTruthFilePath=_groundTruthFile;
	if((!m_uavPoseFile.empty())&&m_cameraImgSize.width>0&&m_cameraImgSize.height>0&&m_fov>0){
		m_locator->loadUAVPoseFile(m_uavPoseFile);
		m_locator->setUAVCamreaParam(m_cameraImgSize,m_fov);
		m_bVOInited=true;
	}
}
void MonoLocationProcessor::initMapper(const std::string &_mapFilePath/* ="" */,double _GeoMapWidth/* =0 */,double _GeoMapHeight/* =0 */)
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
void MonoLocationProcessor::setRect(const cv::Rect &_rect)
{
	m_bTrackerInited=false;
	m_trackingBox=cv::Rect(0,0,0,0);
	if(_rect.width!=0&&_rect.height!=0)
		m_trackingBox=_rect;
}
void MonoLocationProcessor::initTracker(const std::string &_trackingType,const cv::Rect &_rect)
{
	setRect(_rect);
	selectTrackingType(_trackingType);
	clearTrajectory();
	clearGroundTruth();
}
void MonoLocationProcessor::clearTrajectory()
{
		m_trajectoryManager->clear();
		m_calTrajectoryPtr=NULL;
		m_realTrajectoryPtr=NULL;
}
void MonoLocationProcessor::clearGroundTruth()
{
	m_groundTruthFilePath.clear();
}
void MonoLocationProcessor::selectTrackingType(const std::string &_trackingType)
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
		StruckParam param;
		param.m_searchRadius=10;
		m_tracker->initStruck(param);
		m_tracker->create(TRACKER_TYPE_STRUCK);
	}
}
void MonoLocationProcessor::clearAll()
{
	m_uavPoseFile.clear();
	m_cameraImgSize=cv::Size(0,0);
	m_fov=0;
	m_bVOInited=false;
	m_mapFilePath.clear();
	m_geoMapHeight=0;
	m_geoMapWidth=0;
	m_bMapperInited=false;
	clearGroundTruth();
	clearTrajectory();
}
void MonoLocationProcessor::process(const cv::Mat &_input,cv::Mat &_output)
{
	CTickCount counter;
	counter.countInSecond(true);
	counter.startCount();
	if(!m_bTrackerInited)
	{
		if(m_trackingBox.width!=0&&m_trackingBox.height!=0)
		{
			m_tracker->init(_input,m_trackingBox);
			updateTargetPosition();
			updateTrajectories();
			updateViewPort();
			m_bTrackerInited=true;
		}
	}
	else
	{
		m_tracker->tracking(_input,m_trackingBox);
		drawEvent(_output,m_trackingBox);
		updateTargetPosition();
		updateTrajectories();
		updateViewPort();
	}
	m_frameRate=1.0/counter.endCount();
}
void MonoLocationProcessor::updateTargetPosition()
{
	cv::Point center=cv::Point(m_trackingBox.x+m_trackingBox.width/2,
		m_trackingBox.y+m_trackingBox.height/2);
	if(center.x<0||center.x>m_cameraImgSize.width||center.y<0||center.y>m_cameraImgSize.height)return;
	if(m_bVOInited){
		m_locator->getUAVPoseParam(getParents()->frameID(),m_uavPose);
		m_locator->getAbsolutePosition(getParents()->frameID(),center,m_calAbsPosition);
		m_locator->getRelativePosition(getParents()->frameID(),m_calAbsPosition,m_calRelPosition);
		if(!m_groundTruthFilePath.empty()){
			m_locator->errorCalculation(getParents()->frameID(),m_groundTruthFilePath,m_calAbsPosition,m_error);
			m_locator->getGroundTruth(getParents()->frameID(),m_groundTruthFilePath,m_absolutePositin);
		}
	}
}
void MonoLocationProcessor::updateTrajectories()
{
	cv::Point center=cv::Point(m_trackingBox.x+m_trackingBox.width/2,
		m_trackingBox.y+m_trackingBox.height/2);
	if(center.x<0||center.x>m_cameraImgSize.width||center.y<0||center.y>m_cameraImgSize.height)return;
	if(m_bVOInited){
		if(!m_calTrajectoryPtr){//计算轨迹
			m_trajectoryManager->addTrajectory(0,m_calAbsPosition,getParents()->frameID(),center);
			m_calTrajectoryPtr=&m_trajectoryManager->getTrajectory(0);
		}
		else
			m_trajectoryManager->updateTrajectory(0,m_calAbsPosition,getParents()->frameID(),center);
		if(!m_groundTruthFilePath.empty()){
			if(!m_realTrajectoryPtr){//真实轨迹
				m_trajectoryManager->addTrajectory(1,m_absolutePositin,getParents()->frameID(),cv::Point(60,60));
				m_realTrajectoryPtr=&m_trajectoryManager->getTrajectory(1);
			}
			else
				m_trajectoryManager->updateTrajectory(1,m_absolutePositin,getParents()->frameID(),cv::Point(60,60));
		}
	}
}
void MonoLocationProcessor::updateViewPort()
{
	if(m_bVOInited){
		m_locator->getViewPort(getParents()->frameID(),m_viewPoints);
	}
}
const cv::Mat& MonoLocationProcessor::getMap(bool _bDrawCalTrajectory/* =true */,bool _bDrawRealTrajectory/* =false */)
{
	if(m_bMapperInited){
		m_trajectoryMap=m_map.clone();
		if(_bDrawCalTrajectory&&m_calTrajectoryPtr)
			m_mapper->drawTrajectory(m_trajectoryMap,*m_calTrajectoryPtr,cv::Scalar(0,0,255));
		if(_bDrawRealTrajectory&&m_realTrajectoryPtr)
			m_mapper->drawTrajectory(m_trajectoryMap,*m_realTrajectoryPtr,cv::Scalar(0,255,0));
		//m_mapper->drawViewPort(m_trajectoryMap,m_viewPoints,cv::Scalar(200,200,200));//绘制无人机视口
	}
	return m_trajectoryMap;
}
void MonoLocationProcessor::drawEvent(cv::Mat &_image,cv::Rect &_box)
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
		cv::putText(_image,temp,cv::Point(20,30),FONT_HERSHEY_TRIPLEX,0.3,cv::Scalar(0,255,0),1,8,false);
		cv::putText(_image,temp2,cv::Point(10,30),FONT_HERSHEY_TRIPLEX,0.3,cv::Scalar(0,255,0),1,8,false);
	}
		
}
double MonoLocationProcessor::setFovFromFile()
{
	if(!m_uavPoseFile.empty()){
		std::ifstream myFile(m_uavPoseFile);
		if(myFile.is_open()){
			std::string line;
			std::getline(myFile,line);
			std::string model="fov";
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
double MonoLocationProcessor::setWidthFromFile()
{
	if(!m_uavPoseFile.empty()){
		std::ifstream myFile(m_uavPoseFile);
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
double MonoLocationProcessor::setHeightFromFile()
{
	if(!m_uavPoseFile.empty()){
		std::ifstream myFile(m_uavPoseFile);
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
std::string &MonoLocationProcessor::getInfomation()
{
	return std::string();
}