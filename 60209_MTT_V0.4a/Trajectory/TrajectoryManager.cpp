#include "TrajectoryManager.h"
using std::cerr;
using std::endl;
using std::cout;
CTrajectoryManager::CTrajectoryManager(void)
{
	clear();
}
CTrajectoryManager::~CTrajectoryManager(void)
{
	clear();
}
void CTrajectoryManager::clear()
{
	m_totalNum=0;
	m_maxIndex=0;
	for(int i=0;i!=MAX_TRAJECTORIES;i++)
	{
		m_trajectories[i].m_trajectory.clear();
	}
}
int CTrajectoryManager::getTrajectoriesCount() const
{
	return m_totalNum;
}
int CTrajectoryManager::getTrajectoriesFullCount() const
{ 
	return m_maxIndex;
}
void CTrajectoryManager::addTrajectory(int _index,const cv::Mat &_startPosition,int _frameID/* =0 */,const cv::Point2d _pixelCoordinate/*=cv::Point2d()*/)
{
	if(_index<0||_index>MAX_TRAJECTORIES-1)return;
	if(!m_trajectories[_index].m_trajectory.empty())//非空即清空
	{
		m_trajectories[_index].m_trajectory.clear();
		m_totalNum=m_totalNum-1;
	}
	node temp;
	temp.frameID=_frameID;
	temp.x=_startPosition.at<double>(0);
	temp.y=_startPosition.at<double>(1);
	temp.z=_startPosition.at<double>(2);
	m_trajectories[_index].m_trajectory.push_back(temp);
	m_trajectories[_index].m_prevFrameID=_frameID;
	m_trajectories[_index].m_pixelCoordinate=_pixelCoordinate;
	m_totalNum++;
	m_maxIndex=_index;
}
void CTrajectoryManager::updateTrajectory(int _index,const cv::Mat &_newPosition,int _frameID,const cv::Point2d _pixelCoordinate/*=cv::Point2d()*/)
{
	if(_index<0||_index>MAX_TRAJECTORIES||_frameID<=0)return;//index和_frameID检查
	if(m_trajectories[_index].m_trajectory.empty())return;//为空即退出
	node temp;
	if(_frameID==m_trajectories[_index].m_prevFrameID+1)//正常更新
	{
	temp.frameID=_frameID;
	temp.x=_newPosition.at<double>(0);
	temp.y=_newPosition.at<double>(1);
	temp.z=_newPosition.at<double>(2);
	m_trajectories[_index].m_trajectory.push_back(temp);
	m_trajectories[_index].m_prevFrameID=_frameID;
	m_trajectories[_index].m_pixelCoordinate=_pixelCoordinate;
	return;
	}
    if(_frameID>m_trajectories[_index].m_prevFrameID+1)//ID高于prevFrameID+1
	{
		//temp.frameID=_frameID;
		temp.x=-1;
		temp.y=-1;
		temp.z=-1;
		while(_frameID!=m_trajectories[_index].m_prevFrameID+1)
		{
			temp.frameID=++m_trajectories[_index].m_prevFrameID;
			m_trajectories[_index].m_trajectory.push_back(temp);	
		}
		temp.frameID=_frameID;
		temp.x=_newPosition.at<double>(0);
		temp.y=_newPosition.at<double>(1);
		temp.z=_newPosition.at<double>(2);
		m_trajectories[_index].m_trajectory.push_back(temp);
		m_trajectories[_index].m_prevFrameID=_frameID;
		return;
	}
	else
		return;
}
 trajectory&  CTrajectoryManager::getTrajectory(int _index) 
{
	if(_index<0||_index>MAX_TRAJECTORIES)return m_trajectories[0];
	return m_trajectories[_index];
}
void CDrawMap::setParam(const cv::Mat _map,double _GeoMapWidth,double _GeoMapHeight)
{
	 m_scaleX=((double)_map.cols)/_GeoMapWidth;
	 m_scaleY=((double)_map.rows)/_GeoMapHeight;
}
void CDrawMap::drawTrajectory(cv::Mat &_map,const trajectory&_trajectory,const cv::Scalar &_color)
{
	if(!_trajectory.m_trajectory.empty())
	{
		cv::Point prevPoint,currentPoint;
		currentPoint.x=(int)(m_scaleX*_trajectory.m_trajectory.begin()->x);
		currentPoint.y=(int)(_map.rows-m_scaleY*_trajectory.m_trajectory.begin()->z);
		for(std::vector<node>::const_iterator i=_trajectory.m_trajectory.begin();i!=_trajectory.m_trajectory.end();i++)
		{
			if(i->x==-1||i->y==-1||i->z==-1)continue;
			currentPoint.x=(int)(m_scaleX*i->x);
			currentPoint.y=(int)(_map.rows-m_scaleY*i->z);
			if(pow(currentPoint.x-prevPoint.x,2.0)+pow(currentPoint.y-prevPoint.y,2.0)<100.0)
			cv::line(_map,currentPoint,prevPoint,_color,0.5,8,0);
			prevPoint=currentPoint;
		}
		cv::circle(_map,currentPoint,3,_color,2,8,0);
	}
}
void CDrawMap::drawTrajectories(cv::Mat &_map,  CTrajectoryManager* _trajectoriesPtr)
{
	if(_trajectoriesPtr)
	{

		for(int i=0;i!=_trajectoriesPtr->getTrajectoriesFullCount();i++)
		{
			if(_trajectoriesPtr->getTrajectory(i).getType()==trajectory::STATUS_TRACK)
			drawTrajectory(_map,_trajectoriesPtr->getTrajectory(i),CDrawMap_Colors[i%8]);
		}
	}
}
void CDrawMap::drawViewPort(cv::Mat &_map,const std::vector<cv::Point2d>&_viewPoints,const cv::Scalar &_color)
{
	if(_viewPoints.empty())return;
	cv::Point tl,tr,bl,br;
	tl.x=(int)(m_scaleX*_viewPoints[0].x);
	tl.y=(int)(_map.rows-m_scaleY*_viewPoints[0].y);
	tr.x=(int)(m_scaleX*_viewPoints[1].x);
	tr.y=(int)(_map.rows-m_scaleY*_viewPoints[1].y);
	bl.x=(int)(m_scaleX*_viewPoints[3].x);
	bl.y=(int)(_map.rows-m_scaleY*_viewPoints[3].y);
	br.x=(int)(m_scaleX*_viewPoints[2].x);
	br.y=(int)(_map.rows-m_scaleY*_viewPoints[2].y);
	cv::line(_map,tl,tr,_color,1,8,0);
	cv::line(_map,tr,br,_color,1,8,0);
	cv::line(_map,br,bl,_color,1,8,0);
	cv::line(_map,tl,bl,_color,1,8,0);
}