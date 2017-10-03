#include "MyHash.h"
using namespace cv;
using namespace std;

CMyHash::~CMyHash(void)
{
}
void CMyHash::init(const cv::Mat &_frame,const cv::Rect &_trackingBox,bool _usePHash/* =0 */)
{
	cv::Mat temp=_frame(_trackingBox);
	cvtColor(temp,m_model,CV_BGR2GRAY);
	m_trackingBox=_trackingBox;
	m_usePHash=_usePHash;
}
void CMyHash::tracking(const cv::Mat &_frame,cv::Rect&_trackingBox)
{
	cv::Mat temp=_frame.clone();
	hashTrack(temp,m_model,m_trackingBox,!m_usePHash);
	_trackingBox=m_trackingBox;
}
// calculate the hash code of image  
Mat CMyHash::calHashCode(Mat image)  
{  
	resize(image, image, Size(8, 8));  
	Scalar imageMean = mean(image);  
	/*��ÿ�����صĻҶȣ���ƽ��ֵ���бȽϡ����ڻ����ƽ��ֵ��Ϊ1,С��ƽ��ֵ��Ϊ0*/ 
	return (image > imageMean[0]);  
}  
// calculate the pHash code of image  
Mat CMyHash::calPHashCode(Mat image)  
{  
	Mat floatImage, imageDct;  
	resize(image, image, Size(32, 32));   
	image.convertTo(floatImage, CV_32FC1);  
	dct(floatImage, imageDct);  
	Rect roi(0, 0, 8, 8);  
	Scalar imageMean = mean(imageDct(roi));  
	return (imageDct(roi) > imageMean[0]);  
}  
// get hamming distance of two hash code  
int CMyHash::calHammingDistance(Mat modelHashCode, Mat testHashCode)  
{  
	return countNonZero(modelHashCode != testHashCode);  
}  
// tracker: get search patches around the last tracking box,  
// and find the most similar one using hamming distance  
void CMyHash::hashTrack(Mat frame, Mat &model, Rect &trackBox, int flag/* = 0*/)  
{  //model��Ϊģ��ͼ��
	Mat gray;  
	cvtColor(frame, gray, CV_RGB2GRAY);  
	Rect searchWindow;  
	searchWindow.width = trackBox.width * 3;//�������Ǹ��ٴ���������С  
	searchWindow.height = trackBox.height * 3;  
	searchWindow.x = trackBox.x + trackBox.width * 0.5 - searchWindow.width * 0.5;  
	searchWindow.y = trackBox.y + trackBox.height * 0.5 - searchWindow.height * 0.5;  
	searchWindow &= Rect(0, 0, frame.cols, frame.rows);  

	Mat modelHashCode, testHashCode;  
	if (flag)  
		modelHashCode = calHashCode(model);  
	else  
		modelHashCode = calPHashCode(model);  
	int step = 2;  
	int min = 1000;  
	Rect window = trackBox;  
	for (int i = 0; i * step < searchWindow.height - trackBox.height; i++)  
	{  
		window.y = searchWindow.y + i * step;  
		for (int j = 0; j * step < searchWindow.width - trackBox.width; j++)  
		{  
			window.x = searchWindow.x + j * step;  
			if (flag)  
				testHashCode = calHashCode(gray(window));  //���ػ����洢��Hashֵ
			else  
				testHashCode = calPHashCode(gray(window));  
			int distance = calHammingDistance(modelHashCode, testHashCode);  //�����ϣֵ�ĺ�������ȡ��Сֵ
			if (distance < min)  
			{  
				trackBox = window;  
				min = distance;  
			}  
		}  
	}  
	model = gray(trackBox);  
	cout << "The min hanming distance is: " << min << endl;  
}  
