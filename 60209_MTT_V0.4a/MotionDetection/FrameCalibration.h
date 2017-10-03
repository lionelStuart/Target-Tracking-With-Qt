/*****************************************************************/
/***֡�궨��**********************************************************/
/***update160201**************************************************/
/***��������������趨�ͻ�ȡ����************************************************/
/***setFeatureType************************************************/
/***getFeatureType************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#pragma once
//�ṩ�˶�������Ƶ��֡��׼
#include <opencv2/opencv.hpp>
using cv::Mat;
using cv::Point2f;
class CFrameCalibration
{
public:
	enum FEATURE_TYPE{//�������������
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

