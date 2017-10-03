#include "VideoProcessor.h"


VideoProcessor::VideoProcessor(void)
	:m_processor(NULL),m_frameID(-1),m_frameCount(0),
	m_frameSize(cv::Size()),m_fileName("")
{
}
VideoProcessor::~VideoProcessor(void)
{
	clear();
}
void VideoProcessor::clear()
{
	m_processor=NULL;
	m_frameID=-1;
	m_frameCount=0;
	m_frameSize=cv::Size();
	m_fileName.clear();
	m_capture.release();
}
bool VideoProcessor::load(const std::string &_videoFilePath)
{
	clear();
	m_capture.open(_videoFilePath);
	if(!m_capture.isOpened())return false;
	m_capture.read(m_currentFrame);//load后m_currentFrame即有数值，提供封面及保护
	m_outputFrame=m_currentFrame.clone();
	m_capture.open(_videoFilePath);
	m_frameSize=cv::Size(static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_WIDTH)),
		static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_HEIGHT)));
	m_frameCount=static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_COUNT));
	m_fileName=_videoFilePath;
	return true;
}
bool VideoProcessor::process(cv::Mat &_outputFrame)
{
	if(m_frameID>=m_frameCount)return false;
	if(frameCount()-1>frameID()&&m_capture.read(m_currentFrame))
	{
			m_outputFrame=m_currentFrame.clone();
			if(m_processor)
				m_processor->process(m_currentFrame,m_outputFrame);
			_outputFrame=m_outputFrame;
		m_frameID++;
		return true;
	}
	else if(m_capture.isOpened())
	m_capture.release();
	m_frameID++;
	return false;
}

