#ifndef TIMER_H
#define TIMER_H
#include<opencv2\opencv.hpp>
//简单计数类，startCount开始计数，
//endCount结束计数并返回结果
//printCount在控制台打印计数默认为/ms
//countInSecond修改为/s显示
class CTimer
{
public:
	CTimer(void);
	~CTimer(void);
	void countInSecond(bool set);
	void start();
	double end();
	void print();
private:
	double m_duration;
	bool m_bSetSecond;
};

//CLASS CTickCount
inline CTimer::CTimer(void):m_bSetSecond(false)
{
}
inline CTimer::~CTimer(void)
{
}
inline void CTimer::start()
{
	m_duration=static_cast<double>(cv::getTickCount());
}
inline void CTimer::countInSecond(bool set)
{
	m_bSetSecond=set;
}
//return time in ms
inline double CTimer::end()
{
	m_duration=static_cast<double>(cv::getTickCount())-m_duration;
	m_duration/=cv::getTickFrequency();
	if(!m_bSetSecond)
	m_duration*=1000;
	return m_duration;
}
inline void CTimer::print()
{
	end();
	if(m_bSetSecond)
		printf("Time Count\t%lf  s.\n",m_duration);
	else
		printf("Time Count\t%lf  ms.\n",m_duration);

}
#endif

