#include "CMyDetector.h"

CMyDetector::CMyDetector(void)
{
}
CMyDetector::~CMyDetector(void)
{
}
void CMyDetector::set(const std::string &_classifierFilePath)
{
	m_detector.load(_classifierFilePath);
}
void CMyDetector::detect(const cv::Mat &_grayImage,std::vector<cv::Rect> &_ObjectRects)
{
	_ObjectRects.clear();
	m_detector.detectMultiScale(_grayImage,_ObjectRects);
}