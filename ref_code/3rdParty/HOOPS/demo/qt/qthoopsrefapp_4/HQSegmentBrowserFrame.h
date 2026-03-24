#include <QFrame>
#include <QObject>
#include <QTreeWidgetItem>
#include <QTreeView>
#include <QDialog>
#include <QTextEdit>
#include "hc.h"
#include "HTools.h"		// required for MVO_BUFFER_SIZE

class HQApplication;
class QResizeEvent;
class SegmentBrowserFrame;
class HBaseView;
class segTreeListViewItem;

class segTreeListView : public QTreeWidget {

	Q_OBJECT

	public:
		segTreeListView (QWidget * p);
		HBaseView	*m_pHoopsView;

	private:
		void contextMenuEvent ( QContextMenuEvent * e ) ;


	public slots:
		void item_selection_changed(QTreeWidgetItem * i, QTreeWidgetItem* previous);
		void item_expanded(QTreeWidgetItem * i);
		void item_collapsed(QTreeWidgetItem * i);
		void item_double_clicked(QTreeWidgetItem * i);
		void OnRightClickEdit();
		void OnRightClickOptimize();
		void OnRightClickDelete();

	signals:
		void myItemDoubleClickedSignal();
};

class segTreeEditBox : public QDialog{
	Q_OBJECT

	public:
		segTreeEditBox(QWidget* p, segTreeListViewItem* i, HBaseView* b);
		void FoldAttributeText(const char *text, char *foldedtext);

	private:
		segTreeListViewItem* item;
		QTextEdit* textBox;
		struct vlist_s *m_AttributeList;
		HBaseView	*m_pHoopsView; 

	public slots:
		void ok_clicked();
		void cancel_clicked();
};

class segTreeListViewItem : public QTreeWidgetItem {

	private:
		bool leafNode;

	public:
		segTreeListViewItem(segTreeListView *parent, HC_KEY key);
		segTreeListViewItem(segTreeListViewItem *parent, HC_KEY key, bool recurse=false);
		HC_KEY m_segKey;
		void addAttributeLeaves(HC_KEY segKey, segTreeListViewItem *item);
		void addGeometryCountLeaves(HC_KEY segKey, segTreeListViewItem *item);
		char type[MVO_BUFFER_SIZE];
		bool isLeafNode();
		void setLeafNode(bool n);
};


class HQSegmentBrowserFrame : public QFrame{

	Q_OBJECT

    public:
		HQSegmentBrowserFrame(QWidget*p,  HQApplication *mw);
		HQApplication		*main_window;
		segTreeListView		*m_segTreeList;
		HC_KEY				m_segRoot;

		void populateTree ();
		void setHoopsView(HBaseView *view){m_segTreeList->m_pHoopsView = view;};
		void setSegmentRoot(HC_KEY seg){m_segRoot = seg;};

	public slots:
		void slotComboBoxActivated( int );
		void refreshButtonClicked();

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
    virtual ~HoopsAttribute(){}
};

class HoopsAttributeColor : public HoopsAttribute
{
public:
 
    const char * GetName() { return "color"; }
    void Set(char *text) { HC_Set_Color(text); }
    void UnSet() { HC_UnSet_Color(); }
    void Show(char *text) { HC_Show_Color(text); }
    void ShowNet(char *text) { HC_Show_Net_Color(text); }
};


class HoopsAttributeHeuristics : public HoopsAttribute
{
public:
 
    const char * GetName() { return "heuristics"; }
    void Set(char *text) { HC_Set_Heuristics(text); }
    void UnSet() { HC_UnSet_Heuristics(); }
    void Show(char *text) { HC_Show_Heuristics(text); }
    void ShowNet(char *text) { HC_Show_Net_Heuristics(text); }

};

class HoopsAttributeVisibility : public HoopsAttribute
{
public:
  
    const char * GetName() { return "visibility"; }
    void Set(char *text) { HC_Set_Visibility(text); }
    void UnSet() { HC_UnSet_Visibility(); }
    void Show(char *text) { HC_Show_Visibility(text); }
    void ShowNet(char *text) { HC_Show_Net_Visibility(text); }

};

class HoopsAttributeRenderingOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "rendering options"; }
    void Set(char *text) { HC_Set_Rendering_Options(text); }
    void UnSet() { HC_UnSet_Rendering_Options(); }
    void Show(char *text) { HC_Show_Rendering_Options(text); }
    void ShowNet(char *text) { HC_Show_Net_Rendering_Options(text); }

};

class HoopsAttributeWindow : public HoopsAttribute
{
public:
 
