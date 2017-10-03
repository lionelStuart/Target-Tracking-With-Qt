#include "MyUavVO.h"
#include<fstream>
#include<sstream>
#include<iomanip>
using std::stringstream;
using std::ofstream;
using std::ios;
using std::endl;
namespace myUAV{
void writePositionFile(const std::string &_filePath,int _frameID,const cv::Mat&_position)
{
	double x,y,z;
	x=_position.at<double>(0);
	y=_position.at<double>(1);
	z=_position.at<double>(2);
	ofstream outputFile;
	stringstream sstreamTemp;
	using std::setw;
	if(_frameID==0)
	{
		outputFile.open(_filePath,ios::out);
		sstreamTemp<<setw(8)<<"Frames"<<setw(12)<<"X"<<setw(12)<<"Y"<<setw(12)<<"Z"<<endl;
	}
	else
	{
		outputFile.open(_filePath,ios::out|ios::app);
	}
	sstreamTemp<<setw(8)<<_frameID
		<<setw(12)<<x<<setw(12)<<y<<setw(12)<<z;
	string testLine=sstreamTemp.str();
	outputFile<<testLine<<endl;
	outputFile.close();
}
void CMyUavVO::CMyViewport::setSize(int _width/* =0 */,int _height/* =0 */)
{
	m_width=_width;
	m_height=_height;
}
const std::vector<cv::Point2d>&  CMyUavVO::CMyViewport::getAffineViewport(int _frameID)
{
	if(m_width<=0||m_height<=0)std::cerr<<"viewport size not init";
	cv::Point tl(0,0);
	cv::Point tr(m_width,0);
	cv::Point bl(0,m_height);
	cv::Point br(m_width,m_height);
	m_affinePoints.clear();
	m_affinePoints.push_back(affinePoint(_frameID,tl));
	m_affinePoints.push_back(affinePoint(_frameID,tr));
	m_affinePoints.push_back(affinePoint(_frameID,br));
	m_affinePoints.push_back(affinePoint(_frameID,bl));
	return m_affinePoints;
}
cv::Point2d CMyUavVO::CMyViewport::affinePoint(int _frameID,cv::Point _pixelPoint)
{
	cv::Mat absPosition;
	m_parents->getAbsolutePosition(_frameID,_pixelPoint,absPosition);
	return cv::Point2d(absPosition.at<double>(0,0),absPosition.at<double>(0,2));
}
CMyUavVO::~CMyUavVO(void)
{
}
void CMyUavVO::loadUAVPoseFile(const std::string &_filePath)
{
	m_uavPoseFile.setPath(_filePath);
}
void CMyUavVO::setUAVCamreaParam(const cv::Size&_imgSize,double _fov)
{
	m_locator.setCameraParam(_imgSize,_fov);
	m_viewport.setSize(_imgSize.width,_imgSize.height);
}
void CMyUavVO::getViewPort(int _frameID,std::vector<cv::Point2d>& _Points)
{
	_Points.clear();
	_Points=m_viewport.getAffineViewport(_frameID);
}
void CMyUavVO::getAbsolutePosition(int _frameID,const cv::Point &_pixelCoordinate,cv::Mat &_absPosition)
{
	m_uavPoseFile.GetPoseData(_frameID,m_uavPose);
	localization(_pixelCoordinate,_absPosition);
}
void CMyUavVO::getRelativePosition(int _frameID,const cv::Mat&_absPosition,cv::Mat &_relPosition)
{
	m_uavPoseFile.GetPoseData(_frameID,m_uavPose);
	double x,y,z;
	x=_absPosition.at<double>(0)-m_uavPose.x;
	y=_absPosition.at<double>(1)-m_uavPose.y;
	z=_absPosition.at<double>(2)-m_uavPose.z;
	_relPosition=((cv::Mat_<double>(1,3))<<x,y,z);
}
void CMyUavVO::errorCalculation(int _frameID,const std::string &_groundTruthFilePath,const cv::Mat &absolutePosition,cv::Mat &_error)
{
	CGetTargetPosition targetPoseFile;
	targetPoseFile.setPath(_groundTruthFilePath);
	TargetParam groundTruth;
	targetPoseFile.GetPositionData(_frameID,groundTruth);
	double dx,dy,dz,AMSE;
	dx=absolutePosition.at<double>(0)-groundTruth.x;
	dy=absolutePosition.at<double>(1)-groundTruth.y;
	dz=absolutePosition.at<double>(2)-groundTruth.z;
	AMSE=sqrt(pow(dx,2)+pow(dy,2)+pow(dz,2));
	_error=((cv::Mat_<double>(1,4))<<dx,dy,dz,AMSE);
}
void CMyUavVO::getUAVPoseParam(int _frameID,UAVPoseParam &_poseParam)
{
	m_uavPoseFile.GetPoseData(_frameID,_poseParam);
}
void CMyUavVO::getUAVPoseParam(int _frameID,cv::Mat &_poseVec)
{
	UAVPoseParam tempParam;
	m_uavPoseFile.GetPoseData(_frameID,tempParam);
	_poseVec=((cv::Mat_<double>(1,3))<<tempParam.x,tempParam.y,tempParam.z);
}
void CMyUavVO::getGroundTruth(int _frameID,const std::string &_groundTruthFilePath,TargetParam&_targetParam)
{
	CGetTargetPosition targetPosition;
	targetPosition.setPath(_groundTruthFilePath);
	targetPosition.GetPositionData(_frameID,_targetParam);
}
void CMyUavVO::getGroundTruth(int _frameID,const std::string &_groundTruthFilePath,cv::Mat &_targetVec)
{
	TargetParam tempParam;
	CGetTargetPosition targetPosition;
	targetPosition.setPath(_groundTruthFilePath);
	targetPosition.GetPositionData(_frameID,tempParam);
	_targetVec=((cv::Mat_<double>(1,3))<<tempParam.x,tempParam.y,tempParam.z);
}
void CMyUavVO::localization(const cv::Point& _targetCenter,cv::Mat &_absPosition)
{
	double x,y,z,rx,ry,rz,height;//TAG core
	x=m_uavPose.x;
	y=m_uavPose.y;
	z=m_uavPose.z;
	rx=m_uavPose.rx;
	ry=m_uavPose.ry;
	rz=m_uavPose.rz;
	height=m_uavPose.height;
	m_locator.setUAVPosition(x,y,z);
	m_locator.setUAVRotation(rx,ry,rz);
	m_locator.getAbsolutePosition(_targetCenter,height,_absPosition);
}
//namespace myUAV
};

