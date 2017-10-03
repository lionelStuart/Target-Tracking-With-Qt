/************************************************************************/
/* QShowLabel�֧࣬��Label�����ͻ�����Ϊ                                                                     */
/* returnRect���ؿ�λ��
/* clearPaint���Label������������дonClearPaint
/* ��дpaintEvent��֧�ָ���Ļ滭
/* ʹ��
/* ��ui������QLabel��
/* ����ѡĿ��
/* returnPaint ���ػ���
/* virtual PaintEvent �̳��޸Ļ�����Ϊ
/* clearPaint��ջ�ͼ
/* drawRect����
/* virtual onClearPaint�̳��޸������ͼ��Ϊ
/************************************************************************/
#ifndef QSHOWLABEL_H
#define QSHOWLABEL_H
//QLabel�������ؼ��̳��࣬ʵ������ѡĿ����Ϊ
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
	QRect returnRect();           //���ؿ�λ��
    void setPaint();//δʵ��
	void clearPaint();
	void drawRect(const QRect& _rect);
protected:
	virtual void  paintEvent (QPaintEvent * even);   //�̳и�д������Ϊ
	virtual void onClearPaint();
private:
	void mousePressEvent(QMouseEvent* even);  //�̳и�д�����Ϊ
	void mouseMoveEvent(QMouseEvent* even);
	void mouseReleaseEvent(QMouseEvent* even);
	void setSelectRect();
	void clearSelectRect();
private:
	QRect selectRect;      //����ʼ��
	QPoint ptOrign,ptPresent;
	bool m_bClearPaint;
};

#endif // QSHOWLABEL_H
