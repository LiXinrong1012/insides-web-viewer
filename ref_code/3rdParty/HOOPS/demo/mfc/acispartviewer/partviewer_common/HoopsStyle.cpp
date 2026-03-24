// HoopsStyle.cpp: implementation of the HoopsStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "resource.h"
#include "HoopsStyle.h"
#include "HUtilityGeometryCreation.h"
#include "vlist.h"
#include "HUtilityTextParser.h"
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



ColorItem::ColorItem(char *geom, char *chan)
{
    strcpy(m_geometry, geom);
    strcpy(m_channel, chan);
    m_bColorSet = false;
    m_texture = 0;
}

ColorItem::~ColorItem()
{
    delete [] m_texture;
}

void ColorItem::SetColor(HPoint &rgb)
{
    m_color = rgb;
    m_bColorSet = true;
}
void ColorItem::SetColor(float r, float g, float b)
{
    m_color.Set(r,g,b);
    m_bColorSet = true;
}

void ColorItem::SetTexture(const char *texture)
{
    if (texture && strcmp(texture, "<empty>") != 0)
    {
	delete [] m_texture;
	m_texture = new char[strlen(texture)+1];
        strcpy(m_texture, texture);
    }
    else
    {
	delete [] m_texture;
	m_texture = 0;

    }
}

void ColorItem::Reset()
{
    delete [] m_texture;
    m_texture = 0;
    m_bColorSet = 0;

}

bool ColorItem::IsEqual(char *geom, char *chan)
{
       if ((!geom || strcmp(geom, m_geometry) == 0) && (!chan || strcmp(chan, m_channel) == 0))
	   return true;
       else
	   return false;

}

