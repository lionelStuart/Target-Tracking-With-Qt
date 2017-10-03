#ifndef MultiLocationProcessor_H
#define MultiLocationProcessor_H
#include "VideoProcessor\VideoProcessor.h"
#define MTT_DEFAULT_MINSIZE 30
#define MTT_DEFAULT_MAXSIZE 80
class CMyDetector;
class CMultiTargetTracker;
class CDrawMap;
class MultiLocationProcessor:public FrameProcessor
{
public:
	MultiLocationProcessor(void);
	~MultiLocationProcessor(void);
	void setDetectionFilter(int _minSize=-1,int _maxSize=-1);
	void initTracker(const std::string &_classifierFilePath="",const std::string &_uavPoseFilePath="",const cv::Size _img_size=cv::Size(0,0));
	void initMapper(const std::string &_mapFilePath="",double _GeoMapWidth=0,double _GeoMapHeight=0);
	void process(const cv::Mat &_input,cv::Mat &_output);
	void clear();
	bool isInited();
	const cv::Mat& getMap();
	double getFov();
	double getGeoWidth();
	double getGeoHeight();
private:
	double setFovFromFile(const std::string &_poseFilePath);
	double setWidthFromFile(const std::string &_uavPoseFile);
	double setHeightFromFile(const std::string &_uavPoseFile);
	std::string m_classifierFilePath;
	std::string m_uavPoseFilePath;
	cv::Size m_imgSize;
	CMyDetector *m_detector;
	CMultiTargetTracker *m_tracker;
	std::vector<cv::Rect> m_detectRects;
	double m_geoMapWidth;
	double m_geoMapHeight;
	double m_fov;
	std::string m_mapFilePath;						//地图文件路径
	cv::Mat m_map;					/*map*/		//原始地图
	cv::Mat m_trajectoryMap;						//更新轨迹地图
	CDrawMap *m_mapper;							//地图绘制
	bool m_bTrackerInited;
	bool m_bMapperInited;
	float m_frameRate;
};
inline bool MultiLocationProcessor::isInited(){return m_bTrackerInited&&m_bMapperInited;}
inline const cv::Mat& MultiLocationProcessor::getMap(){return m_trajectoryMap;}
inline double MultiLocationProcessor::getGeoWidth(){return m_geoMapWidth;}
inline double MultiLocationProcessor::getGeoHeight(){return m_geoMapHeight;}
inline double MultiLocationProcessor::getFov(){return m_fov;}
#endif//MultiLocationProcessor_H