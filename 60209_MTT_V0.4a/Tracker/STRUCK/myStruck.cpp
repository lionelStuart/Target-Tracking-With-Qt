#include "myStruck.h"
//using namespace cv;
namespace STRUCK
{
//Struct StruckParam
void StruckParam::addFeature(Config::FeatureType _featureType,Config::KernelType _kernelType,double _param)
{
	Config::FeatureKernelPair temp;
	temp.feature=_featureType;
	temp.kernel=_kernelType;
	if(_kernelType==Config::kKernelTypeGaussian)
	temp.params.push_back(_param);
	m_featureKernelPairs.push_back(temp);
}
//class myStruck
myStruck::myStruck(const StruckParam& _param)
{
	m_myConfigPtr=new Config();
	m_myConfigPtr->searchRadius=_param.m_searchRadius;
	m_myConfigPtr->svmC=_param.m_svmc;
	m_myConfigPtr->svmBudgetSize=_param.m_svmBudgetSize;
	m_myConfigPtr->features.clear();
#define FEATURES    _param.m_featureKernelPairs
	typedef 	std::vector<Config::FeatureKernelPair> FeatureVec;
	for(FeatureVec::const_iterator iter=FEATURES.begin();iter!=FEATURES.end();iter++)
	{
		m_myConfigPtr->features.push_back(*iter);
	}
#undef FEATURES    _param.m_featureKernelPairs
	m_myStruckPtr=new Tracker(*m_myConfigPtr);
}
myStruck::~myStruck(void)
{
	delete m_myStruckPtr;
	delete m_myConfigPtr;
}
void myStruck::setRadius(int _radius)
{
	if(_radius>0&&_radius<50)
	{
		m_myConfigPtr->searchRadius=_radius;
	}
}
void myStruck::_init(const cv::Mat &_frame,const cv::Rect &_box)
{
	if(m_myStruckPtr->IsInitialised())
	{
		m_myStruckPtr->Reset();
	}
	else
	{
		FloatRect initBox(_box.x,_box.y,_box.width,_box.height);
		m_myStruckPtr->Initialise(_frame,initBox);
	}
}
void myStruck::_track(const cv::Mat &_frame,cv::Rect &_box)
{
	if(m_myStruckPtr->IsInitialised())
	{
		m_myStruckPtr->Track(_frame);
		FloatRect tempRect(m_myStruckPtr->GetBB());
		_box.x=tempRect.XMin();
		_box.y=tempRect.YMin();
		_box.width=tempRect.XMax()-tempRect.XMin();
		_box.height=tempRect.YMax()-tempRect.YMin();
	}
}
//namespace STRUCK
};

