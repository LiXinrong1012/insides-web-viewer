// HVisualizeSelectionSet.cpp : implementation of the HPSelectionSet class
// 

#include "HVisualizeSelectionSet.h"
#include "HVisualizeModel.h"
#include "HVisualizeView.h"

#include "vlist.h"

HVisualizeSelectionSet::HVisualizeSelectionSet(HBaseView* view) : HSelectionSet(view)
{
}

HVisualizeSelectionSet::~HVisualizeSelectionSet()
{
}

void HVisualizeSelectionSet::Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
}


void HVisualizeSelectionSet::DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}


void HVisualizeSelectionSet::DeSelect(HC_KEY key, bool emit_message )
{
	HSelectionSet::DeSelect(key, emit_message);
}



// If it is a call to select something from HNet message,
// by pass our selection functionality and just call the 
// vanilla Select. JUST SELECT THIS KEY!
// This is to work around the case where the master client
// is in some selection mode (face) and slave is in some (body)
void HVisualizeSelectionSet::SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::Select(key, num_include_keys, include_keys, emit_message);
}

//	See the Description for SelectFromMessage
void HVisualizeSelectionSet::DeSelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message)
{
	HSelectionSet::DeSelect(key, num_include_keys, include_keys, emit_message);
}




