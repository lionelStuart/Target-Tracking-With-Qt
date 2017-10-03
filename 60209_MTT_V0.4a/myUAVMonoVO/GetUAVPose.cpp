#include "GetUAVPose.h"
#include<iostream>
#include<cctype>
#include<sstream>
#include<fstream>
//#include<string>
using namespace std;
CGetUAVPose::CGetUAVPose(void):m_frameID(-1)
{
}
CGetUAVPose::~CGetUAVPose(void)
{
}
void CGetUAVPose::setPath(const std::string &_filePath)
{
	m_Path=_filePath;
}
void CGetUAVPose::GetPoseData(int _frameID,UAVPoseParam& _currentPose)
{
	m_frameID=_frameID;
	if(_frameID<0)cerr<<"Wrong frameID NUM"<<endl;
	if(readLine())
	{
			_currentPose=m_UAVPoseParam;
	}
	else
	{
		cerr<<"GetPoseData Error"<<endl;
	}
}
bool CGetUAVPose::readLine()
{
	ifstream myFile(m_Path);
	if(myFile.is_open())
	{
		int ptr=-1;
		string line;
		while(getline(myFile,line))
		{
			if(ptr==m_frameID)
			{
				std::istringstream in(line);
					for(int j=0;j<9;j++)
					{
						double temp;
						in>>temp;
						if(j==1)m_UAVPoseParam.x=temp;
						if(j==2)m_UAVPoseParam.y=temp;
						if(j==3)m_UAVPoseParam.z=temp;
						if(j==4)m_UAVPoseParam.rx=temp;
						if(j==5)m_UAVPoseParam.ry=temp;
						if(j==6)m_UAVPoseParam.rz=temp;
						if(j==7)m_UAVPoseParam.height=temp;
						if(j==8)m_UAVPoseParam.error=temp;
					}
					return true;
			}
			else
				ptr++;
		}
		if(ptr!=m_frameID){cerr<<"Data Cols do no match frameID"<<endl;return false;}
	}
	else
		return false;
}