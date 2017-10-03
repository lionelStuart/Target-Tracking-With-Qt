/************************************************************************/
/* QShowLabel类，支持Label上鼠标和画框行为                                                                     */
/* returnRect返回框位置
/* clearPaint清空Label上作画，需重写onClearPaint
/* 重写paintEvent以支持更多的绘画
/* 使用
/* 在ui中提升QLabel类
/* 鼠标框选目标
/* returnPaint 返回画框
/* virtual PaintEvent 继承修改画框行为
/* clearPaint清空绘图
/* drawRect画框
/* virtual onClearPaint继承修改清除绘图行为
/************************************************************************/
#ifndef QSHOWLABEL_H
#define QSHOWLABEL_H
//QLabel或其他控件继承类，实现鼠标框选目标行为
#include<qlabel.h>
#include<qpainter.h>
#include <QMouseEvent>
namespace Ui {
class QShowLabel;
}
class QShowLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QShowLabel(QWidget *parent=0);
    ~QShowLabel();
	QRect returnRect();           //返回框位置
    void setPaint();//未实现
	void clearPaint();
	void drawRect(const QRect& _rect);
protected:
	virtual void  paintEvent (QPaintEvent * even);   //继承改写绘制行为
	virtual void onClearPaint();
private:
	void mousePressEvent(QMouseEvent* even);  //继承改写鼠标行为
	void mouseMoveEvent(QMouseEvent* even);
	void mouseReleaseEvent(QMouseEvent* even);
	void setSelectRect();
	void clearSelectRect();
private:
	QRect selectRect;      //框及起始点
	QPoint ptOrign,ptPresent;
	bool m_bClearPaint;
};

#endif // QSHOWLABEL_H
