/*****************************************************************/
/**trackeProcessor���ٴ�����************************************/
/**init�ڸ���ǰȷ�����������ͺ͸��ٴ�************************/
/**process��дprocess����*****************************************/
/*****************************************************************/
/**drawBox������****************************************************/
/**setRect���ø��ٴ���**************************************************/
/**selectTrackingTypeѡ�������****************************************/
/***�Կ�����init֮ǰͨ��gettracker����initKCF/���޸ĳ�ʼ������**************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef trackProcessor_H
#define trackProcessor_H
#include"VideoProcessor\VideoProcessor.h"
#include"Tracker\MyTracker.h"
class CMyTracker;
class trackProcessor:public FrameProcessor//�̳�FrameProcessor����̬�󶨵�QVideoProcessor��ʵ�ָ���
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

