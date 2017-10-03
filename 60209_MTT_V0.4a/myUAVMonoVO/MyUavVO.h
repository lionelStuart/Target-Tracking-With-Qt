/*****************************************************************/
/***���˻���Ŀ�����ӿ���****************************************/
/***writePositionFileдĿ��λ���ĵ�******************************/
/***namespace myUAV******************************************/
/***loadUAVCameraParm�������˻���̬�ļ�********************/
/***setUAVParam���׵����������ͼ���С��fov�Ƕȣ�**********/
/***getAbsolutePosition��ȡĿ�����λ��***********************/
/***getRelativePosition�Ѽ������λ�û�ȡ���λ��*************/
/***errorCalculation�������dx,dy,dz,AMSE*********************/
/***getUAVPoseParam��ȡ���˻�λ��****************************/
/***getGroundTruth��ȡ��ʵ����λ��****************************/
/***********************************************by lionel*********/
/*****************************************************************/
//update 160120 ������Ұӳ�����εļ���CMyViewport
//method getViewPort
#ifndef CMyUavVO_H
#define CMyUavVO_H
#include<iostream>
#include<opencv2/opencv.hpp>
#include"GetTargetPosition.h"
#include"GetUAVPose.h"
#include"VisionLocalization.h"
using std::string;
//Ϊ��̨���˼�������ƵĽӿ�
namespace myUAV{
	void writePositionFile(const std::string &_filePath,int _frameID,const cv::Mat&_position);

	class CMyUavVO
	{
	public:
		void loadUAVPoseFile(const std::string &_filePath);
		void setUAVCamreaParam(const cv::Size&_imgSize,double _fov);
		void getAbsolutePosition(int _frameID,const cv::Point &_pixelCoordinate,cv::Mat &_absPosition);
		void getRelativePosition(int _frameID,const cv::Mat&_absPosition,cv::Mat &_relPosition);
		void errorCalculation(int _frameID,const std::string &_groundTruthFilePath,const cv::Mat &absolutePosition,cv::Mat &_error);
		void getUAVPoseParam(int _frameID,UAVPoseParam &_poseParam);
		void getUAVPoseParam(int _frameID,cv::Mat &_poseVec);
		void getGroundTruth(int _frameID,const std::string &_groundTruthFilePath,TargetParam&_targetParam);
		void getGroundTruth(int _frameID,const std::string &_groundTruthFilePath,cv::Mat &_targetVec);
		void getViewPort(int _frameID,std::vector<cv::Point2d>& _Points);
		CMyUavVO(void):m_viewport(this){}
		~CMyUavVO(void);
	private:class CMyViewport
			{
			public:
				void setSize(int _width=0,int _height=0);
				const std::vector<cv::Point2d>& getAffineViewport(int _frameID);
				CMyViewport(CMyUavVO *_parents):m_width(0),m_height(0),m_parents(_parents){}
			private:
				cv::Point2d affinePoint(int _frameID,cv::Point _pixelPoint);
				int m_width;
				int m_height;
				CMyUavVO *m_parents;
				std::vector<cv::Point2d> m_affinePoints;
			};
	private:
		void localization(const cv::Point& _targetCenter,cv::Mat &_absPosition);//��ͼ��Ŀ��λ�ü�����λ����Ϣȷ��Ŀ����ʵ���꼰������
	private:
		CMyViewport m_viewport;
		CGetUAVPose m_uavPoseFile;
		UAVPoseParam m_uavPose;
		visionLocalization m_locator;
	};
	//namespace myUAV
};
#endif	

