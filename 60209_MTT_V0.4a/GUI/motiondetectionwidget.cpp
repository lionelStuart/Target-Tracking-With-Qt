#include "motiondetectionwidget.h"
#include"VideoProcessor/QVideoProcessor.h"
#include "process/MotionDetectionProcessor.h"
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
MotionDetectionWidget::MotionDetectionWidget(QWidget *parent)
	: QWidget(parent),m_video(NULL),m_motionDetector(NULL),m_bInitedMD(false)
{
	ui.setupUi(this);
	m_video=new QVideoProcessor();
	m_video->init(parent);
	connect(m_video,SIGNAL(display()),this,SLOT(updateFrame()));
	connect(m_video,SIGNAL(loadFile(QString)),this,SIGNAL(updateInfo(const QString&)));
	//读入视频的函数在QVideoProcessor中，为了实现读入视频后传入文件路径，定义了信号loadFile，
	//收到信号后再发射一个信号，传递参数为“onOpenFile”
	connect(this,SIGNAL(updateInfo(QString)),this,SLOT(onUpdateInfo(const QString&)));
	m_motionDetector=new CMotionDetectionProcessor();
}
MotionDetectionWidget::~MotionDetectionWidget()
{
	if(m_video)
		delete m_video;
	if(m_motionDetector)
		delete m_motionDetector;
}
void MotionDetectionWidget::init_UI()
{
	ui.videoInput->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(0,0,0));
	ui.videoInput->setPalette(palette);
	ui.videoProgressSlider->setDisabled(true);
}
void MotionDetectionWidget::onOpenFile()
{
	if(m_video){
		m_video->openFile();
		m_bInitedMD=false;
	}
}
void MotionDetectionWidget::initMotionDetector()
{
	if(m_bInitedMD)return;
	if(m_motionDetector){
		delete m_motionDetector;
	}
	m_motionDetector=new CMotionDetectionProcessor();
	m_video->setFrameProcessor(m_motionDetector);
	m_bInitedMD=true;
	emit updateInfo("initMotionDetector");
}
void MotionDetectionWidget::on_playButton_clicked()
{
	if(m_video&&m_video->isOpen())
	{
		initMotionDetector();
		if(m_video->pause())
			ui.playButton->setText(tr("play"));
		else
			ui.playButton->setText(tr("pause"));
		emit updateInfo("on_playButton_clicked");
	}
}
void MotionDetectionWidget::on_stopButton_clicked()
{
	if(m_video)
	{
		m_video->stop();
		ui.playButton->setText(tr("play"));
		ui.playButton->setDisabled(false);
		m_bInitedMD=false;
		emit updateInfo("on_stopButton_clicked");
	}
}

void MotionDetectionWidget::updateFrame()
{
	if(m_video)
	{
		m_video->showFrame(m_video->outputFrame(),ui.videoInput);
		if(m_bInitedMD)
		m_video->showFrame(m_motionDetector->getMaskImage(),ui.maskInput);
		QString updateFrameCount=
			QString("%1/%2").arg(m_video->frameID(),4).arg(m_video->frameCount(),4);
		ui.frameCount->setText(updateFrameCount);
		ui.videoProgressSlider->setMaximum(m_video->frameCount());
		ui.videoProgressSlider->setValue(m_video->frameID());
		if(!m_video->isOpen())
			ui.playButton->setDisabled(true);

	}
}
void MotionDetectionWidget::onUpdateInfo(const QString &_source)
{
	QDateTime time=QDateTime::currentDateTime();
	QString timeString=time.toString("hh:mm:ss  ");
	if(_source=="onOpenFile"){
		m_infomation.clear();
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
		else{
			m_infomation+=tr("video running");
			m_infomation+="\n";
			m_infomation+=timeString;
			m_infomation+=tr("start detection");
		}
	}
	if(_source=="on_stopButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("video stopped");
	}
	QString temp=m_infomation+"\t  <--";
	ui.infoEdit->setText(temp);
	QScrollBar *scrollbar=ui.infoEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
	ui.infoEdit->show();
}