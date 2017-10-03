/*****************************************************************/
/**��Ŀ����ٴ�����****************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*Ϊ������ʵ��2������MTT_DEFAULT_MINSIZE��30������20
*/
#ifndef CMultiTrackingProcessor_H
#define CMultiTrackingProcessor_H
#include "VideoProcessor/VideoProcessor.h"
#define MTT_DEFAULT_MINSIZE 20
#define MTT_DEFAULT_MAXSIZE 80
class CMyDetector;
class CMultiTargetTracker;
class CMultiTrackingProcessor:public FrameProcessor//�̳�FrameProcessor����̬�󶨵�QVideoProcessor
{
public:
	CMultiTrackingProcessor(void);
	~CMultiTrackingProcessor(void);
	void setDetectionFilter(int _minSize=-1,int _maxSize=-1);
	void init(const std::string &_classifierFilePath);
	void process(const cv::Mat &_input,cv::Mat &_output);
	void clear();
	int getMinWidth();
	int getMaxWidth();
private:
	int m_minSize;
	int m_maxSize;
	std::vector<cv::Rect> m_detectRects;
	CMyDetector *m_detector;
	CMultiTargetTracker *m_tracker;
	bool m_bInited;
	float m_frameRate;
};
inline int CMultiTrackingProcessor::getMinWidth(){return m_minSize;}
inline int CMultiTrackingProcessor::getMaxWidth(){return m_maxSize;}
#endif// CMultiTrackingProcessor_H

