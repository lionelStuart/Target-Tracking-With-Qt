/*****************************************************************/
/***QVideoProcessor**************************************************************/
/***继承VIdeoProcessor和QObject**************************************************************/
/***应用于Qt的视频处理类***************************************************/
/***主要方法****init在parents创建本对象时使用**********************************/
/**********openFile打开文件*****************************************/
/**********closeFile关闭文件******************************************/
/**********pause暂停/播放*********************************************/
/**********stop终止*************************************************/
/**********showFrame在指定label上绘制视频帧********************************/
/**********display在运行新的一帧后发出该信号，通过connect在视类中实现响应的槽函数并绑定****/
/**********run主线程（计时器触发）******************************************/
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
	void loadFile(QString _source);//获取视频后发射信号
private slots:
	void run();//计时器触发视频主线程
private:
	void onOpenFile();
	void onStop();
	void clear();
private:
	QWidget * m_parents;
	QTimer * m_timer;
	CMat2QImage m_mat2QImage;
	QString m_Qfiles;//另一种妥协，为了实现名字获取和显示，忽略编码问题，就直接定义了Qstring
	std::string m_files;
	bool m_bInit;
	bool m_bOpen;
	bool m_bPause;
	bool m_bStop;
};

#endif //QVideoProcessor_H

