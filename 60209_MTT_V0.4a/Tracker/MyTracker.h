/*****************************************************************/
/**Tracker Manager��********************************************/
/**����CT/HASH/KCF/PF/STC/STRUCK���㷨*********************/
/**Create��������************************************************/
/**��Create����ǰ���ø��ӵ�init�������в�������*****************/
/**init/Trackingͨ�÷���******************************************/
/**���������ӵĲ���**********************************************/
/*****************************************************************/
/*****************************************************************/
/******************************************BY Lionel**************/
/*****************************************************************/
//���ӵĳ�ʼ������
//initPF
//initHash
//initKCF
//initSTRUCK
//���ӹ���
//setRadius4Struck
//PF_Confidence
//PF_drawParticle
//getTrackingType���ص�ǰ����������
/*****************************************************************/
//�������ܽӿ�
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
enum TRACKER_TYPE{//����������
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
	void create(const TRACKER_TYPE &_trackerType);                             //����������
	void init(const cv::Mat &_frame,const cv::Rect &_trackWindow);    //��ʼ������
	void tracking(const cv::Mat &_frame,cv::Rect &_trackWindow);      //����
	TRACKER_TYPE getTrackingType();                                                        //��ǰ����������
public:
	void initPF(int num_particles=200,bool _bUseLbp=false);                //���ӵ������˲���ʼ�����ڴ���֮ǰʹ��
	void initHash(bool _bUsePHash);                                                           //��ʼ����ϣ
	void initKCF(const KCFParam & _KCFParam);                                      //��ʼ��KCF
	void initStruck(const StruckParam &_StruckParam);                         //��ʼ��STRUCK
	void setRadius4Struck(int _radius);                                                       //STRUCK �����뾶��0-50
	float PF_Confidence();                                                                              //��ȡPF���Ŷ�
	void PF_drawParticle(bool _bDraw,cv::Mat &_showImage);            //PF�������
private:
	void clear();                                                                                                //���
private://extend
	int m_PFNumParticles;//PF������
	bool m_PFUseLbp;//PF�Ƿ�ʹ��LBP
	bool m_hashUsePHash;//Hash�Ƿ�ʹ��PHASH
	KCFParam* m_KCFParamPtr;//kcf����ָ��
	StruckParam* m_struckParamPtr;//STRUCK����ָ��
private://core
	void* m_ptrTracker;//������ָ��
	TRACKER_TYPE m_trackerType;//����������
};
#endif

