/*****************************************************************/
/***�˶�Ŀ����ӿ���************160131***********************************/
/*****************************************************************/
/*****************************************************************/
/*****��̬ѧ�˲���������ȡֵ��Χ������0~20*****************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef MyMD_H
#define MyMD_H
#include<time.h>
#include"FramePreprocess.h"
#include"FrameCalibration.h"
#include"MotionDetect.h"
//#include"CMHI_d.h"
#include"Timer.h"
#define DefaultSeqNum 10
#define DefaultBlur true
#define DefaultBlurType GAUSSIAN
#define DefaultBlurSize cv::Size(3,3)
#define DefaultBlurSigma 0.5
#define DefaultCvtColor true
#define DefaultResizeImage true
#define DefaultResizeWidth 900
class MyMD
{
public:
	MyMD(void);
	~MyMD(void);
	double getFrameTimeCost();
	void setFrameDeference(int length=DefaultSeqNum);//����֡���
	int getFrameDeference();
	void setFeatureType(CFrameCalibration::FEATURE_TYPE _type);//���ü������������
	const std::string& getFeatureType();
	int getMorpholopyOpenScale();
	void setMorpholopyOpenScale(int _scale);
	int getMorpholopyCloseScale();
	void setMorpholopyCloseScale(int _scale);
	void process(const cv::Mat &_inputFrame,std::vector<cv::Rect> &outputRects,cv::Mat &_outputMask);//main-process
private:
	void preCalculation(const cv::Mat &_inputFrame);//ѭ��ǰ���㣬��ʼ���������
	void loopCalculation(const cv::Mat &_inputFrame,std::vector<cv::Rect> &outputRects,cv::Mat &_outputMask);//ѭ�����㣬��׼���
	void setFramePreProcess();//����֡Ԥ������
private:
	int m_morpholopyOpenScale;
	int m_morpholopyCloseScale;
	int m_seqCounter;
	int m_seqLength;
	int m_seqInitCount;
	bool m_bSeqInited;
	bool m_bSetFramePreProcessor;
	std::vector<cv::Mat> m_sequences;
	cv::Mat m_prevFrame;
	CFramePreprocess m_framePreProcess;
	cv::Mat m_H;
	CFrameCalibration m_matches;
	cv::Mat m_mask;
	CMotionDetect m_motionDetector;
	CTimer m_timer;
	double m_lastTimeCost;

};
inline void MyMD::setFeatureType(CFrameCalibration::FEATURE_TYPE _type){m_matches.setFeatureType(_type);}
inline const std::string& MyMD::getFeatureType(){return m_matches.getFeatureType();}
inline int MyMD::getFrameDeference(){return m_seqLength;}
inline int MyMD::getMorpholopyOpenScale(){return m_morpholopyOpenScale;}
inline void MyMD::setMorpholopyOpenScale(int _scale){if(_scale>0&&_scale<21)m_morpholopyOpenScale=_scale;}
inline int MyMD::getMorpholopyCloseScale(){return m_morpholopyCloseScale;}
inline void MyMD::setMorpholopyCloseScale(int _scale){if(_scale>0&&_scale<21)m_morpholopyCloseScale=_scale;}
inline double MyMD::getFrameTimeCost(){return m_lastTimeCost;}
#endif//myMD_H

