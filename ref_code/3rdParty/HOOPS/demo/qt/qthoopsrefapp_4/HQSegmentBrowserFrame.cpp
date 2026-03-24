#ifdef check
#undef check
#endif

#include <QtGui>
#include <QtCore>


#include "HQSegmentBrowserFrame.h" 
#include "HBaseView.h"
#include "HBaseModel.h"
#include "HMySelectionSet.h"
#include "vlist.h"

//icons
#include "./images/fileopen.xpm"
#include "./images/fileclosed.xpm"
#include "./images/attributeicon.xpm"
#include "./images/geomicon.xpm"

HQSegmentBrowserFrame::HQSegmentBrowserFrame(QWidget *p,  HQApplication *mw):QFrame(p)
{


	QVBoxLayout * vBox = new QVBoxLayout;

	QComboBox *comboBox = new QComboBox( this );
	comboBox->insertItem(0, "File-only Segment Tree");
	comboBox->insertItem(1, "System-wide Segment Tree");

	vBox->addSpacing(10);
	vBox->addWidget(comboBox);
	vBox->addSpacing(5);

	QPushButton *refreshButton = new QPushButton( "Refresh", this );
	vBox->addWidget(refreshButton, 0, 0);
	vBox->addSpacing(10);

	m_segTreeList = new segTreeListView( this );
	vBox->addWidget(m_segTreeList);

	setLayout(vBox);
	connect( comboBox, SIGNAL( activated( int ) ), this, SLOT( slotComboBoxActivated( int ) ) );
	connect( refreshButton, SIGNAL( clicked() ), this, SLOT( refreshButtonClicked() ) );
}

void HQSegmentBrowserFrame::refreshButtonClicked()
{
	populateTree();
}

void HQSegmentBrowserFrame::slotComboBoxActivated( int s)
{
	
	if (s == 0)
		m_segRoot = m_segTreeList->m_pHoopsView->GetModel()->GetModelKey();
	else
	{
		m_segRoot= HC_KOpen_Segment("/");
		HC_Close_Segment();
	}
	populateTree();
}

void HQSegmentBrowserFrame::populateTree ()
{
	m_segTreeList->clear();
	segTreeListViewItem *leaf = new segTreeListViewItem(m_segTreeList, m_segRoot);
	leaf=leaf;
}


segTreeListView::segTreeListView(QWidget * p):QTreeWidget(p) 
{
	setColumnCount(1);
	QStringList headers;
	headers << tr("Segment Hierarchy");
	setHeaderLabels(headers);

	m_pHoopsView = 0;
	setFrameStyle(QFrame::StyledPanel);
	header()->setClickable( FALSE );
	setRootIsDecorated( TRUE );

	connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(item_expanded(QTreeWidgetItem*))); 
	connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(item_collapsed(QTreeWidgetItem*))); 
	connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(item_selection_changed(QTreeWidgetItem*, QTreeWidgetItem*))); 
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(item_double_clicked(QTreeWidgetItem*)));
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SIGNAL(myItemDoubleClickedSignal()));
}


void segTreeListView::item_double_clicked(QTreeWidgetItem* i){
	
	if ( ((segTreeListViewItem*)i)->isLeafNode())
	{
		segTreeEditBox* b;
		b = new segTreeEditBox(this, (segTreeListViewItem*)i, m_pHoopsView);
	}
}

void segTreeListView::OnRightClickEdit(){
	segTreeListViewItem* i = (segTreeListViewItem*)currentItem();
	item_double_clicked(i);
}

void segTreeListView::OnRightClickOptimize(){
	segTreeListViewItem* item = (segTreeListViewItem*)currentItem();
	
	HC_Open_Segment_By_Key(item->m_segKey);{
		HC_Optimize_Segment_Tree(".",
								 "collapse matrices = on,"
								 "discard user data = on,"
								 "expand includes = on,"
								 "generate mapping = on,"
								 "merge shells = on,"
								 "reorganize = (color = on, spatial = on)"
			);
	}HC_Close_Segment();
	m_pHoopsView->Update();
}

