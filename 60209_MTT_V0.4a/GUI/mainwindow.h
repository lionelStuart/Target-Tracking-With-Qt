/*****************************************************************/
/***Qt窗口类**************************************************************/
/***主视口**************************************************************/
/***Qt运行界面主窗口*****************************************************/
/***包含功能：跟踪算法/定位算法/运动检测/目标识别/*************************************/
/*************多目标跟踪/协同目标定位****************************************/
/*****************************************************************/
/*****************************************************************/
/*******************************By *LiSi***************/
/*******************************Email:lisi_xdu@126.com******/
/*******************************Date:10/2015-10/2016*****************/
/*****************************************************************/
/*This software is provided by the copyright holders and contributors "as is" and
/*any express or implied warranties, including, but not limited to, the implied
/*warranties of merchantability and fitness for a particular purpose are disclaimed.
/*In no event shall copyright holders or contributors be liable for any direct,
/*indirect, incidental, special, exemplary, or consequential damages
/*(including, but not limited to, procurement of substitute goods or services;
/*loss of use, data, or profits; or business interruption) however caused
/*and on any theory of liability, whether in contract, strict liability,
/*or tort (including negligence or otherwise) arising in any way out of
/*the use of this software, even if advised of the possibility of such damage.
/****************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
//class TargetTrackingWidget;
class MainWindow : public QMainWindow				//主窗口视类
{
	Q_OBJECT
public:
	enum WIDGET_TYPE{
		WIDGET_MAINWINDOW,
		WIDGET_TARGETTRACKING,
		WIDGET_TARGETLOCATION,
		WIDGET_TARGETRECOGNITION,
		WIDGET_MOTIONDETECTION,
		WIDGET_MULTITRACKING,
		WIDGET_MULTILOCATION,
		WIDGET_COOPLOCATION
	};
	public slots:
		void on_actionReturn_triggered();	//返回首页
		void on_actionClose_triggered();		//关闭程序
		void on_actionTR_triggered();		//目标识别TARGETRECOGNITION
		void on_actionMD_triggered();		//运动检测MOTIONDETECTION
		void on_actionPF_triggered();		//粒子滤波跟踪ParticleFilter
		void on_actionCT_triggered();		//CT跟踪
		void on_actionHash_triggered();		//Hash跟踪
		void on_actionKCF_triggered();		//KCF跟踪
		void on_actionSTRUCK_triggered();	//STRUCK跟踪
		void on_actionSTC_triggered();		//STC跟踪
		void on_actionCTL_triggered();		//CT定位 --Location
		void on_actionPFL_triggered();		//粒子滤波定位
		void on_actionHashL_triggered();	//Hash定位
		void on_actionKCFL_triggered();		//KCF定位
		void on_actionSTRUCKL_triggered();	//STRUCK定位
		void on_actionSTCL_triggered();		//STC定位
		void on_actionMTT_triggered();		//单无人机多目标跟踪MultiTargetTracking
		void on_actionMTL_triggered();     //单无人机多目标定位MultiTargetLocation
		void on_actionMTCL_triggered();		//多无人机协同跟踪定位MultiTargetCooperattionLocation
		void on_actionAbout_triggered();	//关于本软件
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	void createWidgetMotionDetection();
	void createWidgetTargetTracking();
	void createWidgetTargetLocation();
	void createWidgetTargetRecognition();
	void createWidgetMultiTracking();
	void createWidgetCoopLocation();
	void createWidgetMultiLocation();
private:
	void clear(const WIDGET_TYPE &_ignoreType=WIDGET_MAINWINDOW);
	void init_UI();
	Ui::MainWindowClass ui;
	QWidget* m_widget;
	WIDGET_TYPE m_widgetType;
};

#endif // MAINWINDOW_H
