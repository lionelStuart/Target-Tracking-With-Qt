/*****************************************************************/
/**检测器************************************************************/
/**输入图像，由set指定的分类器（级联，LBP，HOG，HAAR）******************************/
/*****检测对象并返回包含结果的一组方框********************************************/
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

