// HoopsSegmentTree.h: interface for the HoopsSegmentTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOPSSEGMENTTREE_H__2BB1A01C_EA49_47C2_AE90_4FBA31AE9961__INCLUDED_)
#define AFX_HOOPSSEGMENTTREE_H__2BB1A01C_EA49_47C2_AE90_4FBA31AE9961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
class TreeGraphItem;
class TreeGraph;
class HoopsGeometry;
class HoopsDefineGeometry;
class HSelectionSet;
/////////////////////////////////////////////////////////////////////////////
// HoopsSegmentTree dialog

class HoopsSegmentTree : public TreeGraphMessageTarget
{
// Construction
public:
	HoopsSegmentTree(HBaseView *view = 0, TreeGraph *graph  = 0, HC_KEY startkey = -1);   // standard constructor
	~HoopsSegmentTree();

   	virtual void OnTextModified(TreeGraphItem *item, const char *newtext);
 	virtual void OnBeforeTextModified(TreeGraphItem *item, const char *newtext);
	virtual TreeGraphItem *GetCurrentItem() { return m_pCurrentItem; };
	virtual void SetCurrentItem(TreeGraphItem * const item) {
		m_pCurrentItem = item;
	};

	void ExpandSegmentItem(TreeGraphItem *item, HC_KEY key);
	TreeGraphItem * AddSegmentItem(HC_KEY segkey, TreeGraphItem *parent);
	void VerifyChildren(TreeGraphItem *item);
	void OnItemExpanding(TreeGraphItem *item, bool expand);
	bool GeometryExists(TreeGraphItem *item);
	bool SegmentsExist(TreeGraphItem *item);

	void ExpandGeometryItem(TreeGraphItem *item, HC_KEY key);
	void ExpandDefinesItem(TreeGraphItem *item, HC_KEY key);
	void SetSelectionSet(HSelectionSet *selection) { m_Selection = selection; }
	HSelectionSet * GetSelectionSet() { return m_Selection; }

	bool GeometryTypeExists(HC_KEY key,const char *type);
	bool DefineTypeExists(HC_KEY key,HoopsGeometry *type);

	void ExpandGeometryType(TreeGraphItem *item, HC_KEY key, HoopsGeometry *geomType);
 	void ExpandDefineType(TreeGraphItem *item, HC_KEY key, HoopsDefineGeometry *geomType);

	TreeGraphItem * AddGeometryItem(HC_KEY segkey, TreeGraphItem *parent, HoopsGeometry *geomType);
	TreeGraphItem * AddStaticModelItem(HC_KEY key, TreeGraphItem *parent);
	void AddSegmentReference(HC_KEY key, TreeGraphItem *parent);
	void AddDummyGeometry(HC_KEY key, TreeGraphItem *parent, HoopsGeometry *geomType);
	void AddGeometryReference(HC_KEY key, TreeGraphItem *parent);
	void AddSegmentGroupItem(int low, int high, TreeGraphItem *parent, void * pt = 0);
	void AddReferenceGroupItem(int low, int high, TreeGraphItem *parent, void * pt = 0);
	void ExpandSegmentGroupItem(TreeGraphItem *item, HC_KEY key);
	void ExpandReferenceGroupItem(TreeGraphItem *item, HC_KEY key);
	bool AttributesExist(TreeGraphItem *item);
	bool AnythingExists(TreeGraphItem *item);
	void ExpandAttributeItem(TreeGraphItem *item, HC_KEY key);
	void ExpandGeometryAttributeItem(TreeGraphItem *item, HC_KEY key);	
	bool AttributeTypeExists(HC_KEY key,char *type);
	TreeGraphItem * ExpandAttributeType(TreeGraphItem *item, HC_KEY key, const char *type = 0);
	bool IncludesExist(TreeGraphItem *item);
	bool StylesExist(TreeGraphItem *item);
	bool NamedStylesExist(TreeGraphItem *item);
	bool StaticModelsExist(TreeGraphItem *item);
	bool ReferencesExist(TreeGraphItem *item);
	bool GeometryReferencesExist(TreeGraphItem *item);
	bool SegmentReferencesExist(TreeGraphItem *item);
	void AddIncludeItem(HC_KEY segkey, TreeGraphItem *parent);
	void ExpandIncludeItem(TreeGraphItem *item, HC_KEY key);
	void ExpandStyleItem(TreeGraphItem *item, HC_KEY key);
	void ExpandNamedStyleItem(TreeGraphItem *item, HC_KEY key);
	void ExpandInclude(TreeGraphItem *item, HC_KEY key);
	void ExpandStyle(TreeGraphItem *item, HC_KEY key);
	void ExpandNamedStyle(TreeGraphItem *item, HC_KEY key);
	void ExpandStaticModel(TreeGraphItem *item, HC_KEY key);
	void ExpandReferenceItem(TreeGraphItem *item, HC_KEY key);
	void ExpandReferenceType(TreeGraphItem *item, HC_KEY key);	
	void OnImageClicked(TreeGraphItem *item);
 	void ShowSelectedItems() { };
	void ValidateSegmentTreeRecursive(TreeGraphItem *item);
	void ValidateSegmentTree();
	bool FindSelectedItemsRecursive(TreeGraphItem *item);
	void FindSelectedItems();
	void ShowNetAttribute(TreeGraphItem *item, char *attname, char *outtext);
	void EditInPlace(TreeGraphItem *item);

	void ExpandSpecificGeometry(TreeGraphItem *item, HC_KEY key);
	void ExpandSpecificReference(TreeGraphItem *item, HC_KEY key);

	void ExpandTextItem(TreeGraphItem *item, HC_KEY key);
	void OnSelectionChanged(TreeGraphItem *item);
	void ExtendAttributeText(const char *type, char *text, char *final);
	void FoldAttributeText(const char *text, char *foldedtext);
	void UndefineAttribute(TreeGraphItem *item);
	void DeleteSegment(TreeGraphItem *item);
	TreeGraphItem *GetRootItem() { return m_pTreeGraph->GetRootItem(); }
 	HBaseView *m_pView;
	TreeGraph *m_pTreeGraph;
	void SetItemImage(TreeGraphItem *item, int type = 0, void * pt = 0);
	bool HasSelectedChildren(HC_KEY startkey);
	void GetKeyList(TreeGraphItem *item, HC_KEY *keys, int &keynum, bool complete=false);
	void VisualizeBoundings(TreeGraphItem * item, HBaseView * m_pView, bool draw_something);

	struct vlist_s *m_AttributeList;
	struct vlist_s *m_GeometryList;
	struct vlist_s *m_DefineList;

	struct vlist_s *m_GeometryAttributeList_Basic;
	struct vlist_s *m_GeometryAttributeList_User;
	struct vlist_s *m_GeometryAttributeList_Text;
	struct vlist_s *m_GeometryAttributeList_Ref;

	HSelectionSet *m_Selection;

	bool DefinesExists(TreeGraphItem *item);
	bool IsAttribute(TreeGraphItem *item);
	bool IsDefine(TreeGraphItem *item);
	bool IsGeometry(TreeGraphItem *item);
	bool IsGeometry(TreeGraphItem *item, const char *text);
	bool IsInclude(TreeGraphItem *item);
	bool IsReference(TreeGraphItem *item);

