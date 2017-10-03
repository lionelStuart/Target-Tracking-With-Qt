/*****************************************************************/
/***VideoProcessor 类**************************************/
/***通用类通过继承获取方法*************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef VideoProcessor_H
#define VideoProcessor_H
#include<opencv2\opencv.hpp>
class VideoProcessor;
class FrameProcessor
{
public:
	virtual void process(const cv::Mat &_input,cv::Mat &_output)=0;
	void setParents(VideoProcessor* _parents);//此函数只允许已定义的VideoProcessor类调用
	VideoProcessor* getParents();
	FrameProcessor():m_parents(NULL){}
	~FrameProcessor(){}
	private:
	VideoProcessor * m_parents;
};
inline void FrameProcessor::setParents(VideoProcessor* _parents){m_parents=_parents;}
inline VideoProcessor* FrameProcessor::getParents(){return m_parents;}
class VideoProcessor
{
public:
	bool load(const std::string &_videoFilePath);
	bool process(cv::Mat &_outputFrame=cv::Mat());
	int frameID();
	int frameCount();
	cv::Size frameSize();
	std::string& fileName();
	VideoProcessor(void);
	~VideoProcessor(void);
	const cv::Mat& currentFrame();
	const cv::Mat& outputFrame();
	void setFrameProcessor(FrameProcessor* _processor);
	bool isOpen();
protected:
	void clear();
private:
	int m_frameID;
	int m_frameCount;
	cv::Size m_frameSize;
	cv::Mat m_currentFrame;
	cv::Mat m_outputFrame;
	cv::VideoCapture m_capture;
	FrameProcessor *m_processor;
	std::string m_fileName;
};
inline bool VideoProcessor::isOpen(){return m_capture.isOpened();}
inline int VideoProcessor::frameID(){return m_frameID;}
inline int VideoProcessor::frameCount(){return m_frameCount-1;}
inline cv::Size VideoProcessor::frameSize(){return m_frameSize;}
inline const cv::Mat & VideoProcessor::currentFrame(){return m_currentFrame;}
inline const cv::Mat &VideoProcessor::outputFrame(){return m_outputFrame;}
inline std::string& VideoProcessor::fileName(){return m_fileName;}
inline void VideoProcessor::setFrameProcessor(FrameProcessor* _processor){
	if(_processor){
		m_processor=_processor;
		_processor->setParents(this);
	}
}
#endif //VideoProcessor_H

