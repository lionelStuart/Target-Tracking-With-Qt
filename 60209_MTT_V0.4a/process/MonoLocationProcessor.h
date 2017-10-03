/*****************************************************************/
/**�����������ʼ������***************************************************************/
/***********initTracker��ʼ��������******************************************************/
/***********initVO��ʼ����λ����ÿ��ֻ��ʼ��һ������롪��poseFilePath/fov/����imgSizeȫ����ʼ��*/
/***********֮�����ʹ�ã�����ȱʡֵΪ���β���ʼ��������groundTruthָ����ʵֵ�ļ�********************************************/
/***********initMapper��ʼ��ͼ���ļ�������ʵ�ߴ�******************************************************/
/***********processΪ����������VideoProcessor����******************************************************/
/***********getMapͨ����������ȷ����Ҫ���ƵĹ켣�����ػ��ƵĽ��******************************************************/
/***********setFovFromFile����poseFile����ļ��ж�ȡfov��ֵ******************************************************/
/***********clearAll���VO��Mapper����Ӧ�����������¶����µ���Ƶʱ******************************************************/
/***********drawEvent��TrakcerProcessor����ͬ�Ļ�ͼ����******************************************************/
/*****************************************************************/
/***********updateTrajectory���¹켣******************************************************/
/***********updateTargetPOSITin����Ŀ��λ��******************************************************/
/***********clearTrajectoryGroundTruth��չ켣����ʵֵ��Ӧ�����¸��ٻ�������ٲ���ʱ******************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*update 160308����setWidthFromFile/setHeightFromFile*/
/*��pose�ļ��ж�����δ�С*/
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
class MonoLocationProcessor :public FrameProcessor//�̳�FrameProcessor����̬�󶨵�QVideoProcessor��ʵ�ֶ�λ
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
	CTrajectoryManager* m_trajectoryManager;//�켣������
	cv::Mat m_map;					/*map*/		//ԭʼ��ͼ
	std::vector<cv::Point2d>m_viewPoints;//��Ұ���Ƶ�
	cv::Mat m_trajectoryMap;						//���¹켣��ͼ
	std::string m_mapFilePath;						//��ͼ�ļ�·��
	double m_geoMapWidth;						//��ʵ���ο�
	double m_geoMapHeight;					//��ʵ���θ�
	trajectory* m_calTrajectoryPtr;					//����켣
	trajectory* m_realTrajectoryPtr;					//��ʵ�켣
	std::string m_uavPoseFile;/*VO*/			//uavPose�ļ�·��
	std::string m_groundTruthFilePath;		//Ŀ����ʵλ��·��
	cv::Size m_cameraImgSize;					//�������
	double m_fov;											//fov��
	cv::Mat m_calAbsPosition;						//�������λ��
	cv::Mat m_calRelPosition;						//�������λ��
	cv::Mat m_absolutePositin;					//Ŀ����ʵλ��
	cv::Mat m_error;										//���
	cv::Mat m_uavPose;									//��̬����
	cv::Rect m_trackingBox;/*tracker*/		//���ٳ�ʼ��
	CMyTracker *m_tracker;							//������
	myUAV::CMyUavVO *m_locator;			//��λ��
	CDrawMap *m_mapper;							//��ͼ����
	bool m_bTrackerInited;							//����ʼ��״̬�Ĳ�������
	bool m_bVOInited;
	bool m_bMapperInited;
	float m_frameRate;
};
inline CMyTracker* MonoLocationProcessor::getTracker(){return m_tracker;}
inline double MonoLocationProcessor::getFov(){return m_fov;}
#endif//MonoLocationProcessor_H

