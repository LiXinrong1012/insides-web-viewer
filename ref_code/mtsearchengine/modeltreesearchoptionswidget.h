#ifndef MODELTREESEARCHOPTIONSWIDGET_H
#define MODELTREESEARCHOPTIONSWIDGET_H

#include <QDialog>
namespace Ui {class ModelTreeSearchOptionsWidget;};
class MTSearchEngineImp;
class ModelSearchToolbar;
	

class ModelTreeSearchOptionsWidget : public QDialog
{
	Q_OBJECT

public:
	ModelTreeSearchOptionsWidget(QWidget *parent = 0);
	~ModelTreeSearchOptionsWidget();

	void updateInputHistory();

public slots:
	
	void showWidget();
private slots:
	void startSearch();
	void onSearchInResultButtonClicked();
	void onRemoveFromResultButtonClicked();
	void onJoinResultButtonClicked();

	void onValueChanged();
	void onRegExpActivated();
	void clearHistory();
private:
	Ui::ModelTreeSearchOptionsWidget *ui;
	ModelSearchToolbar* _searchBar;
	bool initing;

	void value2Control();
	void control2Value();
	void saveGeo();
	void loadGeo();
};

#endif // MODELTREESEARCHOPTIONSWIDGET_H