void segTreeListView::OnRightClickDelete(){
	//hmmm...  how to delete a segment?
	segTreeListViewItem* item = (segTreeListViewItem*)currentItem();
	
	//setItemHidden(item, true);

	if(item->isLeafNode()){
		struct vlist_s *m_AttributeList = new_vlist(malloc, free);

			vlist_add_last(m_AttributeList,new HoopsAttributeColor);
			vlist_add_last(m_AttributeList,new HoopsAttributeVisibility);
			vlist_add_last(m_AttributeList,new HoopsAttributeSelectability);
			vlist_add_last(m_AttributeList,new HoopsAttributeCallback);
			vlist_add_last(m_AttributeList,new HoopsAttributeRenderingOptions);
			vlist_add_last(m_AttributeList,new HoopsAttributeUserOptions);
			vlist_add_last(m_AttributeList,new HoopsAttributeCamera);
			vlist_add_last(m_AttributeList,new HoopsAttributeModellingMatrix);
			vlist_add_last(m_AttributeList,new HoopsAttributeHeuristics);
			vlist_add_last(m_AttributeList,new HoopsAttributeTextFont);
			vlist_add_last(m_AttributeList,new HoopsAttributeDriverOptions);
			vlist_add_last(m_AttributeList,new HoopsAttributeSystemOptions);
			vlist_add_last(m_AttributeList,new HoopsAttributeHandedness);
			vlist_add_last(m_AttributeList,new HoopsAttributeUserValue);
			vlist_add_last(m_AttributeList,new HoopsAttributeWindow);
			vlist_add_last(m_AttributeList,new HoopsAttributeClipRegion);
			vlist_add_last(m_AttributeList,new HoopsAttributeVariableEdgeWeight);
			vlist_add_last(m_AttributeList,new HoopsAttributeEdgeWeight);
			vlist_add_last(m_AttributeList,new HoopsAttributeVariableLineWeight);
			vlist_add_last(m_AttributeList,new HoopsAttributeLineWeight);
			vlist_add_last(m_AttributeList,new HoopsAttributeVariableMarkerSize);
			vlist_add_last(m_AttributeList,new HoopsAttributeMarkerSize);
			vlist_add_last(m_AttributeList,new HoopsAttributeCondition);
			vlist_add_last(m_AttributeList,new HoopsAttributeTextAlignment);
			vlist_add_last(m_AttributeList,new HoopsAttributeWindowPattern);
			vlist_add_last(m_AttributeList,new HoopsAttributeLinePattern);

		
		START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
		   if (strcmp(item->type, temp->GetName()) == 0)
		{
			HC_Open_Segment_By_Key(item->m_segKey);
				temp->UnSet();
			HC_Close_Segment();
			setItemHidden(item, true);
			m_pHoopsView->Update();
			break;
		}
		END_LIST_ITERATION(m_AttributeList);
	}
	else{
		HC_Delete_By_Key(item->m_segKey);
		setItemHidden(item, true);
		m_pHoopsView->Update();
	}
}

//right-click menu
void segTreeListView::contextMenuEvent ( QContextMenuEvent * e ) {
	QMenu * s = new QMenu();
	QAction* action;

	segTreeListViewItem* i = (segTreeListViewItem*)currentItem();

	if ( ((segTreeListViewItem*)i)->isLeafNode()) {
		action = s->addAction( "Edit", this , SLOT(OnRightClickEdit()));
	}
	action = s->addAction( "Optimize", this, SLOT(OnRightClickOptimize()));
	action = s->addAction( "Delete Segment", this , SLOT(OnRightClickDelete()));
	s->exec(QCursor::pos());
}

