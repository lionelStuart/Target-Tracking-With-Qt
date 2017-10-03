/*****************************************************************/
/***帧标定类**********************************************************/
/***update160201**************************************************/
/***增加特征检测子设定和获取方法************************************************/
/***setFeatureType************************************************/
/***getFeatureType************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#pragma once
//提供运动场景视频中帧配准
#include <opencv2/opencv.hpp>
using cv::Mat;
using cv::Point2f;
class CFrameCalibration
{
public:
	enum FEATURE_TYPE{//特征检测子类型
		FEATURE_GRIDSURF,
		FEATURE_GRIDSIFT,
		FEATURE_SURF,
		FEATURE_SIFT,
		FEATURE_BRISK,
		FEATURE_FAST
	};
	CFrameCalibration(void):m_mask(NULL),m_featureType("GridSURF"){}
	~CFrameCalibration(void);
	void getHomography(cv::Mat& _framePrev,cv::Mat& _frameCur,cv::Mat &_H);
	bool setForegroundMask(const cv::Mat&_mask=cv::Mat(),bool _bSetMask=false);
	void getKeyPoint(std::vector<cv::Point2f> &_points);
	void setFeatureType(FEATURE_TYPE _type);
	const std::string& getFeatureType();
private:
	std::string m_featureType;
	bool isForeground(const cv::Point2f &_point);
	const cv::Mat *m_mask;
	std::vector<cv::Point2f>m_CurPoints;
};

