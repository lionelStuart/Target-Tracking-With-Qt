/*******************************************************************/
/**�켣������******************************************************/
/**addTrajecty��Index����¹켣����ʼ֡Ϊ0**********************/
/**updateTrajectory����ά��**************************************/
/**getTrajectory��ȡ�켣*****************************************/
/*****************************************************************/
/**CDrawMap����켣���Ƶ�ͼ***********************************/
/**setParam���õ�ͼ����������ͼ��ʵ�ʵ�����****************/
/**drawTrajectory����ָ���켣***********************************/
/************************************************By Lionel********/
/*****************************************************************/
//51221
//���켣������300
//��չCTrajectoryΪ�ṹ�壬��������
//DrawMap����drawTrajectories����
//
//51223
//trajectory�����m_pixelCoordinate��Ա
//CTrajectoryManager�ڴ����͸��¹켣ʱ���¹켣�����������
//
//51224
//���֮ǰ�汾�нϴ�ĸĶ�������֧�ֶ��Эͬʱ�����ݹ���
//��CDetection���а�����m_pixID ,����ͨ��CTrajectoryManager��getTrajectory����
//��trajectory������ֹ�Ĺ켣��עΪSTATUS_TERMINATE,
//��Эͬ����ʱ��Ҫ����������ֻ��status_track ����ͨ��length��ȡ�켣����
//pixelCoordinate��ȡ�����������꣬����֡δ���£�������ʷ���꣬
//struct node�л�ȡͬ���õ�frameID��x,y,z,�������õ�������x,z
//�켣��������Ҫ�õ��ķ���
//getType
//length
//search
//pixelCoordinate
//update160120CDrawMap������Ұ���Ʒ���drawViewPort
#ifndef CTrajectoryManager_H
#define CTrajectoryManager_H
#include<opencv2\opencv.hpp>
#include<vector>
using std::vector;
//�ڵ�Ϊ֡λ�ú����꣬��0֡��ʼ��¼ÿһ֡λ�ã�addTrajectory_frameID����Ϊ0
const static int MAX_TRAJECTORIES=1000;//����¼�켣����
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
	int search(int _frameID);//����frameID����node
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
public://Trajectoryֻ������
	void addTrajectory(int _index,const cv::Mat &_startPosition,int _frameID=0,const cv::Point2d _pixelCoordinate=cv::Point2d());
	void updateTrajectory(int _index,const cv::Mat &_newPosition,int _frameID,const cv::Point2d _pixelCoordinate=cv::Point2d());
   trajectory& getTrajectory(int _index) ;
	int getTrajectoriesCount() const;
	int getTrajectoriesFullCount() const;//��ǰ����Trajectories_index�����ֵ
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

