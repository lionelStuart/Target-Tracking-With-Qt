/*****************************************************************/
/**Tracker Manager类********************************************/
/**包含CT/HASH/KCF/PF/STC/STRUCK等算法*********************/
/**Create方法创建************************************************/
/**在Create创建前调用附加的init方法进行参数设置*****************/
/**init/Tracking通用方法******************************************/
/**及其它附加的操作**********************************************/
/*****************************************************************/
/*****************************************************************/
/******************************************BY Lionel**************/
/*****************************************************************/
//附加的初始化操作
//initPF
//initHash
//initKCF
//initSTRUCK
//附加功能
//setRadius4Struck
//PF_Confidence
//PF_drawParticle
//getTrackingType返回当前跟踪器类型
/*****************************************************************/
//跟踪器总接口
#ifndef CMyTracker_H
#define  CMyTracker_H
#include"CT/CompressiveTracker.h"
#include"Hash/MyHash.h"
#include"KCF/MyKCFTracker.h"
#include"PF/MyParticleFilter.h"
#include"STCTracker/mySTCTracker.h"
#include"STRUCK/myStruck.h"
#include<opencv2/opencv.hpp>

using KCF::KCFParam;
using STRUCK::StruckParam;
using PF::Options;
enum TRACKER_TYPE{//跟踪器类型
	TRACKER_TYPE_NULL,
	TRACKER_TYPE_CT,
	TRACKER_TYPE_HASH,
	TRACKER_TYPE_KCF,
	TRACKER_TYPE_PF,
	TRACKER_TYPE_STC,
	TRACKER_TYPE_STRUCK
};
class CMyTracker
{

public:
	CMyTracker(void):
	  m_ptrTracker(NULL),m_trackerType(TRACKER_TYPE_NULL),
	  m_hashUsePHash(true),m_KCFParamPtr(NULL),
	  m_struckParamPtr(NULL),m_PFNumParticles(200),m_PFUseLbp(false){}
	~CMyTracker(void);
	void create(const TRACKER_TYPE &_trackerType);                             //创建跟踪器
	void init(const cv::Mat &_frame,const cv::Rect &_trackWindow);    //初始化跟踪
	void tracking(const cv::Mat &_frame,cv::Rect &_trackWindow);      //跟踪
	TRACKER_TYPE getTrackingType();                                                        //当前跟踪器类型
public:
	void initPF(int num_particles=200,bool _bUseLbp=false);                //附加的粒子滤波初始化，在创建之前使用
	void initHash(bool _bUsePHash);                                                           //初始化哈希
	void initKCF(const KCFParam & _KCFParam);                                      //初始化KCF
	void initStruck(const StruckParam &_StruckParam);                         //初始化STRUCK
	void setRadius4Struck(int _radius);                                                       //STRUCK 搜索半径，0-50
	float PF_Confidence();                                                                              //获取PF置信度
	void PF_drawParticle(bool _bDraw,cv::Mat &_showImage);            //PF描绘粒子
private:
	void clear();                                                                                                //清空
private://extend
	int m_PFNumParticles;//PF离子数
	bool m_PFUseLbp;//PF是否使用LBP
	bool m_hashUsePHash;//Hash是否使用PHASH
	KCFParam* m_KCFParamPtr;//kcf参数指针
	StruckParam* m_struckParamPtr;//STRUCK参数指针
private://core
	void* m_ptrTracker;//跟踪器指针
	TRACKER_TYPE m_trackerType;//跟踪器类型
};
#endif

