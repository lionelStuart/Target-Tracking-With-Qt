#include "MultiTargetTracker.h"
void detectionFilter(std::vector<cv::Rect> &_rects,int _minSize,int _maxSize)
{
	if(!_rects.size())return;
	std::vector<cv::Rect> temp;
	for(int i=0;i!=_rects.size();i++)
	{
		if(_rects[i].width<_minSize||_rects[i].height<_minSize)continue;
		if(_rects[i].width>_maxSize||_rects[i].height>_maxSize)continue;
		temp.push_back(_rects[i]);
	}
	if(temp.size()>1)
	for(int i=0;i<=temp.size()-1;i++)
	{
		for(int j=i+1;j<=temp.size()-1;j++)
		{
			if(COverlap::overlap(temp[i],temp[j])!=0)
			{
				temp[i]=COverlap::overlap(temp[i],temp[j])==-1?temp[i]:temp[j];
				temp[j]=temp[temp.size()-1];
				temp.pop_back();
			}
		}
	}
	_rects.clear();
	if(temp.size()>0)
	{
		    _rects.resize(temp.size());
			_rects.assign(temp.begin(),temp.end());
	}

}
int COverlap::overlap(cv::Rect &_rectA,cv::Rect &_rectB)
{
	int tlx=max(_rectA.x,_rectB.x);
	int tly=max(_rectA.y,_rectB.y);
	int brx=min(_rectA.br().x,_rectB.br().x);
	int bry=min(_rectA.br().y,_rectB.br().y);
	int width=brx-tlx;
	int height=bry-tly;
	if(width<0||height<0)return 0;//���غ�
	cv::Rect overlaps(tlx,tly,width,height);
	float overlapA=func(overlaps,_rectA);
	float overlapB=func(overlaps,_rectB);
	if(overlapA==1)return -1;//ѡ��A
	if(overlapB==1)return 1;//ѡ��B
	if(overlapA<0.5||overlapB<0.5)return 0;//�غ϶�̫��
	if(overlapA>overlapB)return -1;//ѡ��A
	else return 1;//ѡ��B
}
float COverlap::func(cv::Rect &_rectOverlap,cv::Rect &_rectSelect)
{
	float  areaOverlap=_rectOverlap.width*_rectOverlap.height;
	float areaSelect=_rectSelect.width*_rectSelect.height;
	return areaOverlap/areaSelect;
}
CMultiTargetTracker::CMultiTargetTracker(void)
	:m_enableVO(false),m_ptrVO(NULL),m_ptrDA(NULL),m_ptrTrajectoryManager(NULL),
	m_prevTargetsCount(0),m_currentTargetsCount(0),m_targetType(""){
		setDA();
		m_currentDetection.clear();
}
CMultiTargetTracker::~CMultiTargetTracker(void)
{
	if(m_enableVO)
	{
		delete m_ptrVO;
		delete m_ptrTrajectoryManager;
	}
	delete m_ptrDA;
}
 CTrajectoryManager* CMultiTargetTracker::getTrajectories()
{
	return m_ptrTrajectoryManager;
}
void CMultiTargetTracker::setTargetType(const std::string &_type)
{
	m_targetType=_type;
}
const std::string & CMultiTargetTracker::getTargetType()
{
	return m_targetType;
}
void CMultiTargetTracker::setVO(const std::string &_UAVPoseFilePath/* ="" */,const cv::Size &_imgSize/* =cv::Size */,double _fov/*=0*/)
{
	if(_UAVPoseFilePath=="")
	{
		m_enableVO=false;
	}
	else
	{
		m_enableVO=true;
		m_ptrVO=new CMyUavVO();
		m_ptrVO->loadUAVPoseFile(_UAVPoseFilePath);
		m_ptrVO->setUAVCamreaParam(_imgSize,_fov);
		m_ptrTrajectoryManager=new CTrajectoryManager();
	}
}
void CMultiTargetTracker::setDA(float _dt/* =0.2 */,float _accel_noise_mag/* =0.5 */,double _dist_thres/* =60 */,int _maximum_allowed_skipped_frames/* =10 */,int _max_trace_length/* =10 */)
{
	if(!m_ptrDA)
		m_ptrDA=new CDataAssociation(_dt,_accel_noise_mag,_dist_thres,_maximum_allowed_skipped_frames,_max_trace_length);
	m_ptrDA->m_dt=_dt;
	m_ptrDA->m_Accel_noise_mag=_accel_noise_mag;
	m_ptrDA->m_dist_thres=_dist_thres;
	m_ptrDA->m_max_trace_length=_max_trace_length;
	m_ptrDA->m_maximum_allowed_skipped_frames=_maximum_allowed_skipped_frames;
}
void CMultiTargetTracker::update(int _frameID,const  std::vector<cv::Rect> &_detectionRects)
{

	if(!_detectionRects.size())return;
	m_currentDetection.clear();
	std::vector<cv::Point2d> detectionCenterVec;
	for(int i=0;i!=_detectionRects.size();i++)//ת��_detectionRects��m_currentDetection����ֵdetectionCenterVec
	{
		int x=_detectionRects[i].x+_detectionRects[i].width/2;
		int y=_detectionRects[i].y+_detectionRects[i].height/2;
		CDetectionBox tempBox;
		tempBox.m_box=_detectionRects[i];
		tempBox.m_center=cv::Point2d(x,y);
		tempBox.m_pixID=-1;
		m_currentDetection.m_detection.push_back(tempBox);
		detectionCenterVec.push_back(cv::Point2d(x,y));
	}
	m_ptrDA->Update(detectionCenterVec);//�켣��������
	for(int i=0;i!=m_currentDetection.size();i++)//ͨ�����ؾ��뽫m_ptrDA�е�traces��m_currentDetection����
	{//���л�ù������µ�detectionbox�����id  1-��m_track_id�ͳ���m_trace.size
		cv::Point2d matchPixCenter=m_currentDetection.m_detection[i].m_center;
		int index=-1;
		for(int j=0;j!=m_ptrDA->m_traces.size();j++)
		{
			if(m_ptrDA->m_traces[j]->m_trace.size()>0&&
				pow(m_ptrDA->m_traces[j]->m_trace[m_ptrDA->m_traces[j]->m_trace.size()-1].x-matchPixCenter.x,2)+
				pow(m_ptrDA->m_traces[j]->m_trace[m_ptrDA->m_traces[j]->m_trace.size()-1].y-matchPixCenter.y,2)<30)
			{
				m_currentDetection.m_detection[i].m_pixID=m_ptrDA->m_traces[j]->m_track_id;
				m_currentDetection.m_detection[i].m_length=m_ptrDA->m_traces[j]->m_trace.size();
				break;
			}
		}
	}
	if(m_enableVO)//���������VO
	{
		m_prevTargetsCount=m_ptrTrajectoryManager->getTrajectoriesFullCount();
		m_currentTargetsCount=0;
		for(int i=0;i<m_ptrDA->m_traces.size();i++)
		{
			if(m_ptrDA->m_traces[i]->m_trace.size()>0)
				m_currentTargetsCount++;
		}
		for(int i=0;i<m_prevTargetsCount;i++)//i��Ӧ���еĹ켣���
		{
			int index=-1;
			for(	int j=0;j<m_ptrDA->m_traces.size();j++)
			{
				if(i==m_ptrDA->m_traces[j]->m_track_id)
				{
					index=j;break;//���Һ��й켣��ŵ�trace
				}
			}
			if(index!=-1)//�ù켣�����trace�����������¹켣
			{
				cv::Point2d pixelCoordinate=m_ptrDA->m_traces[index]->m_trace[m_ptrDA->m_traces[index]->m_trace.size()-1];
				cv::Mat absPosition;
				m_ptrVO->getAbsolutePosition(_frameID,pixelCoordinate,absPosition);
				m_ptrTrajectoryManager->updateTrajectory(i,absPosition,_frameID,pixelCoordinate);
				if(m_ptrTrajectoryManager->getTrajectory(i).length()>10)//���ȴ���10ʱ�ù켣�ж�Ϊ��������
				{
					m_ptrTrajectoryManager->getTrajectory(i).setType(trajectory::STATUS_TRACK);
				}
			}
			else//û��trace������trace�Ѿ���ʧ����ֹ�ù켣
			{
				if(m_ptrTrajectoryManager->getTrajectory(i).getType()!=trajectory::STATUS_TERMINATE)
				m_ptrTrajectoryManager->getTrajectory(i).setType(trajectory::STATUS_TERMINATE);
				if(m_ptrTrajectoryManager->getTrajectory(i).getType()==trajectory::STATUS_TERMINATE)
				{
					if(m_ptrTrajectoryManager->getTrajectory(i).length()>0&&//���켣��ֹ�ҽ϶�ʱִ��remove����
						m_ptrTrajectoryManager->getTrajectory(i).length()<10&&//�ͷŲ����ڴ棬���Ǳ����
						(_frameID-m_ptrTrajectoryManager->getTrajectory(i).m_prevFrameID)>100)
						m_ptrTrajectoryManager->getTrajectory(i).remove();
				}
			}
		}
		for(int j=0;j<m_ptrDA->m_traces.size();j++)//trace��Ŵ������й켣���ж�Ϊ�����켣
		{//ע��m_trace�ı���Ѿ���˳���źã����Կ���ֱ��forѭ����ӹ켣
			if(m_ptrDA->m_traces[j]->m_track_id >=m_prevTargetsCount&&
				m_ptrDA->m_traces[j]->m_trace.size()>0)
			{
				cv::Point2d pixelCoordinate=m_ptrDA->m_traces[j]->m_trace[m_ptrDA->m_traces[j]->m_trace.size()-1];
				cv::Mat absPosition;
				m_ptrVO->getAbsolutePosition(_frameID,pixelCoordinate,absPosition);
				m_ptrTrajectoryManager->addTrajectory(m_ptrDA->m_traces[j]->m_track_id,absPosition,_frameID,pixelCoordinate);
			}
		}
	}
	//cout<<"trajectorys:\t"<<m_ptrTrajectoryManager->getTrajectoriesCount()<<endl;
	//CMultiTargetTracker::update
}
void CMultiTargetTracker::getTraceUpdate(std::vector<int> &_traceIDVec,std::vector<cv::Point2d> &_traceCenterVec)
{//�������õķ�������ȡ�������������ID�Ķ�Ӧ��ϵ
	_traceIDVec.clear();
	_traceCenterVec.clear();
	if(m_ptrDA)
	for(int i=0;i<m_ptrDA->m_traces.size();i++)
	{
		if(m_ptrDA->m_traces[i]->m_trace.size()>0)
		{
			_traceIDVec.push_back(m_ptrDA->m_traces[i]->m_track_id);
			_traceCenterVec.push_back(m_ptrDA->m_traces[i]->m_trace[m_ptrDA->m_traces[i]->m_trace.size()-1]);
		}
	}
}

