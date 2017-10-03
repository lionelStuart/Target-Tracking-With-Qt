/*****************************************************************/
/**�����************************************************************/
/**����ͼ����setָ���ķ�������������LBP��HOG��HAAR��******************************/
/*****�����󲢷��ذ��������һ�鷽��********************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef myDetector_H
#define myDetector_H
#include<opencv2/opencv.hpp>
class CMyDetector
{
public:
	void set(const std::string &_classifierFilePath);
	void detect(const cv::Mat &_grayImage,std::vector<cv::Rect> &_ObjectRects);
	CMyDetector(void);
	~CMyDetector(void);
private:
	cv::CascadeClassifier m_detector;
	std::string m_targetType;
};

#endif 

