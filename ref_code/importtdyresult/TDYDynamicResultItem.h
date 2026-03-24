#pragma once

#include "precore/DynamicResultItem.h"

/*!
	@brief  tdy动态结果条目
	@date   2015.7.7
	@author Jerry
*/
class TDYDynamicResultItem : 
	public INSIDES::DynamicResultItem
{
public:
	TDYDynamicResultItem(INSIDES::IResults* results);
	virtual ~TDYDynamicResultItem(void);

	///设置位置
	virtual void setPos(int pos);

	///设置排序索引，未实现
	void setOrderIndex(int index){_index=index;}

	///获取排序索引
	int getOrderIndex()const{return _index;}

private:
	///用来存储排序索引
	int _index;
};

