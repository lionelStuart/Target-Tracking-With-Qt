/*****************************************************************/
/***Qt������_drawRectWnd���򴰿�******************************/
/***��ʼ�����ٴ�********************************************************/
/***init_drawing��ʼ������ͼ��ͷ��ؿ�λ��**************************/
/***��Ҫ��ShowLabel**************************************************/
/***����ؼ�Label����ΪQShowLabel������qshowlabelӦ��ȫ�ְ���********/
/*****************************************************************/
/***init_UI���ڳ�ʼ������ռ�**********************************************/
/***paintevent����paint�¼�****************************************/
/*******************************************by linoel ************/
//61617
#ifndef DRAWRECTWND_H
#define DRAWRECTWND_H
#include <QWidget>
#include<QImage>
#include "ui_drawrectwnd.h"
namespace cv{
	class Mat;
}
class CMat2QImage;
class CDrawRectWnd : public QWidget
{
	Q_OBJECT

public:
	CDrawRectWnd(QWidget *parent = 0);
	~CDrawRectWnd();
	void init_drawing(const cv::Mat &_inputImage,QRect *_outputRect);
signals:
	void rectReady();
private slots:
	void on_okButton_clicked();
private:
	void init_UI();
	void paintEvent(QPaintEvent*);
private:
	Ui::drawRectWnd ui;
	CMat2QImage* m_trans;
	QImage m_image;
	QRect* m_rects;
};

#endif // DRAWRECTWND_H
