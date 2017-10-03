#include "MyKCFTracker.h"
namespace KCF{
CMyKCFTracker::~CMyKCFTracker(void)
{
}
void CMyKCFTracker::_init(const cv::Mat &_frame,const cv::Rect&_trackWindow)
{
	
	KCFTracker::init(_trackWindow,_frame);
}
void CMyKCFTracker::_tracking(const cv::Mat &_frame,cv::Rect &_trackWindow)
{
	_trackWindow=KCFTracker::update(_frame);
}
//namespace 
};
