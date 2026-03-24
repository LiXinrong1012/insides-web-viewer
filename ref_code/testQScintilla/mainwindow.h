#ifndef TESTQSCINTILLA_H
#define TESTQSCINTILLA_H

#include <QtGui/QMainWindow>
#include "ui_testqscintilla.h"

class QAction;
class QMenu;
class QsciScintilla;
class BaseCodeEditor;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent *event);
	void createEditor();

	private slots:
		void newFile();
		void open();
		bool save();
		bool saveAs();
		void about();
		void documentWasModified();

		void onTestMarker();
		void onTestAnnotation();

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

	BaseCodeEditor *textEdit;
	QString curFile;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveAsAct;
	QAction *exitAct;
	QAction *cutAct;
	QAction *copyAct;
	QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
};

#endif // TESTQSCINTILLA_H
