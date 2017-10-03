#include "targetrecognitionwidget.h"
#include "VideoProcessor/QVideoProcessor.h"
#include "process/TargetRecongnitionProcessor.h"
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
#include<QFileDialog>
TargetRecognitionWidget::TargetRecognitionWidget(QWidget *parent)
	: QWidget(parent),m_video(NULL),m_TR(NULL),m_detectorFilePath(""),m_infomation("")
{
	ui.setupUi(this);
	m_video=new QVideoProcessor();
	m_video->init(parent);
	connect(m_video,SIGNAL(display()),this,SLOT(updateFrame()));
	connect(m_video,SIGNAL(loadFile(QString)),this,SIGNAL(updateInfo(const QString&)));
	//读入视频的函数在QVideoProcessor中，为了实现读入视频后传入文件路径，定义了信号loadFile，
	//收到信号后再发射一个信号，传递参数为“onOpenFile”
	connect(this,SIGNAL(updateInfo(QString)),this,SLOT(onUpdateInfo(const QString&)));
	m_TR=new CTargetRecongnitionProcessor();
	init_UI();
}

TargetRecognitionWidget::~TargetRecognitionWidget()
{
	if(m_video)
		delete m_video;
	if(m_TR)
		delete m_TR;
}
void TargetRecognitionWidget::init_UI()
{
	ui.videoInput->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(0,0,0));
	ui.videoInput->setPalette(palette);
	ui.videoProgressSlider->setDisabled(true);
	ui.minSizeEdit->setText("0");
	ui.minSizeEdit->setDisabled(true);
	ui.maxSizeEdit->setText("500");
	ui.maxSizeEdit->setDisabled(true);
	ui.minSizeSlider->setMinimum(0);
	ui.minSizeSlider->setMaximum(200);
	ui.minSizeSlider->setValue(0);
	ui.maxSizeSlider->setMinimum(0);
	ui.maxSizeSlider->setMaximum(500);
	ui.maxSizeSlider->setValue(500);
}
void TargetRecognitionWidget::onOpenFile()
{
	if(m_video)
		m_video->openFile();
}
void TargetRecognitionWidget::updateFrame()
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
	}
}
void TargetRecognitionWidget::on_playButton_clicked()
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
void TargetRecognitionWidget::on_stopButton_clicked()
{
	if(m_video)
	{
		m_video->stop();
		ui.playButton->setText(tr("play"));
		ui.playButton->setDisabled(false);
		emit updateInfo("on_stopButton_clicked");
	}
}
void TargetRecognitionWidget::on_detectButton_clicked()
{
	if(m_video){
		if(m_video->isOpen()){
			if(m_video->pause())
			ui.playButton->setText(tr("play"));
			else
			m_video->pause();
		}
		emit updateInfo("on_playButton_clicked");	
		const QString FILES=QFileDialog::getOpenFileName(this,
			tr("open xml File"),QString(),tr("detector files(*.xml)"));
		std::string strTemp=FILES.toStdString();
		QTextCodec *code =QTextCodec::codecForName("gb18030");
		if(code)strTemp=code->fromUnicode(FILES).data();
		if(code)
			if(!strTemp.empty())
			{
				m_TR->init(strTemp);
				m_detectorFilePath.clear();
				m_detectorFilePath=FILES;
				if(m_video->isOpen()){
					m_video->setFrameProcessor(m_TR);
					emit updateInfo("on_detectButton_clicked");
				}
				else{
					emit updateInfo("on_detectButton_clicked_Failure");
				}

			}
	}
}
void TargetRecognitionWidget::on_minSizeSlider_valueChanged()
{
	m_TR->setFilterSize(ui.minSizeSlider->value(),-1);
	ui.minSizeEdit->setText(QString("%1").arg(m_TR->getMinWidth()));
	ui.minSizeSlider->setValue(m_TR->getMinWidth());
}
void TargetRecognitionWidget::on_maxSizeSlider_valueChanged()
{
	m_TR->setFilterSize(-1,ui.maxSizeSlider->value());
	ui.maxSizeEdit->setText(QString("%1").arg(m_TR->getMaxWidth()));
	ui.maxSizeSlider->setValue(m_TR->getMaxWidth());
}
void TargetRecognitionWidget::onUpdateInfo(const QString &_source)
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
		if(ui.playButton->text()==tr("play")){
			m_infomation+=tr("video pause");
		}
		else
			m_infomation+=tr("video running");
	}
	if(_source=="on_stopButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("video stopped");
	}
	if(_source=="on_detectButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("load detector:\t");
		m_infomation+=m_detectorFilePath;
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("if you've select video input ,then press start button to detect targets");
	}
	if(_source=="on_detectButton_clicked_Failure"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("load detector failure");
	}
	QString temp=m_infomation+"\t  <--";
	ui.infoEdit->setText(temp);
	QScrollBar *scrollbar=ui.infoEdit->verticalScrollBar();
	scrollbar->setSliderPosition(scrollbar->maximum());
	ui.infoEdit->show();
}
