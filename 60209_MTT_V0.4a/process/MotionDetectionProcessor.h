/*****************************************************************/
/**�˶�Ŀ���⴦����********  ***********************************/
/**��QVideoProcessor��̬����**************************************/
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
class CMotionDetectionProcessor:public FrameProcessor//�̳�FrameProcessor����̬�󶨵�QVideoProcessor
{
public:
	CMotionDetectionProcessor(void);
	~CMotionDetectionProcessor(void);
	void process(const cv::Mat &_input,cv::Mat &_output);
	MyMD* getMD();
	const cv::Mat& getMaskImage(); 
private:
	MyMD *m_md;//�����
	std::vector<cv::Rect> m_detectRects;
	cv::Mat m_maskImage;
	float m_frameRate;
};
inline MyMD* CMotionDetectionProcessor::getMD(){return m_md;}
inline const cv::Mat& CMotionDetectionProcessor::getMaskImage(){return m_maskImage;}
#endif//CMotionDetectionProcessor_H

