#include "VisionLocalization.h"
#include<iostream>
#include<math.h>
using namespace cv;
using std::cerr;
using std::endl;
static const double PI=3.1415926535898;

void visionLocalization::setUAVPosition(double x,double y,double z)
{
	m_uavPosition=(Mat_<double>(1,3)<<x,y,z);
}
void visionLocalization::setUAVRotation(double x,double y,double z)
{
	m_uavRotation=(Mat_<double>(1,3)<<x,y,z);
}
void visionLocalization::setCameraParam(const cv::Size &_imgSize,double _fov)
{
	m_imgSize=_imgSize;
	m_fov=_fov;
}
void visionLocalization::getAbsolutePosition(const cv::Point &_imgCoordinate,double _height,cv::Mat &_AbsolutePosition)
{
	cv::Mat projectionVector;
	pointProjection(_imgCoordinate,m_imgSize,m_fov,projectionVector);
	cv::Mat rotatedProjectionVector;
	Rotation(projectionVector,rotatedProjectionVector,m_uavRotation.at<double>(0,0),m_uavRotation.at<double>(0,1),m_uavRotation.at<double>(0,2));
	getAbsoluteCoordinate(rotatedProjectionVector,m_uavPosition,_height,_AbsolutePosition);
}
double visionLocalization::Radians(double _degrees)//角度到弧度转换
{
	if(int(_degrees)%360==0)_degrees=0;
	return _degrees/double(180)*PI;
}
//坐标系定义为XZY,X轴向前，Y轴向上，逆时针为正
const cv::Mat visionLocalization::RotateX(double _degrees)//X轴旋转矩阵
{
	cv::Mat rotateX=(Mat_<double>(3,3)<<						//TAG core
		1,0,0,
		0,cos(Radians(_degrees)),-sin(Radians(_degrees)),
		0,sin(Radians(_degrees)),cos(Radians(_degrees)));
	return rotateX;
}
const cv::Mat visionLocalization::RotateY(double _degrees)//Y轴旋转矩阵
{
	cv::Mat rotateY=(Mat_<double>(3,3)<<					//TAG core
		cos(Radians(_degrees)),0,sin(Radians(_degrees)),
		0,1,0,
		-sin(Radians(_degrees)),0,cos(Radians(_degrees)));
	return rotateY;
}
const cv::Mat visionLocalization::RotateZ(double _degrees)//Z轴旋转矩阵
{
	cv::Mat rotateZ=(Mat_<double>(3,3)<<					//TAG  core
		cos(Radians(_degrees)),-sin(Radians(_degrees)),0,
		sin(Radians(_degrees)),cos(Radians(_degrees)),0,
		0,0,1);
	return rotateZ;
}
//输入输出定义形式为X ,Z, Y
//角度输入为x, y, z ，单位度，逆时针为正
void visionLocalization::Rotation(const cv::Mat &_input,cv::Mat &_output,double _rotateX,double _rotateY,double _rotateZ)//计算旋转后位置
{
	cv::Mat rotates=RotateZ(_rotateZ)*RotateY(_rotateY)*RotateX(_rotateX);//TAG  core
	_output=_input*rotates;
}
void visionLocalization::pointProjection(const cv::Point &_imgCoordinate,cv::Size _imgSize,double _fov,cv::Mat &_projectionVector)//将像素坐标投影到图像坐标系中，图像坐标系值与真实物理坐标相差s
{
	if(_imgSize.width!=_imgSize.height){cerr<<"Wrong imgSize input!!"<<endl;/*;return;*/}
	double x,y,z;
	x=double(_imgCoordinate.x-_imgSize.width/2);				//TAG  core
	y=double(-_imgCoordinate.y+_imgSize.height/2);
	z=double(_imgSize.width/2)/tan(Radians(_fov/2));
	_projectionVector=(Mat_<double>(1,3)<<x,y,z);
}
//获取地面物体的绝对位置,此方法严格意义上只适合地面目标观测，但不仅限于地面水平，当高度为0时，x ,z无穷大
void visionLocalization::getAbsoluteCoordinate(const cv::Mat&_rotatedProjectionVector,const cv::Mat&_UAVCoordinate,double _height,cv::Mat &_absoluteCoordinate)
{
	double x,z,y;
	y=_UAVCoordinate.at<double>(0,1)-_height;					//TAG  core
	double scale;
	scale=abs(_height/_rotatedProjectionVector.at<double>(0,1));
	x=scale*_rotatedProjectionVector.at<double>(0,0)+_UAVCoordinate.at<double>(0,0);
	z=scale*_rotatedProjectionVector.at<double>(0,2)+_UAVCoordinate.at<double>(0,2);
	_absoluteCoordinate=(Mat_<double>(1,3)<<x,y,z);
}