//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/qthoopsrefapp_4/HQFrameRateDlg.h,v 1.9 2008-12-11 04:15:36 david Exp $
//

#if 0
#ifndef HQFRAMERATEDLG_H
#define HQFRAMERATEDLG_H

	//qt includes
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QString>
#include <QRadioButton>
#include <QSlider>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>

#include "HQWidget.h"
#if 0
#include "hsolidview.h"
#include "hconstantframerate.h"
#include "HConstantFramerate.h"
#endif
class HConstFRSimpType;


class HQFrameRateDlg : public QDialog
{
	Q_OBJECT
public:

	HQFrameRateDlg( QWidget* parent, const char * name, HBaseView *view);
    ~HQFrameRateDlg();

	QComboBox* detail_level;
	QComboBox* falloff_level;
	QCheckBox* maintain_fr;
	QCheckBox* use_lod_generation;
	QRadioButton* reduction_allowed;
	HBaseView* m_pHView;
	HConstantFrameRate* m_pCFR;
	bool m_bboundingboxes;
	int m_increase;

	bool GetFRState() {return FRState;}
	float GetMinFR() {return minimum_FR;}
	bool GetOpStarted() {return OpStarted;}
	void SetOpStarted(bool OpState) {OpStarted = OpState;}
	QSlider* slider;



	QLineEdit * minFR_field;
	
	
public slots:

	void OnFROnOff();
	void OnOKClicked();
	void OnCancelClicked();
	void Apply();
	void OnChangeFR(const QString & newFR);
	void OnDetailLevel(int level);

private:	
		// dialog controls
	QLabel * framerate_label;
	QLabel * minFR_label;
	QLabel * fps;

	QRadioButton * maintainFR_button;

	bool FRState;
	HConstFRSimpType **mlist;
	int					mlistLength;
	void cleanupSimpList();
	float minimum_FR;
	bool OpStarted;
	QWidget * _parent;
};

#endif

#else

#ifndef UI_FRAMERATEDIALOG_H
#define UI_FRAMERATEDIALOG_H


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>