int HoopsStyle::ShowVisibility(char *geom)
{
    char res[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key(GetKey());
    if (!HC_Show_Existence("visibility"))
    {
	HC_Close_Segment();
	return VISIBILITY_UNDEFINED;
    }

    HC_Show_One_Visibility(geom, res);
    HC_Close_Segment();
 if (strcmp(res, "on") == 0 || strcmp(res, "on!") == 0)
	return VISIBILITY_ON;
    else if (strcmp(res, "off") == 0)
	return VISIBILITY_OFF;
    else
	return VISIBILITY_UNDEFINED;

}
void HoopsStyle::AddColorItem(char *geom, char *chan)
{
    ColorItem *item = new ColorItem(geom, chan);
    vlist_add_last(m_ColorItemList, item);

}

void HoopsStyle::ResetColorItems()
{
    START_LIST_ITERATION(ColorItem, m_ColorItemList)
	temp->Reset();     
    END_LIST_ITERATION(m_ColorItemList);


}

ColorItem * HoopsStyle::GetColorItem(char *geom, char *chan)
{
   START_LIST_ITERATION(ColorItem, m_ColorItemList)
       if ((!geom || strcmp(geom, temp->m_geometry) == 0) && (!chan || strcmp(chan, temp->m_channel) == 0))
	   return temp;
     END_LIST_ITERATION(m_ColorItemList);
     return 0;
}

HoopsStyle::HoopsStyle(HoopsStyleLibrary *slib)
{
    m_pStyleLibrary = slib;

    m_TextureList = new_vlist(malloc, free);
    m_ColorItemList = new_vlist(malloc, free);
    m_StyleGeometry = STYLE_GEOMETRY_SPHERE;

    AddColorItem("cut face", "diffuse");
    AddColorItem("cut face", "diffuse2");
    AddColorItem("cut face", "environment");
    AddColorItem("cut face", "mirror");

    AddColorItem("faces", "diffuse");
    AddColorItem("faces", "diffuse2");
    AddColorItem("faces", "specular");
    AddColorItem("faces", "emission");
    AddColorItem("faces", "environment");
    AddColorItem("faces", "bump");
    AddColorItem("faces", "mirror");
    AddColorItem("faces", "transmission");
    AddColorItem("faces", "gloss");

    AddColorItem("front", "diffuse");
    AddColorItem("front", "diffuse2");
    AddColorItem("front", "specular");
    AddColorItem("front", "emission");
    AddColorItem("front", "bump");
    AddColorItem("front", "environment");
    AddColorItem("front", "mirror");
    AddColorItem("front", "transmission");
    AddColorItem("front", "gloss");

    AddColorItem("back", "diffuse");
    AddColorItem("back", "diffuse2");
    AddColorItem("back", "specular");
    AddColorItem("back", "emission");
    AddColorItem("back", "bump");
    AddColorItem("back", "environment");
    AddColorItem("back", "mirror");
    AddColorItem("back", "transmission");
    AddColorItem("back", "gloss");

   AddColorItem("edges", "diffuse");
   AddColorItem("edges", "specular");
   AddColorItem("edges", "transmission");
   
   AddColorItem("lines", "diffuse");
   AddColorItem("lines", "specular");
   AddColorItem("lines", "transmission");

   AddColorItem("markers", "diffuse");
   AddColorItem("markers", "specular");
   AddColorItem("markers", "transmission");

   AddColorItem("lights", "diffuse");
   AddColorItem("lights", "specular");

   HPoint mirror(0.5,0.5,0.5);
   GetColorItem("faces", "mirror")->SetColor(mirror);
}

HoopsStyle::~HoopsStyle()
{
    START_LIST_ITERATION(ColorItem, m_ColorItemList)
	delete temp;   
    END_LIST_ITERATION(m_ColorItemList);
    START_LIST_ITERATION(HoopsTexture, m_TextureList)
	delete temp;   
    END_LIST_ITERATION(m_TextureList);
    delete_vlist(m_ColorItemList);
    delete_vlist(m_TextureList);
}

void HoopsStyle::Create(char *name)
{ 

     m_StyleKey = HC_KOpen_Segment(name);
     HC_Flush_Contents(".", "styles");
     HC_Style_Segment_By_Key(m_pStyleLibrary->GetTextureKey());
     HC_Close_Segment();

}

void HoopsStyle::SetColor(char *geom, char *channel, float r, float g, float b, bool undefine)
{
    ColorItem *item = GetColorItem(geom, channel);
    if (item)
    {
	item->SetColor(r,g,b);
	
	if (undefine)
	{
	    item->m_bColorSet = false;
	    item->SetTexture(0);
	}
    }
    
    SetColors();
    HC_Open_Segment_By_Key(GetKey());
    HC_Set_Rendering_Options("attribute lock = color");
    HC_Close_Segment();

}
void HoopsStyle::SetTexture(char *geom, char *channel, const char *texture)
{
    ColorItem *item = GetColorItem(geom, channel);

    if (item)
    {
	item->SetTexture(texture);
    }
    SetColors();

}


void HoopsStyle::SetColor(char *text)
{

}

HC_KEY HoopsStyle::GetKey()
{
    return m_StyleKey;
}
void HoopsStyle::SetKey(HC_KEY key)
{
    m_StyleKey = key;
     HC_Open_Segment_By_Key(GetKey());
    HC_Flush_Contents(".", "styles");

      HC_Style_Segment_By_Key(m_pStyleLibrary->GetTextureKey());
     HC_Close_Segment();
}

void HoopsStyle::Style(HC_KEY key)
{
    HC_Open_Segment_By_Key(key);
    HC_Flush_Contents(".", "styles");
    HC_Style_Segment_By_Key(m_StyleKey);
    HC_Close_Segment();
}




static delimiter_t find_end_td[] = {{"\x21-\x27", false, "=| |,|", true, false},
			{"\x2D-\x3C", false, "=| |,|", true, false},
			{"\x3E-\x7E|", false, "=| |,|", true, false}};

static delimiter_t find_end_td3[] = {{"\x21-\x3C", false, "=| |,|)|", true, false},
	    {"\x3E-\x7E|", false, "=| |,|)|", true, false}};

//static delimiter_t find_end_td2[] = {{"\x21-\x7E", false, ")|", true, false}};

static delimiter_t find_end_td2[] = {{"\x21-\x27", false, ")|b|", true, false},
			{"\x2D-\x3C", false, ")|b|", true, false},
			{"\x3E-\x7E|", false, ")|b|", true, false}};



static delimiter_t find_end_td4[] = {{"b|", false, "\x30-\x39|)|,|", true, false}};
static delimiter_t find_end_td5[] = {{"\x30-\x39", false, " |)|,|", true, false}};
 
static delimiter_t check_for_end[] = {{"\21-\x7E", false, "\21-x7E|,|)|", true, false}};
  
static delimiter_t find_end_td6[] = {{"\x21-\x3C", false, ")|,|", true, false},
	    {"\x3E-\x7E|", false, ")|,|", true, false}};

bool HoopsStyle::ParseColor(HUtilityTextParser &tp, ColorItem *item)
{
    char part[MVO_BUFFER_SIZE];
    int dlum;
    HPoint col;   
 
    bool res = tp.ParseBuffer(part, (int &)dlum, find_end_td6, 2);
	if (part[0] == '(')
	{
		char temp[256];
		strcpy(temp,part+1);
		strcpy(part,temp);
	}

    HPoint rgb;
    if (HC_Compute_Color(part, "rgb", &col) && part[0]!='(')
    {
	item->SetColor(col);
	item->SetTexture(0);
 	return res;
    }
    else
    {

	if (strcmp(item->m_channel, "gloss") == 0)
	{
	    col.x = atof(part);
	    item->SetColor(col);
	    item->m_bColorSet = true;
	    item->SetTexture(0);
	    return res;
	}
	if (strstr(part, " ") == 0)
	{
 	    item->SetTexture(part);	    
 	    return res;
	}
	tp.Rewind();
    }

    res = tp.ParseBuffer(part, (int &)dlum, find_end_td3, 2);
    if (part[0] == '(' || (tp.PeekAt((unsigned int)-1) =='='))
    {
	char part2[256];
	char part3[256];
	tp.Rewind();
	res = tp.ParseBuffer(part, (int &)dlum, find_end_td2, 3);	
	tp.SkipAhead(-1);
	res = tp.ParseBuffer(part2, (int &)dlum, find_end_td4, 1);	
	tp.SkipAhead(-1);
	res = tp.ParseBuffer(part3, (int &)dlum, find_end_td5, 1);	
	strcat(part, part2);
	strcat(part, part3);
	if (tp.PeekAt(0) == ')')
	tp.SkipAhead(1);
    
    }
 
   
    if (HC_Compute_Color(part, "rgb", &rgb))
	item->SetColor(rgb);
    if (!res)
	return res;
    if (tp.PeekAt((unsigned int)-1) == ',')
	return res;
     res = tp.ParseBuffer(part, (int &)dlum, check_for_end, 1);
    if (!res)
	return res;

    if (part[0] != ' ' && part[0] != ')' &&part[0] != ',')
    {   tp.Rewind();
	res = tp.ParseBuffer(part, (int &)dlum, find_end_td3, 2);
	item->SetTexture(part);
    }
    else
    {
	tp.Rewind();
	item->SetTexture(0);
    }
    return res;

}


void HoopsStyle::GetName(char *name)
{
    char text[MVO_BUFFER_SIZE];
    HC_Show_Segment(GetKey(), text);
    HC_Parse_String(text, "/", -1, name);


}

void HoopsStyle::GatherColorData()
{
    char text[MVO_BUFFER_SIZE];
    ResetColorItems();
     strcpy(text,"");

    HC_Open_Segment_By_Key(GetKey());    

    if (HC_Show_Existence("color"))
    {
     bool facesexist = false;
     HC_Show_One_Color("faces", text);
   //  strcpy(text, "diffuse = ((r=0.5 g=0.5 b=0.5) apple, red), specular = yellow");
     if (strcmp(text, "") != 0)
     {
	 facesexist = true;
         DecipherColorData(text,"faces");
     }     
     strcpy(text,"");

     if (!facesexist)
     {     
     HC_Show_One_Color("front", text);
     if (strcmp(text, "") != 0)
         DecipherColorData(text,"front");
     strcpy(text,"");
     HC_Show_One_Color("back", text);
     if (strcmp(text, "") != 0)
         DecipherColorData(text,"back");
     strcpy(text,"");
     }
     HC_Show_One_Color("cut faces", text);
     if (strcmp(text, "") != 0)
		DecipherColorData(text,"cut face");
     strcpy(text,"");
      HC_Show_One_Color("edges", text);
     if (strcmp(text, "") != 0)
	DecipherColorData(text,"edges");
     strcpy(text,"");
     HC_Show_One_Color("lines", text);
     if (strcmp(text, "") != 0)
	DecipherColorData(text,"lines");
     strcpy(text,"");
     HC_Show_One_Color("markers", text);
     if (strcmp(text, "") != 0)
	DecipherColorData(text,"markers");
     strcpy(text,"");
     HC_Show_One_Color("lights", text);
     if (strcmp(text, "") != 0)
	DecipherColorData(text,"lights");
    }
 
    HC_Close_Segment(); 

}

static delimiter_t check_for_end2[] = {{"(", false, ")", false, true},
	    {"\x2D-\x3C", false, "", true, false}};





bool HoopsStyle::HasTwoColors(HUtilityTextParser &tp)
{
    char part[MVO_BUFFER_SIZE];
    int dlum;
    HPoint col;   
    bool res = tp.ParseBuffer(part, (int &)dlum, check_for_end2, 2);
	(void) res;
    if (tp.GetStartDelimiter() != '(')
    {
	tp.Rewind();
	return false;
    }
    tp.Rewind();

    char *start = strstr(part,",");

    if (!start)
	return false;
    else 
	return true;
    /*
    HUtilityTextParser tp2;
    tp2.InsertBuffer(start, strlen(start));
    tp2.SkipAhead(1);

    res = tp2.ParseBuffer(part, (int &)dlum, find_end_td3, 2);

    return false;
    */

}
void HoopsStyle::DecipherColorData(char *text, char *geom)
{

     HUtilityTextParser tp;
     char part[MVO_BUFFER_SIZE];
    tp.InsertBuffer(text, (unsigned int)strlen(text));
    bool first = false;  
    
     bool done = false;
    while (1)
    {    
    int dlum;
    bool res = tp.ParseBuffer(part, (int &)dlum, find_end_td, 3);

    if (!res && first)
	return;
    first = true;
  
    HPoint dummyColor;
   
   

    START_LIST_ITERATION(ColorItem, m_ColorItemList)
	if (temp->IsEqual(geom,0))
	{	
 	    if (strcmp(part, temp->m_channel) == 0)
	    {
	        bool hastwocolors = false;

			if (strcmp(temp->m_channel, "diffuse") == 0)
			{
				//sometimes diffuse keyword is followed by color "diffuse color="
				tp.ParseBuffer(part, (int &)dlum, find_end_td, 3);
				if (strcmp(part, "color") != 0)
					tp.Rewind();
				hastwocolors = HasTwoColors(tp);
			}

		HPoint color;
  		res = ParseColor(tp, temp);
		ColorItem *item2 = GetColorItem(geom, "diffuse2");
		if (hastwocolors && item2)
	 	    res = ParseColor(tp, item2);
		done = true;
		break;
	    }
	}
    END_LIST_ITERATION(m_ColorItemList);
     
    if (!done)
    {
	ColorItem *temp = GetColorItem(geom, "diffuse");
	tp.Rewind();
	bool hastwocolors = false;
        hastwocolors = HasTwoColors(tp);	
	HPoint color;
	res = ParseColor(tp, temp);
	ColorItem *item2 = GetColorItem(geom, "diffuse2");
	if (hastwocolors && item2)
	    res = ParseColor(tp, item2);
	
    }

    
    if (!res)
	break;
 
    }

}
    
void HoopsStyle::DeleteTexture(const char *texturename)
{
   HC_Open_Segment_By_Key(m_pStyleLibrary->GetTextureKey());    
   HC_UnDefine_Local_Texture(texturename);
   HC_Close_Segment();
}

void HoopsStyle::DecipherTexture(char *texturename)
{

    char texdef[MVO_BUFFER_SIZE];
    HC_Show_Local_Texture(texturename, texdef);
    HoopsTexture *texture = new HoopsTexture(this);
    texture->Set(texturename, texdef);   
    texture->RedefineTexture();
    vlist_add_last(m_TextureList, texture);
}


void HoopsStyle::CopyImages(HC_KEY startkey)
{
    HC_Open_Segment_By_Key(startkey);
    HC_Begin_Contents_Search("...", "images");
    HC_KEY key;
    while (HUtility::FindContents(key))
    {
	HC_Open_Segment_By_Key(m_pStyleLibrary->GetTextureKey());
	HC_Move_By_Key(key, ".");
	HC_Close_Segment();
    }
    HC_End_Contents_Search();
    HC_Close_Segment();
}
void HoopsStyle::GatherTextureData()
{
    START_LIST_ITERATION(HoopsTexture, m_TextureList)
 	delete  temp;
    END_LIST_ITERATION(m_TextureList);
    vlist_flush(m_TextureList);

    char type[MVO_BUFFER_SIZE];
    HC_KEY dummy;
    HC_Open_Segment_By_Key(m_pStyleLibrary->GetTextureKey());    
    HC_Begin_Contents_Search(".", "attributes");
    while (HC_Find_Contents(type, &dummy))
    {
	if (strcmp(type, "texture definitions") == 0)
	{
	    HC_Begin_Local_Texture_Search();
	    char texturename[MVO_BUFFER_SIZE];
	    while (HC_Find_Texture(texturename))
	    {
 		DecipherTexture(texturename);
	    }
	    HC_End_Texture_Search();

	}

    }
    HC_End_Contents_Search();
    HC_Close_Segment();
}

HC_KEY HoopsStyle::FindImage(const char *imagename)
{
 
    char type[MVO_BUFFER_SIZE];
    char name[MVO_BUFFER_SIZE];
    HC_KEY key;
    HC_KEY found = -1;
    HC_Open_Segment_By_Key(m_pStyleLibrary->GetTextureKey());    
    HC_Begin_Contents_Search("...", "images");
    while (HC_Find_Contents(type, &key))
    {
	HoopsTexture::GetImageName(key, name);
	if (strcmp(name, imagename) == 0)
	{
	    found = key;
	    break;
	}

 
    }
    HC_End_Contents_Search();
    HC_Close_Segment();
    return found;
}



void HoopsStyle::StartTextureIteration()
{
    vlist_reset_cursor(m_TextureList);
}


void HoopsStyle::SetColors()
{
    char col[MVO_BUFFER_SIZE];
    char col2[MVO_BUFFER_SIZE];
    char current[MVO_BUFFER_SIZE];
   
    
    strcpy(current,"");
    strcpy(col,"");
    bool first = true;
    START_LIST_ITERATION(ColorItem, m_ColorItemList)
	if (strcmp(temp->m_channel,"diffuse2")!=0)
	{	
	if (temp->m_texture || temp->m_bColorSet)
	{
	    bool start = false;
	    if (strcmp(temp->m_geometry, current)!=0)
	    {
		if (first)
		{
		    first = false;
		    sprintf(col2, "%s = (", temp->m_geometry);
		}
		else
		    sprintf(col2, "),%s = (", temp->m_geometry);

		strcat(col, col2);
		strcpy(current, temp->m_geometry);
		start = true;
	    }
	    if (!start)
		strcat(col, ",");

	    if (strcmp(temp->m_channel, "gloss") == 0)
 		sprintf(col2, "%s = %f", temp->m_channel, temp->m_color.x);
	    else
	    {
		if (strcmp(temp->m_channel, "diffuse") == 0)
		{
		    ColorItem *temp2 = GetColorItem(temp->m_geometry, "diffuse2");
			vlist_reset_cursor(m_ColorItemList);
			while (1)
			{
				if (vlist_peek_cursor(m_ColorItemList)==temp)
					break;
				vlist_advance_cursor(m_ColorItemList);
			}
		    if (temp2 && (temp2->m_bColorSet || temp2->m_texture))
		    {		    

			if (temp->m_bColorSet && !temp->m_texture)
			    sprintf(col2, "%s = (r=%f g=%f b=%f", temp->m_channel, temp->m_color.x, temp->m_color.y, temp->m_color.z);
			else if (temp->m_bColorSet && temp->m_texture)
			    sprintf(col2, "%s = (r=%f g=%f b=%f %s", temp->m_channel, temp->m_color.x, temp->m_color.y, temp->m_color.z, temp->m_texture);
			else
			    sprintf(col2, "%s = (%s", temp->m_channel, temp->m_texture);

			char col3[4096];
			if (temp2->m_bColorSet && !temp2->m_texture)
			    sprintf(col3, ",r=%f g=%f b=%f)", temp2->m_color.x, temp2->m_color.y, temp2->m_color.z);
			else if (temp2->m_bColorSet && temp2->m_texture)
			    sprintf(col3, ",r=%f g=%f b=%f %s)",  temp2->m_color.x, temp2->m_color.y, temp2->m_color.z, temp2->m_texture);
			else
			    sprintf(col3, ",%s)", temp2->m_texture);
			strcat(col2, col3);
			goto done;
		    }
		}


 	    if (temp->m_bColorSet && !temp->m_texture)
		sprintf(col2, "%s = (r=%f g=%f b=%f)", temp->m_channel, temp->m_color.x, temp->m_color.y, temp->m_color.z);
	    else if (temp->m_bColorSet && temp->m_texture)
		sprintf(col2, "%s = (r=%f g=%f b=%f %s)", temp->m_channel, temp->m_color.x, temp->m_color.y, temp->m_color.z, temp->m_texture);
	    else
		sprintf(col2, "%s = %s", temp->m_channel, temp->m_texture);
done:	    ;
	    }
	    strcat(col, col2);
	}
	}
    END_LIST_ITERATION(m_ColorItemList);

    strcat(col, ")");
    HC_Open_Segment_By_Key(GetKey());
    if (HC_Show_Existence("color"))
	HC_UnSet_Color();
    if (strlen(col)>2)
	HC_Set_Color(col);
    HC_Close_Segment();
    
}



HoopsTexture * HoopsStyle::GetNextTexture()
{
    HoopsTexture *ret = ((HoopsTexture *)vlist_peek_cursor(m_TextureList));
    vlist_advance_cursor(m_TextureList);
    return ret;
}

HoopsTexture * HoopsStyle::GetTextureByName(const char *name)
{
    START_LIST_ITERATION(HoopsTexture, m_TextureList)
	if (strcmp(temp->GetName(), name) == 0)
	    return temp;
    END_LIST_ITERATION(m_TextureList);
    return 0;
}


void HoopsStyleViewer::Create()
{
    m_Key = HC_KOpen_Segment("");
    HC_Flush_Contents(".", "everything");
    HC_Set_Camera_Position(0,0,-4);
    HC_Set_Camera_Projection("perspective");
    HC_Close_Segment();
}


void HoopsStyleViewer::ShowGeometry()
{
    int style_geo = m_Style->GetStyleGeometry();
	
	HC_Open_Segment_By_Key(m_Key);
    HC_Flush_Contents(".", "geometry, camera");
    HC_Set_Camera_Position(0,0,-4.2);
    HC_Set_Camera_Projection("perspective");
	HC_Orbit_Camera(style_geo==STYLE_GEOMETRY_PLANE?0:45, style_geo==STYLE_GEOMETRY_PLANE?-45:45);
    HC_Close_Segment();
    if (m_Style)
    {    
		if (style_geo == STYLE_GEOMETRY_SPHERE)
			ShowSphere();
		else if (style_geo == STYLE_GEOMETRY_CUBE)
			ShowCube();
		else
			ShowPlane();
    }

}

void HoopsStyleViewer::ShowSphere()
{
    HC_Open_Segment_By_Key(m_Key);
    HC_Flush_Contents(".", "geometry, segments");
    HUtilityGeometryCreation::CreateSphere(HPoint(0.0f,0.0f,0.0f), 0.8f,25,HPoint(0.0f,1.0f,0.0f), HPoint(0.0f,0.0f,1.0f));
    HC_Insert_Line(-1,-1,-1,1,1,1);
    HC_Insert_Line(-1,1,-1,1,-1,1);
    HC_Insert_Distant_Light(0,0,-1);
    
    HC_Close_Segment();
}
void HoopsStyleViewer::ShowCube()
{
	HC_Open_Segment_By_Key(m_Key);
    HC_Flush_Contents(".", "geometry, segments");
	HPoint maxpt(-0.5,-0.5,-0.5), minpt(0.5,0.5,0.5);
    HUtility::InsertBox(&maxpt, &minpt);
    HC_Insert_Line(-1,-1,-1,1,1,1);
    HC_Insert_Line(-1,1,-1,1,-1,1);
    HC_Insert_Distant_Light(0,0,-1);
    
    HC_Close_Segment();
}


void HoopsStyleViewer::ShowPlane()
{
	float points[12];
	//x
	points[0]=points[6]=-0.5f;
	points[9]=points[3]=0.5f;
	//y
	points[1]=points[4]=-0.5f;
	points[7]=points[10]=0.5f;
	//z
	points[2]=points[5]=points[8]=points[11]=0.f;


	HC_Open_Segment_By_Key(m_Key);
    HC_Flush_Contents(".", "geometry, segments");
	HC_Insert_Mesh(2, 2, points);
    HC_Insert_Line(-1,-1,-1,1,1,1);
    HC_Insert_Line(-1,1,-1,1,-1,1);
    HC_Insert_Distant_Light(0,0,-1);
    
    HC_Close_Segment();
}


void HoopsStyleViewer::SetStyle(HoopsStyle *style)
{
    m_Style = style;
    if (m_Style)
	m_Style->Style(m_Key);
  
}

HoopsStyle *HoopsStyleViewer::SetStyleByKey(HC_KEY key)
{
    m_Style->SetKey(key);
    m_Style->Style(m_Key);
    return m_Style;
 
}

HoopsStyle *HoopsStyleViewer::SetStyleByName(char *name)
{
    m_Style->Create(name);
    m_Style->Style(m_Key);
    return m_Style;

}


HC_KEY HoopsStyleViewer::GetStyleKey()
{
    return (m_Style->GetKey()); 
}

HoopsStyle *HoopsStyleViewer::GetStyle()
{
    return (m_Style); 
}

HoopsStyleViewer::HoopsStyleViewer(HoopsStyleLibrary *selector)
{
    m_Style = 0;
}
HoopsStyleViewer::~HoopsStyleViewer()
{

}

int HoopsStyleSelector::GetNumStyles()
{
	int num = 0;
    START_LIST_ITERATION(HoopsStyle, m_StyleList)
		num++;
    END_LIST_ITERATION(m_StyleList);
	return num;
}

HoopsStyleSelector::HoopsStyleSelector(HoopsStyleLibrary *slib)
{
    m_pStyleLibrary = slib;
    m_Key = HC_KOpen_Segment("selector");
    HC_Flush_Contents(".", "everything");
    HC_Close_Segment();
    m_StyleList = new_vlist(malloc, free);
    m_Position = 0;
    m_VisibleItems = 4;
    m_SelectedStyle = 0;

}
HoopsStyleSelector::~HoopsStyleSelector()
{
    START_LIST_ITERATION(HoopsStyle, m_StyleList)
	delete temp;
    END_LIST_ITERATION(m_StyleList);
    delete_vlist(m_StyleList);

    delete m_pStyleLibrary;


}

void HoopsStyleSelector::SetVisibleItems(int n)
{
    m_VisibleItems = n;
}


void HoopsStyleSelector::GatherStyles()
{
    char type[MVO_BUFFER_SIZE];
    bool first = true;
    HC_KEY key;
    m_ItemNum = 0;
    START_LIST_ITERATION(HoopsStyle, m_StyleList)
	delete temp;
    END_LIST_ITERATION(m_StyleList);
    vlist_flush(m_StyleList);
    m_SelectedStyle = 0;

    HC_Open_Segment_By_Key(m_pStyleLibrary->GetKey());
    HC_Begin_Contents_Search(".", "segments");
     while (HC_Find_Contents(type, &key)) 
    {
	 if (key != m_pStyleLibrary->GetTextureKey())
	 {	 
	HoopsStyle *style = new HoopsStyle(m_pStyleLibrary);
	style->SetKey(key);
	vlist_add_first(m_StyleList, style);
	if (first)
	    m_SelectedStyle = style;
	m_ItemNum++;
	 }
    }
    HC_End_Contents_Search();
    HC_Close_Segment();

}

HoopsStyle * HoopsStyleSelector::AddNewStyle()
{
    HC_Open_Segment_By_Key(m_pStyleLibrary->GetKey());
    HC_KEY key = HC_KOpen_Segment("");

 	HoopsStyle *style = new HoopsStyle(m_pStyleLibrary);
	style->SetKey(key);
	vlist_add_last(m_StyleList, style);
    HC_Close_Segment();
    return style;
    
}

void HoopsStyleSelector::SetSelectedStyle(HoopsStyle *style)
{
    m_SelectedStyle = style;
}

HoopsStyle * HoopsStyleSelector::GetStyleByName(const char *name)
{
     
  START_LIST_ITERATION(HoopsStyle, m_StyleList)
      char tempname[4096];
       temp->GetName(tempname);
      if (strcmp(tempname, name) == 0)
	  return temp;	
    END_LIST_ITERATION(m_StyleList);
    return 0;
}
void HoopsStyleSelector::DrawStyles(bool noset)
{

restart:
     
    HC_Open_Segment_By_Key(m_Key);
    HC_Flush_Contents(".", "everything");
 
    int cc=0;
    int c=0;
    float add = 2.0f / m_VisibleItems;
    START_LIST_ITERATION(HoopsStyle, m_StyleList)
    if (c>=m_Position && cc*add + add<=2.0f)
    {
	HC_Open_Segment("");
 	HoopsStyleViewer * styleviewer = new HoopsStyleViewer(m_pStyleLibrary);
	styleviewer->Create();
	styleviewer->SetStyle(temp);
         styleviewer->ShowGeometry();
 	HC_Set_Window(-0.97 + add * cc, -1 + add * cc+add-0.03,-0.95,0.95);
	if (temp == m_SelectedStyle)
	    HC_Set_Window_Frame("on");
	else
	    HC_Set_Window_Frame("off");

	styleviewer->SetStyle(temp);
	HC_Close_Segment();
	delete styleviewer;
	cc++;
    }
    else
    {
	if (temp == m_SelectedStyle && !noset)
	{
	    m_Position = c;
	    goto restart;
	}
    }
     c++;
   END_LIST_ITERATION(m_StyleList);
   HC_Close_Segment();  
  
}


HoopsStyle * HoopsStyleSelector::SelectStyles(int x, int y)
{
    HPoint in(x,y,0);
    HPoint out;
    HC_Open_Segment_By_Key(m_Key);
    HC_Compute_Coordinates(".", "local pixels", &in, "local window", &out);
    HC_Close_Segment();
    float add = 2.0f / m_VisibleItems;

    int res = (out.x + 1.0f) / add + m_Position;
    m_SelectedStyle = GetStyle(res);
    return (m_SelectedStyle);

}

void HoopsStyleSelector::Scroll(int pos)
{
     m_Position = pos;
     DrawStyles();
}


HoopsStyle * HoopsStyleSelector::GetStyle(int num)
{
    int c=0;
    START_LIST_ITERATION(HoopsStyle, m_StyleList)
    if (c>=num)
	return temp;
	c++;  
    END_LIST_ITERATION(m_StyleList);
   return 0;
}


HoopsTexture::HoopsTexture(HoopsStyle *style)
{
    m_Style = style;
    strcpy(m_InterpolationFilter,"<empty>");
    strcpy(m_DecimationFilter,"<empty>");
    strcpy(m_ParameterizationSource,"<empty>");
    strcpy(m_Layout,"<empty>");
    strcpy(m_Tiling,"<empty>");
    strcpy(m_BlendingMode,"<empty>");
    m_ValueScaleMin = 0.0f;
    m_ValueScaleMax = 1.0f;
    m_ValueScaleSet = false;
    m_bDownsampling = false;
    m_bDownsamplingSet = false;
  
}

HoopsTexture::~HoopsTexture()
{

}

static delimiter_t first_tex_part[] = {"\x21-\x7E", false, "=|,|", true, false};
static delimiter_t second_tex_part[] = {"\x21-\x7E", false, ",", true, false};
static delimiter_t number_part[] = {"\x30-\x39", false, ",|)|", true, false};
 
void HoopsTexture::Set(char *name, char *texdef)
{
    strcpy(m_TextureName, name);
    HUtilityTextParser tp;    
    tp.InsertBuffer(texdef, (unsigned int)strlen(texdef));

    bool hasModulate = false;
    bool hasDecal = false;
    
    char leftside[MVO_BUFFER_SIZE];
    char rightside[MVO_BUFFER_SIZE];
    while (1)
    {    
    int dlum;
    bool res = tp.ParseBuffer(leftside, (int &)dlum, first_tex_part, 1);

    if (strcmp(leftside, "down sample") == 0)
    {	    
 	    m_bDownsampling = true;
    	    m_bDownsamplingSet = true;
    if (!res)
	break;

    }
    else if (strcmp(leftside, "no down sample") == 0)
    {
  	    m_bDownsampling = false;
    	    m_bDownsamplingSet = true;
    if (!res)
	break;

    }
    else if (strcmp(leftside, "modulate") == 0)
    {
	hasModulate = true;
        if (!res)
		break;   
    }
    else if (strcmp(leftside, "decal") == 0)
    {
	hasDecal = true;
        if (!res)
		break;   
    }
    else
    {
    if (!res)
	break;
    res = tp.ParseBuffer(rightside, (int &)dlum, second_tex_part, 1);
    }
    
    if (strcmp(leftside, "parameterization source") == 0)
    {
	strcpy(m_ParameterizationSource, rightside);
    }
    if (strcmp(leftside, "interpolation filter") == 0)
    {
	strcpy(m_InterpolationFilter, rightside);
    }
    if (strcmp(leftside, "decimation filter") == 0)
    {
	strcpy(m_DecimationFilter, rightside);
    }
    
    if (strcmp(leftside, "down-sampling") == 0)
    {
	if (strcmp(rightside, "on"))
	    m_bDownsampling = true;
	else
	    m_bDownsampling = false;
	m_bDownsamplingSet = true;

    }
    if (strcmp(leftside, "layout") == 0)
    {
	strcpy(m_Layout, rightside);
    }
    if (strcmp(leftside, "tiling") == 0)
    {
	strcpy(m_Tiling, rightside);
    }
    if (strcmp(leftside, "source") == 0)
    {
	strcpy(m_Source, rightside);
    }
    if (strcmp(leftside, "value scale") == 0)
    {
	char rightside2[MVO_BUFFER_SIZE];
        res = tp.ParseBuffer(rightside2, (int &)dlum, second_tex_part, 1);
	strcat(rightside, ",");

	strcat(rightside, rightside2);

         HUtilityTextParser tp2;    
	tp2.InsertBuffer(rightside, (unsigned int)strlen(rightside));
    
	char v1[MVO_BUFFER_SIZE];
	res = tp2.ParseBuffer(v1, (int &)dlum, number_part, 1);
	char v2[MVO_BUFFER_SIZE];
	res = tp2.ParseBuffer(v2, (int &)dlum, number_part, 1);
	m_ValueScaleMin = atof(v1);
	m_ValueScaleMax = atof(v2);
	m_ValueScaleSet = true;
    }


    }
    if (hasDecal && hasModulate)
	strcpy(m_BlendingMode, "decal + modulate");
    else if (hasDecal)
	strcpy(m_BlendingMode, "decal");
    else if (hasModulate)
	strcpy(m_BlendingMode, "modulate");

	


}

static delimiter_t first_image_part[] = {"\x21-\x7E", false, "=|,|", true, false};
 static delimiter_t second_image_part[] = {"\x21-\x7E", false, ",", true, false};
 
void HoopsTexture::GetImageName(HC_KEY key, char *name)
{

    float dummy;
    int dummy2;
    char text[MVO_BUFFER_SIZE];
    HC_Show_Image_Size(key, &dummy, &dummy, &dummy, text, &dummy2, &dummy2 );

    HUtilityTextParser tp;    
    tp.InsertBuffer(text, (unsigned int)strlen(text));

    char leftside[MVO_BUFFER_SIZE];
    char rightside[MVO_BUFFER_SIZE];
    while (1)
    {    
    int dlum;
    bool res = tp.ParseBuffer(leftside, (int &)dlum, first_image_part, 1);
     if (!res)
	break;
    if (tp.GetEndDelimiter() == '=')
        res = tp.ParseBuffer(rightside, (int &)dlum, second_image_part, 1);
    
    
    if (strcmp(leftside, "name") == 0)
    {
	strcpy(name, rightside);
    }
    }


}


void HoopsTexture::CloneTexture(const char *name)
{
    RedefineTexture(name);   
}


void HoopsTexture::RedefineTexture(const char *name)
{
    char text[MVO_BUFFER_SIZE];
    char parttext[MVO_BUFFER_SIZE];
    HC_Open_Segment_By_Key(m_Style->GetStyleLibrary()->GetTextureKey());
    if (!name)
    HC_UnDefine_Local_Texture(GetName());
//    HC_Show_Local_Texture(GetName(), text);
    strcpy(text, "");
    if (strcmp(m_ParameterizationSource,"<empty>")!=0)
    {    
	sprintf(parttext, "parameterization source = %s", m_ParameterizationSource);
	strcat(text, parttext);
    }
    if (strcmp(m_Source,"<empty>")!=0)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	sprintf(parttext, "source = %s", m_Source);
	strcat(text, parttext);
    }
    if (m_ValueScaleSet)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
 	sprintf(parttext, "value scale = (%f, %f)", m_ValueScaleMin, m_ValueScaleMax);
	strcat(text, parttext);
    }
  
    if (strcmp(m_InterpolationFilter,"<empty>")!=0)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	sprintf(parttext, "interpolation filter = %s", m_InterpolationFilter);
	strcat(text, parttext);
    }
    if (strcmp(m_DecimationFilter,"<empty>")!=0)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	sprintf(parttext, "decimation filter = %s", m_DecimationFilter);
	strcat(text, parttext);
    }
    if (m_bDownsamplingSet)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	if (m_bDownsampling)
	    sprintf(parttext, "down-sampling = on");
	else
	    sprintf(parttext, "down-sampling = off");
	strcat(text, parttext);
    }

    if (strcmp(m_Layout,"<empty>")!=0)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	sprintf(parttext, "layout = %s", m_Layout);
	strcat(text, parttext);
    }
    if (strcmp(m_Tiling,"<empty>")!=0)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	sprintf(parttext, "tiling = %s", m_Tiling);
	strcat(text, parttext);
    }
    if (strcmp(m_BlendingMode,"<empty>")!=0)
    {    
	if (strcmp(text, "")!= 0)
		strcat(text, ",");
	if (strcmp(m_BlendingMode, "decal + modulate") == 0)
		sprintf(parttext, "decal, modulate");
	else
	    sprintf(parttext, "%s", m_BlendingMode);
	strcat(text, parttext);
    }

