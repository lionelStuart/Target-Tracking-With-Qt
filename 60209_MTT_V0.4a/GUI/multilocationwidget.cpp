#include "multilocationwidget.h"
#include "VideoProcessor/QVideoProcessor.h"
#include"process/multiLocationProcessor.h"
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
#include<QFileDialog>
MultiLocationWidget::MultiLocationWidget(QWidget *parent)
	: QWidget(parent),m_video(NULL),m_detectorFilePath(""),m_MTL(NULL),
	m_infomation(""),m_paramInfomation("")
{
	ui.setupUi(this);
	m_MTL=new MultiLocationProcessor();
	m_video=new QVideoProcessor();
	m_video->init(parent);
	connect(m_video,SIGNAL(display()),this,SLOT(updateFrame()));
	connect(m_video,SIGNAL(loadFile(QString)),this,SIGNAL(updateInfo(const QString&)));
	//读入视频的函数在QVideoProcessor中，为了实现读入视频后传入文件路径，定义了信号loadFile，
	//收到信号后再发射一个信号，传递参数为“onOpenFile”
	connect(m_video,SIGNAL(loadFile(QString)),this,SLOT(onFileLoaded()));
	connect(this,SIGNAL(updateInfo(QString)),this,SLOT(onUpdateInfo(const QString&)));
	init_UI();
}
void MultiLocationWidget::init_UI()
{
	ui.videoInput->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(0,0,0));
	ui.videoInput->setPalette(palette);
	ui.videoProgressSlider->setDisabled(true);
	m_paramInfomation.clear();
	m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
		.arg(m_MTL->getFov(),5)
		.arg(m_MTL->getGeoWidth(),5)
		.arg(m_MTL->getGeoHeight(),5);
		ui.paramEdit->setText(m_paramInfomation);
}
MultiLocationWidget::~MultiLocationWidget()
{
	if(m_video)
		delete m_video;
	if(m_MTL)
		delete m_MTL;
}
void MultiLocationWidget::onOpenFile()
{
	if(m_video){
		m_video->openFile();
	}
}
void MultiLocationWidget::onFileLoaded()
{
	m_MTL->initTracker("","",m_video->frameSize());
}
void MultiLocationWidget::updateFrame()
{
	if(m_video)
	{
		m_video->showFrame(m_video->outputFrame(),ui.videoInput);
		QString updateFrameCount=
			QString("%1/%2").arg(m_video->frameID(),4).arg(m_video->frameCount(),4);
		ui.frameCount->setText(updateFrameCount);
		ui.videoProgressSlider->setMaximum(m_video->frameCount());
		ui.videoProgressSlider->setValue(m_video->frameID());
		if(!m_video->isOpen())
			ui.playButton->setDisabled(true);
		updateMap();
	}
}
void MultiLocationWidget::on_playButton_clicked()
{
	if(m_MTL->isInited()){//MTL初始化
		if(m_video&&m_video->isOpen())
		{
			if(m_video->pause())
				ui.playButton->setText(tr("play"));
			else
				ui.playButton->setText(tr("pause"));
			emit updateInfo("on_playButton_clicked");
		}
	}
	else
		emit updateInfo("on_playButton_clicked_Failure");
}
void MultiLocationWidget::clearImage()
{
	ui.videoInput->clear();
	ui.mapView->clearImage();
}
void MultiLocationWidget::on_stopButton_clicked()
{
	if(m_video)
	{
		m_video->stop();
		m_MTL->clear();
		ui.playButton->setText(tr("play"));
		ui.playButton->setDisabled(false);
		init_UI();
		clearImage();
		onFileLoaded();
		emit updateInfo("on_stopButton_clicked");
	}
}
void MultiLocationWidget::on_loadDetectorButton_clicked()
{
	if(m_video){
		if(m_video->isOpen()){
			if(m_video->pause())
				ui.playButton->setText(tr("play"));
			else
				m_video->pause();
		}
		const QString FILES=QFileDialog::getOpenFileName(this,
			tr("open xml File"),QString(),tr("detector files(*.xml)"));
		std::string strTemp=FILES.toStdString();
		QTextCodec *code =QTextCodec::codecForName("gb18030");
		if(code)strTemp=code->fromUnicode(FILES).data();
		if(code)
			if(!strTemp.empty())
			{
				m_MTL->initTracker(strTemp,"");
				m_detectorFilePath.clear();
				m_detectorFilePath=FILES;
				if(m_video->isOpen()&&m_MTL->isInited()){
					m_video->setFrameProcessor(m_MTL);
				}
					emit updateInfo("on_loadDetectorButton_clicked");
			}
	}
	else
		emit updateInfo("on_loadDetectorButton_clicked_Failure");
}
void MultiLocationWidget::on_loadPoseButton_clicked()
{
	if(m_video){
		if(m_video->isOpen()){
			if(m_video->pause())
				ui.playButton->setText(tr("play"));
			else
				m_video->pause();
		}
		const QString FILES=QFileDialog::getOpenFileName(this,
			tr("open txt File"),QString(),tr("poseFile(*.txt)"));
		std::string strTemp=FILES.toStdString();
		QTextCodec *code =QTextCodec::codecForName("gb18030");
		if(code)strTemp=code->fromUnicode(FILES).data();
		if(code)
			if(!strTemp.empty())
			{
				m_MTL->initTracker("",strTemp);
				m_poseFilePath.clear();
				m_poseFilePath=FILES;
				if(m_video->isOpen()&&m_MTL->isInited()){
					m_video->setFrameProcessor(m_MTL);
				}
				emit updateInfo("on_loadPoseButton_clicked");
			}
	}
	else{
		emit updateInfo("on_loadPoseButton_clicked_Failure");
	}
}
void MultiLocationWidget::on_loadMapButton_clicked()
{
	if(m_video){
		if(m_video->isOpen()){
			if(m_video->pause())
				ui.playButton->setText(tr("play"));
			else
				m_video->pause();
		}
	}
	m_mapFilePath.clear();
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Image File"),QString(),tr("All files(*.*);;image files(*.jpeg;;*.jpg;;*.png)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty())
		{
			m_mapFilePath=FILES;
			m_MTL->initMapper(strTemp);
			updateMap();
			if(m_video->isOpen()&&m_MTL->isInited()){
				m_video->setFrameProcessor(m_MTL);		
			}
			emit updateInfo("on_loadMapButton_clicked");
		}
		else{
			emit updateInfo("on_loadMapButton_clicked_Failure");
		}
}
void MultiLocationWidget::updateMap()
{
	if(m_MTL->isInited())
		ui.mapView->setImage(m_MTL->getMap());//setImage可以判断是否正确读入地形图像
}
void MultiLocationWidget::onUpdateInfo(const QString &_source)
{
	QDateTime time=QDateTime::currentDateTime();
	QString timeString=time.toString("hh:mm:ss  ");
	if(_source=="onOpenFile"){
		m_infomation.clear();
		m_paramInfomation.clear();
		m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
			.arg(m_MTL->getFov(),5)
			.arg(m_MTL->getGeoWidth(),5)
			.arg(m_MTL->getGeoHeight(),5);
		QString temp=timeString;
		temp+=tr("open file path:\t");
		temp+=m_video->fileName();
		temp+="\n";
		m_infomation=temp;
		m_infomation+=timeString;
		m_infomation+=QString(tr("video param:\t resolution:%1*%2  length:%3")
			.arg(m_video->frameSize().width,4).arg(m_video->frameSize().height,4).arg(m_video->frameCount(),4));
	}
	if(_source=="on_playButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		if(ui.playButton->text()==tr("play"))
			m_infomation+=tr("video pause");
		else
			m_infomation+=tr("video running");
	}
	if(_source=="on_stopButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("video stopped");
		m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
			.arg(m_MTL->getFov(),5)
			.arg(m_MTL->getGeoWidth(),5)
			.arg(m_MTL->getGeoHeight(),5);
	}
	if(_source=="on_playButton_clicked_Failure"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("uninitialized param exists");
	}
	if(_source=="on_loadDetectorButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Detector File Loaded  :\t");
		m_infomation+=m_detectorFilePath;
	}
	if(_source=="on_loadDetectorButton_clicked_Failure"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Detector File Loaded  failed");
	}
	if(_source=="on_loadPoseButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("PoseFile Loaded  :\t");
		m_infomation+=m_poseFilePath;
		m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
			.arg(m_MTL->getFov(),5)
			.arg(m_MTL->getGeoWidth(),5)
			.arg(m_MTL->getGeoHeight(),5);
	}
	if(_source=="on_loadPoseButton_clicked_Failure"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Pose File Loaded  failed");
	}
	if(_source=="on_loadMapButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Map File Loaded  :\t");
		m_infomation+=m_mapFilePath;
	}
	if(_source=="on_loadMapButton_clicked_Failure"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Map File Loaded  failed");
	}
	QString temp=m_infomation+"\t  <--";
	ui.infoEdit->setText(temp);
	QScrollBar *scrollbar=ui.infoEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
	ui.infoEdit->show();
	ui.paramEdit->setText(m_paramInfomation);
	ui.paramEdit->show();
}
