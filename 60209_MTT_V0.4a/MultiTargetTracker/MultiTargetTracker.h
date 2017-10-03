/*****************************************************************/
/**多目标跟踪类**********************************************/
/**实现数据关联，视觉测距和轨迹管理******************************/
/**输入为已检测像素图框，使用update方法*************************/
/**setDA修改关联参数，有默认值*********************************/
/**setVO设置相机参数，不设定则不进行视觉测距和轨迹关联**************/
/**set&getTargetType设定目标类型************************************/
/**getTraceUpdate在update后获取新检测的位置和标号(弃用)*****************/
/**getDetection替代getTraceUpdate获取当前检测**************************/
//getTrajectoies 获取当前轨迹
/***************************************By Linoel*****************/
/*****************************************************************/
//detectionFilters检测值滤波
//COverlap detectionFilter私有类
//CDetecionBox 检测box类
//CDetectin vector for CDetecionBox
//51224
#ifndef CMultiTargetTracker_H
#define CMultiTargetTracker_H
#include"../DA/DataAssociation.h"
#include"../myUAVMonoVO/MyUavVO.h"
#include"../Trajectory/TrajectoryManager.h"
using myUAV::CMyUavVO;
//检测值过滤，保留minSize到maxSize之间的检测，并去除重叠检测
void detectionFilter(std::vector<cv::Rect> &_rects,int _minSize,int _maxSize);
class COverlap
{//private class for detectionFilter
	friend void detectionFilter(std::vector<cv::Rect> &_rects,int _minSize,int _maxSize);
private:
	static int overlap(cv::Rect &_rectA,cv::Rect &_rectB);//取值0，-1，1 无重合，选A，选B
	static float func(cv::Rect &_rectOverlap,cv::Rect &_rectSelect);
};
struct CDetectionBox
{
	cv::Rect m_box;
	cv::Point m_center;
	int m_pixID;
	int m_length;
};
struct CDetection
{
	std::vector<CDetectionBox> m_detection;
	void clear();
	int size();
};
inline void CDetection::clear(){m_detection.clear();}
inline int CDetection::size(){return m_detection.size();}
class CMultiTargetTracker
{
public:
	void setDA(float _dt=0.2,float _accel_noise_mag=0.5,double _dist_thres=60,int _maximum_allowed_skipped_frames=10,int _max_trace_length=10);
	void setVO(const std::string &_UAVPoseFilePath="",const cv::Size &_imgSize=cv::Size(),double _fov=0);
	void update(int _frameID,const std::vector<cv::Rect> &_detectionRects);
	void setTargetType(const std::string &_type);
    const std::string &getTargetType();
	void getTraceUpdate(std::vector<int> &_traceIDVec,std::vector<Point2d> &_traceCenterVec);
    CTrajectoryManager* getTrajectories();
	const std::vector<CDetectionBox> &getDetection();
	CMultiTargetTracker(void)/*:m_enableVO(false)*/;
	~CMultiTargetTracker(void);
private:
	CMyUavVO* m_ptrVO;
	std::string m_targetType;
	int m_prevTargetsCount;
	int m_currentTargetsCount;
	CDetection m_currentDetection;
private ://VO Enable Extends		
	bool m_enableVO;
	CDataAssociation* m_ptrDA;
	CTrajectoryManager *m_ptrTrajectoryManager;
};
inline const std::vector<CDetectionBox>& CMultiTargetTracker::getDetection(){return m_currentDetection.m_detection;}
//CMultiTargetTracker_H
#endif

