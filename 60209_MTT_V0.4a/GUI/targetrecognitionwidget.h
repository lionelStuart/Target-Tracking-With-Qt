/*****************************************************************/
/*******Qt������*****************************************************/
/*******Ŀ��ʶ������Widget**********************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef TARGETRECOGNITIONWIDGET_H
#define TARGETRECOGNITIONWIDGET_H

#include <QWidget>
#include "ui_targetrecognitionwidget.h"
class QVideoProcessor;
class CTargetRecongnitionProcessor;
class TargetRecognitionWidget : public QWidget		//Ŀ��ʶ����
{
	Q_OBJECT
public:
	TargetRecognitionWidget(QWidget *parent = 0);
	~TargetRecognitionWidget();
signals:
	void updateInfo(QString _source);
public slots:
	void onOpenFile();
	void updateFrame();//��Ӧqvideoprocessor֡����display�źţ�ÿ֡������Ϣ
	void onUpdateInfo(const QString &_source);
private slots:
	void on_playButton_clicked();
	void on_stopButton_clicked();
	void on_detectButton_clicked();
	void on_minSizeSlider_valueChanged();
	void on_maxSizeSlider_valueChanged();
private:
	void init_UI();
private:
	Ui::TargetRecognitionWidget ui;
	QVideoProcessor* m_video;
	CTargetRecongnitionProcessor *m_TR;
	QString m_infomation;
	QString m_detectorFilePath;
};

#endif // TARGETRECOGNITIONWIDGET_H
