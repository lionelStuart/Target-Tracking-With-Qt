#include "FrameCalibration.h"
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
using namespace cv;
using namespace std;
CFrameCalibration::~CFrameCalibration(void)
{
}
const std::string& CFrameCalibration::getFeatureType()
{
	return m_featureType;
}
void CFrameCalibration::setFeatureType(FEATURE_TYPE _type)
{
	m_featureType.clear();
	switch(_type){
	case FEATURE_GRIDSURF:
		m_featureType="GridSURF";break;
	case FEATURE_GRIDSIFT:
		m_featureType="GridSIFT";break;
	case FEATURE_SURF:
		m_featureType="SURF";break;
	case FEATURE_SIFT:
		m_featureType="SIFT";break;
	case FEATURE_BRISK:
		m_featureType="BRISK";break;
	case FEATURE_FAST:
		m_featureType="FAST";break;
	default:
		m_featureType="GridSURF";break;
	}
}
void CFrameCalibration::getHomography(cv::Mat& _framePrev,cv::Mat& _frameCur,cv::Mat &_H)
{
	std::vector<KeyPoint>prevKeyPoints;
	std::vector<KeyPoint>curKeyPoints;
	Mat PrevDescriptor;
	Mat CurDescriptor;

	initModule_nonfree();

	Ptr<FeatureDetector> pDetector=FeatureDetector::create(m_featureType);//GridSURF

	const int ROIBound=20;
	Mat prevROI=_framePrev(Rect(ROIBound,ROIBound,_framePrev.cols-ROIBound*2,_framePrev.rows-ROIBound*2));
	Mat curROI=_frameCur(Rect(ROIBound,ROIBound,_framePrev.cols-ROIBound*2,_framePrev.rows-ROIBound*2));
	pDetector->detect(prevROI,prevKeyPoints);
	std::vector<unsigned char> opticalStatus;
	std::vector<float> opticalError;
	std::vector<Point2f>prevPoints,curPoints;
	for(size_t i=0;i<prevKeyPoints.size();i++)
	{
		float x=prevKeyPoints[i].pt.x+ROIBound;
		float y=prevKeyPoints[i].pt.y+ROIBound;
		prevPoints.push_back(Point2f(x,y));
	}
	calcOpticalFlowPyrLK(_framePrev,_frameCur,prevPoints,curPoints,opticalStatus,opticalError,Size(21,21),3);
	std::vector<Point2f> prev_corners,cur_corners;
	m_CurPoints.clear();
	for(size_t i=0;i<opticalStatus.size();i++)
	{
		if(opticalStatus[i]!=0)
		{
			if(setForegroundMask()&&isForeground(prevPoints[i]))
			{
				continue;
			}
			prev_corners.push_back(prevPoints[i]);
			cur_corners.push_back(curPoints[i]);
			m_CurPoints.push_back(prevPoints[i]);
		}
	}

	m_mask=NULL;
	_H=cv::findHomography(prev_corners,cur_corners,CV_RANSAC);
}
bool CFrameCalibration::setForegroundMask(const cv::Mat&_mask,bool _bSetMask/*=false*/)
{
	if(_bSetMask==true)
	{
		m_mask=&_mask;
	}
	if(m_mask)return true;
	return false;
}
bool CFrameCalibration::isForeground(const cv::Point2f &_point)
{
	int x,y;
	x=cvFloor(_point.x);
	y=cvFloor(_point.y);
	cv::Point pt(x,y);
	float s=m_mask->at<float>(y,x);
	if(s!=0)
		return true;
	return false;
}
void CFrameCalibration::getKeyPoint(std::vector<cv::Point2f> &_points)
{
	_points=m_CurPoints;
}