	void GetNameAndDefinition(TreeGraphItem *item, char *name, char *definition);
	void DrawTextInInfoWindow(TreeGraphItem *item, int width);
	void ExpandByKeyList(HC_KEY *keys, int keynum);
	void ExpandByKeyListInternal(TreeGraphItem * startitem, HC_KEY *keys, int keynum, int keypos);
	void FindInAttributes(const char *text, TreeGraphItem * startitem=0);
	int FindInAttributesInternal(const char *text, const char *text2, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInGeometry(const char *text, TreeGraphItem * startitem=0);
	int FindInGeometryInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInSegments(const char *text, TreeGraphItem * startitem=0);
	int FindInSegmentsInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInIncludes(const char *text, TreeGraphItem * startitem=0);
	int FindInIncludesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInStyles(const char *text, TreeGraphItem * startitem=0);
	int FindInStylesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInNamedStyles(const char *text, TreeGraphItem * startitem=0);
	int FindInNamedStylesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInSegmentReferences(const char *text, TreeGraphItem * startitem=0);
	int FindInSegmentReferencesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInGeometryReferences(const char *text, TreeGraphItem * startitem=0);
	int	FindInGeometryReferencesInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInDefinitions(const char *text, TreeGraphItem * startitem=0);
	int FindInDefinitionsInternal(const char *text, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);
	void FindInKeys(const char *text, TreeGraphItem * startitem);
	int FindInKeysInternal(HC_KEY searchkey, HC_KEY startkey, HC_KEY *keys, int keynum, int keypos, vlist_s *foundlist);

	void FlushSegmentContents(TreeGraphItem *item, const char *type, bool follow_includes=true);

	void ShowInfoWindow(bool visibility) { m_ShowInfo=visibility; }
	void ShowBoundings(bool visibility) { m_VisualizeBoundings=visibility; }	
	bool InfoWindowShown() { return m_ShowInfo; }

private:

	inline void find_in_blank(int blank, const char *text, TreeGraphItem * startitem, HC_KEY search_key = INVALID_KEY);
	bool m_ShowInfo;
	bool m_VisualizeBoundings;
	TreeGraphItem * m_pCurrentItem;

};


class Keylist
{
public:
	HC_KEY keys[256];
	int keynum;
};


class HoopsAttribute
{
public:
    HoopsAttribute() { }

    virtual const char * GetName() = 0;
    virtual void Set(char *text) = 0;
    virtual void UnSet() = 0;
    virtual void Show(char *text) = 0;
    virtual void ShowNet(char *text) = 0;
    virtual bool Exists() {return (HC_Show_Existence(GetName()) == 1); }
};

class HoopsAttributeColor : public HoopsAttribute
{
public:
 
    const char * GetName() { return "COLOR"; }
	void Set(char *text) { HC_Set_Color(text); }
    void UnSet() { HC_UnSet_Color(); }
    void Show(char *text) { HC_Show_Color(text); }
    void ShowNet(char *text) { HC_Show_Net_Color(text); }
};

class HoopsAttributeColorMap : public HoopsAttribute
{
public:
 
    const char * GetName() { return "COLOR MAP"; }
	void Set(char *text) { HC_Set_Color_Map(text); }
    void UnSet() { HC_UnSet_Color_Map(); }
    void Show(char *text) 
	{ 
		int len;
		
		HC_Show_Color_Map_Length(&len);

		if(len<MVO_BUFFER_SIZE-16)
			HC_Show_Color_Map(text); 
		else
		{
			char * map=new char [len+1];
			HC_Show_Color_Map(map); 
			memcpy(text, map, MVO_BUFFER_SIZE-16);
			text[MVO_BUFFER_SIZE-16]=0x00;
			delete [] map;			
		}
	}
    void ShowNet(char *text) { HC_Show_Net_Color_Map(text); }
};


class HoopsAttributeGeometryOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "GEOMETRY OPTIONS"; }
	void Set(char *text) { 
		HC_KEY key;
		char type[MVO_BUFFER_SIZE];

		HC_Begin_Open_Item_Search();	
			HC_Find_Open_Item(&key, type, 0, 0);
		HC_End_Open_Item_Search();
		
		if(streq(type, "geometry"))
			HC_Set_Geometry_Options(key, text);
	}
    void UnSet() { 
		HC_KEY key;
		char type[MVO_BUFFER_SIZE];

		HC_Begin_Open_Item_Search();	
			HC_Find_Open_Item(&key, type, 0, 0);
		HC_End_Open_Item_Search();
		
		if(streq(type, "geometry"))
			HC_Set_Geometry_Options(key, "");
	}
    void Show(char *text) { 
		HC_KEY key;
		char type[MVO_BUFFER_SIZE];

		HC_Begin_Open_Item_Search();	
			HC_Find_Open_Item(&key, type, 0, 0);
		HC_End_Open_Item_Search();
		
		if(streq(type, "geometry"))
			HC_Show_Geometry_Options(key, text);
	}

    void ShowNet(char *text) { return; }
	
	bool Exists() { 
		HC_KEY key;
		char type[MVO_BUFFER_SIZE];
		bool ret = false;

		HC_Begin_Open_Item_Search();	
			HC_Find_Open_Item(&key, type, 0, 0);
		HC_End_Open_Item_Search();
		
		if(streq(type, "geometry"))
		{
			type[0]='\0';
			HC_Show_Geometry_Options(key, type);
			if(type[0]!='\0')
				ret=true;
		}

		return ret;
	}
};


class HoopsAttributeHeuristics : public HoopsAttribute
{
public:
 
    const char * GetName() { return "HEURISTICS"; }
	void Set(char *text) { HC_Set_Heuristics(text);	}
    void UnSet() { HC_UnSet_Heuristics(); }
    void Show(char *text) { HC_Show_Heuristics(text); }
    void ShowNet(char *text) { HC_Show_Net_Heuristics(text); }

};

class HoopsAttributeConditionalAction : public HoopsAttribute
{
public:
 
    const char * GetName() { return "CONDITIONAL ACTION"; }
	void Set(char *text)
	{
		char complex_conditional[MVO_BUFFER_SIZE],
			condition[MVO_BUFFER_SIZE], action[MVO_BUFFER_SIZE];

		for(int i=0; HC_Parse_String(text, ",", i, complex_conditional); ++i)
		{
			//((condition) ? (action))
			complex_conditional[strlen(complex_conditional)-1] = '\0';

			HC_Parse_String(complex_conditional+1, "?", 0, condition);
			HC_Parse_String(complex_conditional+1, "?", 1, action);

			condition[strlen(condition)-1] = '\0';
			action[strlen(action)-1] = '\0';

			HC_Set_Conditional_Action(action+1, condition+1);
		}
	}
    void UnSet() { HC_UnSet_Conditional_Actions(); }
    void Show(char *text)
	{
		char types[MVO_BUFFER_SIZE], action[MVO_BUFFER_SIZE], 
			condition[MVO_BUFFER_SIZE], single_type[MVO_BUFFER_SIZE];
		*text='\0';

		HC_Show_Cond_Action_Types(types);

		for(int i=0; HC_Parse_String(types, ",", i, single_type); ++i)
		{
			HC_Show_One_Conditional_Action(single_type, action, condition);

			strcat(text, "((");
			strcat(text, condition);
			strcat(text, ") ? (");
			strcat(text, single_type);
			strcat(text, " = ");
			strcat(text, (*action=='\0' ? "segment" : action));
			strcat(text, ")), ");
		}

		//gobble last comma and space
		text[strlen(text)-2]='\0';		
	}
    void ShowNet(char *text) { }
};

class HoopsAttributeVisibility : public HoopsAttribute
{
public:
  
