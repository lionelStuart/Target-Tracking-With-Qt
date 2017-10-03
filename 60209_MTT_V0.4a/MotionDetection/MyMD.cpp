#include "MyMD.h"

MyMD::MyMD(void):
m_seqLength(DefaultSeqNum),m_bSeqInited(false),m_seqInitCount(0),
m_bSetFramePreProcessor(false),m_seqCounter(DefaultSeqNum-1),
m_morpholopyOpenScale(5),m_morpholopyCloseScale(10)
{
	m_prevFrame=cv::Mat(0,0,CV_8U);
	setFramePreProcess();//很多预设值..
	setFrameDeference();
}
MyMD::~MyMD(void)
{
}
void MyMD::process(const cv::Mat &_inputFrame,std::vector<cv::Rect> &outputRects,cv::Mat &_outputMask)
{
	if(!_inputFrame.cols||!_inputFrame.rows)return;//入口检查
	outputRects.clear();
	_outputMask=_inputFrame;
	if(!m_bSetFramePreProcessor){//初始化帧预处理器
		m_prevFrame=_inputFrame;
		setFramePreProcess();
		m_bSetFramePreProcessor=true;
		//在重新初始化后还需要执行的操作
		m_mask=cv::Mat::zeros(cv::Size(m_prevFrame.cols,m_prevFrame.rows),CV_32FC1);//CV_32FC1
	}
	if(!m_bSeqInited){
		preCalculation(_inputFrame);//初始化桢差序列
	}
	else{//执行循环
		loopCalculation(_inputFrame,outputRects,_outputMask);
	}
}
void MyMD::setFrameDeference(int length/* =DefaultSeqNum */)
{
	if(length<2)return;
	m_seqCounter=m_seqLength-1;
	m_seqLength=length;
	m_seqInitCount=0;
	m_sequences.clear();
	m_bSeqInited=false;
	m_bSetFramePreProcessor=false;
}
void MyMD::preCalculation(const cv::Mat &_inputFrame)
{
	cv::Mat temp;
	if(m_seqInitCount<m_seqLength){
		temp=_inputFrame.clone();
		m_framePreProcess.process(temp,temp);
		m_sequences.push_back(temp);
		m_seqInitCount++;
	}
	else
		m_bSeqInited=true;
}
void MyMD::loopCalculation(const cv::Mat &_inputFrame,std::vector<cv::Rect> &outputRects,cv::Mat &_outputMask)
{
	cv::Mat frame=_inputFrame.clone();
	m_timer.start();
	double timestamp = (double)clock()/CLOCKS_PER_SEC;
	m_framePreProcess.process(frame,m_sequences[m_seqCounter%m_seqLength]);//New seq
	//cv::Mat show;
	//framePre.process(frame,show);
	//matches.getHomography(prevFrame,frame,H);
	m_matches.setForegroundMask(m_mask,true);
	m_matches.getHomography(m_sequences[(m_seqCounter+1)%m_seqLength],
		m_sequences[m_seqCounter%m_seqLength],m_H);
	//图像校准
	cv::Mat warp;
	warpPerspective(m_sequences[(m_seqCounter+1)%m_seqLength],warp,m_H,cv::Size(frame.cols,frame.rows));
	cv::Mat matDifference;
	//std::vector<cv::Rect> rects;    
	m_motionDetector.difference(m_sequences[m_seqCounter%m_seqLength],warp,matDifference);
	m_seqCounter++;
	//Mat warp;
	//warpPerspective(prevFrame,warp,H,Size(frame.cols,frame.rows));
	//Mat matDifference;
	//vector<Rect> rects;
	//detect.difference(frame,warp,matDifference,20);
	//历史图
	cv::Mat morphologyMat;
	m_motionDetector.morphology(matDifference,morphologyMat,m_morpholopyOpenScale,m_morpholopyCloseScale);
	std::vector<cv::Rect> tempRects;
	m_motionDetector.motionHistory(morphologyMat,m_mask,tempRects);//ends
	for(int i=0;i!=tempRects.size();i++){
		cv::Rect temp=tempRects[i];
		if(temp.width>5&&temp.height>5&&temp.width<m_mask.cols/3&&temp.height<m_mask.rows/3)
			outputRects.push_back(temp);
	}
	m_lastTimeCost=m_timer.end();
	cv::Mat tempMask;
	m_mask.clone().convertTo(tempMask,CV_8UC1);
	cv::threshold(tempMask,tempMask,0,255,CV_THRESH_BINARY);
	cv::Mat black=cv::Mat::zeros(tempMask.rows,tempMask.cols,CV_8UC1);
	std::vector<cv::Mat>merge;
	merge.push_back(tempMask);
	merge.push_back(black);
	merge.push_back(black);
	cv::Mat mergeImage=cv::Mat(tempMask.rows,tempMask.cols,CV_8UC3);
	cv::merge(merge,mergeImage);
	_outputMask=mergeImage;
	//detect.motionHistory(matDifference,mask,rects);
	//timer.print();
	//显示
	//for(size_t i=0;i!=rects.size();i++)
	//{
	//	cv::Rect temp;
	//	temp=rects[i];
	//	//temp.x=rects[i].x*2;
	//	//temp.y=rects[i].y*2;
	//	//temp.width=rects[i].width*2;
	//	//temp.height=rects[i].height*2;
	//	if(temp.width>10)
	//		rectangle(show,temp,Scalar(255,255,0),1,8,0);
	//}
	//std::vector<cv::Point2f> points;
	//matches.getKeyPoint(points);
	//for(size_t i=0;i!=points.size();i++)
	//{
	//	cv::circle(show,points[i],2,cv::Scalar::all(255));
	//}
	//imshow("showFinal",show);
	//imshow("difference",matDifference);
	//imshow("mask",mask);
	//key=waitKey(10);
	//if(key=='27')break;
	//prevFrame=frame.clone();
}
void MyMD::setFramePreProcess()
{
	m_framePreProcess.setCvtColor(DefaultCvtColor);
	m_framePreProcess.setBlur(DefaultBlur,DefaultBlurType,DefaultBlurSize,DefaultBlurSigma);
	if(m_prevFrame.cols>DefaultResizeWidth) 
		m_framePreProcess.setResize(DefaultResizeImage,cv::Size(m_prevFrame.cols*0.8,m_prevFrame.rows*0.8));
}