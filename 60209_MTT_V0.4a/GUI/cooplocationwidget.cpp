#include "cooplocationwidget.h"
#include "process/CoopLocatoinProcessor.h"
#include "VideoProcessor/VideoProcessor.h"
#include<QFileDialog>
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
CoopLocationWidget::CoopLocationWidget(QWidget *parent)
	: QWidget(parent),m_processor(NULL),m_geoWidth(0),m_geoHeight(0),m_infomation(""),
	m_paramInfo("")
{
	m_processor=new CCoopLocatoinProcessor;
	m_processor->initTimer();
	ui.setupUi(this);
	init_UI();
	connect(this,SIGNAL(updateInfo(QString)),this,SLOT(onUpdateInfo(const QString&)));
	connect(m_processor,SIGNAL(display()),this,SLOT(updateFrame()));
}
void CoopLocationWidget::init_UI()
{
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(0,0,0));
	ui.videoInput_1->setAutoFillBackground(true);
	ui.videoInput_1->setPalette(palette);
	ui.videoInput_2->setAutoFillBackground(true);
	ui.videoInput_2->setPalette(palette);
	ui.mapView->setPalette(palette);
	ui.videoProgressSlider_1->setDisabled(true);
	ui.videoProgressSlider_2->setDisabled(true);
	ui.videoProgressSlider_1->setValue(0);
	ui.videoProgressSlider_2->setValue(0);
	ui.frameCount_1->setText("0000/9999");
	ui.frameCount_2->setText("0000/9999");
	m_paramInfo=QString(tr("Width:%2m   Height:%3m"))
		.arg(0,5)
		.arg(0,5);
	ui.paramEdit->setText(m_paramInfo);
	ui.paramEdit->show();
}
void CoopLocationWidget::clear_Image()
{
	ui.videoInput_2->clear();
	ui.videoInput_1->clear();
	ui.mapView->clearImage();
}
CoopLocationWidget::~CoopLocationWidget()
{
	if(m_processor)
		delete m_processor;
}
void CoopLocationWidget::updateFrame()
{
	if(m_processor)
	{
		VideoProcessor* ptr1=m_processor->getTask_1()->getVideo();
		VideoProcessor* ptr2=m_processor->getTask_2()->getVideo();
		showFrame(m_processor->getOutput_1(),ui.videoInput_1);
		showFrame(m_processor->getOutput_2(),ui.videoInput_2);
		QString updateFrameCount1=
			QString("%1/%2").arg(ptr1->frameID(),4).arg(ptr1->frameCount(),4);
		QString updateFrameCount2=
			QString("%1/%2").arg(ptr2->frameID(),4).arg(ptr2->frameCount(),4);
		ui.frameCount_1->setText(updateFrameCount1);
		ui.frameCount_2->setText(updateFrameCount2);
		ui.videoProgressSlider_1->setMaximum(ptr1->frameCount());
		ui.videoProgressSlider_1->setValue(ptr1->frameID());
		ui.videoProgressSlider_2->setMaximum(ptr2->frameCount());
		ui.videoProgressSlider_2->setValue(ptr2->frameID());
		ui.mapView->setImage(m_processor->getMapOut());
		if(!ptr1->isOpen()||!ptr2->isOpen())
			ui.runButton->setDisabled(true);
	}
}
void CoopLocationWidget::on_loadVideoButton_1_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Video File"),QString(),tr("All files(*.*);;video files(*.avi;*.mpg)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
			m_processor->getTask_1()->initVideo(strTemp);
			showFrame(m_processor->getTask_1()->getVideo()->currentFrame(),ui.videoInput_1);
			emit updateInfo("on_loadVideoButton_1_clicked");
		}
}
void CoopLocationWidget::on_loadVideoButton_2_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Video File"),QString(),tr("All files(*.*);;video files(*.avi;*.mpg)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
			m_processor->getTask_2()->initVideo(strTemp);
			showFrame(m_processor->getTask_2()->getVideo()->currentFrame(),ui.videoInput_2);
			emit updateInfo("on_loadVideoButton_2_clicked");
		}
}
void CoopLocationWidget::on_loadDetectorButton_1_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Xml File"),QString(),tr("detector files(*.xml)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
			m_processor->getTask_1()->initDetector(strTemp);
			emit updateInfo("on_loadDetectorButton_1_clicked");
		}
}
void CoopLocationWidget::on_loadDetectorButton_2_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Xml File"),QString(),tr("detector files(*.xml)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
			m_processor->getTask_2()->initDetector(strTemp);
			emit updateInfo("on_loadDetectorButton_2_clicked");
		}
}
void CoopLocationWidget::on_loadPoseButton_1_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open text File"),QString(),tr("text files(*.txt)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
			m_processor->getTask_1()->initTracker(strTemp);
			m_geoWidth=m_processor->setWidthFromFile(strTemp);
			m_geoHeight=m_processor->setHeightFromFile(strTemp);
			m_processor->initMapper(m_mapFilePath,m_geoWidth,m_geoHeight);
			emit updateInfo("on_loadPoseButton_1_clicked");
		}
}
void CoopLocationWidget::on_loadPoseButton_2_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open text File"),QString(),tr("text files(*.txt)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
				m_processor->getTask_2()->initTracker(strTemp);
				m_geoWidth=m_processor->setWidthFromFile(strTemp);
				m_geoHeight=m_processor->setHeightFromFile(strTemp);
				m_processor->initMapper(m_mapFilePath,m_geoWidth,m_geoHeight);
			emit updateInfo("on_loadPoseButton_2_clicked");
		}
}
void CoopLocationWidget::on_runButton_clicked()
{
	if(m_processor)
		if(m_processor->pause()){
			ui.runButton->setText(tr("pause"));
			emit updateInfo("on_runButton_clicked_run");
		}
		else {
			ui.runButton->setText(tr("run"));
			emit updateInfo("on_runButton_clicked_pause");
		}
}
void CoopLocationWidget::on_stopButton_clicked()
{
	if(m_processor){
		m_processor->clear();
		ui.runButton->setText(tr("run"));
		init_UI();
		clear_Image();
		emit updateInfo("on_stopButton_clicked");
	}
}
void CoopLocationWidget::on_loadMapButton_clicked()
{
	if(m_processor){
		if(m_processor->pause()){
			m_processor->pause();
		}
		ui.runButton->setText(tr("run"));
		emit updateInfo("on_runButton_clicked_pause");
	}
	m_mapFilePath.clear();
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Image File"),QString(),tr("All files(*.*);;image files(*.jpeg;;*.jpg;;*.png)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty()&&m_processor)
		{
			cv::Mat tempMap=cv::imread(strTemp);
			ui.mapView->setImage(tempMap);
			m_mapFilePath=strTemp;
			//m_geoHeight=ui.geoXEdit->text().toDouble();
			//m_geoWidth=ui.geoYEdit->text().toDouble();
			if(m_geoHeight>0&&m_geoWidth>0)
				m_processor->initMapper(m_mapFilePath,m_geoWidth,m_geoHeight);
			emit updateInfo("on_loadMapButton_clicked");
		}
}
//void CoopLocationWidget::on_geoSetButton_clicked()
//{
//	//if(ui.geoXEdit->text().isEmpty()||ui.geoYEdit->text().isEmpty())return;
//	//m_geoWidth=ui.geoXEdit->text().toDouble();
//	//m_geoHeight=ui.geoYEdit->text().toDouble();
//	//if(!m_mapFilePath.empty())
//	//	m_processor->initMapper(m_mapFilePath,m_geoWidth,m_geoHeight);
//}
void CoopLocationWidget::onUpdateInfo(const QString &_source)
{
	QDateTime time=QDateTime::currentDateTime();
	QString timeString=time.toString("hh:mm:ss  ");
	if(_source=="on_loadVideoButton_1_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Channel 1 video loaded\t");
		m_paramInfo=QString(tr("Width:%2m   Height:%3m"))
			.arg(m_geoWidth,5)
			.arg(m_geoHeight,5);
		VideoProcessor* ptr1=m_processor->getTask_1()->getVideo();
		QString updateFrameCount1=
			QString("%1/%2").arg(ptr1->frameID(),4).arg(ptr1->frameCount(),4);
		ui.frameCount_1->setText(updateFrameCount1);
	}
	if(_source=="on_loadVideoButton_2_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Channel 2 video loaded\t");
		m_paramInfo=QString(tr("Width:%2m   Height:%3m"))
			.arg(m_geoWidth,5)
			.arg(m_geoHeight,5);
		VideoProcessor* ptr2=m_processor->getTask_2()->getVideo();
		QString updateFrameCount2=
			QString("%1/%2").arg(ptr2->frameID(),4).arg(ptr2->frameCount(),4);
		ui.frameCount_2->setText(updateFrameCount2);
	}
	if(_source=="on_loadDetectorButton_1_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Channel 1 detector loaded\t");
	}
	if(_source=="on_loadDetectorButton_2_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Channel 2 detector loaded\t");
	}
	if(_source=="on_runButton_clicked_pause"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("pause");
	}
	if(_source=="on_runButton_clicked_run"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("running");
	}
	if(_source=="on_stopButton_clicked"){
		m_infomation.clear();
		m_infomation+=timeString;
		m_infomation+=tr("information clear");
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("stopped");
	}
	if(_source=="on_loadMapButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("map loaded");
	}
	if(_source=="on_loadPoseButton_1_clicked"){
		m_paramInfo=QString(tr("Width:%1m   Height:%2m"))
			.arg(m_geoWidth,5)
			.arg(m_geoHeight,5);
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Channel 1 poseFile loaded\t");
	}
	if(_source=="on_loadPoseButton_2_clicked"){
		m_paramInfo=QString(tr("Width:%1m   Height:%2m"))
			.arg(m_geoWidth,5)
			.arg(m_geoHeight,5);
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Channel 2 poseFile loaded\t");
	}
	QString temp=m_infomation+"\t  <--";
	ui.infoEdit->setText(temp);
	QScrollBar *scrollbar=ui.infoEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
	ui.infoEdit->show();
	ui.paramEdit->setText(m_paramInfo);
	ui.paramEdit->show();
}