class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QRadioButton *none_radio_button;
    QRadioButton *culling_thresh_radio_btn;
    QRadioButton *target_framerate_radio_button;
    QLineEdit *culling_thresh_px_line_edit;
    QLabel *label;
    QLineEdit *target_framerate_fps_line_edit;
    QLineEdit *max_thresh_px_line_edit;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *use_lods_check_box;
    QCheckBox *dynamic_adjustment_check_box;
    QLineEdit *detail_steps_line_edit;
    QLabel *label_6;
    QComboBox *comboBox;
    QPushButton *OkButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    Dialog->resize(277, 341);
    groupBox = new QGroupBox(Dialog);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(20, 10, 241, 271));
    none_radio_button = new QRadioButton(groupBox);
    none_radio_button->setObjectName(QString::fromUtf8("none_radio_button"));
    none_radio_button->setGeometry(QRect(20, 30, 84, 18));
    none_radio_button->setChecked(true);
    culling_thresh_radio_btn = new QRadioButton(groupBox);
    culling_thresh_radio_btn->setObjectName(QString::fromUtf8("culling_thresh_radio_btn"));
    culling_thresh_radio_btn->setEnabled(true);
    culling_thresh_radio_btn->setGeometry(QRect(20, 60, 111, 21));
    target_framerate_radio_button = new QRadioButton(groupBox);
    target_framerate_radio_button->setObjectName(QString::fromUtf8("target_framerate_radio_button"));
    target_framerate_radio_button->setEnabled(true);
    target_framerate_radio_button->setGeometry(QRect(20, 100, 111, 16));
    culling_thresh_px_line_edit = new QLineEdit(groupBox);
    culling_thresh_px_line_edit->setObjectName(QString::fromUtf8("culling_thresh_px_line_edit"));
    culling_thresh_px_line_edit->setEnabled(false);
    culling_thresh_px_line_edit->setGeometry(QRect(140, 60, 41, 21));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    label->setEnabled(false);
    label->setGeometry(QRect(190, 60, 46, 14));
    target_framerate_fps_line_edit = new QLineEdit(groupBox);
    target_framerate_fps_line_edit->setObjectName(QString::fromUtf8("target_framerate_fps_line_edit"));
    target_framerate_fps_line_edit->setEnabled(false);
    target_framerate_fps_line_edit->setGeometry(QRect(140, 100, 41, 20));
    max_thresh_px_line_edit = new QLineEdit(groupBox);
    max_thresh_px_line_edit->setObjectName(QString::fromUtf8("max_thresh_px_line_edit"));
    max_thresh_px_line_edit->setEnabled(false);
    max_thresh_px_line_edit->setGeometry(QRect(130, 170, 41, 20));
    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setEnabled(false);
    label_3->setGeometry(QRect(190, 100, 46, 14));
    label_4 = new QLabel(groupBox);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setEnabled(false);
    label_4->setGeometry(QRect(180, 170, 46, 14));
    label_5 = new QLabel(groupBox);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setEnabled(false);
    label_5->setGeometry(QRect(40, 170, 81, 16));
    use_lods_check_box = new QCheckBox(groupBox);
    use_lods_check_box->setObjectName(QString::fromUtf8("use_lods_check_box"));
    use_lods_check_box->setEnabled(false);
    use_lods_check_box->setGeometry(QRect(40, 200, 72, 18));
    dynamic_adjustment_check_box = new QCheckBox(groupBox);
    dynamic_adjustment_check_box->setObjectName(QString::fromUtf8("dynamic_adjustment_check_box"));
    dynamic_adjustment_check_box->setEnabled(false);
    dynamic_adjustment_check_box->setGeometry(QRect(40, 220, 131, 18));
    detail_steps_line_edit = new QLineEdit(groupBox);
    detail_steps_line_edit->setObjectName(QString::fromUtf8("detail_steps_line_edit"));
    detail_steps_line_edit->setEnabled(false);
    detail_steps_line_edit->setGeometry(QRect(130, 240, 41, 20));
    label_6 = new QLabel(groupBox);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setEnabled(false);
    label_6->setGeometry(QRect(60, 240, 71, 16));
    comboBox = new QComboBox(groupBox);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setEnabled(false);
    comboBox->setGeometry(QRect(40, 130, 111, 22));
    OkButton = new QPushButton(Dialog);
    OkButton->setObjectName(QString::fromUtf8("OkButton"));
    OkButton->setGeometry(QRect(100, 300, 75, 23));
    CancelButton = new QPushButton(Dialog);
    CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
    CancelButton->setGeometry(QRect(180, 300, 75, 23));

    retranslateUi(Dialog);
    QObject::connect(dynamic_adjustment_check_box, SIGNAL(toggled(bool)), detail_steps_line_edit, SLOT(setEnabled(bool)));
    QObject::connect(culling_thresh_radio_btn, SIGNAL(toggled(bool)), culling_thresh_px_line_edit, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), target_framerate_fps_line_edit, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), max_thresh_px_line_edit, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), use_lods_check_box, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), dynamic_adjustment_check_box, SLOT(setEnabled(bool)));
    QObject::connect(OkButton, SIGNAL(pressed()), Dialog, SLOT(accept()));
    QObject::connect(CancelButton, SIGNAL(pressed()), Dialog, SLOT(reject()));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), label_4, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), label_3, SLOT(setEnabled(bool)));
    QObject::connect(culling_thresh_radio_btn, SIGNAL(toggled(bool)), label, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), label_5, SLOT(setEnabled(bool)));
    QObject::connect(dynamic_adjustment_check_box, SIGNAL(toggled(bool)), label_6, SLOT(setEnabled(bool)));
    QObject::connect(target_framerate_radio_button, SIGNAL(toggled(bool)), comboBox, SLOT(setEnabled(bool)));

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("Dialog", "Framerate Optimization", 0, QApplication::UnicodeUTF8));
    none_radio_button->setText(QApplication::translate("Dialog", "None", 0, QApplication::UnicodeUTF8));
    culling_thresh_radio_btn->setText(QApplication::translate("Dialog", "Culling Threshold", 0, QApplication::UnicodeUTF8));
    target_framerate_radio_button->setText(QApplication::translate("Dialog", "Target Framerate", 0, QApplication::UnicodeUTF8));
    culling_thresh_px_line_edit->setText(QApplication::translate("Dialog", "10", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "px", 0, QApplication::UnicodeUTF8));
    target_framerate_fps_line_edit->setText(QApplication::translate("Dialog", "0.05", 0, QApplication::UnicodeUTF8));
    max_thresh_px_line_edit->setText(QApplication::translate("Dialog", "100", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Dialog", "sec", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("Dialog", "px", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("Dialog", "Max Thresh.", 0, QApplication::UnicodeUTF8));
    use_lods_check_box->setText(QApplication::translate("Dialog", "Use Lods", 0, QApplication::UnicodeUTF8));
    dynamic_adjustment_check_box->setText(QApplication::translate("Dialog", "Dynamic Adjustment", 0, QApplication::UnicodeUTF8));
    detail_steps_line_edit->setText(QApplication::translate("Dialog", "15", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("Dialog", "Detail Steps:", 0, QApplication::UnicodeUTF8));
    comboBox->insertItems(0, QStringList()
     << QApplication::translate("Dialog", "Fixed Framerate", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("Dialog", "Target Framerate", 0, QApplication::UnicodeUTF8)
    );
    OkButton->setText(QApplication::translate("Dialog", "OK", 0, QApplication::UnicodeUTF8));
    CancelButton->setText(QApplication::translate("Dialog", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Dialog);
    } // retranslateUi

};



namespace FramerateUi {
    class Dialog: public Ui_Dialog {};
} // namespace Ui



#endif // UI_FRAMERATEDIALOG_H

#endif