    const char * GetName() { return "window"; }

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
 
    const char * GetName() { return "clip region"; }

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
 
    const char * GetName() { return "selectability"; }
    void Set(char *text) { HC_Set_Selectability(text); }
    void UnSet() { HC_UnSet_Selectability(); }
    void Show(char *text) { HC_Show_Selectability(text); }
    void ShowNet(char *text) { HC_Show_Net_Selectability(text); }

};

class HoopsAttributeCallback : public HoopsAttribute
{
public:
 
    const char * GetName() { return "callback"; }
    void Set(char *text) { HC_Set_Callback(text); }
    void UnSet() { HC_UnSet_Callback(); }
    void Show(char *text) { HC_Show_Callback(text); }
    void ShowNet(char *text) { HC_Show_Net_Callback(text); }

};

class HoopsAttributeUserOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "user options"; }
    void Set(char *text) { HC_Set_User_Options(text); }
    void UnSet() { HC_UnSet_User_Options(); }
    void Show(char *text) { 
	int len;
	HC_Show_User_Options_Length(&len);
	char *temp = new char[len+1];
	HC_Show_User_Options(temp); 
	if (len>MVO_BUFFER_SIZE-100)
	{
	    memcpy(text, temp, MVO_BUFFER_SIZE-101);
	    text[MVO_BUFFER_SIZE-101] = 0;
	}
	else
	    strcpy(text, temp);	
	delete [] temp;
	}
    void ShowNet(char *text) { HC_Show_Net_User_Options(text); }

};

class HoopsAttributeTextFont : public HoopsAttribute
{
public:
 
    const char * GetName() { return "text font"; }
    void Set(char *text) { HC_Set_Text_Font(text); }
    void UnSet() { HC_UnSet_Text_Font(); }
    void Show(char *text) { HC_Show_Text_Font(text); }
    void ShowNet(char *text) { HC_Show_Net_Text_Font(text); }

};
class HoopsAttributeWindowPattern : public HoopsAttribute
{
public:
 
    const char * GetName() { return "window pattern"; }
    void Set(char *text) { HC_Set_Window_Pattern(text); }
    void UnSet() { HC_UnSet_Window_Pattern(); }
    void Show(char *text) { HC_Show_Window_Pattern(text); }
    void ShowNet(char *text) { HC_Show_Net_Window_Pattern(text); }

};

class HoopsAttributeTextAlignment : public HoopsAttribute
{
public:
 
    const char * GetName() { return "text alignment"; }
    void Set(char *text) { HC_Set_Text_Alignment(text); }
    void UnSet() { HC_UnSet_Text_Alignment(); }
    void Show(char *text) { HC_Show_Text_Alignment(text); }
    void ShowNet(char *text) { HC_Show_Net_Text_Alignment(text); }

};

class HoopsAttributeVariableEdgeWeight : public HoopsAttribute
{
public:
 
    const char * GetName() { return "variable edge weight"; }
    void Set(char *text) { HC_Set_Variable_Edge_Weight(text); }
    void UnSet() { HC_UnSet_Edge_Weight(); }
    void Show(char *text) { HC_Show_Variable_Edge_Weight(text); }
    void ShowNet(char *text) { HC_Show_Net_Var_Edge_Weight(text); }
    bool Exists() {

        if (HC_Show_Existence("edge weight") == 1)
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
 
    const char * GetName() { return "edge weight"; }
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

        if (HC_Show_Existence("edge weight") == 1)
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
 
    const char * GetName() { return "variable line weight"; }
    void Set(char *text) { HC_Set_Variable_Line_Weight(text); }
    void UnSet() { HC_UnSet_Line_Weight(); }
    void Show(char *text) { HC_Show_Variable_Line_Weight(text); }
    void ShowNet(char *text) { HC_Show_Net_Var_Line_Weight(text); }
    bool Exists() {

        if (HC_Show_Existence("line weight") == 1)
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
 
    const char * GetName() { return "line pattern"; }
    void Set(char *text) { HC_Set_Line_Pattern(text); }
    void UnSet() { HC_UnSet_Line_Pattern(); }
    void Show(char *text) { HC_Show_Line_Pattern(text); }
    void ShowNet(char *text) { HC_Show_Net_Line_Pattern(text); }

};


class HoopsAttributeLineWeight : public HoopsAttribute
{
public:
 
    const char * GetName() { return "line weight"; }
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

        if (HC_Show_Existence("line weight") == 1)
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
 
    const char * GetName() { return "variable marker size"; }
    void Set(char *text) { HC_Set_Variable_Marker_Size(text); }
    void UnSet() { HC_UnSet_Marker_Size(); }
    void Show(char *text) { HC_Show_Variable_Marker_Size(text); }
    void ShowNet(char *text) { HC_Show_Net_Var_Marker_Size(text); }
    bool Exists() {

        if (HC_Show_Existence("marker size") == 1)
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
 
    const char * GetName() { return "marker size"; }
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

        if (HC_Show_Existence("marker size") == 1)
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
 
    const char * GetName() { return "handedness"; }
    void Set(char *text) { HC_Set_Handedness(text); }
    void UnSet() { HC_UnSet_Handedness(); }
    void Show(char *text) { HC_Show_Handedness(text); }
    void ShowNet(char *text) { HC_Show_Net_Handedness(text); }

};

class HoopsAttributeCondition : public HoopsAttribute
{
public:
 
    const char * GetName() { return "condition"; }
    void Set(char *text) { HC_Set_Conditions(text); }
    void UnSet() { HC_UnSet_Conditions(); }
    void Show(char *text) { HC_Show_Conditions(text); }
    void ShowNet(char *text) { HC_Show_Net_Conditions(text); }

};


class HoopsAttributeDriverOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "driver options"; }
    void Set(char *text) { HC_Set_Driver_Options(text); }
    void UnSet() { HC_UnSet_Driver_Options(); }
    void Show(char *text) { HC_Show_Driver_Options(text); }
    void ShowNet(char *text) { HC_Show_Net_Driver_Options(text); }

};



class HoopsAttributeUserValue : public HoopsAttribute
{
public:
 
