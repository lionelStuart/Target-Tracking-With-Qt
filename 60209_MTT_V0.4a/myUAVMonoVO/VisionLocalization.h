/***************************************************************/
/*                ��Ŀ�Ӿ���λ/VisionLocalization                                  */
/* �ӿ�setCameraParam ����ͼ��ߴ���fov/��                             */
/*         setUAVPosition   �������˻�λ��                                        */
/*         setUAVRotation  �������˻��Ƕ�                                        */
/*         getAbsolutePosition�ɷ��и߶����������������ʵλ��*/
/*         ֻ�ʺ�3DVIA����ϵ                                               by Lionel*/
/***************************************************************/
#ifndef visionLocalization_H
#define visionLocalization_H

#include<opencv2\opencv.hpp>
using cv::Mat;
using cv::Size;

class visionLocalization{
public:
	void setCameraParam(const cv::Size &_imgSize,double _fov);//һ���������һ��
	void setUAVPosition(double x,double y,double z);//һ֡����һ��
	void setUAVRotation(double x,double y,double z);//һ֡����һ��
	void getAbsolutePosition(const cv::Point &_imgCoordinate,double _height,cv::Mat &_AbsolutePosition);//һ֡һ��Ŀ������һ��
private:
	double visionLocalization::Radians(double _degrees);//���ȽǶ�ת��
	const cv::Mat visionLocalization::RotateX(double _degrees);//X����ת����
	const cv::Mat visionLocalization::RotateY(double _degrees);//Y����ת����
	const cv::Mat visionLocalization::RotateZ(double _degrees);//Z����ת����
	void visionLocalization::Rotation(const cv::Mat &_input,cv::Mat &_output,double _rotateX,double _rotateY,double _rotateZ);//�����ת������
	void visionLocalization::pointProjection(const cv::Point &_imgCoordinate,cv::Size _imgSize,double _fov,cv::Mat &_projectionVector);//��������ͶӰ��ͼ������
	void visionLocalization::getAbsoluteCoordinate(const cv::Mat&_rotatedProjectionVector,const cv::Mat&_UAVCoordinate,double _height,cv::Mat &_absoluteCoordinate);//��ȡ��ʵ����
private:
	cv::Mat m_uavPosition;
	cv::Mat m_uavRotation;
	cv::Size m_imgSize;
	double m_fov;
};

#endif

