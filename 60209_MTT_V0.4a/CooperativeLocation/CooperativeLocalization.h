/*****************************************************************/
/***Эͬ��λ�㷨********************************************************/
/***matchedTrajectories******�����켣���ݵĽṹ��************************/
/*****************************************************************/
/***CCooperativeLocalization****Эͬ��λ***************************************/
/****��Ҫ����ͷ�ļ�***TrajectoryManager.h****MultiTargetTracker.h*****************/
/*****************************************************************/
/*****************************************************************/
#ifndef CCooperativeLocalization_H
#define CCooperativeLocalization_H
#include"Trajectory\TrajectoryManager.h"
#include"MultiTargetTracker\MultiTargetTracker.h"
const static int MAX_UAV_COUNT =10;
struct matchedTrajectories{
	enum trajectoryStatus{T_UPDATE,T_NOFOUND};
	int m_matchedTrajectoriesID[MAX_UAV_COUNT];//ÿ̨���˻���Ӧ�����켣���
	int m_trajectoriesStatus[MAX_UAV_COUNT];
	trajectory* m_ptrTrajectories[MAX_UAV_COUNT];//ָ��켣ָ��
	trajectory m_mixTrajectory;
	int m_uavCount;
	matchedTrajectories(){	clear();}
	void clear();
	void clearStatus();
	cv::Point2d getPixelCoordinateByChannel(int i);
};
inline cv::Point2d matchedTrajectories::getPixelCoordinateByChannel(int i){
	if(i<2){//MAX_UAV_COUNT->2
		return m_ptrTrajectories[i]->pixelCoordinate();
	}
	else
		return cv::Point2d(0,0);
}
inline void matchedTrajectories::clear(){
	m_uavCount=0;
	for(int i=0;i!=MAX_UAV_COUNT;i++){
		m_matchedTrajectoriesID[i]=-1;
		m_ptrTrajectories[i]=NULL;
		m_trajectoriesStatus[i]=T_NOFOUND;
	}
	m_mixTrajectory.m_trajectory.clear();
}
inline void matchedTrajectories::clearStatus()
{
	for(int i=0;i!=MAX_UAV_COUNT;i++){
		m_trajectoriesStatus[i]=T_NOFOUND;
	}
}
class CCooperativeLocalization
{
public:/*ʵ��ֻ�������̨��֧�ֶ�̨��Ҫ����*/
	CCooperativeLocalization(void):m_drawer(NULL){clear();}
	~CCooperativeLocalization(void);
	void init(CMultiTargetTracker** _uavList,int _uavCount);
	void update(int _frameID);
	void pairMatch(int _uavIndex_i,int _uavIndex_j);
	void set_draw(cv::Mat &_map,double _GeoMapWidth,double _GeoMapHeight);
	void draw(cv::Mat &_map);
	std::vector<matchedTrajectories>& getMatchedTrajectoried();
private:
	void clear();
	void updateMatchedTrajectory(int _uavID,int _matchedTrajectories);
	int getIndexMatched(int _uavID,int _trajectoriesID);//��ȡָ�����˻�������켣��matchedTrajectois�еĶ�Ӧλ�ã�û���򷵻�-1
	std::vector<matchedTrajectories> m_matchedTrajectories;
	CMultiTargetTracker* m_uavList[MAX_UAV_COUNT];
	CDrawMap* m_drawer;
    int m_frameID;
	int m_matchedCount;
};
inline std::vector<matchedTrajectories>& CCooperativeLocalization::getMatchedTrajectoried(){return m_matchedTrajectories;}
static CvScalar  CCoop_Colors[]= 
{
	{{0,0,255}},
	{{0,128,255}},
	{{0,255,255}},
	{{0,255,0}},
	{{255,128,0}},
	{{255,255,0}},
	{{255,0,0}},
	{{255,0,255}}
};
#endif

