/************************************************************************/
/* cv::Mat to QIMageת���� 
/* importImage(_file)���ļ���ȡһ��ͼ�񣬻�ÿ���                                                                  */
/* importImage(_MatImage)��Mat��ȡͼ�񣬿����ļ�ͷ
/* exportImage(QSize _wnd)����QImageͼ��ָ�룬ͼ�����ŵ�_wnd�߶�
/*��ͼ��������ţ���û�ж���ĸ��Ʋ���
/*��ͼ��û�����ţ������һ�ݶ���Ŀ���
/************************************************************************/
#ifndef MAT2QIMAGE_H
#define MAT2QIMAGE_H
#include<opencv2\opencv.hpp>
#include<QtWidgets\qmainwindow.h>
using cv::Mat;
using cv::imread;
using cv::resize;
//����OPENCV��ȡͼƬ��ת����ʽ���ṩ��ʾ��Rect����
//��ʱֻ������ͨ��ͼ��
class CMat2QImage
{
private:
	Mat orignImage;       //Opencv����ͼƬ
	Mat convertImage;     //ת����RGB�����ų߶�
	QImage outputImage;   //��convertImage�����ڴ棬�½�QImage�ļ�ͷ
	CvSize imageSize;     //ͼ��ߴ�
	CvSize wndSize;       //��ô��ڳߴ�
	bool bConverted;
public:
	CMat2QImage();
	~CMat2QImage();
	bool importImage(const char *filename);     //����ͼ��
	bool importImage(const cv::Mat &inputImage );
	QImage* exportImage(const QSize &wndSize);  //���ͼ��
};



#endif