#ifndef BASECODEEDITOR_H
#define BASECODEEDITOR_H

#include <Qsci/qsciscintilla.h>

class BaseCodeEditor : public QsciScintilla
{
	Q_OBJECT

public:
	BaseCodeEditor(QWidget *parent);
	~BaseCodeEditor();

	void testMarker();
	void testAnnotation();

protected slots:
	void onCharAdded(int charAdded);
	int getCurrentLineNumber();

protected:
	virtual void closeEvent(QCloseEvent *event);

private:
	
};

#endif // BASECODEEDITOR_H
