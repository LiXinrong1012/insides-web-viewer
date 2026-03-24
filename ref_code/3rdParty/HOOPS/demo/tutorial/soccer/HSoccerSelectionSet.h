
#ifndef _HSoccerSelectionSet_H__20010203__0953__
#define _HSoccerSelectionSet_H__20010203__0953__

#include "HSelectionSet.h"

class HSoccerSelectionSet :  public HSelectionSet 
{
private:
	/*! denotes the current selection level */
	HSelectLevel m_SelectLevel;

public:
	HSoccerSelectionSet(HBaseView* view);
	~HSoccerSelectionSet();
 
    virtual void Select(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelect(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual bool IsSelected(HC_KEY key, int num_include_keys, HC_KEY * include_keys) const;
	virtual void DeSelectAll();

	virtual void SelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);
	virtual void DeSelectFromMessage(HC_KEY key, int num_include_keys, HC_KEY * include_keys, bool emit_message = false);

	/*! Set the Selection Level */
	void SetSelectLevel(HSelectLevel level) { m_SelectLevel = level; }

	/*! \returns an HSelectLevel */
	const HSelectLevel GetSelectLevel() { return (m_SelectLevel);}

};

#endif	// _HSoccerSelectionSet_H__20010203__0953__



