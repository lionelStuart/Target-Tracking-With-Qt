/*****************************************************************/
/***Qt窗口类_drawRectWnd画框窗口******************************/
/***初始化跟踪窗********************************************************/
/***init_drawing初始化画框图像和返回框位置**************************/
/***需要类ShowLabel**************************************************/
/***界面控件Label提升为QShowLabel并包含qshowlabel应用全局包含********/
/*****************************************************************/
/***init_UI用于初始化界面空间**********************************************/
/***paintevent重载paint事件****************************************/
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
