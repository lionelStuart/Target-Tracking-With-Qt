/*****************************************************************/
/*******Qt界面类*****************************************************/
/*******多无人机协同跟踪定位任务widget**************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef COOPLOCATIONWIDGET_H
#define COOPLOCATIONWIDGET_H

#include <QWidget>
#include "ui_cooplocationwidget.h"

class CCoopLocatoinProcessor;

class CoopLocationWidget : public QWidget
{
	Q_OBJECT

public:
	CoopLocationWidget(QWidget *parent = 0);
	~CoopLocationWidget();
signals:
	void updateInfo(QString _source);
private slots:
		void updateFrame();//响应oprocessor帧处理，display信号，每帧更新信息
		void onUpdateInfo(const QString &_source);
		void on_loadVideoButton_1_clicked();
		void on_loadVideoButton_2_clicked();
		void on_loadDetectorButton_1_clicked();
		void on_loadDetectorButton_2_clicked();
		void on_loadPoseButton_1_clicked();
		void on_loadPoseButton_2_clicked();
		void on_runButton_clicked();
		void on_stopButton_clicked();
		void on_loadMapButton_clicked();
		//void on_geoSetButton_clicked();
private:
	void init_UI();
	void clear_Image();
private:
	Ui::CoopLocationWidget ui;
	CCoopLocatoinProcessor* m_processor;
	std::string m_mapFilePath;
	double m_geoWidth;
	double m_geoHeight;
	QString m_infomation;
	QString m_paramInfo;
};

#endif // COOPLOCATIONWIDGET_H
