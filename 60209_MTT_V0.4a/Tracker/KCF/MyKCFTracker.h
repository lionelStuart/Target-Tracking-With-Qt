/*****************************************************************/
/***封装KCFTracker*****namespace KCF*************************/
/***KCFParam用于参数设定***************************************/
/***CMyKCFTracker继承KCFTracker******************************/
/***通用的方法_init/_tracking*************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************By Lionel***************/
/*****************************************************************/
#ifndef CMyKCFTracker_H
#define CMyKCFTracker_H
#include "kcftracker.hpp"
namespace KCF{
//Struct KCFParam
struct KCFParam{
	bool bHog;
	bool bFixed_window;
	bool bMultiscale;
	bool bLab;
	KCFParam():bHog(true),bFixed_window(true),bMultiscale(true),bLab(true){}
};
//class CMyKCFTracker
class CMyKCFTracker:private KCFTracker
{
public:
	explicit CMyKCFTracker(const KCFParam& _param=KCFParam()):
	KCFTracker(_param.bHog,_param.bFixed_window,_param.bMultiscale,_param.bLab){}
	void _init(const cv::Mat &_frame,const cv::Rect&_trackWindow);
	void _tracking(const cv::Mat &_frame,cv::Rect &_trackWindow);
	~CMyKCFTracker(void);
};
//namespace KCF
};
#endif

