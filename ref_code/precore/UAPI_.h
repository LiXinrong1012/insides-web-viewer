#pragma once

#include "precore/precore_global.h"

namespace INSIDES{
	class BaseItem;
}

void PRECORE_EXPORT PREI_Delete_Item(INSIDES::BaseItem* item);
bool PRECORE_EXPORT PREI_Add_Item(INSIDES::BaseItem* parent,INSIDES::BaseItem* item,int pos=-1);
bool PRECORE_EXPORT PREI_Remove_Item(INSIDES::BaseItem* item,bool deleteIt);
bool PRECORE_EXPORT PREI_Modify_Item(INSIDES::BaseItem* src,INSIDES::BaseItem* dst);