    const char * GetName() { return "user value"; }
    void Set(char *text) { HC_Set_User_Value(1); }
    void UnSet() { HC_UnSet_User_Value(); }
    void Show(char *text) { 
	HC_POINTER_SIZED_INT value;	
	HC_Show_User_Value(&value);
	sprintf(text,"%ld", value);
    }
    void ShowNet(char *text) { 
	HC_POINTER_SIZED_INT value;	
	HC_Show_Net_User_Value(&value);
	sprintf(text,"%ld", value);
    }

};



class HoopsAttributeSystemOptions : public HoopsAttribute
{
public:
 
    const char * GetName() { return "system options"; }
    void Set(char *text) { HC_Define_System_Options(text); }
    void UnSet() { ; }
    void Show(char *text) { HC_Show_System_Options(text); }
    void ShowNet(char *text) { HC_Show_System_Options(text); }

    bool Exists() {
 	HC_KEY key = HC_KOpen_Segment(".");
	HC_Close_Segment();
  	if (HC_KShow_Owner_By_Key(key) == -1)
 	    return true;
	else
	    return false;
    }


};


class HoopsAttributeCamera : public HoopsAttribute
{
public:
    
    const char * GetName() { return "camera"; }
    void Set(char *text) { 
	HPoint pos,target,up;
	float width, height;
	char projection[MVO_BUFFER_SIZE];
 	sscanf(text, "Pos: %f %f %f Target: %f %f %f Up: %f %f %f Width: %f Height: %f Projection:%s", &pos.x, &pos.y,
	    &pos.z, &target.x, &target.y, &target.z, &up.x, &up.y, &up.z, &width, &height, projection);
	HC_Set_Camera(&pos, &target, &up, width, height, projection);
    }
    void UnSet() { HC_UnSet_Camera(); }
    void Show(char *text) 
    {
	HPoint pos,target,up;
	float width, height;
	char projection[MVO_BUFFER_SIZE];
	HC_Show_Camera(&pos, &target, &up, &width, &height, projection);
	sprintf(text, "Pos: %f %f %f Target: %f %f %f Up: %f %f %f Width: %f Height: %f Projection:%s", pos.x, pos.y,
	    pos.z, target.x, target.y, target.z, up.x, up.y, up.z, width, height, projection);
 	
    }
    void ShowNet(char *text) 
    {
	HPoint pos,target,up;
	float width, height;
	char projection[MVO_BUFFER_SIZE];
	HC_Show_Net_Camera(&pos, &target, &up, &width, &height, projection);
	sprintf(text, "Pos: %f %f %f Target: %f %f %f Up: %f %f %f Width: %f Height: %f Projection:%s", pos.x, pos.y,
	    pos.z, target.x, target.y, target.z, up.x, up.y, up.z, width, height, projection);
 	
    }


};

class HoopsAttributeModellingMatrix : public HoopsAttribute
{
public:
    
    const char * GetName() { return "modelling matrix"; }
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