segTreeEditBox::segTreeEditBox(QWidget* p, segTreeListViewItem* i, HBaseView* b):QDialog(p){
		m_pHoopsView = b;
		item = (segTreeListViewItem*) ((QTreeWidget*)p)->currentItem();
		QVBoxLayout* popupLayout = new QVBoxLayout;
		QFrame* buttonBox = new QFrame;
		QHBoxLayout* buttonLayout = new QHBoxLayout;
		QPushButton* ok = new QPushButton("OK");
		QPushButton* cancel = new QPushButton("Cancel");

		connect(ok, SIGNAL(clicked()), this, SLOT(ok_clicked()));
		connect(cancel, SIGNAL(clicked()), this, SLOT(cancel_clicked()));

		buttonLayout->addWidget(ok);
		buttonLayout->addWidget(cancel);
		buttonBox->setLayout(buttonLayout);

		textBox = new QTextEdit();
			textBox->insertPlainText(i->text(0));
			popupLayout->addWidget(textBox);
			popupLayout->addWidget(buttonBox);
		setLayout(popupLayout);

		setVisible(true);

		m_AttributeList = new_vlist(malloc, free);

		vlist_add_last(m_AttributeList,new HoopsAttributeColor);
		vlist_add_last(m_AttributeList,new HoopsAttributeVisibility);
		vlist_add_last(m_AttributeList,new HoopsAttributeSelectability);
		vlist_add_last(m_AttributeList,new HoopsAttributeCallback);
		vlist_add_last(m_AttributeList,new HoopsAttributeRenderingOptions);
		vlist_add_last(m_AttributeList,new HoopsAttributeUserOptions);
		vlist_add_last(m_AttributeList,new HoopsAttributeCamera);
		vlist_add_last(m_AttributeList,new HoopsAttributeModellingMatrix);
		vlist_add_last(m_AttributeList,new HoopsAttributeHeuristics);
		vlist_add_last(m_AttributeList,new HoopsAttributeTextFont);
		vlist_add_last(m_AttributeList,new HoopsAttributeDriverOptions);
		vlist_add_last(m_AttributeList,new HoopsAttributeSystemOptions);
		vlist_add_last(m_AttributeList,new HoopsAttributeHandedness);
		vlist_add_last(m_AttributeList,new HoopsAttributeUserValue);
		vlist_add_last(m_AttributeList,new HoopsAttributeWindow);
		vlist_add_last(m_AttributeList,new HoopsAttributeClipRegion);
		vlist_add_last(m_AttributeList,new HoopsAttributeVariableEdgeWeight);
		vlist_add_last(m_AttributeList,new HoopsAttributeEdgeWeight);
		vlist_add_last(m_AttributeList,new HoopsAttributeVariableLineWeight);
		vlist_add_last(m_AttributeList,new HoopsAttributeLineWeight);
		vlist_add_last(m_AttributeList,new HoopsAttributeVariableMarkerSize);
		vlist_add_last(m_AttributeList,new HoopsAttributeMarkerSize);
		vlist_add_last(m_AttributeList,new HoopsAttributeCondition);
		vlist_add_last(m_AttributeList,new HoopsAttributeTextAlignment);
		vlist_add_last(m_AttributeList,new HoopsAttributeWindowPattern);
		vlist_add_last(m_AttributeList,new HoopsAttributeLinePattern);
}

void segTreeEditBox::FoldAttributeText(const char *text, char *foldedtext) 
{
    const char *res = strstr(text, "<");
    const char *res2 = strstr(text, ">");
    if (!res || !res2){
		res = text;
        strcpy(foldedtext, res);
    }
    else{    
		strcpy(foldedtext, res+1);
		if (foldedtext[strlen(foldedtext)-1] == '>') foldedtext[strlen(foldedtext)-1] = 0;
	}
}

void segTreeEditBox::cancel_clicked(){
	this->close();
}

void segTreeEditBox::ok_clicked(){

	// de-select
	HSelectionSet *selection;
	selection = (HMySelectionSet *)m_pHoopsView->GetSelection();
	selection->DeSelectAll();
	//

	char text[MVO_BUFFER_SIZE];

	FoldAttributeText(textBox->toPlainText().toLatin1(), text); 
	START_LIST_ITERATION(HoopsAttribute, m_AttributeList)	   
	   if (strcmp(item->type, temp->GetName()) == 0)
	{
		HC_Open_Segment_By_Key(item->m_segKey);
		temp->Set(text);
 		HC_Close_Segment();
		item->setText(0, textBox->toPlainText());
		

		m_pHoopsView->Update();
		//char final[4096];
	    //    ExtendAttributeText(temp->GetName(), text, final);

		//item->ModifyText(final);
		//m_pView->Update();
		break;
	}
	END_LIST_ITERATION(m_AttributeList);

	//re-select:
	selection->Select(item->m_segKey, "", 0, 0, true);

	this->close();
}

void segTreeListView::item_expanded(QTreeWidgetItem * i)
{
	if(!i) 
		return;

	QPixmap *segmentOpenIcon= new QPixmap( (const char**)fileopen );
	i->setIcon(0,  QIcon(*segmentOpenIcon));
}

