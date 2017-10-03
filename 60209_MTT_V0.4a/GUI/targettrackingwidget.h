/*****************************************************************/
/****Qt界面类*************************************************************/
/*****单目标跟踪任务Widget********************************************/
/*****slots内为各控件槽函数**************************************/
/*****updateFrame与QVideoProcessor类的信号display绑定********/
/*****包含头文件：paramWidget参数widget类************************************************************/
/*****drawrectwnd鼠标框选widget************************************************************/
/*****process/trackProcessor跟踪处理类************************************************************/
/*****videoProcessor/QvideoProcessor视频播放类************************************************************/
/*****************************************************************/
#ifndef TARGETTRACKINGWIDGET_H
#define TARGETTRACKINGWIDGET_H

#include <QWidget>
#include "ui_targettrackingwidget.h"
class trackProcessor;
class QVideoProcessor;
class CDrawRectWnd;
class CParamWidget;
class TargetTrackingWidget : public QWidget		//单目标跟踪视类
{
	Q_OBJECT
public:
	TargetTrackingWidget(QWidget *parent = 0);
	~TargetTrackingWidget();
	void setTrackingType(const std::string &_type);
	std::string& getTrackingType();
signals:
	void updateInfo(QString _source);
	void receiveTrackingType(QString _source);
public slots:
	void onOpenFile();
private slots:
	void on_playButton_clicked();
	void on_stopButton_clicked();
	void on_drawButton_clicked();
	void receiveRects();//响应rectReady,初始化跟踪器，设置processor
	void updateFrame();//响应qvideoprocessor帧处理，display信号，每帧更新信息
	void onUpdateInfo(const QString &_source);
	void initParamWidget(const QString&_source);
private:
	void init_UI();
	void initTrackerWithParam();
private:
	CParamWidget *m_paramWidget;
	Ui::TargetTrackingWidget ui;
	QVideoProcessor* m_video;
	trackProcessor* m_trackMethod;
	QRect m_boundingBox;
	std::string m_trackType;
	QString m_infomation;
};

#endif // TARGETTRACKINGWIDGET_H
