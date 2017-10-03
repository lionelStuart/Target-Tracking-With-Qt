/*******************************************************************/
/**轨迹管理类******************************************************/
/**addTrajecty按Index添加新轨迹，初始帧为0**********************/
/**updateTrajectory更新维护**************************************/
/**getTrajectory获取轨迹*****************************************/
/*****************************************************************/
/**CDrawMap输入轨迹绘制地图***********************************/
/**setParam设置地图参数，读入图像及实际地理长宽****************/
/**drawTrajectory绘制指定轨迹***********************************/
/************************************************By Lionel********/
/*****************************************************************/
//51221
//最大轨迹调整到300
//扩展CTrajectory为结构体，增加属性
//DrawMap增加drawTrajectories方法
//
//51223
//trajectory类添加m_pixelCoordinate成员
//CTrajectoryManager在创建和更新轨迹时更新轨迹最后像素坐标
//
//51224
//相比之前版本有较大的改动，用以支持多机协同时的数据关联
//在CDetection类中包含有m_pixID ,可以通过CTrajectoryManager类getTrajectory访问
//在trajectory类中终止的轨迹标注为STATUS_TERMINATE,
//在协同关联时需要关联的类型只有status_track ，并通过length获取轨迹长度
//pixelCoordinate获取所在像素坐标，若本帧未更新，则是历史坐标，
//struct node中获取同步好的frameID和x,y,z,其中有用的数据是x,z
//轨迹关联中需要用到的方法
//getType
//length
//search
//pixelCoordinate
//update160120CDrawMap增加视野绘制方法drawViewPort
#ifndef CTrajectoryManager_H
#define CTrajectoryManager_H
#include<opencv2\opencv.hpp>
#include<vector>
using std::vector;
//节点为帧位置和坐标，从0帧开始记录每一帧位置，addTrajectory_frameID输入为0
const static int MAX_TRAJECTORIES=1000;//最大记录轨迹数量
struct node{
		double frameID;
		double x;
		double y;
		double z;
		node():frameID(0),x(-1),y(-1),z(-1){}
};
//typedef std::vector<node> trajectory ;
struct trajectory
{
	std::vector<node> m_trajectory ;
	int m_prevFrameID;
	cv::Point2d m_pixelCoordinate;
	enum status{
		STATUS_NULL,STATUS_TRACK,STATUS_TERMINATE};
	status m_status;
	cv::Point2d pixelCoordinate() const;
	int length() const;
	status getType() const;
	void setType(const trajectory::status &_status);
	void remove();
	int search(int _frameID);//依照frameID查找node
	trajectory():m_prevFrameID(0),m_status(STATUS_NULL){}
};
inline cv::Point2d trajectory::pixelCoordinate() const {return m_pixelCoordinate;}
inline int trajectory::length()const{return m_trajectory.size();}
inline trajectory::status trajectory::getType()const{return m_status;}
inline void trajectory::setType(const trajectory::status &_status){m_status=_status;}
inline void trajectory::remove(){m_trajectory.clear();}
inline int trajectory::search(int _frameID){
	for(int i=0;i!=m_trajectory.size();i++)
		if(m_trajectory[i].frameID==_frameID)return i;
	return -1;}
class CTrajectoryManager
{
public://Trajectory只增不减
	void addTrajectory(int _index,const cv::Mat &_startPosition,int _frameID=0,const cv::Point2d _pixelCoordinate=cv::Point2d());
	void updateTrajectory(int _index,const cv::Mat &_newPosition,int _frameID,const cv::Point2d _pixelCoordinate=cv::Point2d());
   trajectory& getTrajectory(int _index) ;
	int getTrajectoriesCount() const;
	int getTrajectoriesFullCount() const;//当前到达Trajectories_index最大数值
	void clear();
	CTrajectoryManager(void);
	~CTrajectoryManager(void);
private:
	trajectory m_trajectories[MAX_TRAJECTORIES];
	int m_totalNum;
	int m_maxIndex;
};
class CDrawMap
{
public:
	void setParam(const cv::Mat _map,double _GeoMapWidth,double _GeoMapHeight);
	void drawTrajectories(cv::Mat &_map,  CTrajectoryManager* _trajectoriesPtr);
	void drawTrajectory(cv::Mat &_map,const trajectory&_trajectory,const cv::Scalar &_color);
	void drawViewPort(cv::Mat &_map,const std::vector<cv::Point2d>&_viewPoints,const cv::Scalar &_color);
private:
	double m_scaleX;
	double m_scaleY;
};
 static CvScalar  CDrawMap_Colors[]= 
{
	{{0,0,255}},
	{{0,128,255}},
	{{0,255,255}},
	{{0,255,0}},
	{{255,128,0}},
	{{255,255,0}},
	{{255,0,0}},
	{{255,0,255}}
};
#endif

