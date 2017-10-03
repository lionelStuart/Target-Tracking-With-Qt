#include "CooperativeLocalization.h"


CCooperativeLocalization::~CCooperativeLocalization(void)
{
	clear();
}
void CCooperativeLocalization::clear()
{
	m_frameID=-1;
	m_matchedCount=0;
	for(int i=0;i!=MAX_UAV_COUNT;i++)
	{
		m_uavList[i]=NULL;
	}
	m_matchedTrajectories.clear();
	if(m_drawer)
	{
			delete m_drawer;
			m_drawer=NULL;
	}
}
void CCooperativeLocalization::init(CMultiTargetTracker** _uavList,int _uavCount)
{
	for(int i=0;i!=_uavCount;i++)
	{
		m_uavList[i]=_uavList[i];
	}
}
int CCooperativeLocalization::getIndexMatched(int _uavID,int _trajectoriesID)
{
	if(_uavID<0||_trajectoriesID<0)return -1;
	if(_uavID>MAX_UAV_COUNT-1) return -1;
	for(int i=0;i!=m_matchedTrajectories.size();i++)
	{
		if(m_matchedTrajectories[i].m_matchedTrajectoriesID[_uavID]==_trajectoriesID)return i;
	}
	return -1;
}
void CCooperativeLocalization::updateMatchedTrajectory(int _uavID,int _matchedTrajectories)
{
	
}
void CCooperativeLocalization::pairMatch(int _uavIndex_i,int _uavIndex_j)
{
	CTrajectoryManager* MTT_1_ptr=m_uavList[_uavIndex_i]->getTrajectories();
	CTrajectoryManager* MTT_2_ptr=m_uavList[_uavIndex_j]->getTrajectories();
	for(int i=0;i!=m_matchedTrajectories.size();i++)//去掉终止的轨迹关联
	{
		for(int j=0;j!=MAX_UAV_COUNT;j++)
		if(m_uavList[j]!=NULL&&m_matchedTrajectories[i].m_matchedTrajectoriesID[j]!=-1&&
			m_uavList[j]->getTrajectories()->getTrajectory(m_matchedTrajectories[i].m_matchedTrajectoriesID[j]).getType()==trajectory::STATUS_TERMINATE)
		{
			   cout<<"remove ID"<<m_matchedTrajectories[i].m_matchedTrajectoriesID[j]<<"  of  uav"<<j<<"   from   Matched pair "<<i<<endl;
				m_matchedTrajectories[i].m_matchedTrajectoriesID[j]=-1;
				m_matchedTrajectories[i].m_ptrTrajectories[j]=NULL;
				m_matchedTrajectories[i].m_uavCount--;
				
		}
	}
   for(int i=0;i<m_matchedTrajectories.size();i++)//双方均终止的轨迹清除
   {
	   if(m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.size()>1&&m_matchedTrajectories[i].m_uavCount<=0)
	   {
		   //cout<<" delete Match "<<i<<"   size  "<<m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.size()<<endl;
		   m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.clear();
	   }
   }
   for(int i=0;i!=MTT_1_ptr->getTrajectoriesFullCount();i++)//遍历MTT_1_ptr，MTT_2_ptr
   {
	   if(MTT_1_ptr->getTrajectory(i).length()<10||//不是指定类型轨迹跳过
		   MTT_1_ptr->getTrajectory(i).getType()!=trajectory::STATUS_TRACK)continue;
	   if(getIndexMatched(_uavIndex_i,i)!=-1&&m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_uavCount==2)continue;//已经关联的跳过
	   for(int j=0;j!=MTT_2_ptr->getTrajectoriesFullCount();j++)
	   {
		   if(MTT_2_ptr->getTrajectory(j).length()<10||//不是指定类型轨迹跳过
			   MTT_2_ptr->getTrajectory(j).getType()!=trajectory::STATUS_TRACK)continue;
		   if(getIndexMatched(_uavIndex_i,i)!=-1&&m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_uavCount==2)continue;
		   if(getIndexMatched(_uavIndex_j,j)!=-1&&m_matchedTrajectories[getIndexMatched(_uavIndex_j,j)].m_uavCount==2)continue;//已经关联的跳过
		  // if(getIndexMatched(_uavIndex_i,i)!=-1&&m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_uavCount==1)
			   //计算所选轨迹i，j的末端节点相似度
		     //  cout<<"compete\t"<<i<<"=="<<j<<endl;
			   int nodePtr=MTT_1_ptr->getTrajectory(i).search(m_frameID);
			   if(nodePtr==-1)continue;
			   node tempNode=MTT_1_ptr->getTrajectory(i).m_trajectory[nodePtr];
			   int nodePtr2=MTT_2_ptr->getTrajectory(j).search(m_frameID);
			   if(nodePtr==-1)continue;
			   node tempNode2=MTT_2_ptr->getTrajectory(j).m_trajectory[nodePtr2];
			  // cout<<"uav_1   Trajectory"<<i<<"   frame   "<<tempNode.frameID<<"   :\t"<<tempNode.x<<"\t"<<tempNode.y<<"\t"<<tempNode.z<<endl;
			  // cout<<"uav_2   Trajectory"<<j<<"   frame   "<<tempNode2.frameID<<"    :\t"<<tempNode2.x<<"\t"<<tempNode2.y<<"\t"<<tempNode2.z<<endl;
			   if(pow(tempNode.x-tempNode2.x,2)+
				   pow(tempNode.y-tempNode2.y,2)+
				   pow(tempNode.z-tempNode2.z,2)<150)
			   {
				   if(getIndexMatched(_uavIndex_i,i)!=-1&&m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_uavCount==1)//第一台有历史关联并丢失
				   {
					   m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_matchedTrajectoriesID[_uavIndex_j]=j;
					   m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_ptrTrajectories[_uavIndex_j]=&MTT_2_ptr->getTrajectory(j);
					   m_matchedTrajectories[getIndexMatched(_uavIndex_i,i)].m_uavCount=2;
					   cout<<"reconnect "<<i<<"---"<<j<<endl;
				   }
				   else if(getIndexMatched(_uavIndex_j,j)!=-1&&m_matchedTrajectories[getIndexMatched(_uavIndex_j,j)].m_uavCount==1)
				   {
					   m_matchedTrajectories[getIndexMatched(_uavIndex_j,j)].m_matchedTrajectoriesID[_uavIndex_i]=i;
					   m_matchedTrajectories[getIndexMatched(_uavIndex_j,j)].m_ptrTrajectories[_uavIndex_i]=&MTT_1_ptr->getTrajectory(i);
					   cout<<"reconnect "<<i<<"---"<<j<<endl;
				   }
				   else
				   {
					   matchedTrajectories tempTrajectory;
					   tempTrajectory.m_matchedTrajectoriesID[_uavIndex_i]=i;
					   tempTrajectory.m_matchedTrajectoriesID[_uavIndex_j]=j;
					   tempTrajectory.m_ptrTrajectories[_uavIndex_i]=&MTT_1_ptr->getTrajectory(i);
					   tempTrajectory.m_ptrTrajectories[_uavIndex_j]=&MTT_2_ptr->getTrajectory(j);
					   tempTrajectory.m_uavCount=2;
					   m_matchedTrajectories.push_back(tempTrajectory);
					   cout<<"match  "<<i<<"---"<<j<<endl;
				   }
			   }
	   }
   }
   //cout<<"Matched Pair:\t"<<m_matchedTrajectories.size()<<endl;
   //
}
void CCooperativeLocalization::update(int _frameID)
{
	m_frameID=_frameID;
	pairMatch(0,1);
	for(int i=0;i!=m_matchedTrajectories.size();i++)
	{
		int nodePtr_a=-1;
		int nodePtr_b=-1;
		if(m_matchedTrajectories[i].m_ptrTrajectories[0])
		nodePtr_a=m_matchedTrajectories[i].m_ptrTrajectories[0]->search(_frameID);
		if(m_matchedTrajectories[i].m_ptrTrajectories[1])
		int nodePtr_b=m_matchedTrajectories[i].m_ptrTrajectories[1]->search(_frameID);
		node tempNode,tempNode_2,tempNode_3;
		if(nodePtr_a!=-1)//取第一轨迹值
		tempNode=m_matchedTrajectories[i].m_ptrTrajectories[0]->m_trajectory[nodePtr_a];
		if(nodePtr_b!=-1)//取第二轨迹值
		tempNode_2=m_matchedTrajectories[i].m_ptrTrajectories[1]->m_trajectory[nodePtr_b];
		tempNode_3.x=(tempNode.x+tempNode_2.x)/2;//求和
		tempNode_3.y=(tempNode.y+tempNode_2.y)/2;
		tempNode_3.z=(tempNode_3.z+tempNode_3.z)/2;
		tempNode_3.frameID=tempNode_2.frameID=tempNode.frameID=_frameID;
		if(tempNode.x==-1&&tempNode.y==-1&&tempNode.z==-1&&//两值均无效
			tempNode_2.x==-1&&tempNode_2.y==-1&&tempNode_2.z==-1)
			//m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.push_back(tempNode);
			continue;
		if(tempNode.x!=-1&&tempNode.y!=-1&&tempNode.z!=-1&&//两值均有效
			tempNode_2.x!=-1&&tempNode_2.y!=-1&&tempNode_2.z!=-1)
			m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.push_back(tempNode_3);
		else if(tempNode.x!=-1&&tempNode.y!=-1&&tempNode.z!=-1)//第一值有效
			m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.push_back(tempNode);
		else if(tempNode_2.x!=-1&&tempNode_2.y!=-1&&tempNode_2.z!=-1)//第二值有效
			m_matchedTrajectories[i].m_mixTrajectory.m_trajectory.push_back(tempNode_2);
	}
}
void CCooperativeLocalization::set_draw(cv::Mat &_map,double _GeoMapWidth,double _GeoMapHeight)
{
	if(!m_drawer)
		m_drawer=new CDrawMap;
	m_drawer->setParam(_map,_GeoMapWidth,_GeoMapHeight);
}
void CCooperativeLocalization::draw(cv::Mat &_map)
{
	if(m_drawer)
	{
		for(int i=0;i!=m_matchedTrajectories.size();i++)
		{
			//cout<<"draw\t"<<i<<endl;
			m_drawer->drawTrajectory(_map,m_matchedTrajectories[i].m_mixTrajectory,CCoop_Colors[i%8]);
		}
	}
}
