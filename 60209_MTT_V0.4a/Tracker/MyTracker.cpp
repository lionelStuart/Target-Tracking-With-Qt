#include"MyTracker.h"

using namespace KCF;
using namespace PF;
using namespace STRUCK;
CMyTracker::~CMyTracker(void)
{
	clear();
	if(m_KCFParamPtr)
	{
		delete m_KCFParamPtr;
		m_KCFParamPtr=NULL;
	}
	if(m_struckParamPtr)
	{
		delete m_struckParamPtr;
		m_struckParamPtr=NULL;
	}
	m_hashUsePHash=true;
	m_PFNumParticles=200;
	m_PFUseLbp=false;
	m_trackerType=TRACKER_TYPE_NULL;
}
void CMyTracker::clear()
{
	if(m_trackerType==TRACKER_TYPE_NULL)return;
	if(m_trackerType==TRACKER_TYPE_CT)
	{
		delete (myCTTracker*)m_ptrTracker;
	}
	if(m_trackerType==TRACKER_TYPE_HASH)
	{
		delete (CMyHash*)m_ptrTracker;
	}
	if(m_trackerType==TRACKER_TYPE_KCF)
	{
		delete (CMyKCFTracker*)m_ptrTracker;
	}
	if(m_trackerType==TRACKER_TYPE_PF)
	{
		((CMyParticleFilter*)m_ptrTracker)->cancelTracking();
		delete (CMyParticleFilter*)m_ptrTracker;
	}
	if(m_trackerType==TRACKER_TYPE_STC)
	{
		delete (mySTCTracker*)m_ptrTracker;
	}
	if(m_trackerType==TRACKER_TYPE_STRUCK)
	{
		delete (myStruck*)m_ptrTracker;
	}
}
void CMyTracker::create(const TRACKER_TYPE &_trackerType)
{
	clear();
	m_trackerType=_trackerType;
	if(m_trackerType==TRACKER_TYPE_CT)
	{
		m_ptrTracker=(myCTTracker*)(new myCTTracker());
	}
	if(m_trackerType==TRACKER_TYPE_HASH)
	{
		m_ptrTracker=(CMyHash*)(new CMyHash());
	}
	if(m_trackerType==TRACKER_TYPE_KCF)
	{
		if(m_KCFParamPtr)
			m_ptrTracker=(CMyKCFTracker*)(new CMyKCFTracker(*m_KCFParamPtr));
		else
			m_ptrTracker=(CMyKCFTracker*)(new CMyKCFTracker());
	}
	if(m_trackerType==TRACKER_TYPE_PF)
	{
		PF::Options opt;
		opt.num_particles=m_PFNumParticles;
		opt.use_lbp=m_PFUseLbp;
		m_ptrTracker=(CMyParticleFilter*)(new CMyParticleFilter(opt));
	}
	if(m_trackerType==TRACKER_TYPE_STC)
	{
		m_ptrTracker=(mySTCTracker*)(new mySTCTracker());
	}
	if(m_trackerType==TRACKER_TYPE_STRUCK)
	{
		if(m_struckParamPtr)
			m_ptrTracker=(myStruck*)(new myStruck(*m_struckParamPtr));
		else
			m_ptrTracker=(myStruck*)(new myStruck());
	}
}
void CMyTracker::init(const cv::Mat &_frame,const cv::Rect &_trackWindow)
{
	if(m_trackerType==TRACKER_TYPE_NULL)return;
	if(m_trackerType==TRACKER_TYPE_CT)
	{
		((myCTTracker*)m_ptrTracker)->_init(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_HASH)
	{
		((CMyHash*)m_ptrTracker)->init(_frame,_trackWindow,m_hashUsePHash);
	}
	if(m_trackerType==TRACKER_TYPE_KCF)
	{
		((CMyKCFTracker*)m_ptrTracker)->_init(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_PF)
	{
		((CMyParticleFilter*)m_ptrTracker)->init(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_STC)
	{
		((mySTCTracker*)m_ptrTracker)->_init(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_STRUCK)
	{
		((myStruck*)m_ptrTracker)->_init(_frame,_trackWindow);
	}
}
void CMyTracker::tracking(const cv::Mat &_frame,cv::Rect &_trackWindow)
{
	if(m_trackerType==TRACKER_TYPE_NULL)return;
	if(m_trackerType==TRACKER_TYPE_CT)
	{
		((myCTTracker*)m_ptrTracker)->_tracking(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_HASH)
	{
		((CMyHash*)m_ptrTracker)->tracking(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_KCF)
	{
		((CMyKCFTracker*)m_ptrTracker)->_tracking(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_PF)
	{
		((CMyParticleFilter*)m_ptrTracker)->tracking(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_STC)
	{
		((mySTCTracker*)m_ptrTracker)->_tracking(_frame,_trackWindow);
	}
	if(m_trackerType==TRACKER_TYPE_STRUCK)
	{
		((myStruck*)m_ptrTracker)->_track(_frame,_trackWindow);
	}
}
TRACKER_TYPE CMyTracker::getTrackingType()
{
	return m_trackerType;
}
void CMyTracker::initHash(bool _bUsePHash)
{
	m_hashUsePHash=_bUsePHash;
}
void CMyTracker::initKCF(const KCFParam& _KCFParam)
{
	if(!m_KCFParamPtr)
	{
		m_KCFParamPtr=new KCFParam(_KCFParam);
	}
	else{
		delete m_KCFParamPtr;
		m_KCFParamPtr=new KCFParam(_KCFParam);
	}
}
void CMyTracker::initStruck(const StruckParam &_StruckParam)
{
	if(!m_struckParamPtr)
	{
		m_struckParamPtr=new StruckParam(_StruckParam);
	}
	else{
		delete m_KCFParamPtr;
		m_struckParamPtr=new StruckParam(_StruckParam);
	}
}
void CMyTracker::setRadius4Struck(int _radius)
{
	if(m_trackerType==TRACKER_TYPE_STRUCK&&m_ptrTracker)
	((myStruck*)m_ptrTracker)->setRadius(_radius);
}
float CMyTracker::PF_Confidence()
{
	if(m_trackerType==TRACKER_TYPE_PF&&m_ptrTracker)
		return ((CMyParticleFilter*)m_ptrTracker)->getConfidence();
	else return -1;
}
void CMyTracker::PF_drawParticle(bool _bDraw,cv::Mat &_showImage)
{
		if(m_trackerType==TRACKER_TYPE_PF&&m_ptrTracker)
			((CMyParticleFilter*)m_ptrTracker)->drawParticles(_bDraw,_showImage);
}
void CMyTracker::initPF(int num_particles/* =200 */,bool _bUseLbp/* =false */)
{
	m_PFNumParticles=num_particles;
	m_PFUseLbp=_bUseLbp;
}