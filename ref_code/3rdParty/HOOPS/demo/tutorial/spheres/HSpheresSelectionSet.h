
#ifndef _HSpheresSelectionSet_H__20010203__0953__
#define _HSpheresSelectionSet_H__20010203__0953__

#include "HSelectionSet.h"

class HSpheresSelectionSet :  public HSelectionSet 
{
private:
	HSelectLevel m_SelectLevel;

public:
	HSpheresSelectionSet(HBaseView* view);
	~HSpheresSelectionSet();

    virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, bool emit_message = false);

	virtual void SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);

	void SetSelectLevel(HSelectLevel level) { m_SelectLevel = level; }
	const HSelectLevel GetSelectLevel() { return (m_SelectLevel);}

};

#endif	// _HSpheresSelectionSet_H__20010203__0953__



