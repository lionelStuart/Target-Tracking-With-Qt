/*****************************************************************/
/***无人机单目测量接口类****************************************/
/***writePositionFile写目标位置文档******************************/
/***namespace myUAV******************************************/
/***loadUAVCameraParm加载无人机姿态文件********************/
/***setUAVParam配套的相机参数（图像大小和fov角度）**********/
/***getAbsolutePosition获取目标绝对位置***********************/
/***getRelativePosition已计算绝对位置获取相对位置*************/
/***errorCalculation计算误差dx,dy,dz,AMSE*********************/
/***getUAVPoseParam读取无人机位姿****************************/
/***getGroundTruth读取真实地理位置****************************/
/***********************************************by lionel*********/
/*****************************************************************/
//update 160120 增加视野映射多边形的计算CMyViewport
//method getViewPort
#ifndef CMyUavVO_H
#define CMyUavVO_H
#include<iostream>
#include<opencv2/opencv.hpp>
#include"GetTargetPosition.h"
#include"GetUAVPose.h"
#include"VisionLocalization.h"
using std::string;
//为单台无人及测量设计的接口
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
		void localization(const cv::Point& _targetCenter,cv::Mat &_absPosition);//由图像目标位置及读入位子信息确定目标真实坐标及误差计算
	private:
		CMyViewport m_viewport;
		CGetUAVPose m_uavPoseFile;
		UAVPoseParam m_uavPose;
		visionLocalization m_locator;
	};
	//namespace myUAV
};
#endif	

