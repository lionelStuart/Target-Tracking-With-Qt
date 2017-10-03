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
	/*将每个像素的灰度，与平均值进行比较。大于或等于平均值记为1,小于平均值记为0*/ 
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
{  //model中为模板图像
	Mat gray;  
	cvtColor(frame, gray, CV_RGB2GRAY);  
	Rect searchWindow;  
	searchWindow.width = trackBox.width * 3;//搜索窗是跟踪窗的三倍大小  
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
				testHashCode = calHashCode(gray(window));  //返回划窗存储的Hash值
			else  
				testHashCode = calPHashCode(gray(window));  
			int distance = calHammingDistance(modelHashCode, testHashCode);  //计算哈希值的汉明距离取最小值
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
