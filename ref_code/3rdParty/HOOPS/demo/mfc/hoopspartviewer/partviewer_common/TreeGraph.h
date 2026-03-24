// TreeGraph.h: interface for the TreeGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEGRAPH_H__A73BF51F_FDB9_4BE7_8211_666EEBCC3B72__INCLUDED_)
#define AFX_TREEGRAPH_H__A73BF51F_FDB9_4BE7_8211_666EEBCC3B72__INCLUDED_

#define STATIC_MODEL		1
#define GEOMETRY_REFERENCE	1<<1
#define SEGMENT_REFERENCE	1<<2
#define REFERENCE_GROUP		1<<3
#define READONLY_OBJECT		1<<4
#define STATIC_OR_REFERENCE	STATIC_MODEL|GEOMETRY_REFERENCE|SEGMENT_REFERENCE|REFERENCE_GROUP

class TreeGraphItem;
 


class TreeGraphMessageTarget
{
public:
	virtual void OnSelectionChanged(TreeGraphItem *item) { };
	virtual void OnTextModified(TreeGraphItem *item, const char *newtext) { }
	virtual void OnBeforeTextModified(TreeGraphItem *item, const char *oldtext) { }
	virtual void OnItemExpanding(TreeGraphItem *item, bool expand) { }
	virtual void OnImageClicked(TreeGraphItem *item) { }

};

class TreeGraph;

class TreeGraphItem
{
public:
	TreeGraphItem(TreeGraphItem *item, TreeGraph *control);
	virtual ~TreeGraphItem();
	virtual void Flush();

	virtual TreeGraphItem *GetNextSibling();
	virtual TreeGraphItem *GetLastChild();
	
	virtual void AddChildItem(TreeGraphItem *item, bool insertlast);
	virtual void AddSiblingItem(TreeGraphItem *item);
	virtual TreeGraphItem * AddChildItem(const TCHAR *text, void *extradata, bool InsertLast = true);
	virtual TreeGraphItem * AddSiblingItem(TCHAR *text, void *extradata, bool InsertLast = true);
	virtual void DeleteChildItem(TreeGraphItem *item);
	virtual void SetData(const char *text, void *extradata, void *extradata2=0);
//	virtual void Verify();
	virtual void SetHasChildren(bool hasChildren) { };
	virtual void SetBold(bool bold = true) { };
	virtual void SetSelected(bool selected = true) { };
	virtual void SetImage(int checkstate) { };
	virtual bool IsExpanded() { return false; }
	virtual void ModifyText(const char *text);
	virtual void ModifyText2(const char *text);
 	TreeGraphItem *m_pParentItem;
	TreeGraph *m_pTreeGraph;
	struct vlist_s*	m_ChildItemList;
	virtual void Expand() { m_bExpanded = true; };
	virtual void UnExpand() { m_bExpanded = false; };
	virtual void EditInPlace() { ; };

	char *m_pItemText;
	char *m_pItemText2;
	void *m_pExtraData;
	void *m_pExtraData2;
	bool m_bExpanded;
 	bool m_bEditable;
	unsigned int m_Flags;
	unsigned int m_Type;
};


class TreeGraph : public TreeGraphMessageTarget
{
public:

	TreeGraph();
	virtual ~TreeGraph();
	virtual void ResetInfoContent();
	virtual void AddInfoString(char *text);

	virtual TreeGraphItem *GetRootItem() { return m_pRootItem; };
	virtual void SetRootItem(TreeGraphItem * const item) {
		delete m_pRootItem;
		m_pRootItem = item;
	};

	virtual void OnSelectionChanged(TreeGraphItem *item);
	virtual void OnItemExpanding(TreeGraphItem *item, bool expand);
	virtual void OnTextModified(TreeGraphItem *item, const char * text);
	virtual void OnBeforeTextModified(TreeGraphItem *item, const char * text);
	virtual void OnImageClicked(TreeGraphItem *item);
	virtual void Flush() { };

	void SetMessageTarget(TreeGraphMessageTarget * target) { m_pMessageTarget = target; }

	TreeGraphMessageTarget * m_pMessageTarget;
	void AddItemToHash(TreeGraphItem *item);

	struct vhash_s *m_ExtraDataHash;
	void DeleteItemFromHash(TreeGraphItem *item);
	struct vlist_s *GetItemFromHash(void *key);

private:
	TreeGraphItem *m_pRootItem;

};

#endif // !defined(AFX_TREEGRAPH_H__A73BF51F_FDB9_4BE7_8211_666EEBCC3B72__INCLUDED_)
