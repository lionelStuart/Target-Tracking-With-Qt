/*****************************************************************/
/***扩展QGraphicsView的功能********************************************/
/***用于显示地图的控件*****************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
#ifndef QMapView_H
#define QMapView_H
#include<qgraphicsscene.h>
#include<QGraphicsView>
#include<QPainter>
#include<QMouseEvent>
#include<opencv2/opencv.hpp>
class CMat2QImage;
class QImage;
class QMapView :public QGraphicsView
{
	Q_OBJECT
public:
	explicit QMapView(QWidget * parent=0);
	~QMapView(void);
	void setImage(const cv::Mat &_source);
	void clearImage();
private:
	QGraphicsScene *m_scene;
	CMat2QImage* m_mat2QImage;
	QImage* m_orignImage;
};
#endif//QMapView_H