    const char * GetName() { return "VISIBILITY"; }
    void Set(char *text) { HC_Set_Visibility(text); }
    void UnSet() { HC_UnSet_Visibility(); }
    void Show(char *text) { HC_Show_Visibility(text); }
    void ShowNet(char *text) { HC_Show_Net_Visibility(text); }

};

class HoopsAttributeRenderingOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "RENDERING OPTIONS"; }
    void Set(char *text) { HC_Set_Rendering_Options(text); }
    void UnSet() { HC_UnSet_Rendering_Options(); }
    void Show(char *text) { HC_Show_Rendering_Options(text); }
    void ShowNet(char *text) { HC_Show_Net_Rendering_Options(text); }

};

class HoopsAttributeWindow : public HoopsAttribute
{
public:
 
    const char * GetName() { return "WINDOW"; }

    void Set(char *text) { 
	float left, right, bottom, top;
  	sscanf(text, "%f %f %f %f" , &left, &right, &bottom, &top);
 	HC_Set_Window(left, right, bottom, top);
    }

    void UnSet() { HC_UnSet_Window(); }
    void Show(char *text) { 
	float left, right, bottom, top;

	HC_Show_Window(&left, &right, &bottom, &top);
	sprintf(text, "%f %f %f %f", left, right, bottom , top);
    }    
    void ShowNet(char *text) { 
	float left, right, bottom, top;

	HC_Show_Net_Window(&left, &right, &bottom, &top);
	sprintf(text, "%f %f %f %f", left, right, bottom , top);	
		}
};
 

class HoopsAttributeClipRegion: public HoopsAttribute
{
public:
 
    const char * GetName() { return "CLIP REGION"; }

    void Set(char *text) { ;
    }

    void UnSet() { HC_UnSet_Clip_Region(); }
    void Show(char *text) { 
	int loops, total;
	char spec[MVO_BUFFER_SIZE];
 	HC_Show_Clip_Region_Size(&loops, &total, spec);
	sprintf(text, "Loops:%d Total:%d Specs:%s", loops, total, spec);
    }    
    void ShowNet(char *text) { 
	int loops, total;
	char spec[MVO_BUFFER_SIZE];
 	HC_Show_Net_Clip_Region_Size(&loops, &total, spec);
	sprintf(text, "Loops:%d Total:%d Specs:%s", loops, total, spec);
		}
};





class HoopsAttributeSelectability : public HoopsAttribute
{
public:
 
    const char * GetName() { return "SELECTABILITY"; }
    void Set(char *text) { HC_Set_Selectability(text); }
    void UnSet() { HC_UnSet_Selectability(); }
    void Show(char *text) { HC_Show_Selectability(text); }
    void ShowNet(char *text) { HC_Show_Net_Selectability(text); }

};

class HoopsAttributeCallback : public HoopsAttribute
{
public:
 
    const char * GetName() { return "CALLBACK"; }
    void Set(char *text) { HC_Set_Callback(text); }
    void UnSet() { HC_UnSet_Callback(); }
    void Show(char *text) { HC_Show_Callback(text); }
    void ShowNet(char *text) { HC_Show_Net_Callback(text); }

};

class HoopsAttributeUserOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "USER OPTIONS"; }
    void Set(char *text) { HC_Set_User_Options(text); }
    void UnSet() { HC_UnSet_User_Options(); }

    void Show(char *text) { 
		int len;
		HC_Show_User_Options_Length(&len);
		char *temp = new char[len+1];
		HC_Show_User_Options(temp); 
		strncpy(text, temp, MVO_BIG_BUFFER_SIZE-100);
		text[MVO_BIG_BUFFER_SIZE-100] = 0;
		delete [] temp;
	}
    void ShowNet(char *text) { HC_Show_Net_User_Options(text); }

	bool Exists() {
		int len = 0;
		if(HC_Show_Existence("user options") > 0)
			HC_Show_User_Options_Length(&len);
		return len > 0;
	}
};

class HoopsAttributeUserIndex : public HoopsAttribute
{
public:
 
    const char * GetName() { return "USER INDEX"; }
    void Set(char *text) {  }
    void UnSet() { }

    void Show(char *text) { 
		int count = 0;
		HC_Show_User_Index_Count(&count);
		if(count)
		{
			size_t max = MVO_BUFFER_SIZE - 100;
			size_t current_size = 0;
			long *		indices = new long[count];
			void **		values = new void * [count];

			HC_Show_User_Indices(&count, indices, values);

			sprintf(text, "%d : { (%lu = %p)", count, indices[0], values[0]);
			current_size = strlen(text);
			for(int i = 1; i<count && current_size<max; ++i)
			{
				char local_index[128];
				sprintf(local_index, ", (%lu = %p)", indices[i], values[i]);
				strcat(text, local_index);
				current_size += strlen(local_index);
			}
			if(current_size >= max)
				strcat(text, ", ...");
			strcat(text, "}");
			delete [] indices;
			delete [] values;
		}
	}
    void ShowNet(char *text) { }

	bool Exists() {
		int cnt = 0;
		HC_Show_User_Index_Count(&cnt);
		return (cnt > 0);
	}
};

class HoopsAttributeUserData : public HoopsAttribute
{
public:
 
    const char * GetName() { return "USER DATA"; }
    void Set(char *text) {  }
    void UnSet() { }

    void Show(char *text) { 
		int count = -HC_Show_User_Data_Indices(0, 0);
		if(count)
		{
			size_t max = MVO_BUFFER_SIZE - 100;
			size_t current_size = 0;
			POINTER_SIZED_INT * indices = new POINTER_SIZED_INT[count];
			HC_Show_User_Data_Indices(indices, count);
			sprintf(text, "%d : {%lu", count, indices[0]);
			current_size = strlen(text);
			for(int i = 1; i<count && current_size<max; ++i)
			{
				char local_index[128];
				sprintf(local_index, ", %lu", indices[i]);
				strcat(text, local_index);
				current_size += strlen(local_index);
			}
			if(current_size >= max)
				strcat(text, ", ...");
			strcat(text, "}");
			delete [] indices;
		}
	}
    void ShowNet(char *text) { }

	bool Exists() {
		int cnt = -HC_Show_User_Data_Indices(0, 0);
		return (cnt > 0);
	}
};

class HoopsAttributeUnicodeOptions : public HoopsAttribute
{
public:

	const char * GetName() {
		return "UNICODE OPTIONS";
	}

	bool Exists() {
		int len = 0;
		if(HC_Show_Existence("user options") > 0)
			HC_Show_Unicode_Options_Length(&len);
		return len > 0;
	}

	void Set(char *text) {
		H_UTF16 unicode_text(text);
		HC_Set_Unicode_Options((unsigned short*)unicode_text.encodedText());
	}

	void UnSet() {
		HC_UnSet_Unicode_Options();
	}

	void Show(char *text) { 
		int len;
		HC_Show_Unicode_Options_Length(&len);
		unsigned short *temp = new unsigned short[len+1];
		HC_Show_Unicode_Options(temp); 
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*)temp);
		delete [] temp;
		H_UTF8 utf8(utf16);
		strncpy(text, (char const*)utf8.encodedText(), MVO_BIG_BUFFER_SIZE-100);
		text[MVO_BIG_BUFFER_SIZE-100]=0;
	}

	void ShowNet(char *text) {
		int len;
		HC_Show_Unicode_Options_Length(&len);
		unsigned short *temp = new unsigned short[len+1];
		HC_Show_Net_Unicode_Options(temp); 
		H_UTF16 utf16;
		utf16.encodedText((utf16_char const*)temp);
		delete [] temp;
		H_UTF8 utf8(utf16);
		strcpy(text, (char const*)utf8.encodedText());
	}
};

