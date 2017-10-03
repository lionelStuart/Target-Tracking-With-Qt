#include "CDrawRectWnd.h"
#include <QGraphicsDropShadowEffect>
#include<QPainter>
#include"ShowLabel/qshowlabel.h"
#include"Mat2QImage/Mat2QImage.h"
CDrawRectWnd::CDrawRectWnd(QWidget *parent)
	: QWidget(parent),m_trans(NULL),m_rects(NULL)
{
	m_trans=new CMat2QImage();
	ui.setupUi(this);
	init_UI();
}

CDrawRectWnd::~CDrawRectWnd()
{
	if(m_trans)
		delete m_trans;
}
void CDrawRectWnd::on_okButton_clicked()
{if(ui.drawArea->returnRect().width()!=0&&ui.drawArea->returnRect().height()!=0)
{
	*m_rects=ui.drawArea->returnRect();
	emit rectReady();
}
	this->close();
}
void CDrawRectWnd::init_UI()
{
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_DeleteOnClose);
	resize(parentWidget()->size());
	setWindowFlags(Qt::FramelessWindowHint|Qt::Window);
	setWindowModality(Qt::WindowModal);
	setGeometry(parentWidget()->parentWidget()->geometry());
	QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect(this);
	effect->setOffset(3,3);
	ui.okButton->setGraphicsEffect(effect);
}
void CDrawRectWnd::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	p.save();
	QBrush brush(QColor(0,0,0,200));
	p.setBrush(brush);
	p.drawRect(rect());
	p.restore();
}
void CDrawRectWnd::init_drawing(const cv::Mat &_image,QRect* _outputRect)
{
	m_trans->importImage(_image);
	QSize size=QSize(_image.cols,_image.rows);
	m_image=*m_trans->exportImage(size);
	ui.drawArea->resize(size);
	ui.okButton->move(ui.drawArea->geometry().topRight().x()-ui.okButton->width(),
		ui.drawArea->geometry().topRight().y());
	ui.okButton->raise();
	ui.drawArea->setPixmap(QPixmap::fromImage(m_image));
#define WND_SIZE parentWidget()->parentWidget()->size()
	resize((WND_SIZE.width()>120+m_image.width())?WND_SIZE.width():120+m_image.width(),
		(WND_SIZE.height()>120+m_image.height())?WND_SIZE.height():120+m_image.height());
#undef WND_SIZE parentWidget()->parentWidget()->size()
	m_rects=_outputRect;
}
