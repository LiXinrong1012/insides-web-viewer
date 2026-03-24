#include "searchlineedit.h"

SearchLineEdit::SearchLineEdit()
{

}

SearchLineEdit::~SearchLineEdit()
{

}

void SearchLineEdit::keyPressEvent( QKeyEvent* event)
{
	if (event->key() ==  Qt::Key_Up)
	{
		emit pressKey("UP");
		return;
	}
	if (event->key() == Qt::Key_Down)
	{
		emit pressKey("DOWN");
		return;
	}
	if(event->key() == Qt::Key_Enter)
	{
		emit pressKey("ENTER");
		return ;
	}
	QLineEdit::keyPressEvent(event);
}
