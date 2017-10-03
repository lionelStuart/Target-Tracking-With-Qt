/*****************************************************************/
/**运动目标检测处理类********  ***********************************/
/**由QVideoProcessor动态加载**************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef CMotionDetectionProcessor_H
#define CMotionDetectionProcessor_H
#include"VideoProcessor/VideoProcessor.h"
#include"MotionDetection\MyMD.h"
class MyMD;
class CMotionDetectionProcessor:public FrameProcessor//继承FrameProcessor，动态绑定到QVideoProcessor
{
public:
	CMotionDetectionProcessor(void);
	~CMotionDetectionProcessor(void);
	void process(const cv::Mat &_input,cv::Mat &_output);
	MyMD* getMD();
	const cv::Mat& getMaskImage(); 
private:
	MyMD *m_md;//检测器
	std::vector<cv::Rect> m_detectRects;
	cv::Mat m_maskImage;
	float m_frameRate;
};
inline MyMD* CMotionDetectionProcessor::getMD(){return m_md;}
inline const cv::Mat& CMotionDetectionProcessor::getMaskImage(){return m_maskImage;}
#endif//CMotionDetectionProcessor_H

