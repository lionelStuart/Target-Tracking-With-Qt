/***************************************************************/
/*                单目视觉定位/VisionLocalization                                  */
/* 接口setCameraParam 设置图像尺寸与fov/度                             */
/*         setUAVPosition   定点无人机位置                                        */
/*         setUAVRotation  设置无人机角度                                        */
/*         getAbsolutePosition由飞行高度与像素坐标求解真实位置*/
/*         只适合3DVIA坐标系                                               by Lionel*/
/***************************************************************/
#ifndef visionLocalization_H
#define visionLocalization_H

#include<opencv2\opencv.hpp>
using cv::Mat;
using cv::Size;

class visionLocalization{
public:
	void setCameraParam(const cv::Size &_imgSize,double _fov);//一次侦测设置一次
	void setUAVPosition(double x,double y,double z);//一帧设置一次
	void setUAVRotation(double x,double y,double z);//一帧设置一次
	void getAbsolutePosition(const cv::Point &_imgCoordinate,double _height,cv::Mat &_AbsolutePosition);//一帧一个目标设置一次
private:
	double visionLocalization::Radians(double _degrees);//弧度角度转换
	const cv::Mat visionLocalization::RotateX(double _degrees);//X轴旋转矩阵
	const cv::Mat visionLocalization::RotateY(double _degrees);//Y轴旋转矩阵
	const cv::Mat visionLocalization::RotateZ(double _degrees);//Z轴旋转矩阵
	void visionLocalization::Rotation(const cv::Mat &_input,cv::Mat &_output,double _rotateX,double _rotateY,double _rotateZ);//求解旋转后向量
	void visionLocalization::pointProjection(const cv::Point &_imgCoordinate,cv::Size _imgSize,double _fov,cv::Mat &_projectionVector);//像素坐标投影到图像坐标
	void visionLocalization::getAbsoluteCoordinate(const cv::Mat&_rotatedProjectionVector,const cv::Mat&_UAVCoordinate,double _height,cv::Mat &_absoluteCoordinate);//获取真实坐标
private:
	cv::Mat m_uavPosition;
	cv::Mat m_uavRotation;
	cv::Size m_imgSize;
	double m_fov;
};

#endif

