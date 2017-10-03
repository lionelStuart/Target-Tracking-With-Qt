/*****************************************************************/
/****Qt������*************************************************************/
/*****��Ŀ���������Widget********************************************/
/*****slots��Ϊ���ؼ��ۺ���**************************************/
/*****updateFrame��QVideoProcessor����ź�display��********/
/*****����ͷ�ļ���paramWidget����widget��************************************************************/
/*****drawrectwnd����ѡwidget************************************************************/
/*****process/trackProcessor���ٴ�����************************************************************/
/*****videoProcessor/QvideoProcessor��Ƶ������************************************************************/
/*****************************************************************/
#ifndef TARGETTRACKINGWIDGET_H
#define TARGETTRACKINGWIDGET_H

#include <QWidget>
#include "ui_targettrackingwidget.h"
class trackProcessor;
class QVideoProcessor;
class CDrawRectWnd;
class CParamWidget;
class TargetTrackingWidget : public QWidget		//��Ŀ���������
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
	void receiveRects();//��ӦrectReady,��ʼ��������������processor
	void updateFrame();//��Ӧqvideoprocessor֡����display�źţ�ÿ֡������Ϣ
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
