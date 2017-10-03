#include "CParamWidget.h"
#include"Tracker/MyTracker.h"
CParamWidget::CParamWidget(QWidget *parent)
	: QWidget(parent),m_bLBP(true),m_bPHash(true),
	m_bHog(true),m_bFixWnd(true),m_bMultiScale(true),
	m_particleNum(200),m_struckSearchRadius(12)
{
	ui.setupUi(this);
	clearParam();
	setDisable(false);
}

CParamWidget::~CParamWidget()
{
}
void CParamWidget::init_UI()
{//此处为何不使用成员变量赋值？类中重定义了stateChanged和valueChanged
	//函数，当调用set函数时，会回调这两个slots函数，并改变成员变量的数值
	ui.checkLBP->setChecked(true);
	ui.particleNumEdit->setText("200");
	ui.particleNumEdit->setDisabled(true);
	ui.ParticlesNumSlider->setMinimum(10);
	ui.ParticlesNumSlider->setMaximum(500);
	ui.ParticlesNumSlider->setValue(200);
	ui.checkPHash->setChecked(true);
	ui.searchRadiusSlider->setMinimum(5);
	ui.searchRadiusSlider->setMaximum(50);
	ui.searchRadiusSlider->setValue(12);
	ui.radiusEdit->setText("12");
	ui.radiusEdit->setDisabled(true);
	ui.checkHOG->setChecked(true);
	ui.checkFixWnd->setChecked(true);
	ui.checkMultiScale->setChecked(true);
	ui.methodEdit->setDisabled(true);
	setDisable(false);
}
void CParamWidget::clearParam()
{//因此clearParam会同时修改成员变量和空间的值
	init_UI();
	m_bLBP=true;
	m_bPHash=true;
	m_bHog=true;
	m_bFixWnd=true;
	m_bMultiScale=true;
	m_particleNum=200;
	m_struckSearchRadius=12;
}
void CParamWidget::showMethod(const QString &_method)
{
	ui.methodEdit->setText(_method);
}
void CParamWidget::on_paramButton_clicked()
{
	emit sendParam();
}
void CParamWidget::on_checkLBP_stateChanged()
{
	m_bLBP=ui.checkLBP->isChecked();
}
void CParamWidget::on_ParticlesNumSlider_valueChanged()
{
	m_particleNum=ui.ParticlesNumSlider->value();
	ui.particleNumEdit->setText(QString("%1").arg(m_particleNum));
}
void CParamWidget::on_checkPHash_stateChanged()
{
	m_bPHash=ui.checkPHash->isChecked();
}
void CParamWidget::on_searchRadiusSlider_valueChanged()
{
	m_struckSearchRadius=ui.searchRadiusSlider->value();
	ui.radiusEdit->setText(QString("%1").arg(m_struckSearchRadius));
}
void CParamWidget::on_checkHOG_stateChanged()
{
	m_bHog=ui.checkHOG->isChecked();
}
void CParamWidget::on_checkFixWnd_stateChanged()
{
	m_bFixWnd=ui.checkFixWnd->isChecked();
}
void CParamWidget::on_checkMultiScale_stateChanged()
{
	m_bMultiScale=ui.checkMultiScale->isChecked();
}
void CParamWidget::setDisable(bool _set)
{
	this->setDisabled(_set);
}
void CParamWidget::disablePF(bool _set)
{
	ui.checkLBP->setDisabled(_set);
	ui.ParticlesNumSlider->setDisabled(_set);
}
void CParamWidget::disableHash(bool _set)
{
	ui.checkPHash->setDisabled(_set);
}
void CParamWidget::disableStruck(bool _set)
{
	ui.searchRadiusSlider->setDisabled(_set);
}
void CParamWidget::disableKCF(bool _set)
{
	ui.checkHOG->setDisabled(_set);
	ui.checkFixWnd->setDisabled(_set);
	ui.checkMultiScale->setDisabled(_set);
}