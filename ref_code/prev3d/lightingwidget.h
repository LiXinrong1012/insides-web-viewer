#ifndef LIGHTINGWIDGET_H
#define LIGHTINGWIDGET_H

#include <QWidget>
#include "HBaseView.h"

namespace Ui {class LightingWidget;};

class LightingWidget : public QWidget
{
	Q_OBJECT

public:
	LightingWidget(QWidget *parent = 0);
	~LightingWidget();
	void updateLightingWidget();

	void setHBaseView(HBaseView* view){_hBaseView = view;}

protected:
	bool eventFilter ( QObject * watched, QEvent * event );
private slots:
	void onApplyPushButtonClicked();

	void onAmbientCheckBoxStateChanged();

	void onColor1FrameDoubleClicked();
	void onColor2FrameDoubleClicked();

	void onLightFrame1DoubleClicked();
	void onLightFrame2DoubleClicked();
	void onLightFrame3DoubleClicked();
	void onLightFrame4DoubleClicked();
	void onLightFrame5DoubleClicked();
	void onLightFrame6DoubleClicked();
	void onResetBtnClicked();

private:
	void updateItemsEnable();

	void updateHoopsLights();
	
private:
	Ui::LightingWidget *ui;
	HBaseView* _hBaseView;
};

#endif // LIGHTINGWIDGET_H
