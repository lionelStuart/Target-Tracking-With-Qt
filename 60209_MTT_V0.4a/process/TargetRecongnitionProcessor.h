/*****************************************************************/
/*****目标识别处理功能处理类*************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef CTargetRecongnitionProcessor_H
#define CTargetRecongnitionProcessor_H
#include "VideoProcessor/VideoProcessor.h"
class CMyDetector;
#define TARGETMAXSIZE 400
class CTargetRecongnitionProcessor:public FrameProcessor//继承FrameProcessor，动态绑定到QVideoProcessor
{
public:
	CTargetRecongnitionProcessor(void);
	~CTargetRecongnitionProcessor(void);
	void init(const std::string &_classifierFilePath);
	void setFilterSize(int _minWidth=-1,int _maxWidth=-1);
	void clear();
	void process(const cv::Mat &_input,cv::Mat &_output);
	int getMinWidth();
	int getMaxWidth();
private:
	int m_minSize;
	int m_maxSize;
	std::vector<cv::Rect> m_rects;
	CMyDetector* m_detector;
	bool m_bInited;
	float m_frameRate;
};
inline int CTargetRecongnitionProcessor::getMinWidth(){return m_minSize;}
inline int CTargetRecongnitionProcessor::getMaxWidth(){return m_maxSize;}
#endif//CTargetRecongnitionProcessor_H

