#ifndef TDY_PRE_PRECORE_UAPI_H_
#define TDY_PRE_PRECORE_UAPI_H_

#include "precore/precore_global.h"
#include "precore/precore_data.h"

namespace INSIDES
{
class ModelDocument;
class BaseItem;

void PRECORE_EXPORT PRE_Add_Item(ModelDocument* doc,BaseItem* parent,BaseItem* item);

void PRECORE_EXPORT PRE_Remove_Item(ModelDocument* doc, BaseItem* item);

void PRECORE_EXPORT PRE_Modify_Item(ModelDocument* doc,BaseItem* src,BaseItem* dst);

}

#endif