class HoopsAttributeTextFont : public HoopsAttribute
{
public:
 
    const char * GetName() { return "TEXT FONT"; }
    void Set(char *text) { HC_Set_Text_Font(text); }
    void UnSet() { HC_UnSet_Text_Font(); }
    void Show(char *text) { HC_Show_Text_Font(text); }
    void ShowNet(char *text) { HC_Show_Net_Text_Font(text); }

};


class HoopsAttributeTextPath : public HoopsAttribute
{
public:
 
    const char * GetName() { return "TEXT PATH"; }
    void Set(char *text) {
		float x, y, z;
  		sscanf(text, "%f %f %f" , &x, &y, &z);
 		HC_Set_Text_Path(x, y, z);
    }
    void UnSet() { HC_UnSet_Text_Path(); }
    void Show(char *text) { 
		float x, y, z;
		HC_Show_Text_Path(&x, &y, &z);
		sprintf(text, "%f %f %f", x, y, z);
	}
    void ShowNet(char *text) { 
		float x, y, z;
		HC_Show_Net_Text_Path(&x, &y, &z);
		sprintf(text, "%f %f %f", x, y, z);
	}

};

class HoopsAttributeTextSpacing : public HoopsAttribute
{
public:
 
    const char * GetName() { return "TEXT SPACING"; }
    void Set(char *text) { 
		float spacing;
		sscanf(text, "%f", &spacing);
		HC_Set_Text_Spacing(spacing); 
	}
    void UnSet() { HC_UnSet_Text_Spacing(); }
    void Show(char *text) {
		float spacing;
		HC_Show_Text_Spacing(&spacing); 
		sprintf(text, "%f", spacing);
	}
    void ShowNet(char *text) { 
		float spacing;
		HC_Show_Net_Text_Spacing(&spacing); 
		sprintf(text, "%f", spacing);
	}

};

class HoopsAttributeWindowPattern : public HoopsAttribute
{
public:
 
    const char * GetName() { return "WINDOW PATTERN"; }
    void Set(char *text) { HC_Set_Window_Pattern(text); }
    void UnSet() { HC_UnSet_Window_Pattern(); }
    void Show(char *text) { HC_Show_Window_Pattern(text); }
    void ShowNet(char *text) { HC_Show_Net_Window_Pattern(text); }

};

class HoopsAttributeTextAlignment : public HoopsAttribute
{
public:
 
    const char * GetName() { return "TEXT ALIGNMENT"; }
    void Set(char *text) { HC_Set_Text_Alignment(text); }
    void UnSet() { HC_UnSet_Text_Alignment(); }
    void Show(char *text) { HC_Show_Text_Alignment(text); }
    void ShowNet(char *text) { HC_Show_Net_Text_Alignment(text); }

};

class HoopsAttributeVariableEdgeWeight : public HoopsAttribute
{
public:
 
    const char * GetName() { return "VARIABLE EDGE WEIGHT"; }
    void Set(char *text) { HC_Set_Variable_Edge_Weight(text); }
    void UnSet() { HC_UnSet_Edge_Weight(); }
    void Show(char *text) { HC_Show_Variable_Edge_Weight(text); }
    void ShowNet(char *text) { HC_Show_Net_Var_Edge_Weight(text); }
    bool Exists() {

        if (HC_Show_Existence("EDGE WEIGHT") == 1)
	{
	    float ew;
	    HC_Show_Edge_Weight(&ew);
	    if (ew <0.0f)
 		return true;
	    else return false;
	}
	return false;

    }


};
class HoopsAttributeEdgeWeight : public HoopsAttribute
{
public:
 
    const char * GetName() { return "EDGE WEIGHT"; }
    void Set(char *text) { 
	float ew;
 	sscanf(text, "%f", &ew);
	HC_Set_Edge_Weight(ew);	
    }
	
     void UnSet() { HC_UnSet_Edge_Weight(); }
    void Show(char *text) { 
	float ew;
	HC_Show_Edge_Weight(&ew);
	sprintf(text, "%f", ew);
    
    }
    void ShowNet(char *text) { 
	float ew;
	HC_Show_Net_Edge_Weight(&ew);
	sprintf(text, "%f", ew);	
	}
    bool Exists() {

        if (HC_Show_Existence("EDGE WEIGHT") == 1)
	{
	    float ew;
	    HC_Show_Edge_Weight(&ew);
	    if (ew >=0.0f)
 		return true;
	    else return false;
	}
	return false;

    }


};

class HoopsAttributeVariableLineWeight : public HoopsAttribute
{
public:
 
    const char * GetName() { return "VARIABLE LINE WEIGHT"; }
    void Set(char *text) { HC_Set_Variable_Line_Weight(text); }
    void UnSet() { HC_UnSet_Line_Weight(); }
    void Show(char *text) { HC_Show_Variable_Line_Weight(text); }
    void ShowNet(char *text) { HC_Show_Net_Var_Line_Weight(text); }
    bool Exists() {

        if (HC_Show_Existence("LINE WEIGHT") == 1)
	{
	    float ew;
	    HC_Show_Line_Weight(&ew);
	    if (ew <0.0f)
 		return true;
	    else return false;
	}
	return false;

    }


};

class HoopsAttributeLinePattern : public HoopsAttribute
{
public:
 
    const char * GetName() { return "LINE PATTERN"; }
    void Set(char *text) { HC_Set_Line_Pattern(text); }
    void UnSet() { HC_UnSet_Line_Pattern(); }
    void Show(char *text) { HC_Show_Line_Pattern(text); }
    void ShowNet(char *text) { HC_Show_Net_Line_Pattern(text); }

};

class HoopsAttributeEdgePattern : public HoopsAttribute
{
public:
 
    const char * GetName() { return "EDGE PATTERN"; }
    void Set(char *text) { HC_Set_Edge_Pattern(text); }
    void UnSet() { HC_UnSet_Edge_Pattern(); }
    void Show(char *text) { HC_Show_Edge_Pattern(text); }
    void ShowNet(char *text) { HC_Show_Net_Edge_Pattern(text); }

};


class HoopsAttributeMarkerSymbol : public HoopsAttribute
{
public:
 
    const char * GetName() { return "MARKER SYMBOL"; }
    void Set(char *text) { HC_Set_Marker_Symbol(text); }
    void UnSet() { HC_UnSet_Marker_Symbol(); }
    void Show(char *text) { HC_Show_Marker_Symbol(text); }
    void ShowNet(char *text) { HC_Show_Net_Marker_Symbol(text); }

};

class HoopsAttributeFacePattern : public HoopsAttribute
{
public:
 
    const char * GetName() { return "FACE PATTERN"; }
    void Set(char *text) { HC_Set_Face_Pattern(text); }
    void UnSet() { HC_UnSet_Face_Pattern(); }
    void Show(char *text) { HC_Show_Face_Pattern(text); }
    void ShowNet(char *text) { HC_Show_Net_Face_Pattern(text); }

};


class HoopsAttributeLineWeight : public HoopsAttribute
{
public:
 
    const char * GetName() { return "LINE WEIGHT"; }
    void Set(char *text) { 
	float ew;
 	sscanf(text, "%f", &ew);
	HC_Set_Line_Weight(ew);	
    }
	
