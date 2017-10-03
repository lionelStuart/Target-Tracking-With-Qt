/*****************************************************************/
/**trackeProcessor跟踪处理器************************************/
/**init在跟踪前确定跟踪器类型和跟踪窗************************/
/**process重写process函数*****************************************/
/*****************************************************************/
/**drawBox画框函数****************************************************/
/**setRect设置跟踪窗口**************************************************/
/**selectTrackingType选择跟踪器****************************************/
/***仍可以在init之前通过gettracker调用initKCF/等修改初始化参数**************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef trackProcessor_H
#define trackProcessor_H
#include"VideoProcessor\VideoProcessor.h"
#include"Tracker\MyTracker.h"
class CMyTracker;
class trackProcessor:public FrameProcessor//继承FrameProcessor，动态绑定到QVideoProcessor，实现跟踪
{
public:
	trackProcessor(void);
	~trackProcessor(void);
	void init(const std::string &_trackingType,const cv::Rect &_rect);
	void process(const cv::Mat &_input,cv::Mat &_output);
	CMyTracker* getTracker();
private:
	void drawEvent(cv::Mat &_image,cv::Rect &_box);
	void setRect(const cv::Rect &_rect);
	void selectTrackingType(const std::string &_trackingType);
private:
	cv::Rect m_trackingBox;
	CMyTracker *m_tracker;
	bool m_bInited;
	float m_frameRate;
};
inline CMyTracker* trackProcessor::getTracker(){return m_tracker;}
#endif

