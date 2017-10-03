#include "QMapView.h"
#include"Mat2QImage/Mat2QImage.h"
#include<QImage>
QMapView::QMapView(QWidget *parent):
QGraphicsView(parent),m_mat2QImage(NULL),m_orignImage(NULL),
	m_scene(NULL)
{
	m_mat2QImage=new CMat2QImage();
	m_scene=new QGraphicsScene();
	this->setScene(m_scene);
}


QMapView::~QMapView(void)
{
	if(m_mat2QImage)
		delete m_mat2QImage;
}
void QMapView::setImage(const cv::Mat &_source)
{
	if(_source.cols<=0||_source.rows<=0)return;
	m_mat2QImage->importImage(_source);
	m_orignImage=m_mat2QImage->exportImage(QSize(_source.cols,_source.rows));
	m_scene->clear();
	m_scene->addPixmap(QPixmap::fromImage(*m_orignImage));
	this->show();
}
void QMapView::clearImage()
{
	if(m_scene){
		m_scene->clear();
		this->show();
	}
}
