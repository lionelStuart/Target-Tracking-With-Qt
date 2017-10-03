/*****************************************************************/
/****数据关联算法*******************************************************/
/****包含卡尔曼滤波和贪心算法*****************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef DATAASSOCIATION_H
#define DATAASSOCIATION_H

#include "Kalman.h"
#include "HungarianAlg.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

class CTrace
{
public:
	
	vector<Point2d> m_trace;
	static size_t m_NextTrackID;
	size_t m_track_id;
	size_t m_skipped_frames; 
	Point2d m_prediction;
	TKalmanFilter* m_KF;
	CTrace(Point2f _p, float _dt, float _Accel_noise_mag);
	~CTrace();
};


class CDataAssociation
{
public:
	float m_dt;

	int m_max_trace_length;

	float m_Accel_noise_mag;

	double m_dist_thres;
	
	int m_maximum_allowed_skipped_frames;
	
	vector<CTrace*> m_traces;

	void Update(const  vector<Point2d>& _detections);
	CDataAssociation(float _dt, float _Accel_noise_mag, double _dist_thres=60, int _maximum_allowed_skipped_frames=10,int _max_trace_length=10);
	~CDataAssociation(void);
};


#endif
