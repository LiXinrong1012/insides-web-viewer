#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class SearchLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	SearchLineEdit();
	~SearchLineEdit();
protected:
	void keyPressEvent(QKeyEvent* event);
signals:
	void pressKey(QString key);

private:
	
};

#endif // SEARCHLINEEDIT_H
