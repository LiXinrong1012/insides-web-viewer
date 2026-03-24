#include "isearchreplacedialog.h"

ISearchReplaceDialog::ISearchReplaceDialog(QWidget *parent)
	: QDialog(parent)
	,_searchPlace(SearchInCurrentDocument)
{
}

ISearchReplaceDialog::~ISearchReplaceDialog()
{
}
