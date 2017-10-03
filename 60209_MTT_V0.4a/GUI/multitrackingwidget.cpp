#include "multitrackingwidget.h"
#include"VideoProcessor/QVideoProcessor.h"
#include "process/MultiTrackingProcessor.h"
#include<QTranslator>
#include<QSlider>
#include<QScrollBar>
#include<QFileDialog>
MultiTrackingWidget::MultiTrackingWidget(QWidget *parent)
	: QWidget(parent),m_video(NULL),m_MTT(NULL),m_detectorFilePath(""),m_infomation("")
{
	ui.setupUi(this);
	m_video=new QVideoProcessor();
	m_video->init(parent);
	connect(m_video,SIGNAL(display()),this,SLOT(updateFrame()));
	connect(m_video,SIGNAL(loadFile(QString)),this,SIGNAL(updateInfo(const QString&)));
	//������Ƶ�ĺ�����QVideoProcessor�У�Ϊ��ʵ�ֶ�����Ƶ�����ļ�·�����������ź�loadFile��
	//�յ��źź��ٷ���һ���źţ����ݲ���Ϊ��onOpenFile��
	connect(this,SIGNAL(updateInfo(QString)),this,SLOT(onUpdateInfo(const QString&)));
	m_MTT=new CMultiTrackingProcessor();
	init_UI();
}

MultiTrackingWidget::~MultiTrackingWidget()
{
	if(m_video)
		delete m_video;
	if(m_MTT)
		delete m_MTT;
}
void MultiTrackingWidget::init_UI()
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
void MultiTrackingWidget::onOpenFile()
{
	if(m_video)
		m_video->openFile();
}
void MultiTrackingWidget::updateFrame()
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
void MultiTrackingWidget::on_playButton_clicked()
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
void MultiTrackingWidget::on_stopButton_clicked()
{
	if(m_video)
	{
		m_video->stop();
		m_MTT->clear();
		ui.playButton->setText(tr("play"));
		ui.playButton->setDisabled(false);
		emit updateInfo("on_stopButton_clicked");
	}
}
void MultiTrackingWidget::on_trackingButton_clicked()
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
				m_MTT->init(strTemp);
				m_detectorFilePath.clear();
				m_detectorFilePath=FILES;
				if(m_video->isOpen()){
					m_video->setFrameProcessor(m_MTT);
					emit updateInfo("on_trackingButton_clicked");
				}
				else{
					emit updateInfo("on_trackingButton_clicked_Failure");
				}
			}
				}
}
void MultiTrackingWidget::on_minSizeSlider_valueChanged()
{
	m_MTT->setDetectionFilter(ui.minSizeSlider->value(),-1);
	ui.minSizeEdit->setText(QString("%1").arg(m_MTT->getMinWidth()));
	ui.minSizeSlider->setValue(m_MTT->getMinWidth());
}
void MultiTrackingWidget::on_maxSizeSlider_valueChanged()
{
	m_MTT->setDetectionFilter(-1,ui.maxSizeSlider->value());
	ui.maxSizeEdit->setText(QString("%1").arg(m_MTT->getMaxWidth()));
	ui.maxSizeSlider->setValue(m_MTT->getMaxWidth());
}
void MultiTrackingWidget::onUpdateInfo(const QString &_source)
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
		else
			m_infomation+=tr("video running");
	}
	if(_source=="on_stopButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("video stopped");
	}
	if(_source=="on_trackingButton_clicked"){
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("load detector:\t");
		m_infomation+=m_detectorFilePath;
		m_infomation+="\n";
		m_infomation+=timeString;
		m_infomation+=tr("if you've select video input ,then press start button to detect targets");
	}
	if(_source=="on_trackingButton_clicked_Failure"){
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
