#ifndef myStruck_H
#define myStruck_H
/*****************************************************************/
/***myStruck��**************************************************/
/***STRUCK�ӿڣ���ҪEigen/Դ�ļ�ָ��src�ļ���/Ĭ�Ϲ��캯����Ҫ*/
/***config.txt�ļ�*************************************************/
/***StruckParam�����趨STRUCK����*****************************/
/***���ӹ��캯��myStruck(StruckParam)**************************/
/***setRadius�ı������뾶****************************************/
/***ͨ�õ�_init��_track����***************************************/
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
//������Ϊ��˹ʱ���趨���������Gamma
/*****************************************************************/
//���������ͻ���⣬�޸�Rect.h�ļ�ΪRect_S.h Rect-��Rect_S
//Tracker����KCFTracker�����ظ����޸�Tracker_K
//�޸�ConfigĬ�����ã�ȡ��һ��Ĭ�Ϲ��캯����������ҪStruckConfig.txt�ļ�
/*****************************************************************/
#include"Tracker.h"
#include"Config.h"
#include<opencv2/opencv.hpp>
using cv::Mat;
using cv::Rect;
namespace STRUCK
{
struct StruckParam{//STRUCK�㷨�����趨
	std::vector<Config::FeatureKernelPair> m_featureKernelPairs;
	int m_searchRadius;
	double m_svmc;
	int m_svmBudgetSize;
	StruckParam():m_searchRadius(30),m_svmc(1.0),m_svmBudgetSize(0){
	m_featureKernelPairs.clear();addFeature(Config::kFeatureTypeHaar,Config::kKernelTypeGaussian,0.2);}
	void addFeature(Config::FeatureType _featureType,Config::KernelType _kernelType,double _param);//��������
};
class myStruck
{
public:
	  //myStruck(const std::string &_configPath=".\\STRUCK\\StruckConfig.txt")://Ĭ�Ϲ��캯��
	  //m_myConfigPtr(new Config(_configPath)),m_myStruckPtr(new Tracker(*m_myConfigPtr)){}
	explicit myStruck(const StruckParam& _param=StruckParam());//�����趨�Ĺ��캯��
	  void setRadius(int _radius);
	  ~myStruck(void);
	  void _init(const cv::Mat &_frame,const cv::Rect&_box);//��ʼ��
	  void _track(const cv::Mat &_frame,cv::Rect &_box);//����
private:
	Config* m_myConfigPtr;
	Tracker* m_myStruckPtr;
};
//namespace STRUCK
};
#endif

