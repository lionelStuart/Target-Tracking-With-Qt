/************************************************************************/
/* cv::Mat to QIMage转换类 
/* importImage(_file)从文件读取一副图像，获得拷贝                                                                  */
/* importImage(_MatImage)从Mat获取图像，拷贝文件头
/* exportImage(QSize _wnd)返回QImage图像指针，图像缩放到_wnd尺度
/*若图像存在缩放，则没有多余的复制操作
/*若图像并没有缩放，则存在一份多余的拷贝
/************************************************************************/
#ifndef MAT2QIMAGE_H
#define MAT2QIMAGE_H
#include<opencv2\opencv.hpp>
#include<QtWidgets\qmainwindow.h>
using cv::Mat;
using cv::imread;
using cv::resize;
//调用OPENCV读取图片，转换格式，提供显示和Rect操作
//暂时只考虑三通道图像
class CMat2QImage
{
private:
	Mat orignImage;       //Opencv输入图片
	Mat convertImage;     //转换到RGB并缩放尺度
	QImage outputImage;   //与convertImage共用内存，新建QImage文件头
	CvSize imageSize;     //图像尺寸
	CvSize wndSize;       //获得窗口尺寸
	bool bConverted;
public:
	CMat2QImage();
	~CMat2QImage();
	bool importImage(const char *filename);     //输入图像
	bool importImage(const cv::Mat &inputImage );
	QImage* exportImage(const QSize &wndSize);  //输出图像
};



#endif