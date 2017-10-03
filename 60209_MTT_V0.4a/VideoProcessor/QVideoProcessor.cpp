#include "QVideoProcessor.h"
#include<QFileDialog>
QVideoProcessor::QVideoProcessor(void):
    m_parents(NULL),m_timer(NULL),
	m_bInit(false),m_bOpen(false),m_bPause(true),m_bStop(false)
{
}
QVideoProcessor::~QVideoProcessor(void)
{
	clear();
	if(m_bInit)delete m_timer;
}
void QVideoProcessor::clear()
{
	VideoProcessor::clear();
	m_bInit=true;
	m_bOpen=false;
	m_bPause=true;
	m_bStop=false;
}
void QVideoProcessor::init(QWidget * _parents)
{
	m_parents=_parents;
	m_timer=new QTimer();
	connect(m_timer,SIGNAL(timeout()),this,SLOT(run()));
	m_timer->start(20);
	m_bInit=true;
}
void QVideoProcessor::run()
{
	if(!m_bInit)return;
	if(m_bOpen)	{
		m_bOpen=false;
		onOpenFile();
	}
	if(VideoProcessor::isOpen()){
		if(m_bStop)
			onStop();
		else{
			if(!m_bPause)
			{
					VideoProcessor::process();
			}
		}
		emit display();
	}
	else if(m_bStop)
		onStop();
	//else{
	//	m_bStop=true;
	//	onStop();
	//}
}
void QVideoProcessor::onOpenFile()
{
	const QString FILES=QFileDialog::getOpenFileName(m_parents,
		tr("open Video File"),QString(),tr("All files(*.*);;video files(*.avi;*.mpg)"));
	std::string strTemp=FILES.toStdString();
	QTextCodec *code =QTextCodec::codecForName("gb18030");
	if(code)strTemp=code->fromUnicode(FILES).data();
	if(code)
		if(!strTemp.empty())
		{
			m_Qfiles.clear();
			m_Qfiles=FILES;
			m_files.clear();
			m_files=strTemp;
			VideoProcessor::load(strTemp);
			emit loadFile("onOpenFile");
		}
}
void QVideoProcessor::showFrame(const cv::Mat & _image,QLabel *_window)
{
	m_mat2QImage.importImage(_image);
	_window->setPixmap(QPixmap::fromImage(*m_mat2QImage.exportImage(_window->size())));
	_window->show();
}
void QVideoProcessor::onStop()
{
	clear();
	VideoProcessor::load(m_files);
}
void QVideoProcessor::openFile()
{
	m_bOpen=true;
	m_bPause=true;
}
void QVideoProcessor::closeFile()
{
	clear();
	m_files.clear();
	m_bOpen=false;
}
bool QVideoProcessor::pause()
{
	m_bStop=false;
	m_bPause=!m_bPause;
	return m_bPause;
}
void QVideoProcessor::stop()
{
	m_bStop=true;
	m_bPause=true;
}
QString QVideoProcessor::fileName()
{
	return m_Qfiles;
}
