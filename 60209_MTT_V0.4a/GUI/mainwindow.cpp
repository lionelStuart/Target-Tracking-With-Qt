#include "mainwindow.h"
#include "targettrackingwidget.h"				//TargetTrackingWidget_UI
#include "targetlocationwidget.h"			    //TargetLocationWidget_UI
#include "motiondetectionwidget.h"				//MotionDetectionWidget_UI
#include "targetrecognitionwidget.h"			//TargetRecognitionWidget_UI
#include "multitrackingwidget.h"				//MultiTrackingWidget_UI
#include "cooplocationwidget.h"					//CoopLocationWidget_UI
#include"multilocationwidget.h"						//MultiTargetLocationWidget_UI
#include <QMessageBox>
#include<QTranslator>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
		ui.setupUi(this);
		init_UI();
}
void MainWindow::init_UI()
{
	m_widgetType=WIDGET_MAINWINDOW;
	m_widget=NULL;
	this->move(100,100);
}
void MainWindow::clear(const WIDGET_TYPE &_ignoreType/* =WIDGET_TYPE */)
{
	if(!m_widget)return;
	WIDGET_TYPE ignoreType=_ignoreType;//跳过指定类型
	m_widget->close();
	if(m_widgetType==WIDGET_TARGETTRACKING&&ignoreType!=WIDGET_TARGETTRACKING)
	{
		delete  (TargetTrackingWidget*)m_widget;
		m_widget=NULL;
	}
	if(m_widgetType==WIDGET_TARGETLOCATION&&ignoreType!=WIDGET_TARGETLOCATION)
	{
		delete (TargetLocationWidget*)m_widget;
		m_widget=NULL;
	}
	if(m_widgetType==WIDGET_MOTIONDETECTION)
	{
		delete (MotionDetectionWidget*)m_widget;
		m_widget=NULL;
	}
	if(m_widgetType==WIDGET_TARGETRECOGNITION)
	{
		delete (TargetRecognitionWidget*)m_widget;
		m_widget=NULL;
	}
	if(m_widgetType==WIDGET_MULTITRACKING)
	{
		delete (MultiTrackingWidget*)m_widget;
		m_widget=NULL;
	}
	if(m_widgetType==WIDGET_MULTILOCATION)
	{
		delete (MultiLocationWidget*)m_widget;
		m_widget=NULL;
	}
	if(m_widgetType==WIDGET_COOPLOCATION)
	{
		delete (CoopLocationWidget*)m_widget;
		m_widget=NULL;
	}
	disconnect(ui.actionOpenVideo,0);
}
MainWindow::~MainWindow()
{
}
void MainWindow::createWidgetTargetTracking()
{
	if(m_widgetType!=WIDGET_TARGETTRACKING)//当目前指向类型不是widget_targetTracking
	{																					//先清空m_widget指向类型，
		clear(WIDGET_TARGETTRACKING);											//再指向新类型
		m_widget=new TargetTrackingWidget(this);		//调用clear(m_widget)在清空时忽略widget_targetTracking类型
		m_widgetType=WIDGET_TARGETTRACKING;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		connect(ui.actionOpenVideo,SIGNAL(triggered()),
			m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::createWidgetTargetLocation()
{
	if(m_widgetType!=WIDGET_TARGETLOCATION)
	{
		clear(WIDGET_TARGETLOCATION);
		m_widget=new TargetLocationWidget(this);
		m_widgetType=WIDGET_TARGETLOCATION;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		connect(ui.actionOpenVideo,SIGNAL(triggered()),
			m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::on_actionReturn_triggered()
{
	if(m_widgetType!=WIDGET_MAINWINDOW)
	{
			clear();
			m_widgetType=WIDGET_MAINWINDOW;
			ui.centralWidget->setHidden(false);
			disconnect(ui.actionOpenVideo,0);
	}
}
void MainWindow::on_actionClose_triggered()
{
	on_actionReturn_triggered();
	this->close();
}
void MainWindow::on_actionCTL_triggered()
{
	createWidgetTargetLocation();
	((TargetLocationWidget*)m_widget)->setTrackingType("CT");
}
void MainWindow::on_actionPFL_triggered()
{
	createWidgetTargetLocation();
	((TargetLocationWidget*)m_widget)->setTrackingType("PF");
}
void MainWindow::on_actionHashL_triggered()
{
	createWidgetTargetLocation();
	((TargetLocationWidget*)m_widget)->setTrackingType("Hash");
}
void MainWindow::on_actionKCFL_triggered()
{
	createWidgetTargetLocation();
	((TargetLocationWidget*)m_widget)->setTrackingType("KCF");
}
void MainWindow::on_actionSTRUCKL_triggered()
{
	createWidgetTargetLocation();
	((TargetLocationWidget*)m_widget)->setTrackingType("STRUCK");
}
void MainWindow::on_actionSTCL_triggered()
{
	createWidgetTargetLocation();
	((TargetLocationWidget*)m_widget)->setTrackingType("STC");
}
void MainWindow::on_actionPF_triggered()
{
	createWidgetTargetTracking();
	((TargetTrackingWidget*)m_widget)->setTrackingType("PF");
}
void MainWindow::on_actionCT_triggered()
{
	createWidgetTargetTracking();
	((TargetTrackingWidget*)m_widget)->setTrackingType("CT");
}
void MainWindow::on_actionHash_triggered()
{
	createWidgetTargetTracking();
	((TargetTrackingWidget*)m_widget)->setTrackingType("Hash");
}
void MainWindow::on_actionKCF_triggered()
{
	createWidgetTargetTracking();
	((TargetTrackingWidget*)m_widget)->setTrackingType("KCF");
}
void MainWindow::on_actionSTRUCK_triggered()
{
	createWidgetTargetTracking();
	((TargetTrackingWidget*)m_widget)->setTrackingType("STRUCK");
}
void MainWindow::on_actionSTC_triggered()
{
	createWidgetTargetTracking();
	((TargetTrackingWidget*)m_widget)->setTrackingType("STC");
}
void MainWindow::createWidgetMotionDetection()
{
	if(m_widgetType!=WIDGET_MOTIONDETECTION)
	{
		clear(WIDGET_MOTIONDETECTION);
		m_widget=new MotionDetectionWidget(this);
		m_widgetType=WIDGET_MOTIONDETECTION;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		connect(ui.actionOpenVideo,SIGNAL(triggered()),
			m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::createWidgetTargetRecognition()
{
	if(m_widgetType!=WIDGET_TARGETRECOGNITION)
	{
		clear(WIDGET_TARGETRECOGNITION);
		m_widget=new TargetRecognitionWidget(this);
		m_widgetType=WIDGET_TARGETRECOGNITION;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		connect(ui.actionOpenVideo,SIGNAL(triggered()),
			m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::on_actionMD_triggered()
{
	createWidgetMotionDetection();
}
void MainWindow::on_actionTR_triggered()
{
	createWidgetTargetRecognition();
}
void MainWindow::createWidgetMultiTracking()
{
	if(m_widgetType!=WIDGET_MULTITRACKING)
	{
		clear(WIDGET_MULTITRACKING);
		m_widget=new MultiTrackingWidget(this);
		m_widgetType=WIDGET_MULTITRACKING;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		connect(ui.actionOpenVideo,SIGNAL(triggered()),
			m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::on_actionMTT_triggered()
{
	createWidgetMultiTracking();
}
void MainWindow::on_actionMTCL_triggered()
{
	createWidgetCoopLocation();
}
void MainWindow::createWidgetCoopLocation()
{
	if(m_widgetType!=WIDGET_COOPLOCATION)
	{
		clear(WIDGET_COOPLOCATION);
		m_widget=new CoopLocationWidget(this);
		m_widgetType=WIDGET_COOPLOCATION;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		//connect(ui.actionOpenVideo,SIGNAL(triggered()),
		//	m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::createWidgetMultiLocation()
{
	if(m_widgetType!=WIDGET_MULTILOCATION)
	{
		clear(WIDGET_MULTILOCATION);
		m_widget=new MultiLocationWidget(this);
		m_widgetType=WIDGET_MULTILOCATION;
		ui.centralWidget->setHidden(true);
		m_widget->setParent(this);
		m_widget->setWindowFlags(Qt::Widget);
		m_widget->resize(ui.centralWidget->size());
		m_widget->setGeometry(ui.centralWidget->geometry());
		m_widget->show();
		disconnect(ui.actionOpenVideo,0);
		connect(ui.actionOpenVideo,SIGNAL(triggered()),
			m_widget,SLOT(onOpenFile()));
	}
}
void MainWindow::on_actionMTL_triggered()
{
	createWidgetMultiLocation();
}
void MainWindow::on_actionAbout_triggered()
{
	QMessageBox informatinBox;
	QString copyRightInformation;
	QString title;
	title=tr("About");
	informatinBox.setWindowTitle(title);
	copyRightInformation=tr("About this software");
	copyRightInformation+="\n";
	copyRightInformation+=tr("UAVs tracking experimental platform");
	copyRightInformation+="\n";
	copyRightInformation+=tr("Version 1.0  ");
	informatinBox.setText(copyRightInformation);
	informatinBox.exec();
}