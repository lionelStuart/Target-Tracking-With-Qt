#if _MSC_VER>=1600
#pragma execution_character_set("utf-8")
#endif
#include"CParamWidget.h"
#include"CDrawRectWnd.h"
#include "targettrackingwidget.h"
#include"process/trackProcessor.h"
#include"VideoProcessor/QVideoProcessor.h"
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
TargetTrackingWidget::TargetTrackingWidget(QWidget *parent)
	: QWidget(parent),m_video(NULL),m_trackMethod(NULL),
	m_trackType(""),m_infomation(""),m_paramWidget(NULL)
{
	ui.setupUi(this);
	init_UI();
	m_video=new QVideoProcessor();
	m_video->init(parent);
	m_trackMethod=new trackProcessor();
	connect(m_video,SIGNAL(display()),this,SLOT(updateFrame()));
	connect(m_video,SIGNAL(loadFile(QString)),this,SIGNAL(updateInfo(const QString&)));
	//读入视频的函数在QVideoProcessor中，为了实现读入视频后传入文件路径，定义了信号loadFile，
	//收到信号后再发射一个信号，传递参数为“onOpenFile”
	connect(this,SIGNAL(updateInfo(QString)),this,SLOT(onUpdateInfo(const QString&)));
	connect(this,SIGNAL(receiveTrackingType(QString)),this,SLOT(initParamWidget(const QString&)));
}
TargetTrackingWidget::~TargetTrackingWidget()
{
	if(m_video)
		delete m_video;
	if(m_trackMethod)
		delete m_trackMethod;
	if(m_paramWidget)
		delete m_paramWidget;
}
void TargetTrackingWidget::setTrackingType(const std::string &_type)
{//在mainWindow创建完WidgetTargetTracking后执行该函数确定跟踪选择类型
	m_trackType.clear();
	m_trackType=_type;
	emit updateInfo("setTrackingType");
	emit receiveTrackingType(QString::fromStdString(m_trackType));
}
void TargetTrackingWidget::initParamWidget(const QString&_source)
{//setTrackingType后发出receiveTrakcingType信号并执行本函数
	//初始化ParmWidget
	if(_source=="PF"){
		m_paramWidget->disableHash(true);
		m_paramWidget->disableKCF(true);
		m_paramWidget->disablePF(false);
		m_paramWidget->disableStruck(true);
		m_paramWidget->setDisable(false);
	}
	if(_source=="CT"){
		m_paramWidget->setDisable(true);
	}
	if(_source=="Hash"){
		m_paramWidget->disableHash(false);
		m_paramWidget->disableKCF(true);
		m_paramWidget->disablePF(true);
		m_paramWidget->disableStruck(true);
		m_paramWidget->setDisable(false);
	}
	if(_source=="KCF"){
		m_paramWidget->disableHash(true);
		m_paramWidget->disableKCF(false);
		m_paramWidget->disablePF(true);
		m_paramWidget->disableStruck(true);
		m_paramWidget->setDisable(false);
	}
	if(_source=="STRUCK"){
		m_paramWidget->disableHash(true);
		m_paramWidget->disableKCF(true);
		m_paramWidget->disablePF(true);
		m_paramWidget->disableStruck(false);
		m_paramWidget->setDisable(false);
	}
	if(_source=="STC"){
		m_paramWidget->setDisable(true);
	}
}
std::string& TargetTrackingWidget::getTrackingType()
{
	return m_trackType;
}
void TargetTrackingWidget::init_UI()
{//创建Widget时执行本函数初始化UI
	ui.videoInput->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(0,0,0));
	ui.videoInput->setPalette(palette);
	ui.videoProgressSlider->setDisabled(true);
	m_paramWidget=new CParamWidget(this);
	m_paramWidget->setParent(this);
	m_paramWidget->setWindowFlags(Qt::Widget);
	m_paramWidget->setGeometry(ui.paramBox->geometry());
	m_paramWidget->show();
}
void TargetTrackingWidget::onOpenFile()
{
	if(m_video)
	m_video->openFile();
}
void TargetTrackingWidget::on_playButton_clicked()
{
	if(m_video&&m_video->isOpen())
	{
		if(m_video->pause())
			ui.playButton->setText(tr("play"));
		else
		ui.playButton->setText(tr("pause"));
		emit updateInfo("on_playButton_clicked");
	}
}
void TargetTrackingWidget::on_stopButton_clicked()
{
	if(m_video)
	{
		m_video->stop();
		ui.playButton->setText(tr("play"));
		ui.playButton->setDisabled(false);
		emit updateInfo("on_stopButton_clicked");
	}
}
void TargetTrackingWidget::on_drawButton_clicked()
{//画框响应函数
	if(m_video)
	{
		if(m_video->isOpen())
		{
			if(m_video->pause())
			ui.playButton->setText(tr("play"));
			else
				m_video->pause();
			const QSize drawSize=QSize(m_video->frameSize().width,m_video->frameSize().height);
			CDrawRectWnd*  drawBox=new CDrawRectWnd(this);
			drawBox->init_drawing(m_video->currentFrame(),&m_boundingBox);
			connect(drawBox,SIGNAL(rectReady()),this,SLOT(receiveRects()));
			drawBox->show();
			emit updateInfo("on_drawButton_clicked");
		}
	}
}
void TargetTrackingWidget::initTrackerWithParam()
{//附加参数设定，在receiveRect中在m_trakMethod——》init前调用获取参数值
	if(m_trackType=="KCF"){
		KCFParam param;
		param.bFixed_window=m_paramWidget->getFixWndChecked();
		param.bHog=m_paramWidget->getHogChecked();
		param.bMultiscale=m_paramWidget->getMultiScaleChecked();
		m_trackMethod->getTracker()->initKCF(param);
	}
	if(m_trackType=="STRUCK"){
		StruckParam param;
		param.m_searchRadius=m_paramWidget->getStruckSearchRadius();
		m_trackMethod->getTracker()->initStruck(param);
	}
	if(m_trackType=="PF"){
		m_trackMethod->getTracker()->initPF(m_paramWidget->getParticleNum(),
			m_paramWidget->getLBPChecked());
	}
	if(m_trackType=="Hash"){
		m_trackMethod->getTracker()->initHash(m_paramWidget->getPHashChecked());
	}
}
void TargetTrackingWidget::receiveRects()
{//与on_draw_BUtton_clicked中创建的drawBox对象的rectReady信号绑定，
	//获取初始跟踪位置
	if(m_boundingBox.width()!=0&&m_boundingBox.height()!=0)
	{
		cv::Rect temp=cv::Rect(m_boundingBox.topLeft().x(),m_boundingBox.topLeft().y(),
			m_boundingBox.width(),m_boundingBox.height());
		initTrackerWithParam();
		m_trackMethod->init(m_trackType,temp);
		m_video->setFrameProcessor(m_trackMethod);
		m_video->pause();
		ui.playButton->setText(tr("pause"));
		emit updateInfo("receiveRects");
	}
}
void TargetTrackingWidget::updateFrame()
{//与run原型信号绑定，每帧执行更新
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
	}
}
void TargetTrackingWidget::onUpdateInfo(const QString &_source)
{//更新infoEdit中的信息,m_paramWidget:: showMethod
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
		 m_infomation+="\n";
		 m_infomation+=timeString;
		 m_infomation+=tr("select tracking method:\t");
		 m_infomation+=QString::fromStdString(getTrackingType());
	}
	if(_source=="setTrackingType"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("select tracking method:\t");
		m_infomation+=QString::fromStdString(getTrackingType());
		m_paramWidget->showMethod(QString::fromStdString(m_trackType));
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
	}
	if(_source=="on_drawButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("pause to draw rect,press ok to continue");
	}
	if(_source=="receiveRects"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("get init target:");
		m_infomation+=QString("X%1 Y%2 W%3 H%4").arg(m_boundingBox.x(),4).arg(m_boundingBox.y(),4).
			arg(m_boundingBox.width(),4).arg(m_boundingBox.height(),4);
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("start tracking...");
	}
	QString temp=m_infomation+"\t  <--";
	ui.infoEdit->setText(temp);
	QScrollBar *scrollbar=ui.infoEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
	ui.infoEdit->show();
}