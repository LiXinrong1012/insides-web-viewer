// HoopsStyle.h: interface for the HoopsStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOOPSSTYLE_H__A8F17610_A672_4150_BA40_25993E08CAF8__INCLUDED_)
#define AFX_HOOPSSTYLE_H__A8F17610_A672_4150_BA40_25993E08CAF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class HoopsStyle;

#define VISIBILITY_ON 1
#define VISIBILITY_OFF 0
#define VISIBILITY_UNDEFINED 2

#define STYLE_GEOMETRY_SPHERE	0
#define STYLE_GEOMETRY_CUBE		1
#define STYLE_GEOMETRY_PLANE	2

#include "HUtilityTextParser.h"
class HoopsStyleSelector;

class ColorItem
{
public:
    ColorItem(char *geometry, char *channel);
    ~ColorItem();
    void Reset();
    void SetTexture(const char *texture);
    void SetColor(HPoint &rgb);
    void SetColor(float r, float g, float b);

    bool IsEqual(char *geom, char *chan);


    
	char m_geometry[32];
	char m_channel[32];

	char *m_texture;
	HPoint m_color;
	bool m_bColorSet;
};


class HoopsTexture 
{
public:
 	HoopsTexture(HoopsStyle *style);
	virtual ~HoopsTexture();
 	void Set(char *name, char *texdef); 
	char *GetName() { return m_TextureName; }
	char *GetParameterizationSource() { return m_ParameterizationSource; }
	char *GetInterpolationFilter() { return m_InterpolationFilter; }
	char *GetDecimationFilter() { return m_DecimationFilter; }
	char *GetSource() { return m_Source; }
	char *GetLayout() { return m_Layout; }
	char *GetTiling() { return m_Tiling; }
	char *GetBlendingMode() { return m_BlendingMode; }
	bool GetDownsampling() { return m_bDownsampling; }

	void RedefineTexture(const char *name = 0);
	void CloneTexture(const char *name);
	void SetParameterizationSource(const char *source);
	void SetInterpolationFilter(const char *filter);
	void SetDecimationFilter(const char *filter);
	void SetDownsampling(bool ds);
	void SetLayout(const char *filter);
	void SetTiling(const char *filter);
	void SetBlendingMode(const char *filter);
	void SetSource(const char *source);
	void SetValueScaleMin(float vsmin);
	void SetValueScaleMax(float vsmax);
	float GetValueScaleMin() { return m_ValueScaleMin; }
	float GetValueScaleMax() { return m_ValueScaleMax; }
	bool GetValueScaleSet() { return m_ValueScaleSet; }
	bool GetDownsamplingSet() { return m_ValueScaleSet; }
	static void GetImageName(HC_KEY key, char *name);
	void ShowImage(int x, int y);
	

	
protected:
	char m_TextureName[512];
	char m_ParameterizationSource[256];
	char m_InterpolationFilter[256];
	char m_DecimationFilter[256];
	char m_Layout[256];
	char m_Tiling[256];
	char m_BlendingMode[256];
	char m_Source[512];
	float m_ValueScaleMin;
	float m_ValueScaleMax;
	bool  m_ValueScaleSet;
	bool  m_bDownsampling;
	bool  m_bDownsamplingSet;
	HoopsStyle *m_Style;

  	
};

class HoopsStyleLibrary
{
public:
	HoopsStyleLibrary();
	void Create(char *text);

	HC_KEY GetKey() { return m_Key; }
	HC_KEY GetTextureKey() {return m_TextureKey; }
protected:
    HC_KEY m_Key;
    HC_KEY m_TextureKey;
	
	
};
class HoopsStyle  
{
public:
	HC_KEY GetKey();
	void Style(HC_KEY key);

	void SetKey(HC_KEY key);
	void SetColor(char *text);
	void Create(char *name);
	HoopsStyle(HoopsStyleLibrary *selector);
	virtual ~HoopsStyle();
	void DecipherColorData(char *text, char *geom);
 
	void GatherColorData();

	void GatherTextureData();
	void DecipherTexture(char *name);

 	bool ParseColor(HUtilityTextParser &tp, ColorItem *item);
	void SetColor(char *geom, char *channel, float r, float g, float b, bool undefine);
	void SetTexture(char *geom, char *channel,const char *texture);

	void StartTextureIteration();
	HoopsTexture *GetNextTexture();
	HoopsTexture *GetTextureByName(const char *name);
	void AddColorItem(char *geom, char *chan);
	int ShowVisibility(char *geom);

 	void ResetColorItems();
	ColorItem * GetColorItem(char *geom, char *chan);


 
	HoopsStyleLibrary *GetStyleLibrary() { return m_pStyleLibrary; }
	void GetName(char *name);
	    	    	  	
	void CopyImages(HC_KEY startkey);

	int GetStyleGeometry() { return m_StyleGeometry; }
	void SetStyleGeometry(int sg) { m_StyleGeometry = sg; }
	bool HasTwoColors(HUtilityTextParser &tp);
	HC_KEY FindImage(const char *imagename);
	void DeleteTexture(const char *texturename);

	
 protected:	
	void SetColors();
	HoopsStyleLibrary *m_pStyleLibrary;
	HC_KEY m_StyleKey;
	struct vlist_s*	m_TextureList;
	struct vlist_s*	m_ColorItemList;	
	int m_StyleGeometry;
};

class HoopsStyleViewer
{
public:
	HoopsStyle * SetStyleByKey(HC_KEY key);
	HoopsStyle * SetStyleByName(char * name);
	HC_KEY GetKey();
	void SetColor(char *text);
	void Create();
	HoopsStyleViewer(HoopsStyleLibrary *m_pStyleLibrary);
	void ShowSphere();
	void ShowCube();
	void ShowPlane();
	void ShowGeometry();
	HC_KEY GetStyleKey();
	HoopsStyle *GetStyle();
	void SetStyle(HoopsStyle *style);
 
	virtual ~HoopsStyleViewer();
protected:
	HoopsStyleLibrary *m_pStyleLibrary;
	HoopsStyle *m_Style;
	HC_KEY m_Key;
};


class HoopsStyleSelector
{
public:
 	HoopsStyleSelector(HoopsStyleLibrary *m_StyleLibrary);
 	virtual ~HoopsStyleSelector();
	void GatherStyles();
	void DrawStyles(bool noset = true);
	void SetVisibleItems(int i);
	HoopsStyle * SelectStyles(int x, int y);
	HoopsStyle * GetStyle(int num);
	HoopsStyle * AddNewStyle();
	void SetPosition(int position) { m_Position = position; }
	int GetPosition() { return m_Position; }
	HoopsStyle *GetSelectedStyle() { return m_SelectedStyle; }
	int GetStyleNum() { return m_ItemNum; }
	void Scroll(int pos);
	HoopsStyleLibrary *GetStyleLibrary() { return m_pStyleLibrary; }
	HoopsStyle * GetStyleByName(const char *name);
	void SetSelectedStyle(HoopsStyle *style);
	int GetNumStyles();
	
protected:
	HoopsStyleLibrary *m_pStyleLibrary;
	HoopsStyle *m_SelectedStyle;
	int m_Position;
	int m_VisibleItems;
	int m_ItemNum;
	struct vlist_s*	m_StyleList;
	HC_KEY m_Key;

};

#endif // !defined(AFX_HOOPSSTYLE_H__A8F17610_A672_4150_BA40_25993E08CAF8__INCLUDED_)
