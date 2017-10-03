/*********************************************************/
/*       ���Զ����ʽ�ĵ��ж��������������                          */
/*        TargetParam�洢��������������Ϣ                            */
/*          CGetTargetPositionֻ����������                             */
/*            setPath���ö�ȡ���ĵ�										        */
/*               GetPositionData��ָ��֡������Ϣ                      */
/*																		By Lionel		    */
/*********************************************************/
#ifndef GetTargetPosition_H
#define GetTargetPosition_H
#include<string>
struct TargetParam{//����Ŀ��������룬���꣬���������ά��������
	double x;
	double y;
	double z;
};
class CGetTargetPosition
{
public:
	void setPath(const std::string &_filePath);//�����ĵ�λ��
	void GetPositionData(int _frameID,TargetParam& _currentPosition);//��֡����Ŀ��λ��
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

