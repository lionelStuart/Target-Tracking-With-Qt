#ifndef TARGETLOCATIONWIDGET_H
#define TARGETLOCATIONWIDGET_H
/*****************************************************************/
/****Ŀ�궨λ���UIģ��*************************************************************/
/****��myTrakcer����ѡһ�ָ��������ڻ�ȡͼ������*************************************************************/
/****��ʹ��myUAVMonoVO��ȡ�����˻��������ж�λ*************************************************************/
/*****����ͷ�ļ�drawrectwnd��ѡ��ʼλ��************************************************************/
/*****process/MonoLocationProcessorѡ�ø������Ͷ�λ�Ĵ�����************************************************************/
/*****videoProcessor/QvideoProcessor��Ƶ������************************************************************/
/*****m_monoLocatorΪ���ٶ�λ����************************************************************/
/*****m_videoΪ��Ƶ����************************************************************/
/*****m_boundingBoxΪ��ʼ�����ٿ�************************************************************/
/*****��Ϣm_trackingType/m_information************************************************************/
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
	//void on_geoSetButton_clicked();��������Ϊ��pose�ļ�����
	void on_loadMapButton_clicked();
	//void on_loadTargetButton_clicked();��������ʱ����
	void on_loadPoseButton_clicked();
	void on_playButton_clicked();
	void on_stopButton_clicked();
	void on_drawButton_clicked();
	void receiveRects();//��ӦrectReady,��ʼ��������������processor
	void updateFrame();//��Ӧqvideoprocessor֡����display�źţ�ÿ֡������Ϣ
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
