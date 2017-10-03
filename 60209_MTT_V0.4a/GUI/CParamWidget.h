#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include <QWidget>
#include "ui_paramwidget.h"

class CParamWidget : public QWidget
{
	Q_OBJECT

public:
	CParamWidget(QWidget *parent = 0);
	~CParamWidget();
	void setDisable(bool _set);
	void clearParam();
	void disablePF(bool _set);
	void disableHash(bool _set);
	void disableStruck(bool _set);
	void disableKCF(bool _set);
	int getParticleNum() const;
	int getStruckSearchRadius() const;
	bool getLBPChecked() const;
	bool getPHashChecked() const;
	bool getHogChecked() const;
	bool getFixWndChecked() const;
	bool getMultiScaleChecked() const;
	void showMethod(const QString & _method);
private slots:
	void on_paramButton_clicked();
	void on_checkLBP_stateChanged();
	void on_ParticlesNumSlider_valueChanged();
	void on_checkPHash_stateChanged();
	void on_searchRadiusSlider_valueChanged();
	void on_checkHOG_stateChanged();
	void on_checkFixWnd_stateChanged();
	void on_checkMultiScale_stateChanged();
signals:
	void sendParam();
private:
		void init_UI();
private:
	Ui::paramWidget ui;
	bool m_bLBP;
	bool m_bPHash;
	bool m_bHog;
	bool m_bFixWnd;
	bool m_bMultiScale;
	int m_particleNum;
	int m_struckSearchRadius;
	
};
inline int CParamWidget::getParticleNum() const{return m_particleNum;}
inline int CParamWidget::getStruckSearchRadius() const{return m_struckSearchRadius;}
inline bool CParamWidget::getLBPChecked() const{return m_bLBP;}
inline bool CParamWidget::getPHashChecked() const{return m_bPHash;}
inline bool CParamWidget::getHogChecked() const{return m_bHog;}
inline bool CParamWidget::getFixWndChecked() const{return m_bFixWnd;}
inline bool CParamWidget::getMultiScaleChecked() const{return m_bMultiScale;}
#endif // PARAMWIDGET_H