void segTreeListView::item_collapsed(QTreeWidgetItem * i)
{
	if(!i) 
		return;

	QPixmap *segmentClosedIcon= new QPixmap( (const char**)fileclosed );
	i->setIcon(0, QIcon(*segmentClosedIcon));
}


void segTreeListView::item_selection_changed(QTreeWidgetItem * i, QTreeWidgetItem* previous)
{
	if(!i) 
		return; 

	
	if(!((segTreeListViewItem*)i)->isLeafNode())
	{
		HC_KEY key = ((segTreeListViewItem *)i)->m_segKey;

		// now select the entity
		HSelectionSet *selection;
		selection = (HMySelectionSet *)m_pHoopsView->GetSelection();
		selection->DeSelectAll();
		if (!selection->IsSelected(key))
			selection->Select(key, 0, 0, true);
		m_pHoopsView->Update();
	}
}


segTreeListViewItem::segTreeListViewItem( segTreeListView *parent, HC_KEY key) : QTreeWidgetItem( parent )
{
	m_segKey = key;
	char temp[512];
	leafNode = false;
	
	HC_Show_Segment(m_segKey, temp);

	char segname[256];
	sprintf(segname, " %s", temp);
	setText(0, segname);

	QPixmap *segmentClosedIcon= new QPixmap( (const char**)fileclosed );
	setIcon(0, QIcon(*segmentClosedIcon));

	char type[80];
	HC_KEY segKey;

	
	HC_Open_Segment_By_Key(m_segKey);
		HC_Begin_Contents_Search(".", "segments");
			while (HC_Find_Contents(type, &segKey)){
				new segTreeListViewItem(this, segKey, true);
			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	
	addGeometryCountLeaves(m_segKey, this);
	addAttributeLeaves(m_segKey, this);
	
	
}


segTreeListViewItem::segTreeListViewItem( segTreeListViewItem *parent, HC_KEY key, bool recurse) : QTreeWidgetItem( parent )
{
	m_segKey = key;
	char temp[512], segName[512];
	leafNode = false;
	
	if( HC_Show_Existence_By_Key(key, "self")){
		HC_Show_Key_Type(key, temp);
		if(strcmp(temp, "segment")==0){
		
			HC_Show_Segment(key, temp);
			HC_Parse_String(temp, "/", -1, segName);
			sprintf(temp, " %s", segName);
			setText(0, temp);

			if (recurse){
				QPixmap *segmentClosedIcon= new QPixmap( (const char**)fileclosed );
				setIcon(0, QIcon(*segmentClosedIcon));
			}

			char type[80];
			HC_KEY segKey;

			if(recurse){
				HC_Open_Segment_By_Key(m_segKey);
					HC_Begin_Contents_Search(".", "segments");
						while (HC_Find_Contents(type, &segKey)){
							new segTreeListViewItem(this, segKey, true);
						}
					HC_End_Contents_Search();
				HC_Close_Segment();
			
				addGeometryCountLeaves(m_segKey, this);
				// put in the attribute strings
				addAttributeLeaves(m_segKey, this);
			}
		}
	}


}

bool segTreeListViewItem::isLeafNode(){
	return leafNode;
}

void segTreeListViewItem::setLeafNode(bool n){
	leafNode = n;
}

void segTreeListViewItem::addAttributeLeaves(HC_KEY segKey, segTreeListViewItem *item)
{
	char type[80];
	HC_KEY tempKey;
	
	HC_Open_Segment_By_Key(segKey);
		HC_Begin_Contents_Search(".", "attributes, includes");
			while (HC_Find_Contents(type, &tempKey))
			{
				segTreeListViewItem *attributeLeaf = new segTreeListViewItem(item, segKey);
				strcpy(attributeLeaf->type, type);
				attributeLeaf->setLeafNode(true);
				//QPixmap *segmentAttributeIcon= new QPixmap( "./images/attributeicon.png");
				QPixmap *segmentAttributeIcon= new QPixmap( (const char**)attributeicon);
				attributeLeaf->setIcon(0,  QIcon(*segmentAttributeIcon));


				char attributeString[4096], temp[4096];

				if (streq (type, "modelling matrix"))
					{
						float mm[16];
						HC_Show_Modelling_Matrix(mm);
						int size=0;
						char *location = attributeString;
						size = sprintf(location, "Modelling Matrix <");
						for (int i=0; i<16; i++)
							size += sprintf(&location[size], "%f ", mm[i]);
						sprintf(&location[size], ">");	
					}
				else if (streq (type, "callback"))
					{
						HC_Show_Callback(temp);
						sprintf(attributeString, "Callback <%s>", temp);
					}
				else if (streq (type, "clip region"))
					{
						int loops, total;
						char spec[MVO_BUFFER_SIZE];
 						HC_Show_Clip_Region_Size(&loops, &total, spec);
						sprintf(attributeString, "Clip Regions < Loops:%d Total:%d Specs:%s >", loops, total, spec);
 					}
				else if (streq (type, "user options"))
					{
						HC_Show_User_Options(temp);
						sprintf(attributeString, "User Options <%s>", temp);
					}
				else if (streq (type, "user value"))
					{
						HC_POINTER_SIZED_INT value;
						HC_Show_User_Value(&value);
						sprintf(attributeString, "User Value <%ld>", value);
					}
				else if (streq (type, "camera"))
					{
						sprintf(attributeString, "Locally Set Camera");
					}
				else if (streq (type, "window"))
					{
						float left, right, top, bottom;
						HC_Show_Window(&left, &right, &top, &bottom);
						sprintf(attributeString, "Window <%f, %f, %f, %f>", left, right, bottom, top);
					}
				else if (streq (type, "window pattern"))
					{
						HC_Show_Window_Pattern(temp);
						sprintf(attributeString, "Window Pattern <%s>", temp);
					}
				else if (streq (type, "color"))
					{
						HC_Show_Color(temp);
						sprintf(attributeString, "Color <%s>", temp);
					}
				else if (streq (type, "visibility"))
					{
						HC_Show_Visibility(temp);
						sprintf(attributeString, "Visibility <%s>", temp);
					}
				else if (streq (type, "rendering options"))
					{
						HC_Show_Rendering_Options(temp);
						sprintf(attributeString, "Rendering Options <%s>", temp);
					}
				else if (streq (type, "heuristics"))
					{
						HC_Show_Heuristics(temp);
						sprintf(attributeString, "Heuristics <%s>", temp);
					}
				else if (streq (type, "driver options"))
					{
						HC_Show_Driver_Options(temp);
						sprintf(attributeString, "Driver Options <%s>", temp);
					}
				else if (streq (type, "include"))
					{
						HC_Show_Include_Segment(tempKey, temp);
						sprintf(attributeString, "Include <%s>", temp);
						//attributeLeaf = new segTreeListViewItem(item, tempKey, true);
						//strcpy(attributeLeaf->type, type);
					}
				else if (streq (type, "color map"))
					{
						int count;
						HC_Show_Color_Map_Count(&count);
						sprintf(attributeString, "Color Map <number of entries:%d>", count);
					}
				else if (streq (type, "text font"))
					{
						HC_Show_Text_Font(temp);
						sprintf(attributeString, "Text Font <%s>", temp);
					}
				else if (streq (type, "text alignment"))
					{
						HC_Show_Text_Alignment(temp);
						sprintf(attributeString, "Text Alignment <%s>", temp);
					}
				else if (streq (type, "text spacing"))
					{
						float spacing;
						HC_Show_Text_Spacing(&spacing);
						sprintf(attributeString, "Text Spacing <%f>", spacing);
					}
				else if (streq (type, "text path"))
					{
						float x, y,z;
						HC_Show_Text_Path(&x, &y, &z);
						sprintf(attributeString, "Text Path <%f %f %f>", x, y, z);
					}
				else if (streq (type, "handedness"))
					{
						HC_Show_Handedness(temp);
						sprintf(attributeString, "Handedness <%s>", temp);
					}
				else if (streq (type, "selectability"))
					{
						HC_Show_Selectability(temp);
						sprintf(attributeString, "Selectability <%s>", temp);
					}
				else if (streq (type, "marker size"))
					{
						float size;
						HC_Show_Marker_Size(&size);
						sprintf(attributeString, "Marker Size <%f>", size);
					}
				else if (streq (type, "marker symbol"))
					{
						HC_Show_Marker_Symbol(temp);
						sprintf(attributeString, "Marker Symbol <%s>", temp);
					}
				else if (streq (type, "edge weight"))
					{
						float weight;
						HC_Show_Edge_Weight(&weight);
						sprintf(attributeString, "Edge Weight <%f>", weight);
					}
				else if (streq (type, "line weight"))
					{
						float weight;
						HC_Show_Line_Weight(&weight);
						sprintf(attributeString, "Line Weight <%f>", weight);
					}
				else if (streq (type, "edge pattern"))
					{
						HC_Show_Edge_Pattern(temp);
						sprintf(attributeString, "Edge Pattern <%s>", temp);
					}
				else if (streq (type, "line pattern"))
					{
						HC_Show_Line_Pattern(temp);
						sprintf(attributeString, "Line Pattern <%s>", temp);
					}
				else if (streq (type, "face pattern"))
					{
						HC_Show_Face_Pattern(temp);
						sprintf(attributeString, "Face Pattern <%s>", temp);
					}
				else if (streq (type, "window pattern"))
					{
						HC_Show_Window_Pattern(temp);
						sprintf(attributeString, "Window Pattern <%s>", temp);
					}
				else if (streq (type, "driver"))
					{
						sprintf(attributeString, "Driver Instance");
					}
				else if (streq (type, "style"))
					{
						sprintf(attributeString, "Styled Segment");
					}
				else if (streq (type, "conditions"))
					{
						HC_Show_Conditions(temp);
						sprintf(attributeString, "Conditions <%s>", temp);
					}
				else if (streq (type, "clip region"))
					{
						sprintf(attributeString, "Clip Region");
					}
				else if (streq (type, "texture matrix"))
					{
						sprintf(attributeString, "Texture Matrix");
					}
				else if (streq (type, "streaming mode"))
					{
						HC_Show_Streaming_Mode(temp);
						sprintf(attributeString, "Streaming Mode <%s>", temp);
					}
				else if (streq (type, "window frame"))
					{
						HC_Show_Window_Frame(temp);
						sprintf(attributeString, "Window Frame <%s>", temp);
					}
				else
					{
						sprintf(attributeString, "Unknown Attribute Type");
					}
				attributeLeaf->setText(0, attributeString);
			}
		HC_End_Contents_Search();
	HC_Close_Segment();
}

void segTreeListViewItem::addGeometryCountLeaves(HC_KEY segKey, segTreeListViewItem *item)
{
	long	TotalSegments = 0;	 
	long	TotalCircle = 0;		 
	long	TotalCircularArc = 0;	 
	long	TotalCircularChord = 0;
	long	TotalCircularWedge = 0;
	long	TotalEllipse =0;		
	long	TotalEllipticalArc = 0;
	long	TotalGrid=0;		
	long	TotalImage = 0;		
	long	TotalLine = 0;				
	long	TotalMarker = 0;		
	long	TotalMesh = 0;		
	long	TotalPolygon = 0;		
	long	TotalPolyline = 0;	
	long	TotalShell = 0;		
	long	TotalText = 0;		
   	long	TotalSpotLight = 0;	
   	long	TotalDistantLight = 0;
	long	TotalLocalLight = 0;	
	long	TotalCuttingPlane = 0;
	long	TotalFaces = 0; 
	long	TotalVertices = 0;
	long	TotalTriangles = 0;
	long	TotalNurbsSurface = 0;
	long	TotalNurbsCurve = 0;
	long	TotalPolycylinder = 0;

	char type[80];
	HC_KEY key;

	HC_Open_Segment_By_Key(segKey);
		HC_Begin_Contents_Search(".", "geometry");
			while (HC_Find_Contents(type, &key))
			{
				if (streq (type, "circle")) {
					TotalCircle++;
				}
				else if (streq (type, "circular arc")) {
					TotalCircularArc++;
				}
				else if (streq (type, "circular chord")) {
					TotalCircularChord++;
				}
				else if (streq (type, "circular wedge")) {
					TotalCircularWedge++;
				}
				else if (streq (type, "cutting plane")) {
					TotalCuttingPlane++;
				}
				else if (streq (type, "distant_light")) {
					TotalDistantLight++;
				}
				else if (streq (type, "ellipse")) {
					TotalEllipse++;
				}
				else if (streq (type, "elliptical arc")) {
					TotalEllipticalArc++;
				}
				else if (streq (type, "grid")) {
					TotalGrid++;
				}
				else if (streq (type, "image")) {
					TotalImage++; 
				} 
				else if (streq (type, "line")) {
					TotalLine++; 
				} 
				else if (streq (type, "local light")) {
					TotalLocalLight++;
				}
				else if (streq (type, "marker")) { 
					TotalMarker++; 
				} 
				else if (streq (type, "mesh")) { 
					int        rows, columns;

					HC_Show_Mesh_Size (key, &rows, &columns);
					TotalFaces += (rows - 1) * (columns -1);
					TotalMesh++;
					TotalVertices += rows * columns;
					TotalTriangles += 2 * (rows - 1) * (columns -1);
				}
				else if (streq (type, "polygon")) {
					int count;

					TotalPolygon++;
					TotalFaces++;

					HC_Show_Polygon_Count (key, &count);
					TotalVertices += count;

					TotalTriangles += count - 2;
				}
				else if (streq (type, "polyline")) {
					TotalPolyline++;
				}
				else if (streq (type, "shell")) {
         
					 TotalShell++;

					// obtain totals for shell components
					int face_count = 0;
					int vertex_count = 0;
					int triangle_count = 0;

					HUtility::CountShellData (key, &face_count, &vertex_count, &triangle_count);        
        
					TotalFaces        += face_count;  
					TotalVertices     += vertex_count;
					TotalTriangles    += triangle_count;
				}
				else if (streq (type, "spot light")) {
					TotalSpotLight++;
				}
				else if (streq (type, "segment")) {
					TotalSegments++;
				}
				else if (streq (type, "text")) {
					TotalText++;
				}
				else if (streq (type, "nurbs curve")) {
					TotalNurbsCurve++;
				}
				else if (streq (type, "nurbs surface")) {
					TotalNurbsSurface++;
				}
				else if (streq (type, "polycylinder")) {
					TotalPolycylinder++;
				}

			}
		HC_End_Contents_Search();
	HC_Close_Segment();

	char geomString[1024];

	if (TotalSegments > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Segment Count : %ld", TotalSegments);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalMarker > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Marker Count : %ld", TotalMarker);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalImage > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Image Count : %ld", TotalImage);
		geomLeaf->setText(0, geomString);
		//QPixmap *segmentGeomIcon= new QPixmap( "./images/geomicon.png");
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalLine > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Line Count : %ld", TotalLine);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalPolyline > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Polyline Count : %ld", TotalPolyline);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalCircularArc > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Circular Arc Count : %ld", TotalCircularArc);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalEllipticalArc > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Elliptical Arc Count : %ld", TotalEllipticalArc);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalNurbsCurve > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "NURBS Curve Count : %ld", TotalNurbsCurve);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalCircle > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Circle Count : %ld", TotalCircle);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalCircularChord > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Chircular Chord Count : %ld", TotalCircularChord);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalCircularWedge > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Circular Wedge Count : %ld", TotalCircularWedge);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalEllipse > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Ellipse Count : %ld", TotalEllipse);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalGrid > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Grid Count : %ld", TotalGrid);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalPolygon > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Polygon Count : %ld", TotalPolygon);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalMesh > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Mesh Count : %ld", TotalMesh);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalShell > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Shell Count : %ld", TotalShell);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalNurbsSurface > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "NURBS Surface Count : %ld", TotalNurbsSurface);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalPolycylinder > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "PolyCylinder Count : %ld", TotalNurbsSurface);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalFaces > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Facet Count : %ld", TotalFaces);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalTriangles > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Triangle Count : %ld", TotalTriangles);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalVertices > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Vertex Count : %ld", TotalVertices);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalText > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Text String Count : %ld", TotalText);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalSpotLight > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Spot Light Count : %ld", TotalSpotLight);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalLocalLight > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Local Light Count : %ld", TotalLocalLight);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalDistantLight > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Distant Light Count : %ld", TotalDistantLight);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}

	if (TotalCuttingPlane > 0)
	{
		segTreeListViewItem *geomLeaf = new segTreeListViewItem(item, key, false);
		sprintf(geomString, "Cutting Place Count : %ld", TotalCuttingPlane);
		geomLeaf->setText(0, geomString);
		QPixmap *segmentGeomIcon= new QPixmap( (const char**)geomicon);
		geomLeaf->setIcon(0,  QIcon(*segmentGeomIcon));
	}
	
}
