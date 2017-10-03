/*****************************************************************/
/**本类的三个初始化函数***************************************************************/
/***********initTracker初始化跟踪器******************************************************/
/***********initVO初始化定位，可每次只初始化一项，但必须——poseFilePath/fov/——imgSize全部初始化*/
/***********之后才能使用，给予缺省值为本次不初始化参数，groundTruth指定真实值文件********************************************/
/***********initMapper初始化图像文件，和真实尺寸******************************************************/
/***********process为处理函数，由VideoProcessor调用******************************************************/
/***********getMap通过布尔变量确定需要绘制的轨迹并返回绘制的结果******************************************************/
/***********setFovFromFile读入poseFile后从文件中读取fov数值******************************************************/
/***********clearAll清空VO和Mapper，对应操作：当重新读入新的视频时******************************************************/
/***********drawEvent与TrakcerProcessor中相同的绘图操作******************************************************/
/*****************************************************************/
/***********updateTrajectory更新轨迹******************************************************/
/***********updateTargetPOSITin更新目标位置******************************************************/
/***********clearTrajectoryGroundTruth清空轨迹和真实值对应于重新跟踪或结束跟踪操作时******************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*update 160308增加setWidthFromFile/setHeightFromFile*/
/*从pose文件中读入地形大小*/
#ifndef MonoLocationProcessor_H
#define MonoLocationProcessor_H

#include "VideoProcessor\VideoProcessor.h"
class CMyTracker;
class CDrawMap;
class trajectory;
class CTrajectoryManager;
namespace myUAV{
	class CMyUavVO;
}
class MonoLocationProcessor :public FrameProcessor//继承FrameProcessor，动态绑定到QVideoProcessor，实现定位
{
public:
	MonoLocationProcessor(void);
	~MonoLocationProcessor(void);
	void initTracker(const std::string &_trackingType,const cv::Rect &_rect);
	void initVO(const std::string &_poseFilePath="",double _fov=0,const cv::Size &_imgSize=cv::Size(0,0),const std::string &_groundTruthFile="");
	void initMapper(const std::string &_mapFilePath="",double _GeoMapWidth=0,double _GeoMapHeight=0);
	void process(const cv::Mat &_input,cv::Mat &_output);
	CMyTracker* getTracker();
	const cv::Mat& getMap(bool _bDrawCalTrajectory=true,bool _bDrawRealTrajectory=false);
	double setFovFromFile();
	double setWidthFromFile();
	double setHeightFromFile();
	double getFov();
	void clearAll();
	std::string &getInfomation();
private:
	void drawEvent(cv::Mat &_image,cv::Rect &_box);
	void setRect(const cv::Rect &_rect);
	void selectTrackingType(const std::string &_trackingType);
	void updateTargetPosition();
	void updateTrajectories();
	void updateViewPort();
	void clearTrajectory();
	void clearGroundTruth();
private:
	CTrajectoryManager* m_trajectoryManager;//轨迹管理类
	cv::Mat m_map;					/*map*/		//原始地图
	std::vector<cv::Point2d>m_viewPoints;//视野绘制点
	cv::Mat m_trajectoryMap;						//更新轨迹地图
	std::string m_mapFilePath;						//地图文件路径
	double m_geoMapWidth;						//真实地形宽
	double m_geoMapHeight;					//真实地形高
	trajectory* m_calTrajectoryPtr;					//计算轨迹
	trajectory* m_realTrajectoryPtr;					//真实轨迹
	std::string m_uavPoseFile;/*VO*/			//uavPose文件路径
	std::string m_groundTruthFilePath;		//目标真实位置路径
	cv::Size m_cameraImgSize;					//相机长宽
	double m_fov;											//fov角
	cv::Mat m_calAbsPosition;						//计算绝对位置
	cv::Mat m_calRelPosition;						//计算相对位置
	cv::Mat m_absolutePositin;					//目标真实位置
	cv::Mat m_error;										//误差
	cv::Mat m_uavPose;									//姿态参数
	cv::Rect m_trackingBox;/*tracker*/		//跟踪初始框
	CMyTracker *m_tracker;							//跟踪器
	myUAV::CMyUavVO *m_locator;			//定位器
	CDrawMap *m_mapper;							//地图绘制
	bool m_bTrackerInited;							//各初始化状态的布尔变量
	bool m_bVOInited;
	bool m_bMapperInited;
	float m_frameRate;
};
inline CMyTracker* MonoLocationProcessor::getTracker(){return m_tracker;}
inline double MonoLocationProcessor::getFov(){return m_fov;}
#endif//MonoLocationProcessor_H

