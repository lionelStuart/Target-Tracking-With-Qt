#include "targetlocationwidget.h"
#include "CDrawRectWnd.h"
#include"process/MonoLocationProcessor.h"
#include "VideoProcessor/QVideoProcessor.h"
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
#include<QFileDialog>
TargetLocationWidget::TargetLocationWidget(QWidget *parent)
	: QWidget(parent),m_video(NULL),m_trackType(""),m_monoLocator(NULL),
	m_infomation(""),m_paramInfomation("")
{
	ui.setupUi(this);
	m_monoLocator=new MonoLocationProcessor();
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
TargetLocationWidget::~TargetLocationWidget()
{
	if(m_video)
		delete m_video;
	if(m_monoLocator)
		delete m_monoLocator;
}
void TargetLocationWidget::init_UI()
{
	ui.videoInput->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(0,0,0));
	ui.videoInput->setPalette(palette);
	ui.videoProgressSlider->setDisabled(true);
}
void TargetLocationWidget::onOpenFile()
{
	if(m_video){
		m_video->openFile();
	}
}
void TargetLocationWidget::onFileLoaded()
{
	m_monoLocator->initVO("",0,m_video->frameSize());//加载完视频后用获取视频尺寸初始化VO中相机参数
}
void TargetLocationWidget::setTrackingType(const std::string &_type)
{//在mainWindow创建完WidgetTargetTracking后执行该函数确定跟踪选择类型
	m_trackType.clear();
	m_trackType=_type;
	emit updateInfo("setTrackingType");
	emit receiveTrackingType(QString::fromStdString(m_trackType));
}
std::string& TargetLocationWidget::getTrackingType()
{
	return m_trackType;
}
void TargetLocationWidget::on_playButton_clicked()
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
void TargetLocationWidget::on_stopButton_clicked()
{
	if(m_video)
	{
		m_video->stop();
		ui.playButton->setText(tr("play"));
		ui.playButton->setDisabled(false);
		emit updateInfo("on_stopButton_clicked");
	}
}
void TargetLocationWidget::on_drawButton_clicked()
{
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
void TargetLocationWidget::on_loadPoseButton_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open text File"),QString(),tr("txt files(*.txt)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty())
		{
			m_monoLocator->initVO(strTemp);
			m_monoLocator->initVO("",m_monoLocator->setFovFromFile());
			m_monoLocator->initMapper("",m_monoLocator->setWidthFromFile(),m_monoLocator->setHeightFromFile());
			updateMap();
			emit updateInfo("on_loadPoseButton_clicked");
		}
}
//void TargetLocationWidget::on_loadTargetButton_clicked()
//{//加载目标位置参数文件
//	const QString FILES=QFileDialog::getOpenFileName(this,
//		tr("open text File"),QString(),tr("txt files(*.txt)"));
//	std::string strTemp=FILES.toStdString();
//	QTextCodec *code =QTextCodec::codecForName("gb18030");
//	if(code)strTemp=code->fromUnicode(FILES).data();
//	if(code)
//		if(!strTemp.empty())
//		{
//			m_monoLocator->initVO("",0.0,cv::Size(0,0),strTemp);
//		}
//}
void TargetLocationWidget::on_loadMapButton_clicked()
{
	const QString FILES=QFileDialog::getOpenFileName(this,
		tr("open Image File"),QString(),tr("image files(*.jpg;*.png;*.bmp)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty())
		{
			m_monoLocator->initMapper(strTemp);
			updateMap();
			emit updateInfo("on_loadMapButton_clicked");
		}
}
//void TargetLocationWidget::on_geoSetButton_clicked()
//{
//	if(ui.geoXEdit->text().isEmpty()||ui.geoYEdit->text().isEmpty())return;
//	double x=ui.geoXEdit->text().toDouble();
//	double y=ui.geoYEdit->text().toDouble();
//	m_monoLocator->initMapper("",x,y);
//	updateMap();
//}
void TargetLocationWidget::receiveRects()
{//与on_draw_BUtton_clicked中创建的drawBox对象的rectReady信号绑定，
	//获取初始跟踪位置
	if(m_boundingBox.width()!=0&&m_boundingBox.height()!=0)
	{
		cv::Rect temp=cv::Rect(m_boundingBox.topLeft().x(),m_boundingBox.topLeft().y(),
			m_boundingBox.width(),m_boundingBox.height());
		m_monoLocator->initTracker(m_trackType,temp);
		m_video->setFrameProcessor(m_monoLocator);
		m_video->pause();
		ui.playButton->setText(tr("pause"));
		emit updateInfo("receiveRects");
	}

}
void TargetLocationWidget::updateMap()
{
	ui.mapView->setImage(m_monoLocator->getMap(true,false));//setImage可以判断是否正确读入地形图像
}//重绘地图
void TargetLocationWidget::updateFrame()
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
}//每帧更新
void TargetLocationWidget::onUpdateInfo(const QString &_source)
{
	QDateTime time=QDateTime::currentDateTime();
	QString timeString=time.toString("hh:mm:ss  ");
	if(_source=="onOpenFile"){
		m_infomation.clear();
		m_paramInfomation.clear();
		m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
			.arg(m_monoLocator->setFovFromFile(),5)
			.arg(m_monoLocator->setWidthFromFile(),5)
			.arg(m_monoLocator->setHeightFromFile(),5);
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
		m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
			.arg(m_monoLocator->setFovFromFile(),5)
			.arg(m_monoLocator->setWidthFromFile(),5)
			.arg(m_monoLocator->setHeightFromFile(),5);
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
	if(_source=="on_loadPoseButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("PoseFile Loaded  !");
		m_paramInfomation=QString(tr("FOV:%1degrees   Width:%2m   Height:%3m"))
			.arg(m_monoLocator->setFovFromFile(),5)
			.arg(m_monoLocator->setWidthFromFile(),5)
			.arg(m_monoLocator->setHeightFromFile(),5);
	}
	if(_source=="on_loadMapButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("Map Loaded ! Why is a raven like a writing desk? ");
	}
	QString temp=m_infomation+"\t  <--";
	ui.infoEdit->setText(temp);
	QScrollBar *scrollbar=ui.infoEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
	ui.infoEdit->show();
	ui.paramEdit->setText(m_paramInfomation);
	ui.paramEdit->show();
}
