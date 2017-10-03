#ifndef TICKCOUNT_H
#define TICKCOUNT_H
#include<opencv2\opencv.hpp>
//简单计数类，startCount开始计数，
//endCount结束计数并返回结果
//printCount在控制台打印计数默认为/ms
//countInSecond修改为/s显示
class CTickCount
{
public:
	CTickCount(void);
	~CTickCount(void);
	void countInSecond(bool set);
	void startCount();
	double endCount();
	void printCount();
private:
	double m_duration;
	bool m_setSecond;
};

//CLASS CTickCount
inline CTickCount::CTickCount(void):m_setSecond(false)
{
}
inline CTickCount::~CTickCount(void)
{
}
inline void CTickCount::startCount()
{
	m_duration=static_cast<double>(cv::getTickCount());
}
inline void CTickCount::countInSecond(bool set)
{
	m_setSecond=set;
}
//return time in ms
inline double CTickCount::endCount()
{
	m_duration=static_cast<double>(cv::getTickCount())-m_duration;
	m_duration/=cv::getTickFrequency();
	if(!m_setSecond)
		m_duration*=1000;
	return m_duration;
}
inline void CTickCount::printCount()
{
	endCount();
	if(m_setSecond)
		printf("Time Count\t%lf  s.\n",m_duration);
	else
		printf("Time Count\t%lf  ms.\n",m_duration);

}
#endif

