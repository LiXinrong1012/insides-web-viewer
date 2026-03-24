#ifndef PREDOCUMENT_H
#define PREDOCUMENT_H

#include <QObject>

class BaseItem;

class PreDocument : public QObject
{
	Q_OBJECT

public:
	static PreDocument* instance();

	BaseItem* getRoot(){return _rootItem;}
	BaseItem* getCurrentRoot(){return _currentRoot;}

	// General API
	void appendChild(BaseItem* parent,BaseItem* item);
	void removeItem(BaseItem* item);
	void modifyItem(BaseItem* src,BaseItem* dst);
	void createDefault();
	void setCurrentRoot(BaseItem* root);



signals:
	void itemAdded(BaseItem* item,bool isIncludingChildren);
	void itemModified(BaseItem* item,bool isIncludingChildren);
	void itemRemoved(BaseItem* parent,BaseItem* item);
	void modelReseted(BaseItem* rootItem);

	void beginRootItemChanging(BaseItem* currentRoot);
	void rootItemChanged(BaseItem* currentRoot);


private:
	PreDocument(QObject *parent);
	~PreDocument();

	BaseItem*	_rootItem;
	BaseItem*	_currentRoot;
	bool		_enableSignal;
};

#endif // PREDOCUMENT_H