     void UnSet() { HC_UnSet_Line_Weight(); }
    void Show(char *text) { 
	float ew;
	HC_Show_Line_Weight(&ew);
	sprintf(text, "%f", ew);
    
    }
    void ShowNet(char *text) { 
	float ew;
	HC_Show_Net_Line_Weight(&ew);
	sprintf(text, "%f", ew);	
	}
    bool Exists() {

        if (HC_Show_Existence("LINE WEIGHT") == 1)
	{
	    float ew;
	    HC_Show_Line_Weight(&ew);
	    if (ew >=0.0f)
 		return true;
	    else return false;
	}
	return false;

    }


};



class HoopsAttributeVariableMarkerSize : public HoopsAttribute
{
public:
 
    const char * GetName() { return "VARIABLE MARKER SIZE"; }
    void Set(char *text) { HC_Set_Variable_Marker_Size(text); }
    void UnSet() { HC_UnSet_Marker_Size(); }
    void Show(char *text) { HC_Show_Variable_Marker_Size(text); }
    void ShowNet(char *text) { HC_Show_Net_Var_Marker_Size(text); }
    bool Exists() {

        if (HC_Show_Existence("MARKER SIZE") == 1)
	{
	    float ew;
	    HC_Show_Marker_Size(&ew);
	    if (ew <0.0f)
 		return true;
	    else return false;
	}
	return false;

    }


};
class HoopsAttributeMarkerSize : public HoopsAttribute
{
public:
 
    const char * GetName() { return "MARKER SIZE"; }
    void Set(char *text) { 
	float ew;
 	sscanf(text, "%f", &ew);
	HC_Set_Marker_Size(ew);	
    }
	
     void UnSet() { HC_UnSet_Marker_Size(); }
    void Show(char *text) { 
	float ew;
	HC_Show_Marker_Size(&ew);
	sprintf(text, "%f", ew);
    
    }
    void ShowNet(char *text) { 
	float ew;
	HC_Show_Net_Marker_Size(&ew);
	sprintf(text, "%f", ew);	
	}
    bool Exists() {

        if (HC_Show_Existence("MARKER SIZE") == 1)
	{
	    float ew;
	    HC_Show_Marker_Size(&ew);
	    if (ew >=0.0f)
 		return true;
	    else return false;
	}
	return false;

    }


};






class HoopsAttributeHandedness : public HoopsAttribute
{
public:
 
    const char * GetName() { return "HANDEDNESS"; }
    void Set(char *text) { HC_Set_Handedness(text); }
    void UnSet() { HC_UnSet_Handedness(); }
    void Show(char *text) { HC_Show_Handedness(text); }
    void ShowNet(char *text) { HC_Show_Net_Handedness(text); }

};

class HoopsAttributeCondition : public HoopsAttribute
{
public:
 
    const char * GetName() { return "CONDITION"; }
    void Set(char *text) { HC_Set_Conditions(text); }
    void UnSet() { HC_UnSet_Conditions(); }
    void Show(char *text) { HC_Show_Conditions(text); }
    void ShowNet(char *text) { HC_Show_Net_Conditions(text); }

};


class HoopsAttributeDriverOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "DRIVER OPTIONS"; }
    void Set(char *text) { HC_Set_Driver_Options(text); }
    void UnSet() { HC_UnSet_Driver_Options(); }
    void Show(char *text) { HC_Show_Driver_Options(text); }
    void ShowNet(char *text) { HC_Show_Net_Driver_Options(text); }

};


class HoopsAttributeUserValue : public HoopsAttribute
{
public:
 
    const char * GetName() { return "USER VALUE"; }
    void Set(char *text) { HC_Set_User_Value(1); }
    void UnSet() { HC_UnSet_User_Value(); }
    void Show(char *text) { 
	HC_POINTER_SIZED_INT value;	
	HC_Show_User_Value(&value);
	sprintf(text,"%d", value);
    }
    void ShowNet(char *text) { 
	HC_POINTER_SIZED_INT value;	
	HC_Show_Net_User_Value(&value);
	sprintf(text,"%d", value);
    }

};

class HoopsAttributeSystemOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "SYSTEM OPTIONS"; }
    void Set(char *text) { HC_Define_System_Options(text); }
    void UnSet() { ; }
    void Show(char *text) { HC_Show_System_Options(text); }
    void ShowNet(char *text) { HC_Show_System_Options(text); }

    bool Exists() {
 	HC_KEY key = HC_KOpen_Segment(".");
	HC_Close_Segment();
   	if (key <0 && HC_KShow_Owner_By_Key(key) == -1)
 	    return true;
	else
	    return false;
    }


};


class HoopsAttributeCamera : public HoopsAttribute
{
public:
    
    const char * GetName() { return "CAMERA"; }
    void Set(char *text) { 
		HPoint pos,target,up;
		float width, height, nl;
		char projection[MVO_BUFFER_SIZE];
		int count;
		count = sscanf(text, "Pos: %f %f %f Target: %f %f %f Up: %f %f %f Width: %f Height: %f Near Limit: %f Projection:%s", 
			&pos.x, &pos.y,&pos.z, 
			&target.x, &target.y, &target.z, 
			&up.x, &up.y, &up.z, &width, &height, &nl, projection);
		if (count < 12) {
			//try again in the formatting style of hmf
			count = sscanf(text, "(Camera (%f %f %f) (%f %f %f) (%f %f %f) %f %f \"%s\")",
				&pos.x, &pos.y,&pos.z, 
				&target.x, &target.y, &target.z, 
				&up.x, &up.y, &up.z, &width, &height, projection);
			char *ptr = strrchr (projection, '"');
			if (ptr)
				*ptr = '\0';
		}
		if (count < 12)
			HDB::ReportError ("parse error in HoopsAttributeCamera");
		else
			HC_Set_Camera(&pos, &target, &up, width, height, projection);
    }
    void UnSet() { HC_UnSet_Camera(); }
    void Show(char *text) 
    {
		HPoint pos,target,up;
		float width, height;
		float near_limit;
		char projection[MVO_BUFFER_SIZE];
		HC_Show_Camera(&pos, &target, &up, &width, &height, projection);
		HC_Show_Camera_Near_Limit(&near_limit);
		sprintf(text, "Pos: %f %f %f Target: %f %f %f Up: %f %f %f Width: %f Height: %f Near Limit: %f Projection:%s", pos.x, pos.y,
			pos.z, target.x, target.y, target.z, up.x, up.y, up.z, width, height, near_limit, projection);
	 	
    }
    void ShowNet(char *text) 
    {
		HPoint pos,target,up;
		float width, height;
		float near_limit;
		char projection[MVO_BUFFER_SIZE];
		HC_Show_Net_Camera(&pos, &target, &up, &width, &height, projection);
		HC_Show_Net_Camera_Near_Limit(&near_limit);

		sprintf(text, "Pos: %f %f %f Target: %f %f %f Up: %f %f %f Width: %f Height: %f Near Limit: %f Projection:%s", pos.x, pos.y,
			pos.z, target.x, target.y, target.z, up.x, up.y, up.z, width, height, near_limit, projection);
	 	
    }


};

class HoopsAttributeModellingMatrix : public HoopsAttribute
{
public:
    
    const char * GetName() { return "MODELLING MATRIX"; }
    void Set(char *text) { 
	float m[16];
 	sscanf(text, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &m[0],&m[1],&m[2],&m[3], 
	    &m[4],&m[5],&m[6],&m[7],&m[8],&m[9],&m[10],&m[11],&m[12],&m[13],&m[14],&m[15]);
  	HC_Set_Modelling_Matrix(m);
    }

