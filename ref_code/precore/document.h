#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "precore/precore_global.h"
#include <QObject>

namespace INSIDES
{

class ModelDocument;
class ResultDocument;


/*!
	@breif 表示一个导入的文档，包括模型和结果数据。
	@author	Jerry He
	@date	2014.9
*/
class PRECORE_EXPORT Document : public QObject
{
	Q_OBJECT

public:
	Document(QObject *parent=0);
	~Document();

	ModelDocument* getDocument(){return _preDocument;}
	ResultDocument* getResultDocument(){return _resultDocument;}

	bool save(const QString& fileName,bool saveResult);
	bool load(const QString& fileName,bool loadResult);

	public slots:
		void onGoInto();
		void onGoOut();

private:
	Q_DISABLE_COPY(Document);

	ModelDocument*		_preDocument;
	ResultDocument*		_resultDocument;
};

/*!
	@breif 表示此程序中的所有文档列表。
	单例模式，储存程序相关所有文档列表。
	@author	Jerry He
	@dae	2014.9
*/
class PRECORE_EXPORT MultiDocuments : public QObject
{
	Q_OBJECT
public:
	QList<Document*> getDocuments()const{return _documents;}
	
	Document* getActiveDocument();
	
	static MultiDocuments* instance();
	static void destruct();

	void notifyDisableUIUpdating(bool b);

signals:
	/// 当文档内容需要大规模改变，可以触发此信号强令窗口不要更新。
	void disableUIUpdating(bool b);

private:
	MultiDocuments();
	Q_DISABLE_COPY(MultiDocuments);

	QList<Document*> _documents;
	Document*	_activeDocument;
	static MultiDocuments* _instance;
};

} //end namespace INSIDES

#endif // DOCUMENT_H
