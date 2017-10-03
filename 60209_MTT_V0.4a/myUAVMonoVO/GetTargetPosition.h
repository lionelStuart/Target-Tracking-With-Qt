/*********************************************************/
/*       从自定义格式文档中读入地面物体坐标                          */
/*        TargetParam存储地面物体坐标信息                            */
/*          CGetTargetPosition只有两个方法                             */
/*            setPath设置读取的文档										        */
/*               GetPositionData从指定帧读入信息                      */
/*																		By Lionel		    */
/*********************************************************/
#ifndef GetTargetPosition_H
#define GetTargetPosition_H
#include<string>
struct TargetParam{//地面目标参数输入，坐标，亦可用作三维向量读入
	double x;
	double y;
	double z;
};
class CGetTargetPosition
{
public:
	void setPath(const std::string &_filePath);//设置文档位置
	void GetPositionData(int _frameID,TargetParam& _currentPosition);//按帧读入目标位置
	CGetTargetPosition(void);
	~CGetTargetPosition(void);
private:
	bool readLine();
private:
	int m_frameID;
	std::string m_Path;
	TargetParam m_TargetParam;
};
#endif

