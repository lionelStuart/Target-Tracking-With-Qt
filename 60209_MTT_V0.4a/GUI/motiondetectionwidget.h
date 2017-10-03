/*****************************************************************/
/****Qt������************************************/
/****�˶�Ŀ���⹦�ܴ���**************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef MOTIONDETECTIONWIDGET_H
#define MOTIONDETECTIONWIDGET_H

#include <QWidget>
#include "ui_motiondetectionwidget.h"
//class MotionDetectionWidget 
class QVideoProcessor;
class CMotionDetectionProcessor;
class MotionDetectionWidget : public QWidget
{
	Q_OBJECT

public:
	MotionDetectionWidget(QWidget *parent = 0);
	~MotionDetectionWidget();
signals:
	void updateInfo(QString _source);
public slots:
	void onOpenFile();
private slots:
	void on_playButton_clicked();
	void on_stopButton_clicked();
	void updateFrame();//��Ӧqvideoprocessor֡����display�źţ�ÿ֡������Ϣ
	void onUpdateInfo(const QString &_source);
private:
	void initMotionDetector();
	void init_UI();
private:
	bool m_bInitedMD;
	Ui::MotionDetectionWidget ui;
	QVideoProcessor *m_video;
	CMotionDetectionProcessor *m_motionDetector;
	QString m_infomation;
};

#endif // MOTIONDETECTIONWIDGET_H
