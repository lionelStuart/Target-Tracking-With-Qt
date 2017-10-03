#include "qshowlabel.h"
#define min(a,b) a>b?b:a
#define max(a,b) a>b?a:b
QShowLabel::QShowLabel(QWidget *parent):
QLabel(parent),m_bClearPaint(false)
	//,ui(new Ui::QShowLabel)
{
	//ui->setupUi(this);
	setPaint();
}

QShowLabel::~QShowLabel()
{
	//delete ui;
}
QRect QShowLabel::returnRect()
{
	return selectRect;
}
void QShowLabel::setPaint()
{

}
void QShowLabel::setSelectRect()          //记录方框
{
	QPoint tl;
	tl.setX(min(ptOrign.x(),ptPresent.x()));
	tl.setY(min(ptOrign.y(),ptPresent.y()));
	int width=abs(ptOrign.x()-ptPresent.x());
	int height=abs(ptOrign.y()-ptPresent.y());
	selectRect.setRect(tl.x(),tl.y(),width,height);
}
void QShowLabel::clearSelectRect()
{
	ptOrign.setX(0);
	ptOrign.setY(0);
	ptPresent.setX(0);
	ptPresent.setY(0);
	selectRect.setRect(0,0,0,0);
}
void  QShowLabel::paintEvent (QPaintEvent * even) 
{
	onClearPaint();
	QLabel::paintEvent(even);//继承QLabel，显示背景图片必须	
	QPainter painter(this);	
	QPen pen;
	pen.setColor(QColor(200,200,200));  //设置画笔为hui色,绘制经纬线
	painter.setPen(pen);
	int width=this->width();
	int height=this->height();
	if(ptPresent.x()!=0&&ptPresent.y()!=0)
	{
		painter.drawLine(QPoint(ptPresent.x(),0),
			QPoint(ptPresent.x(),height));
		painter.drawLine(QPoint(0,ptPresent.y()),
			QPoint(width,ptPresent.y()));
	}
	pen.setColor(QColor(0,255,0));  //设置画笔为绿色，绘制框图
	painter.setPen(pen);
	painter.drawRect(selectRect);
	QString tempText=QString("X:%1\tY:%2\nW:%3\tH:%4")
		.arg(selectRect.x(),4).arg(selectRect.y(),4).arg(selectRect.width(),4).arg(selectRect.height(),4);
	painter.drawText(QRect(ptPresent.x()+5,ptPresent.y()+5,85,30),tempText);
}
void QShowLabel::clearPaint()
{
	m_bClearPaint=true;
	update();
}
void QShowLabel::onClearPaint()
{
	if(!m_bClearPaint) return;
		m_bClearPaint=false;
		clearSelectRect();
}
void QShowLabel::drawRect(const QRect& _rect)
{
	QPainter painter(this);	
	QPen pen;
	pen.setColor(QColor(0,255,0));  //设置画笔为绿色
	painter.setPen(pen);
	painter.drawRect(_rect);
}
void QShowLabel::mousePressEvent(QMouseEvent* even)
{
	if(even->buttons() && Qt::LeftButton)  //记录起点
	{
		ptOrign.setX(even->x());
		ptOrign.setY(even->y());
	}
}
void QShowLabel::mouseMoveEvent(QMouseEvent* even)
{
	int wndWidth=this->size().width()-1;       //刷新终点
	int wndHeight=this->size().height()-1;
	ptPresent.setX(max(min(even->x(),wndWidth),0));
	ptPresent.setY(max(min(even->y(),wndHeight),0));
	setSelectRect();
	update();
}
void QShowLabel::mouseReleaseEvent(QMouseEvent* even)
{
	int wndWidth=this->size().width()-1;          //记录终点
	int wndHeight=this->size().height()-1;
	ptPresent.setX(max(min(even->x(),wndWidth),0));
	ptPresent.setY(max(min(even->y(),wndHeight),0));
	setSelectRect();
}