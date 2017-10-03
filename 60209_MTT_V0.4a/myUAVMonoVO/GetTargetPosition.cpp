#include "GetTargetPosition.h"
#include<iostream>
#include<cctype>
#include<sstream>
#include<fstream>
//#include<string>
using namespace std;
CGetTargetPosition::CGetTargetPosition(void)
{
}
CGetTargetPosition::~CGetTargetPosition(void)
{
}
void CGetTargetPosition::setPath(const std::string &_filePath)
{
	m_Path=_filePath;
}
void CGetTargetPosition::GetPositionData(int _frameID,TargetParam& _currentPose)
{
	m_frameID=_frameID;
	if(_frameID<0)cerr<<"Wrong frameID NUM"<<endl;
	if(readLine())
	{
		_currentPose=m_TargetParam;
	}
	else
	{
		cerr<<"GetTargetData Error"<<endl;
	}
}
bool CGetTargetPosition::readLine()
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
					if(j==1)m_TargetParam.x=temp;
					if(j==2)m_TargetParam.y=temp;
					if(j==3)m_TargetParam.z=temp;
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