//    sprintf(text, "source = %s, parameterization source = %s, interpolation filter = %s", m_Source, m_ParameterizationSource, m_InterpolationFilter);
    if (!name)
	HC_Define_Local_Texture(GetName(), text);
    else
	HC_Define_Local_Texture(name, text);
    HC_Close_Segment();

}

void HoopsTexture::ShowImage(int xmax, int ymax)
{
    HC_Open_Segment_By_Key(m_Style->GetStyleLibrary()->GetTextureKey());
    HC_Begin_Contents_Search("...", "images");
	HC_KEY imagekey;
	char imagename[MVO_BUFFER_SIZE];
	bool found = false;
	while (HUtility::FindContents(imagekey))
	{
	    HoopsTexture::GetImageName(imagekey, imagename);    
	    if (strcmp(imagename, m_Source) == 0)
	    {
		found = true;
		break;
	    } 
	}
	HC_End_Contents_Search();
	HC_Close_Segment();

	HC_Open_Segment("image");
	HC_Flush_Contents(".", "everything");
         HC_Style_Segment_By_Key(m_Style->GetStyleLibrary()->GetTextureKey());
	 
	 if (found)
	 {
	     static	float vcor[12] = { 1.0, 0.0, 0.0,
		 1.0, 1.0, 0.0,
		 0.0, 1.0, 0.0,
		 0.0, 0.0, 0.0};
	     
	   
	     char text[4096];
	     sprintf(text, "source = %s, interpolation filter = off, no downsampling, parameterization source = uv",imagename);
	     
	     HC_Define_Local_Texture("imagetexture",text);
	     
	     HC_Set_Visibility("everything = off,faces = on");
	     HC_KEY key = HUtility::InsertRectangle(".", -1,-1,1,1,0,true);
	     HC_MSet_Vertex_Parameters(key,0,4,3,vcor);
	     sprintf(text,"faces=(diffuse=white imagetexture)");
	     HC_Set_Color(text);			
	     
	     
	 }
	 HC_Close_Segment();
}
 





