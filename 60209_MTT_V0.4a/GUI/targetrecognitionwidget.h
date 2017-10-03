/*****************************************************************/
/*******Qt界面类*****************************************************/
/*******目标识别任务Widget**********************************************/
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
class TargetRecognitionWidget : public QWidget		//目标识别类
{
	Q_OBJECT
public:
	TargetRecognitionWidget(QWidget *parent = 0);
	~TargetRecognitionWidget();
signals:
	void updateInfo(QString _source);
public slots:
	void onOpenFile();
	void updateFrame();//响应qvideoprocessor帧处理，display信号，每帧更新信息
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
