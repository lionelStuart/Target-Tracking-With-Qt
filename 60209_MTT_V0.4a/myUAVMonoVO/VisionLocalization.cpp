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
double visionLocalization::Radians(double _degrees)//�Ƕȵ�����ת��
{
	if(int(_degrees)%360==0)_degrees=0;
	return _degrees/double(180)*PI;
}
//����ϵ����ΪXZY,X����ǰ��Y�����ϣ���ʱ��Ϊ��
const cv::Mat visionLocalization::RotateX(double _degrees)//X����ת����
{
	cv::Mat rotateX=(Mat_<double>(3,3)<<						//TAG core
		1,0,0,
		0,cos(Radians(_degrees)),-sin(Radians(_degrees)),
		0,sin(Radians(_degrees)),cos(Radians(_degrees)));
	return rotateX;
}
const cv::Mat visionLocalization::RotateY(double _degrees)//Y����ת����
{
	cv::Mat rotateY=(Mat_<double>(3,3)<<					//TAG core
		cos(Radians(_degrees)),0,sin(Radians(_degrees)),
		0,1,0,
		-sin(Radians(_degrees)),0,cos(Radians(_degrees)));
	return rotateY;
}
const cv::Mat visionLocalization::RotateZ(double _degrees)//Z����ת����
{
	cv::Mat rotateZ=(Mat_<double>(3,3)<<					//TAG  core
		cos(Radians(_degrees)),-sin(Radians(_degrees)),0,
		sin(Radians(_degrees)),cos(Radians(_degrees)),0,
		0,0,1);
	return rotateZ;
}
//�������������ʽΪX ,Z, Y
//�Ƕ�����Ϊx, y, z ����λ�ȣ���ʱ��Ϊ��
void visionLocalization::Rotation(const cv::Mat &_input,cv::Mat &_output,double _rotateX,double _rotateY,double _rotateZ)//������ת��λ��
{
	cv::Mat rotates=RotateZ(_rotateZ)*RotateY(_rotateY)*RotateX(_rotateX);//TAG  core
	_output=_input*rotates;
}
void visionLocalization::pointProjection(const cv::Point &_imgCoordinate,cv::Size _imgSize,double _fov,cv::Mat &_projectionVector)//����������ͶӰ��ͼ������ϵ�У�ͼ������ϵֵ����ʵ�����������s
{
	if(_imgSize.width!=_imgSize.height){cerr<<"Wrong imgSize input!!"<<endl;/*;return;*/}
	double x,y,z;
	x=double(_imgCoordinate.x-_imgSize.width/2);				//TAG  core
	y=double(-_imgCoordinate.y+_imgSize.height/2);
	z=double(_imgSize.width/2)/tan(Radians(_fov/2));
	_projectionVector=(Mat_<double>(1,3)<<x,y,z);
}
//��ȡ��������ľ���λ��,�˷����ϸ�������ֻ�ʺϵ���Ŀ��۲⣬���������ڵ���ˮƽ�����߶�Ϊ0ʱ��x ,z�����
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