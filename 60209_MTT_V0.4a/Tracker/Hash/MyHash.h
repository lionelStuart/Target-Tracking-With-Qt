/*****************************************************************/
/*******CMyHash跟踪类*******************************************/
/*******哈希跟踪算法**********************************************/
/*******init和Trakcing两种方法***********************************/
/*******_usePHash为真时使用PHash******************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*******************************************By Lionel*************/
/*****************************************************************/
/*****************************************************************/
#ifndef CMyHash_H
#define CMyHash_H
#include<opencv2\opencv.hpp>
using cv::Mat;
using cv::Rect;
class CMyHash
{
public:
	CMyHash(void):m_usePHash(true){}
	~CMyHash(void);
	void init(const cv::Mat &_frame,const cv::Rect &_trackingBox,bool _usePHash=true);
	void tracking(const cv::Mat &_frame,cv::Rect&_trackingBox);
private:	
	Mat calHashCode(Mat image)  ;
	Mat calPHashCode(Mat image)  ;
	int calHammingDistance(Mat modelHashCode, Mat testHashCode)  ;
    void hashTrack(Mat frame, Mat &model, Rect &trackBox, int flag = 0) ;
private:
	cv::Mat m_model;
	cv::Rect m_trackingBox;
	bool m_usePHash;
};
#endif

