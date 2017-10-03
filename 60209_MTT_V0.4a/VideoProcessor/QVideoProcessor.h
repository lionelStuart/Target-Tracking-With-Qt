/*****************************************************************/
/***QVideoProcessor**************************************************************/
/***�̳�VIdeoProcessor��QObject**************************************************************/
/***Ӧ����Qt����Ƶ������***************************************************/
/***��Ҫ����****init��parents����������ʱʹ��**********************************/
/**********openFile���ļ�*****************************************/
/**********closeFile�ر��ļ�******************************************/
/**********pause��ͣ/����*********************************************/
/**********stop��ֹ*************************************************/
/**********showFrame��ָ��label�ϻ�����Ƶ֡********************************/
/**********display�������µ�һ֡�󷢳����źţ�ͨ��connect��������ʵ����Ӧ�Ĳۺ�������****/
/**********run���̣߳���ʱ��������******************************************/
/*********************************by lionel 1617****************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef QVideoProcessor_H
#define  QVideoProcessor_H
#include<QtCore/QtCore>
#include <QtWidgets/QLabel>
#include<qtimer.h>
#include"VideoProcessor.h"
#include"Mat2QImage/Mat2QImage.h"
class QVideoProcessor:public QObject,public VideoProcessor
{
	Q_OBJECT
public:
	QVideoProcessor(void);
	~QVideoProcessor(void);
	void init(QWidget * _parents);
	void openFile();
	void closeFile();
	bool pause();
	void stop();
	void showFrame(const cv::Mat & _image,QLabel*_window);
	QString fileName();
 signals:
	void display();
	void loadFile(QString _source);//��ȡ��Ƶ�����ź�
private slots:
	void run();//��ʱ��������Ƶ���߳�
private:
	void onOpenFile();
	void onStop();
	void clear();
private:
	QWidget * m_parents;
	QTimer * m_timer;
	CMat2QImage m_mat2QImage;
	QString m_Qfiles;//��һ����Э��Ϊ��ʵ�����ֻ�ȡ����ʾ�����Ա������⣬��ֱ�Ӷ�����Qstring
	std::string m_files;
	bool m_bInit;
	bool m_bOpen;
	bool m_bPause;
	bool m_bStop;
};

#endif //QVideoProcessor_H

