
#ifndef _HAnalysisSelectionSet_H__20010203__0953__
#define _HAnalysisSelectionSet_H__20010203__0953__

#include "HSelectionSet.h"

class HAnalysisSelectionSet :  public HSelectionSet 
{
private:
	HSelectLevel m_SelectLevel;

public:
	HAnalysisSelectionSet(HBaseView* view);
	~HAnalysisSelectionSet();
 
 	virtual void Select( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);
    virtual void DeSelect( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = true);
	virtual void DeSelect(HC_KEY key, bool emit_message = false);

	virtual void SelectFromMessage( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelectFromMessage( HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);

protected:
	
};

#endif	// _HAnalysisSelectionSet_H__20010203__0953__



