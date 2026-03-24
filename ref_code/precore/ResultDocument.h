#pragma once

#include "precore/precore_global.h"
#include <QObject>

#include "precore/IResults.h"
#include "precore/document.h"


namespace pp{class XMLHandler; class DataStreamWriter;}

namespace INSIDES
{
class MyAnimationControler;

/// 指示选择的一个结果条目。
struct ResultItemSelect
{
	QString  itemName;
	int		sectionIndex;
	int		subSectionIndex;
	int		subsubSectionIndex;
	int		index;

	ResultItemSelect()
		:sectionIndex(-1)
		,subSectionIndex(-1)
		,subsubSectionIndex(-1)
	{
	}

};

struct ResultGlobalParameters
{
	bool topChanged;
};

/*!
*	结果变更的观察者，Priority数值越大，越能排在前面。
*	@author	Jerry He
*	@date	2014.6.9
*/
class IResultListener
{
public:
	IResultListener(){_priority=0;}

	int getPriority(){return _priority;}
	void setPriority(int p){_priority=p;}
	
protected:
	virtual void onResultCurrentFrameChanged(){}

	/// 当结果数据准备被删除时被调用
	virtual void res_ResultsBeginDeleting(){}
	/// 当结果数据删除时调用
	virtual void res_ResultsDeleted(){}
	/// 结果数据新导入时调用
	virtual void res_ResultsLoaded(IResults* results){}

private:
	int	_priority;

	friend class ResultDocument;
};
/*!
*	负责管理和供查询动画数据
*	@author Jerry He
*	@date 2014.3.6
*/
class PRECORE_EXPORT ResultDocument
{
public:
	ResultDocument();
	~ResultDocument(void);

	IResults*	getResults(){return _results;}
	IResults* createDefaultResults();
	IResults* loadTDYResults();
	IResults* loadTDYEigResults();

	bool save(pp::XMLHandler* xmlHandler,const QString& baseName);
	bool load(pp::XMLHandler* xmlHandler);

	void clear();

	void attachListener(IResultListener* x);
	void disattachListener(IResultListener* x);

	void notifyListeners();

	void notifyResultsBeginDeleting();
	void notifyResultsDeleted();
	void notifyResultsLoaded(IResults* results);

	void setEmitMessage(bool b){_emitMessage=b;}

private:
	typedef QList<IResultListener*> ListenerList;

	IResults*	_results;
	ListenerList _listeners;
	MyAnimationControler*	_resultControler;
	bool		_emitMessage;
};


inline ResultDocument* myResultDocument(){return MultiDocuments::instance()->getActiveDocument()->getResultDocument();}

}