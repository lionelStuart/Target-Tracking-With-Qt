#include "DataAssociation.h"

using namespace cv;
using namespace std;

size_t CTrace::m_NextTrackID=0;
// ---------------------------------------------------------------------------
// Track constructor.
// The track begins from initial point (pt)
// ---------------------------------------------------------------------------
CTrace::CTrace(Point2f pt, float dt, float Accel_noise_mag)
{
	m_track_id=m_NextTrackID;

	m_NextTrackID++;
	// Every track have its own Kalman filter,
	// it user for next point position prediction.
	m_KF = new TKalmanFilter(pt,dt,Accel_noise_mag);
	// Here stored points coordinates, used for next position prediction.
	m_prediction=pt;
	m_skipped_frames=0;
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CTrace::~CTrace()
{
	// Free resources.
	delete m_KF;
}

// ---------------------------------------------------------------------------
// Tracker. Manage tracks. Create, remove, update.
// ---------------------------------------------------------------------------
CDataAssociation::CDataAssociation(float _dt, float _Accel_noise_mag, double _dist_thres, int _maximum_allowed_skipped_frames,int _max_trace_length)
{
	m_dt=_dt;
	m_Accel_noise_mag=_Accel_noise_mag;
	m_dist_thres=_dist_thres;
	m_maximum_allowed_skipped_frames=_maximum_allowed_skipped_frames;
	m_max_trace_length=_max_trace_length;
}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void CDataAssociation::Update(const vector<Point2d>& detections)
{
	// -----------------------------------
	// If there is no tracks yet, then every point begins its own track.
	// -----------------------------------
	if(m_traces.size()==0)
	{
		// If no tracks yet
		for(int i=0;i<detections.size();i++)
		{
			CTrace* tr=new CTrace(detections[i],m_dt,m_Accel_noise_mag);
			m_traces.push_back(tr);
		}	
	}

	int N=m_traces.size();		
	int M=detections.size();
	
	vector< vector<double> > Cost(N,vector<double>(M));
	vector<int> assignment; 

	// -----------------------------------
	
	double dist;
	for(int i=0;i<m_traces.size();i++)
	{	
		// Point2d prediction=tracks[i]->prediction;
		// cout << prediction << endl;
		for(int j=0;j<detections.size();j++)
		{
			Point2d diff=(m_traces[i]->m_prediction-detections[j]);
			dist=sqrtf(diff.x*diff.x+diff.y*diff.y);
			Cost[i][j]=dist;
		}
	}
	// -----------------------------------
	// Solving assignment problem (tracks and predictions of Kalman filter)
	// -----------------------------------
	AssignmentProblemSolver APS;
	APS.Solve(Cost,assignment,AssignmentProblemSolver::optimal);

	// -----------------------------------
	// clean assignment from pairs with large distance
	// -----------------------------------
	// Not assigned tracks
	vector<int> not_assigned_tracks;

	for(int i=0;i<assignment.size();i++)
	{
		if(assignment[i]!=-1)
		{
			if(Cost[i][assignment[i]]>m_dist_thres)
			{
				assignment[i]=-1;
				// Mark unassigned tracks, and increment skipped frames counter,
				// when skipped frames counter will be larger than threshold, track will be deleted.
				not_assigned_tracks.push_back(i);
			}
		}
		else
		{			
			// If track have no assigned detect, then increment skipped frames counter.
			m_traces[i]->m_skipped_frames++;
		}

	}

	// -----------------------------------
	// If track didn't get detects long time, remove it.
	// -----------------------------------
	for(int i=0;i<m_traces.size();i++)
	{
		if(m_traces[i]->m_skipped_frames>m_maximum_allowed_skipped_frames)
		{
			delete m_traces[i];
			m_traces.erase(m_traces.begin()+i);
			assignment.erase(assignment.begin()+i);
			i--;
		}
	}
	// -----------------------------------
	// Search for unassigned detects
	// -----------------------------------
	vector<int> not_assigned_detections;
	vector<int>::iterator it;
	for(int i=0;i<detections.size();i++)
	{
		it=find(assignment.begin(), assignment.end(), i);
		if(it==assignment.end())
		{
			not_assigned_detections.push_back(i);
		}
	}

	// -----------------------------------
	// and start new tracks for them.
	// -----------------------------------
	if(not_assigned_detections.size()!=0)
	{
		for(int i=0;i<not_assigned_detections.size();i++)
		{
			CTrace* tr=new CTrace(detections[not_assigned_detections[i]],m_dt,m_Accel_noise_mag);
			m_traces.push_back(tr);
		}	
	}

	// Update Kalman Filters state

	for(int i=0;i<assignment.size();i++)
	{
		// If track updated less than one time, than filter state is not correct.

		m_traces[i]->m_KF->GetPrediction();

		if(assignment[i]!=-1) // If we have assigned detect, then update using its coordinates,
		{
			m_traces[i]->m_skipped_frames=0;
			m_traces[i]->m_prediction=m_traces[i]->m_KF->Update(detections[assignment[i]],1);
		}else				  // if not continue using predictions
		{
			m_traces[i]->m_prediction=m_traces[i]->m_KF->Update(Point2f(0,0),0);	
		}
		
		if(m_traces[i]->m_trace.size()>m_max_trace_length)
		{
			m_traces[i]->m_trace.erase(m_traces[i]->m_trace.begin(),m_traces[i]->m_trace.end()-m_max_trace_length);
		}

		m_traces[i]->m_trace.push_back(m_traces[i]->m_prediction);
		m_traces[i]->m_KF->LastResult=m_traces[i]->m_prediction;
	}

}
// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
CDataAssociation::~CDataAssociation(void)
{
	for(int i=0;i<m_traces.size();i++)
	{
		delete m_traces[i];
	}
	m_traces.clear();
	CTrace::m_NextTrackID=0;
}
