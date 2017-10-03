/**********************************************************/
/*       ���Զ����ʽ�ĵ��ж������˻���̬                               */
/*        UAVPoseParam�洢���˻���̬��Ϣ                            */
/*          CGetUAVPoseֻ����������                                       */
/*            setPath���ö�ȡ���ĵ�										        */
/*               GetPoseData��ָ��֡������Ϣ                            */
/*																		By Lionel		    */
/*********************************************************/
//UAVPose��TargetPosition�Ķ�ȡ��ʽ
//���Ǵ��ĵ������ж��룬�ڶ������ǵ�0֡��������ȡ�����ݱȽ����׶��룬
//Ҳ��ζ�ŷֶν�ȡ��Ƶ�ٷָ��ĵ������ز����޷�ʵ�ֵ�
//�����޸�readLine����
//notice _1224
#ifndef CGetUAVPose_H
#define CGetUAVPose_H
#include <string>
struct UAVPoseParam{//���˻���������,���꣬ŷ���ǣ��߶ȣ��߶Ȳ������
	double x;
	double y;
	double z;
	double rx;
	double ry;
	double rz;
	double height;
	double error;
};
class CGetUAVPose//���ĵ��ж������˻���̬��Ϣ
{
public:
	void setPath(const std::string &_filePath);//�����ĵ�λ��
	void GetPoseData(int _frameID,UAVPoseParam& _currentPose);//��֡��ȡ����
	CGetUAVPose(void);
	~CGetUAVPose(void);
private:
	bool readLine();
private:
	int m_frameID;//Ŀ��֡�����д�-1����,֡��������һ��
	std::string m_Path;
	UAVPoseParam m_UAVPoseParam;
};

#endif

