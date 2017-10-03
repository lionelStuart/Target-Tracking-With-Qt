#ifndef MULTILOCATIONWIDGET_H
#define MULTILOCATIONWIDGET_H

#include <QWidget>
#include "ui_multilocationwidget.h"
class QVideoProcessor;
class MultiLocationProcessor;
class MultiLocationWidget : public QWidget
{
	Q_OBJECT

public:
	MultiLocationWidget(QWidget *parent = 0);
	~MultiLocationWidget();
signals:
	void updateInfo(QString _source);
	public slots:
		void onOpenFile();
		void updateFrame();//响应qvideoprocessor帧处理，display信号，每帧更新信息
		void onUpdateInfo(const QString &_source);
		void onFileLoaded();
		private slots:
			void on_playButton_clicked();
			void on_stopButton_clicked();
			void on_loadDetectorButton_clicked();
			void on_loadPoseButton_clicked();
			void on_loadMapButton_clicked();
private:
	void init_UI();
	void updateMap();
	void clearImage();
private:
	QVideoProcessor* m_video;
	MultiLocationProcessor *m_MTL;
	QString m_detectorFilePath;
	QString m_poseFilePath;
	QString m_mapFilePath;
	QString m_infomation;
	QString m_paramInfomation;
	Ui::MultiLocationWidget ui;
};

#endif // MULTILOCATIONWIDGET_H
