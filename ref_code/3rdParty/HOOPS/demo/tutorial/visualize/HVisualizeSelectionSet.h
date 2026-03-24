
#ifndef _HVisualizeSelectionSet_H__20010203__0953__
#define _HVisualizeSelectionSet_H__20010203__0953__

#include "HSelectionSet.h"

class HVisualizeSelectionSet :  public HSelectionSet 
{

public:
	HVisualizeSelectionSet(HBaseView* view);
	~HVisualizeSelectionSet();

    virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, bool emit_message = false);

	virtual void SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);

protected:
	
};

#endif	// _HVisualizeSelectionSet_H__20010203__0953__



