/*****************************************************************/
/***Qt������**************************************************************/
/***���ӿ�**************************************************************/
/***Qt���н���������*****************************************************/
/***�������ܣ������㷨/��λ�㷨/�˶����/Ŀ��ʶ��/*************************************/
/*************��Ŀ�����/ЭͬĿ�궨λ****************************************/
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
class MainWindow : public QMainWindow				//����������
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
		void on_actionReturn_triggered();	//������ҳ
		void on_actionClose_triggered();		//�رճ���
		void on_actionTR_triggered();		//Ŀ��ʶ��TARGETRECOGNITION
		void on_actionMD_triggered();		//�˶����MOTIONDETECTION
		void on_actionPF_triggered();		//�����˲�����ParticleFilter
		void on_actionCT_triggered();		//CT����
		void on_actionHash_triggered();		//Hash����
		void on_actionKCF_triggered();		//KCF����
		void on_actionSTRUCK_triggered();	//STRUCK����
		void on_actionSTC_triggered();		//STC����
		void on_actionCTL_triggered();		//CT��λ --Location
		void on_actionPFL_triggered();		//�����˲���λ
		void on_actionHashL_triggered();	//Hash��λ
		void on_actionKCFL_triggered();		//KCF��λ
		void on_actionSTRUCKL_triggered();	//STRUCK��λ
		void on_actionSTCL_triggered();		//STC��λ
		void on_actionMTT_triggered();		//�����˻���Ŀ�����MultiTargetTracking
		void on_actionMTL_triggered();     //�����˻���Ŀ�궨λMultiTargetLocation
		void on_actionMTCL_triggered();		//�����˻�Эͬ���ٶ�λMultiTargetCooperattionLocation
		void on_actionAbout_triggered();	//���ڱ����
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
