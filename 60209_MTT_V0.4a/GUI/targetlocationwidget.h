#ifndef TARGETLOCATIONWIDGET_H
#define TARGETLOCATIONWIDGET_H
/*****************************************************************/
/****目标定位类的UI模块*************************************************************/
/****从myTrakcer中任选一种跟踪器用于获取图像坐标*************************************************************/
/****并使用myUAVMonoVO获取的无人机参数进行定位*************************************************************/
/*****包含头文件drawrectwnd框选初始位置************************************************************/
/*****process/MonoLocationProcessor选用跟踪器和定位的处理类************************************************************/
/*****videoProcessor/QvideoProcessor视频播放类************************************************************/
/*****m_monoLocator为跟踪定位方法************************************************************/
/*****m_video为视频对象************************************************************/
/*****m_boundingBox为初始化跟踪框************************************************************/
/*****信息m_trackingType/m_information************************************************************/
#include <QWidget>
#include "ui_targetlocationwidget.h"
class MonoLocationProcessor;
class QVideoProcessor;
class CDrawRectWnd;
class TargetLocationWidget : public QWidget
{
	Q_OBJECT
public:
	TargetLocationWidget(QWidget *parent = 0);
	~TargetLocationWidget();
	void setTrackingType(const std::string &_type);
	std::string& getTrackingType();
signals:
	void updateInfo(QString _source);
	void receiveTrackingType(QString _source);
public slots:
	void onOpenFile();
	void onFileLoaded();
private slots:
	//void on_geoSetButton_clicked();废弃，改为从pose文件读入
	void on_loadMapButton_clicked();
	//void on_loadTargetButton_clicked();废弃，暂时无用
	void on_loadPoseButton_clicked();
	void on_playButton_clicked();
	void on_stopButton_clicked();
	void on_drawButton_clicked();
	void receiveRects();//响应rectReady,初始化跟踪器，设置processor
	void updateFrame();//响应qvideoprocessor帧处理，display信号，每帧更新信息
	void onUpdateInfo(const QString &_source);
private:
	void init_UI();
	void updateMap();
private:
	Ui::TargetLocationWidget ui;
	MonoLocationProcessor* m_monoLocator;
	QVideoProcessor* m_video;
	QRect m_boundingBox;
	std::string m_trackType;
	QString m_infomation;
	QString m_paramInfomation;
};

#endif // TARGETLOCATIONWIDGET_H
