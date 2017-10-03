// Fast object tracking algorithm  
// Author : zouxy  
// Date   : 2013-11-21  
// HomePage : http://blog.csdn.net/zouxy09  
// Email  : zouxy09@qq.com  
// Reference: Kaihua Zhang, et al. Fast Tracking via Spatio-Temporal Context Learning  
// HomePage : http://www4.comp.polyu.edu.hk/~cskhzhang/  
// Email: zhkhua@gmail.com   
#ifndef  mySTCTracker_H
#define  mySTCTracker_H

#include <opencv2/opencv.hpp>  

//using namespace cv;  
using namespace std;  
using cv::Rect;
using cv::Mat;
using cv::Point;
class mySTCTracker;

class STCTracker  
{  
public:  
	STCTracker();  
	~STCTracker();  
	void init(const Mat &frame, const cv::Rect box);//��ʼ��   
	void tracking(const Mat &frame, cv::Rect &trackBox);//����  

private:  
	void createHammingWin();  
	//�������㣬flagΪ1��������Ĭ��flagΪ0���˷� 
	void complexOperation(const Mat src1, const Mat src2, Mat &dst, int flag = 0);  
	void getCxtPriorPosteriorModel(const Mat image);  
	void learnSTCModel(const Mat image);  

private:  
	double sigma;           // scale parameter (variance)  
	double alpha;           // scale parameter  
	double beta;            // shape parameter  
	double rho;             // learning parameter  
	Point center;           // the object position  
	cv::Rect cxtRegion;         // context region//�ռ����������򷽿�  

	Mat cxtPriorPro;        // prior probability//��cxtPriorPro�ȴ�С��ͨ��float��ʽ���������  
	Mat cxtPosteriorPro;    // posterior probability//cxtPriorPro�ȴ󣬺������  
	Mat STModel;            // conditional probability//cxtPriorPro�ȴ���������  
	Mat STCModel;           // spatio-temporal context model//cxtPriorPro�ȴ�ʱ��ģ��  
	Mat hammingWin;         // Hamming window//�ȴ󣬺�����  
}; 
class mySTCTracker:private STCTracker
{

public:
	mySTCTracker(){}
	void _init(const cv::Mat &_frame, const cv::Rect &_box);
	void _tracking(const cv::Mat &_frame,cv::Rect &_box);
private:
	cv::Rect m_trackingBox;
};
#endif