void HoopsTexture::SetParameterizationSource(const char *source)
{
    strcpy(m_ParameterizationSource, source);
    RedefineTexture();
}


void HoopsTexture::SetInterpolationFilter(const char *source)
{

    strcpy(m_InterpolationFilter, source);
    RedefineTexture();
}
void HoopsTexture::SetDecimationFilter(const char *source)
{

    strcpy(m_DecimationFilter, source);
    RedefineTexture();
}
void HoopsTexture::SetDownsampling(bool ds)
{
    m_bDownsampling = ds;
    m_bDownsamplingSet = true;
     RedefineTexture();
}
void HoopsTexture::SetLayout(const char *source)
{

    strcpy(m_Layout, source);
    RedefineTexture();
}
void HoopsTexture::SetTiling(const char *source)
{

    strcpy(m_Tiling, source);
    RedefineTexture();
}

void HoopsTexture::SetBlendingMode(const char *source)
{

    strcpy(m_BlendingMode, source);
    RedefineTexture();
}


void HoopsTexture::SetSource(const char *source)
{

    strcpy(m_Source, source);
    RedefineTexture();
}
void HoopsTexture::SetValueScaleMin(float vsmin)
{
    m_ValueScaleMin = vsmin;
    m_ValueScaleSet = true;
 
    RedefineTexture();
}
void HoopsTexture::SetValueScaleMax(float vsmax)
{
    m_ValueScaleMax = vsmax;
    m_ValueScaleSet = true;
 
    RedefineTexture();
}



HoopsStyleLibrary::HoopsStyleLibrary()
{
    
}
void HoopsStyleLibrary::Create(char *text)
{
    m_Key = HC_KOpen_Segment(text);
    HC_Set_Visibility("everything = off");
    m_TextureKey = HC_KOpen_Segment("textures");
    HC_Close_Segment();
    HC_Close_Segment();

}


