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
	void init(const Mat &frame, const cv::Rect box);//初始化   
	void tracking(const Mat &frame, cv::Rect &trackBox);//跟踪  

private:  
	void createHammingWin();  
	//复数运算，flag为1：除法，默认flag为0：乘法 
	void complexOperation(const Mat src1, const Mat src2, Mat &dst, int flag = 0);  
	void getCxtPriorPosteriorModel(const Mat image);  
	void learnSTCModel(const Mat image);  

private:  
	double sigma;           // scale parameter (variance)  
	double alpha;           // scale parameter  
	double beta;            // shape parameter  
	double rho;             // learning parameter  
	Point center;           // the object position  
	cv::Rect cxtRegion;         // context region//空间上下文区域方框  

	Mat cxtPriorPro;        // prior probability//与cxtPriorPro等大小单通道float格式，先验概率  
	Mat cxtPosteriorPro;    // posterior probability//cxtPriorPro等大，后验概率  
	Mat STModel;            // conditional probability//cxtPriorPro等大，条件概率  
	Mat STCModel;           // spatio-temporal context model//cxtPriorPro等大，时空模型  
	Mat hammingWin;         // Hamming window//等大，汉宁窗  
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