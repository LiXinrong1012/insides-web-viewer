#pragma once
#include "baseitem.h"

class TDYParameters;


namespace INSIDES
{
/*!
*	@breif 参数条目类。
*	代表树中的参数条目，包括一个参数列表。
*	@author Jerry He
*	@date 2014.3.11
*/
class PRECORE_EXPORT ParametersBaseItem :
	public BaseItem
{
public:
	ParametersBaseItem();
	virtual ~ParametersBaseItem(void);

	virtual void copyTo(BaseItem* item)const;

	const TDYParameters* getParameters()const;
	TDYParameters* getParameters();
	void setTDYParameters(TDYParameters* para);
	void refreshChildren();

	/// 仅仅更新内容,Jerry, 2014.9.18
	void refreshContents();

private:
	TDYParameters* _parameters;
};

} // end namespace INSIDES