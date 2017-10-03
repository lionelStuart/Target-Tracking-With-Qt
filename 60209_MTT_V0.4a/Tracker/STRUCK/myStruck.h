#ifndef myStruck_H
#define myStruck_H
/*****************************************************************/
/***myStruck类**************************************************/
/***STRUCK接口，需要Eigen/源文件指定src文件夹/默认构造函数需要*/
/***config.txt文件*************************************************/
/***StruckParam用于设定STRUCK参数*****************************/
/***增加构造函数myStruck(StruckParam)**************************/
/***setRadius改变搜索半径****************************************/
/***通用的_init和_track方法***************************************/
/*****************************************************************/
/*****************************************************************/
/************************************************By Lionel********/
/*Notice:********************************************************/
//Config::FeatureType Config::kFeatureTypeHaar
//Config::FeatureType Config::kFeatureTypeRaw
//Config::FeatureType Config::kFeatureTypeHistogram
//Config::KernelType Config::kKernelTypeLinear
//Config::KernelType Config::kKernelTypeGaussian
//Config::KernelType Config::kKernelTypeIntersection
//Config::KernelType Config::kKernelTypeChi2
//核类型为高斯时，设定第三项参数Gamma
/*****************************************************************/
//解决命名冲突问题，修改Rect.h文件为Rect_S.h Rect-》Rect_S
//Tracker类与KCFTracker基类重复，修改Tracker_K
//修改Config默认设置，取消一种默认构造函数，不再需要StruckConfig.txt文件
/*****************************************************************/
#include"Tracker.h"
#include"Config.h"
#include<opencv2/opencv.hpp>
using cv::Mat;
using cv::Rect;
namespace STRUCK
{
struct StruckParam{//STRUCK算法参数设定
	std::vector<Config::FeatureKernelPair> m_featureKernelPairs;
	int m_searchRadius;
	double m_svmc;
	int m_svmBudgetSize;
	StruckParam():m_searchRadius(30),m_svmc(1.0),m_svmBudgetSize(0){
	m_featureKernelPairs.clear();addFeature(Config::kFeatureTypeHaar,Config::kKernelTypeGaussian,0.2);}
	void addFeature(Config::FeatureType _featureType,Config::KernelType _kernelType,double _param);//增加特征
};
class myStruck
{
public:
	  //myStruck(const std::string &_configPath=".\\STRUCK\\StruckConfig.txt")://默认构造函数
	  //m_myConfigPtr(new Config(_configPath)),m_myStruckPtr(new Tracker(*m_myConfigPtr)){}
	explicit myStruck(const StruckParam& _param=StruckParam());//参数设定的构造函数
	  void setRadius(int _radius);
	  ~myStruck(void);
	  void _init(const cv::Mat &_frame,const cv::Rect&_box);//初始化
	  void _track(const cv::Mat &_frame,cv::Rect &_box);//跟踪
private:
	Config* m_myConfigPtr;
	Tracker* m_myStruckPtr;
};
//namespace STRUCK
};
#endif