    void UnSet() { HC_UnSet_Modelling_Matrix(); }

    void Show(char *text) 
    {
	float m[16];
	HC_Show_Modelling_Matrix(m);
	sprintf(text, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", m[0],m[1],m[2],m[3], 
	    m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
 	
    }
    void ShowNet(char *text) 
    {
	float m[16];
	HC_Show_Net_Modelling_Matrix(m);
	sprintf(text, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", m[0],m[1],m[2],m[3], 
	    m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
 	
    }
};

class HoopsAttributeTextureMatrix : public HoopsAttribute
{
public:
    
    const char * GetName() { return "TEXTURE MATRIX"; }
    void Set(char *text) { 
	float m[16];
 	sscanf(text, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &m[0],&m[1],&m[2],&m[3], 
	    &m[4],&m[5],&m[6],&m[7],&m[8],&m[9],&m[10],&m[11],&m[12],&m[13],&m[14],&m[15]);
  	HC_Set_Texture_Matrix(m);
    }

    void UnSet() { HC_UnSet_Texture_Matrix(); }

    void Show(char *text) 
    {
	float m[16];
	HC_Show_Texture_Matrix(m);
	sprintf(text, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", m[0],m[1],m[2],m[3], 
	    m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
 	
    }
    void ShowNet(char *text) 
    {
	float m[16];
	HC_Show_Net_Texture_Matrix(m);
	sprintf(text, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", m[0],m[1],m[2],m[3], 
	    m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
 	
    }
};

 
class HoopsGeometry
{
public:
    HoopsGeometry() { }

    virtual const char * GetName() = 0;
     virtual int Exists() {return (HC_Show_Existence(GetName())); }
    virtual void GetData(HC_KEY key, char *text) { strcpy(text, ""); }
    virtual void ModifyGeometry(HC_KEY key, const char *text) { ; }
};

class HoopsReference : public HoopsGeometry
{
public:
 
    const char * GetName() { return "REFERENCE"; }
    void GetData(HC_KEY key, char *text) 
    { 
		int count = 0;
		HC_Show_Reference_Keys_Count(key, &count);
		
		sprintf(text, "%d keys", count);
	}

};

class HoopsDefineGeometry : public HoopsGeometry
{
public:
    HoopsDefineGeometry() { }

    virtual void StartDefineSearch() = 0;
    virtual void EndDefineSearch() = 0;
    virtual int DoDefineSearch(char *text) = 0;
    virtual void ShowDefine(char *name, char *result) { ; }
    virtual void EditDefine(char *name, char *definition) { ; }
    virtual void GetNameAndDefinition(char *input, char *name, char *definition) 
    { 
	strcpy(name, input);
	strcpy(definition,"");          
    }

   
};


class HoopsGeometryShell : public HoopsGeometry
{
public:
 
    const char * GetName() { return "SHELL"; }
    void GetData(HC_KEY key, char *text) 
    { 
		int plen, flen, ts;
		int totallevel = 0;
		int low=0, high=0;
		int vert_att, edge_att, face_att;
		HC_Show_Shell_Size(key, &plen, &flen);	
		HC_Show_Shell_Face_Count(key, &flen);
		HC_Show_Shell_Tristrip_Count(key, &ts);
		for (int level=0;level <8;level++)
		{
			char text[MVO_BUFFER_SIZE];
			HC_Show_LOD_Type(key,level,text);
			if (strcmp(text,"invalid") != 0)
			totallevel = level;
		}
		sprintf(text, "Points:%d, %d Faces in %d Tristrips, LODS:%d", plen, flen, ts, totallevel); 

		vert_att=HC_Show_Existence_By_Key(key, "vertex attributes");
		edge_att=HC_Show_Existence_By_Key(key, "edge attributes");
		face_att=HC_Show_Existence_By_Key(key, "face attributes");

		HC_Show_Region_Range(key, &low, &high);
		if(high!=low)
		{
			char t2[MVO_BUFFER_SIZE];
			sprintf(t2, ", Regions: [%d, %d]", low, high);
			strcat(text, t2);
		}

		if(vert_att)
			strcat(text, " VertexAttributes");
		if(edge_att)
			strcat(text, " EdgeAttributes");
		if(face_att)
			strcat(text, " FaceAttributes");
	 }

};

class HoopsGeometryGrid : public HoopsGeometry
{
public:
 
    const char * GetName() { return "GRID"; }
    void GetData(HC_KEY key, char *text) 
    { 
		char type[MVO_BUFFER_SIZE];
		HPoint origin, ref1, ref2;
		int count1, count2;

		HC_Show_Grid(key, type, &origin, &ref1, &ref2, &count1, &count2);

		sprintf(text, "%s, %d x %d", type, count1, count2); 
	}

};
class HoopsGeometryPolyline : public HoopsGeometry
{
public:
 
    const char * GetName() { return "POLYLINE"; }

    void GetData(HC_KEY key, char *text) 
    { 
	int plen;
	HC_Show_Polyline_Count(key, &plen);	
 	sprintf(text, "Points:%d",  plen);
    }

};
class HoopsGeometrySphere : public HoopsGeometry
{
public:
 
    const char * GetName() { return "SPHERE"; }

    void GetData(HC_KEY key, char *text) 
    { 
	HPoint center,axis, ortho;
	float r;
	HC_Show_Sphere(key, &center, &r, &axis, &ortho);	
 	sprintf(text, "Center:%f %f %f, Radius: %f, Axis: %f %f %f, Ortho: %f %f %f", center.x, center.y, center.z,
	    r,axis.x,axis.y,axis.z, ortho.x, ortho.y, ortho.z);
    }

};


class HoopsGeometryMarker : public HoopsGeometry
{
public:
 
    const char * GetName() { return "MARKER"; }
};
    
class HoopsGeometryPolygon : public HoopsGeometry
{
public:
 
    const char * GetName() { return "POLYGON"; }
};

class HoopsGeometryLine : public HoopsGeometry
{
public:

    const char * GetName() { return "LINE"; }

	void GetData(HC_KEY key, char *text) 
    { 
		float xa, ya, za, xb, yb, zb;

		HC_Show_Line(key, &xa, &ya, &za, &xb, &yb, &zb);
 		sprintf(text, "Points: (%f, %f, %f), (%f, %f, %f)",  xa, ya, za, xb, yb, zb);
    }
};

class HoopsGeometryInfiniteLine : public HoopsGeometry
{
public:

    const char * GetName() { return "INFINITE LINE"; }

	void GetData(HC_KEY key, char *text) 
    { 
		float xa, ya, za, xb, yb, zb;

		HC_Show_Infinite_Line(key, &xa, &ya, &za, &xb, &yb, &zb);
 		sprintf(text, "Points: (%f, %f, %f), (%f, %f, %f)",  xa, ya, za, xb, yb, zb);
    }
};

class HoopsGeometryInfiniteRay : public HoopsGeometry
{
public:

    const char * GetName() { return "INFINITE RAY"; }

	void GetData(HC_KEY key, char *text) 
    { 
		float xa, ya, za, xb, yb, zb;

		HC_Show_Infinite_Ray(key, &xa, &ya, &za, &xb, &yb, &zb);
 		sprintf(text, "Points: (%f, %f, %f), (%f, %f, %f)",  xa, ya, za, xb, yb, zb);
    }
};
 
class HoopsGeometryCircle : public HoopsGeometry
{
public:
 
    const char * GetName() { return "CIRCLE"; }
};

class HoopsGeometryCircularChord : public HoopsGeometry
{
public:
 
    const char * GetName() { return "CIRCULAR CHORD"; }
};

class HoopsGeometryCircularWedge : public HoopsGeometry
{
public:
 
    const char * GetName() { return "CIRCULAR WEDGE"; }
};
class HoopsGeometryCuttingPlane: public HoopsGeometry
{
public:
 
    const char * GetName() { return "CUTTING PLANE"; }
};

class HoopsGeometryCircularArc : public HoopsGeometry
{
public:
 
    const char * GetName() { return "CIRCULAR ARC"; }
};
    
class HoopsGeometryNurbsCurve : public HoopsGeometry
{
public:
 
    const char * GetName() { return "NURBS CURVE"; }
};
    
class HoopsGeometryNurbsSurface : public HoopsGeometry
{
public:
 
    const char * GetName() { return "NURBS SURFACE"; }
};
class HoopsGeometryImage : public HoopsGeometry
{
public:
 
    const char * GetName() { return "IMAGE"; }
    void GetData(HC_KEY key, char *text) 
    { 
 	float x,y,z;
	char format[4096];
	int width, height;
	HC_Show_Image_Size(key, &x, &y, &z, format, &width, &height);	
 	sprintf(text, "Format: %s, W:%d H:%d, Pos: %f %f %f",format, width, height,x,y,z);
    }

};

class HoopsGeometryText : public HoopsGeometry
{
public:
 
    const char * GetName() { return "TEXT"; }
    void GetData(HC_KEY key, char *text) 
    { 
	float x,y,z;
 	char text2[MVO_BUFFER_SIZE];
	HC_Show_Text(key, &x, &y, &z, text2);	
 	sprintf(text, "Position: %f %f %f  Text: %s", x,y,z,text2); 
    }

    void ModifyGeometry(HC_KEY key, const char *text) 
    { 
	float x,y,z;
	char oldtext[MVO_BUFFER_SIZE];
   	const char *start = strstr(text, "Text: ") + strlen("Text: ");
	HC_Show_Text(key, &x,&y,&z,oldtext);
  	HC_Edit_Text(key, 0,0,0,(int)strlen(oldtext),start);
    }


};

class HoopsGeometryDistantLight : public HoopsGeometry
{
public:
 
    const char * GetName() { return "DISTANT LIGHT"; }

    void GetData(HC_KEY key, char *text) 
    { 
		H_FORMAT_TEXT data;
		HC_Open_Geometry(key);
		if (HC_Show_Existence("color")){
			char text2[MVO_BUFFER_SIZE] = {""};
			HC_Show_Color(text2);
			if(strlen(text2)){
				data.Append("Color = \"%s\"", text2);
			}
		}
		HC_Close_Geometry();
		float x, y, z;
		HC_Show_Distant_Light(key, &x, &y, &z);
		if(strlen(data)){
			data.Append(", ");
		}
		data.Append("Position = (%g, %g, %g)", x, y, z);

 		strcpy(text, data); 
    }

    void ModifyGeometry(HC_KEY key, const char *text) 
    { 
		if (strstr(text, "Color: "))
		{
    		const char *start = strstr(text, "Color: ") + strlen("Color: ");
			HC_Open_Geometry(key);
			HC_Set_Color(start);
			HC_Close_Geometry();
		}
	}

};
    
class HoopsGeometryLocalLight : public HoopsGeometry
{
public:
 
    const char * GetName() { return "LOCAL LIGHT"; }
    void GetData(HC_KEY key, char *text) 
    { 
  	char text2[MVO_BUFFER_SIZE];
	strcpy(text2,"");
	HC_Open_Geometry(key);
	if (HC_Show_Existence("color"))
		HC_Show_Color(text2);
	HC_Close_Geometry();

 	sprintf(text, "Color: %s",text2); 
    }

    void ModifyGeometry(HC_KEY key, const char *text) 
    { 
		if (strstr(text, "Color: "))
		{
    		const char *start = strstr(text, "Color: ") + strlen("Color: ");
			HC_Open_Geometry(key);
			HC_Set_Color(start);
			HC_Close_Geometry();
		}
	}
};

class HoopsGeometrySpotLight : public HoopsGeometry
{
public:
 
    const char * GetName() { return "SPOT LIGHT"; }
    void GetData(HC_KEY key, char *text) 
    { 
  		char text2[MVO_BUFFER_SIZE];
		strcpy(text2,"");
		
		HC_Open_Geometry(key);
			if (HC_Show_Existence("color"))
			{
				HC_Show_Color(text2);
				sprintf(text, "Color: %s \n",text2);
			}
			else
				strcpy(text,"");
		HC_Close_Geometry();

		HPoint pos, targ;
		float matrix[16];
		
		HC_Open_Segment_By_Key(HC_KShow_Owner_Original_Key(key));
			HC_Show_Net_Modelling_Matrix(matrix);
		HC_Close_Segment();

		HC_Show_Spot_Light(key, &pos, &targ, text2);
		HC_Compute_Transformed_Points(1, &pos, matrix, &pos);
		HC_Compute_Transformed_Points(1, &targ, matrix, &targ);
		
		sprintf(text, "%s Position=(%f, %f, %f), Target=(%f, %f, %f)%s%s", 
			text, pos.x, pos.y, pos.z, targ.x, targ.y, targ.z, 
			*text2=='\0' ? "" : ", Options=", text2);
    }

    void ModifyGeometry(HC_KEY key, const char *text) 
    { 
		if (strstr(text, "Color: "))
		{
    		const char *start = strstr(text, "Color: ") + strlen("Color: ");
			HC_Open_Geometry(key);
			HC_Set_Color(start);
			HC_Close_Geometry();
		}
	}
};


class HoopsGeometryEllipse : public HoopsGeometry
{
public:
 
    const char * GetName() { return "ELLIPSE"; }
};

class HoopsGeometryStyle : public HoopsGeometry
{
public:
 
    const char * GetName() { return "STYLE"; }
};

class HoopsGeometryNamedStyle : public HoopsGeometry
{
public:
 
    const char * GetName() { return "NAMED STYLE"; }
};

class HoopsGeometryEllipticalArc : public HoopsGeometry
{
public:
 
    const char * GetName() { return "ELLIPTICAL ARC"; }
};
class HoopsGeometryMesh : public HoopsGeometry
{
public:
 
    const char * GetName() { return "MESH"; }
	void GetData(HC_KEY key, char *text) 
    { 
		int rows, cols;
		int vert_att, edge_att, face_att;
		HC_Show_Mesh_Size(key, &rows, &cols);	

		sprintf(text, "Rows:%d Columns:%d", rows, cols);

		vert_att=HC_Show_Existence_By_Key(key, "vertex attributes");
		edge_att=HC_Show_Existence_By_Key(key, "edge attributes");
		face_att=HC_Show_Existence_By_Key(key, "face attributes");

		if(vert_att)
			strcat(text, " VertexAttributes");
		if(edge_att)
			strcat(text, " EdgeAttributes");
		if(face_att)
			strcat(text, " FaceAttributes");
	 }
};

class HoopsGeometryCylinder : public HoopsGeometry
{
public:
 
    const char * GetName() { return "CYLINDER"; }
};
class HoopsGeometryPolyCylinder : public HoopsGeometry
{
public:
 
    const char * GetName() { return "POLYCYLINDER"; }
};

class HoopsGeometryLocalTextures : public HoopsDefineGeometry
{
public:
    void StartDefineSearch() {
		HC_Begin_Local_Texture_Search();
    }

    void EndDefineSearch() {
		HC_End_Texture_Search();
    }
	
    int DoDefineSearch(char * text) 
    {
	char text1[4096];
 	int ret = HC_Find_Texture(text1);
	if (ret)
	{
	    ShowDefine(text1, text);
	}
	return (ret);
    }
    void ShowDefine(char *name, char *res)
    {
	char text[4096];
	HC_Show_Local_Texture(name, text);
	sprintf(res, "%s - %s", name, text);
    }
    
     
    void EditDefine(char *name, char *definition)
    {
	 HC_UnDefine_Local_Texture(name);
	 HC_Define_Local_Texture(name, definition);
    }

    
   

    void GetNameAndDefinition(char *input, char *name, char *definition) 
    {
	char temp[MVO_BUFFER_SIZE];
	strcpy(temp, input);
  	strcpy(definition, strstr(input, " - ")+3);
	*(strstr(temp, " - ")) = 0;
	strcpy(name, temp);
    }

    const char * GetName() { return "LOCAL TEXTURE"; }
};

class HoopsGeometryGlyph : public HoopsDefineGeometry
{
public:
    void StartDefineSearch() {
		HC_Begin_Glyph_Search();
    }

    void EndDefineSearch() {
		HC_End_Glyph_Search();
    }
	
 int DoDefineSearch(char * text) 
    {
	char text1[4096];
 	int ret = HC_Find_Glyph(text1);
	if (ret)
	{
	    ShowDefine(text1, text);
	}
	return (ret);
    }
    void ShowDefine(char *name, char *res)
    {
	int size;
	char text[4096];
	HC_Show_Glyph_Size(name,&size);
	char *glyphstring = new char[size+1];
	HC_Show_Glyph(name, glyphstring);
	MakeGlyphString(size, glyphstring, text);
 	sprintf(res, "%s - %s", name, text);
	delete [] glyphstring;
    }
    

    void MakeGlyphString(int length, char *text, char *res)
    {
	strcpy(res,"");
	for (int i=0;i<length;i++)
	{
	    char temp[128];
	    itoa(text[i], temp,10);
	    strcat(res,temp);
	    if (i<length-1)
		strcat(res," ");
	}	
    }
   

    void EditDefine(char *name, char *definition)
    {
	char res_def[4096];
	char def[4096];
	strcpy(def, definition);
	char *start = def;
	int length = 0;
	while (1)
	{
	    char *end = strstr(start, " ");
 	    if (end)	
		*end = 0;
	    char num = atoi(start);
	    res_def[length++] = num;
	    start = end+1;
	    if (!end)
		break;
	}
	HC_Define_Glyph(name, length, res_def);
    }

    void GetNameAndDefinition(char *input, char *name, char *definition) 
    {
	sscanf(input, "%s -",name);
 	strcpy(definition, strstr(input, "-")+2);
    }
    
    const char * GetName() { return "GLYPH DEFINITION"; }
};

class HoopsNamedStyleDefinition : public HoopsDefineGeometry
{
public:
    void StartDefineSearch()
	{
		HC_Begin_Named_Style_Search();
    }

    void EndDefineSearch()
	{
		HC_End_Named_Style_Search();
    }
	
	int DoDefineSearch(char * text) 
    {
		char text1[4096];
 		int ret = HC_Find_Named_Style(text1);
		if(ret)
			ShowDefine(text1, text);
		return ret;
    }
    
	void ShowDefine(char *name, char *res)
    {
		char text[4096];
		HC_Show_Named_Style(name, text);
 		sprintf(res, "%s - %s", name, text);
    }

    void EditDefine(char *name, char *definition)
    {
		HC_Define_Named_Style(name, definition);
    }

    void GetNameAndDefinition(char *input, char *name, char *definition) 
    {
		sscanf(input, "%s -",name);
 		strcpy(definition, strstr(input, "-")+2);
    }
    
    const char * GetName() { return "NAMED STYLE DEFINITION"; }
};

class HoopsGeometryLinePattern : public HoopsDefineGeometry
{
public:
    void StartDefineSearch() {
		HC_Begin_Line_Style_Search();
    }

    void EndDefineSearch() {
		HC_End_Line_Style_Search();
    }
	
    int DoDefineSearch(char * text) 
    {
	char text1[4096];
 	int ret = HC_Find_Line_Style(text1);
	if (ret)
	{
	    ShowDefine(text1, text);
	}
	return (ret);
    }
    void ShowDefine(char *name, char *res)
    {
	char text[4096];
	HC_Show_Line_Style(name, text);
	sprintf(res, "%s - %s", name, text);
    }
    
    void EditDefine(char *name, char *definition)
    {
	 HC_Define_Line_Style(name, definition);
    }

    void GetNameAndDefinition(char *input, char *name, char *definition) 
    {
	sscanf(input, "%s -",name);
 	strcpy(definition, strstr(input, "-")+2);
    }
   
    const char * GetName() { return "LINE PATTERN DEFINITION"; }
};

class HoopsShaderDefinition : public HoopsDefineGeometry
{
public:
    void StartDefineSearch()
	{
		HC_Begin_Shader_Search();
    }

    void EndDefineSearch()
	{
		HC_End_Shader_Search();
    }
	
    int DoDefineSearch(char * text) 
    {
		char name[4096];
		int ret = HC_Find_Shader(name);
		
		if(ret)
			ShowDefine(name, text);

		return (ret);
    }

    void ShowDefine(char *name, char *res)
    {
		char def[4096], source[4096];

		HC_Show_Shader(name, def, source);
		sprintf(res, "%s - %s\n{\n%s\n}", name, def, source);
    }
    
    void EditDefine(char *name, char *definition)
    {
		char def[4096]="", source[4096]="";
		int src_start=0, src_end;

		src_end = strlen(definition)-2; //\n, }
		if(src_end <= 0)
			return; //the definition is forked up
		
		while(definition[src_start] != '{' && src_start < src_end) ++src_start;
		src_start += 2; // {, \n
		if(src_start >= src_end)
			return; //the definition is forked up

		if(src_start > 3)
		{
			memcpy(def, definition, src_start-3);
			def[src_start-3] = '\0';
		}
		memcpy(source, definition+src_start, src_end-src_start);
		source[src_end-src_start] = '\0';

		HC_Define_Shader(name, def, source);
    }

    void GetNameAndDefinition(char *input, char *name, char *definition) 
    {
		sscanf(input, "%s -",name);
 		strcpy(definition, strstr(input, "-")+2);
    }
   
    const char * GetName()
	{
		return "SHADER";
	}
};


class HoopsGeometryFont : public HoopsDefineGeometry
{
public:
    void StartDefineSearch() {
 	
 		HC_Begin_Font_Search(".", "specific");
    }

    void EndDefineSearch() {
		HC_End_Font_Search();
    }
	
    int DoDefineSearch(char * text) 
    {
	return (HC_Find_Font(text));
    }

    virtual int Exists() { 
	if (HC_Show_Existence("driver options"))
	{
	    HC_KEY mainkey = HC_KCreate_Segment("/");
	    HC_KEY currentkey = HC_KCreate_Segment(".");
	    if (mainkey == currentkey)
		return false;
	    else
		return true;
	}
	return false;

    }				 
    const char * GetName() { return "Font"; }
};

#endif // !defined(AFX_HOOPSSEGMENTTREE_H__2BB1A01C_EA49_47C2_AE90_4FBA31AE9961__INCLUDED_)
