#ifndef CCoopLocatoinProcessor_H
#define CCoopLocatoinProcessor_H
//协同定位需要实现多路视频的读取，QVideoProcessor的框架无法满足这一需求，
//构造新的Qt-视频处理类实现该需求
//本文件下继承VideoProcessor和QtWidget实现新的多路视频处理类
//
#include<QtCore/QtCore>
#include <QtWidgets/QLabel>
#include<qtimer.h>
#include"Mat2QImage/Mat2QImage.h"
class VideoProcessor;
class CMyDetector;
class CMultiTargetTracker;
class CCooperativeLocalization;
class CDrawMap;

class CSingleTaskProcessor
{
public:
	CSingleTaskProcessor();
	~CSingleTaskProcessor();
	void clear();
	void initVideo(const std::string &_videoFilePath);
	void initDetector(const std::string &_classifierFilePath);
	void initTracker(const std::string &_poseFilePath);
	bool videoIsInited();
	bool detectorIsInited();
	bool trackerIsInited();
	CMultiTargetTracker* getMTT();
	VideoProcessor* getVideo();
	void processFrame(cv::Mat &_outputFrame);
public:
	double setFovFromFile(const std::string &_poseFilePath);
private:
	VideoProcessor  *m_video;
	CMyDetector *m_detector;
	CMultiTargetTracker *m_tracker;
	bool m_bInitVideo;
	bool m_bInitDetector;
	bool m_bInitTracker;
	float m_frameRate;
};
inline bool CSingleTaskProcessor::videoIsInited(){return m_bInitVideo;}
inline bool CSingleTaskProcessor::detectorIsInited(){return m_bInitDetector;}
inline bool CSingleTaskProcessor::trackerIsInited(){return m_bInitTracker;}
inline CMultiTargetTracker* CSingleTaskProcessor::getMTT(){return m_tracker;}
inline VideoProcessor* CSingleTaskProcessor::getVideo(){return m_video;}

void showFrame(const cv::Mat & _image,QLabel *_window);

class CCoopLocatoinProcessor:public QObject
{
	Q_OBJECT
public:
	CCoopLocatoinProcessor(void);
	~CCoopLocatoinProcessor(void);
	CSingleTaskProcessor* getTask_1();
	CSingleTaskProcessor* getTask_2();
	void clear();
	void initTimer();
	void initMapper(const std::string &_mapPath="",double _GeoMapWidth=-1,double _GeoMapHeight=-1);
	double setWidthFromFile(const std::string &_poseFilePath);
	double setHeightFromFile(const std::string &_poseFilePath);
	const cv::Mat &getOutput_1();
	const cv::Mat &getOutput_2();
	const cv::Mat &getMapOut();
	const cv::Mat &getBlankMask();
	bool pause();
signals:
	void display();
private slots:
	void run();
private:
	void drawSyncIDInUAV(cv::Mat &_input_1,cv::Mat &_input_2);
	bool isInited();
	bool mapperIsInited();
	//void initCoopLocator();
private:
	CSingleTaskProcessor* m_task_1;
	CSingleTaskProcessor* m_task_2;
	CCooperativeLocalization* m_coopLocator;
	CDrawMap *m_mapper;
	QTimer *m_timer;
	cv::Mat m_map;
	cv::Mat m_mapOut;
	cv::Mat m_output_1;
	cv::Mat m_output_2;
	bool m_bInitMapper;
	bool m_bIsRun;
};
inline CSingleTaskProcessor* CCoopLocatoinProcessor::getTask_1(){return m_task_1;}
inline CSingleTaskProcessor* CCoopLocatoinProcessor::getTask_2(){return m_task_2;}
inline bool CCoopLocatoinProcessor::mapperIsInited(){return m_bInitMapper;}
inline const cv::Mat &CCoopLocatoinProcessor::getOutput_1(){return m_output_1;}
inline const cv::Mat &CCoopLocatoinProcessor::getOutput_2(){return m_output_2;}
inline const cv::Mat &CCoopLocatoinProcessor::getMapOut(){return m_mapOut;}
inline bool CCoopLocatoinProcessor::pause(){m_bIsRun=!m_bIsRun;return m_bIsRun;}
#endif//CCoopLocatoinProcessor_H

