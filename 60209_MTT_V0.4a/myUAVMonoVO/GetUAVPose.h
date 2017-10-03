/**********************************************************/
/*       从自定义格式文档中读入无人机姿态                               */
/*        UAVPoseParam存储无人机姿态信息                            */
/*          CGetUAVPose只有两个方法                                       */
/*            setPath设置读取的文档										        */
/*               GetPoseData从指定帧读入信息                            */
/*																		By Lionel		    */
/*********************************************************/
//UAVPose和TargetPosition的读取方式
//均是从文档中逐行读入，第二行总是第0帧，这样读取的数据比较容易对齐，
//也意味着分段截取视频再分割文档制作素材是无法实现的
//除非修改readLine函数
//notice _1224
#ifndef CGetUAVPose_H
#define CGetUAVPose_H
#include <string>
struct UAVPoseParam{//无人机参数输入,坐标，欧拉角，高度，高度测量误差
	double x;
	double y;
	double z;
	double rx;
	double ry;
	double rz;
	double height;
	double error;
};
class CGetUAVPose//从文档中读入无人机姿态信息
{
public:
	void setPath(const std::string &_filePath);//设置文档位置
	void GetPoseData(int _frameID,UAVPoseParam& _currentPose);//按帧读取参数
	CGetUAVPose(void);
	~CGetUAVPose(void);
private:
	bool readLine();
private:
	int m_frameID;//目标帧数，行从-1计算,帧数与行数一致
	std::string m_Path;
	UAVPoseParam m_UAVPoseParam;
};

#endif

