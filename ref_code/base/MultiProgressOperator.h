#pragma once

#include "base/base_global.h"
#include <QObject>
#include <QDialog>
#include <QScopedPointer>

class QMainWindow;



namespace Ui{
	class MulProgressDialogClass;
	class ProgressBarWidgetClass;
}


namespace Base
{
class MulProgressDialog;
class MulProgressDialogMapperPrivate;


class BASE_EXPORT MultiProgressOperator
{
public:
	static void setMainWindow(QMainWindow* mainWindow);
	/*!
	 * Start a new time-consuming progress.
	 * @param progressDescription String that will be displayed on progress bar.
	 */
	static void startProgress(const char* progressDescription);

	/*!
	 * Set current progress.
	 * @param value Current progress, from 0 to 100.
	 */
	static bool setProgress(int value);

	/*!
	 * Stop current time-consuming progress.
	 */
	static void stopProgress();

	/*!
	 * Return whether this progress was canceled by user.
	 * @return Whether this progress was canceled.
	 */
	static bool isProgressCanceled();	

	/*! 
	 * Terminate progress.
	 * @todo
	 */
	static void terminateProgress();
};



class BASE_EXPORT MulProgressDialogMapper : public QObject
{
	Q_OBJECT

public:
	static MulProgressDialogMapper* instance();
	static void destruct();

	void startProgress(const QString& description);
	bool setProgress(int percent);
	void stopProgress();

	private slots:
		void sStartProgress(const QString& description);
		bool sSetProgress(int percent);
		void sStopProgress();

signals:
		void progressTerminated();
		void progressFinished();

private:

	MulProgressDialogMapper();
	MulProgressDialogMapper(QObject *parent);
	~MulProgressDialogMapper();

	static MulProgressDialogMapper* _instance;
	QScopedPointer<MulProgressDialogMapperPrivate> _ptr;

};


class MulProgressDialogPrivate;

class BASE_EXPORT MulProgressDialog : public QDialog
{
	Q_OBJECT

public:
	MulProgressDialog(const QString& discription,QWidget *parent = 0);
	~MulProgressDialog();

	void startProgress(const QString& discription);
	void setProgress(int percent);
	void stopProgress();

	bool isTerminated();
	bool isFinished();

private:
	void onRejected();

private:
	Ui::MulProgressDialogClass* ui;
	QScopedPointer<MulProgressDialogPrivate> _ptr;
};


class ProgressBarWidget : public QWidget
{
	Q_OBJECT

public:
	ProgressBarWidget(QWidget *parent = 0);
	~ProgressBarWidget();

	void setProgress(int percent);
	void setDescription(const QString& discription);

private:
	Ui::ProgressBarWidgetClass* ui;
};

}	//end namespace Base