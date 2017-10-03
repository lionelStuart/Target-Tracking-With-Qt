/*****************************************************************/
/*******Qt界面类*****************************************************/
/*******多目标跟踪任务widget***************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef MULTITRACKINGWIDGET_H
#define MULTITRACKINGWIDGET_H

#include <QWidget>
#include "ui_multitrackingwidget.h"
class QVideoProcessor;
class CMultiTrackingProcessor;
class MultiTrackingWidget : public QWidget
{
	Q_OBJECT

public:
	MultiTrackingWidget(QWidget *parent = 0);
	~MultiTrackingWidget();
signals:
	void updateInfo(QString _source);
	public slots:
		void onOpenFile();
		void updateFrame();//响应qvideoprocessor帧处理，display信号，每帧更新信息
		void onUpdateInfo(const QString &_source);
		private slots:
			void on_playButton_clicked();
			void on_stopButton_clicked();
			void on_trackingButton_clicked();
			void on_minSizeSlider_valueChanged();
			void on_maxSizeSlider_valueChanged();
private:
	void init_UI();
private:
	QVideoProcessor* m_video;
	CMultiTrackingProcessor *m_MTT;
	QString m_detectorFilePath;
	Ui::MultiTrackingWidget ui;
	QString m_infomation;
};

#endif // MULTITRACKINGWIDGET_H
