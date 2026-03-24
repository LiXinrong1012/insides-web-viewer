#include "ModelViewManager.h"
#include "precore/BaseItem.h"
#include "HoopsUpdator.h"
#include "precore/BaseItem.h"
#include "precore/modeldocument.h"
#include "PreHQWidget.h"
#include "HObjects.h"

#include "base/ParametersManager.h"
#include "Base/Console.h"
#include "coresps/ShapeManager.h"

ModelViewManager::ModelViewManager(PreHQWidget* preHQWidget)
	:ViewManager(preHQWidget)
{
	setViewType(ModelViewType);
}


ModelViewManager::~ModelViewManager(void)
{
	clearHCKey(myDocument()->getAssembly());
	_hcMap.clear();
}


void ModelViewManager::createAll( BaseItem* item )
{
	if( (item->isPartOrAssembly()&&(item!=myDocument()->getActiveItem()))
		|| item->isExternal() )
		return;
	HC_KEY key=HC_Open_Segment("");

	AppearanceItem* appearance=item->getAppearance();
	appearance->setHCKey(key);
	appearance->setBaseItem(item);
	_hcMap[key]=item;
	HoopsUpdator()->onItemUpdating(appearance);
	onVisibilityChanged(appearance);
	onApplyMaterial(appearance);

	int n=item->count();
	for(int i=0;i<n;++i)
		createAll(item->child(i));
	
	HC_Close_Segment();
}


HC_KEY ModelViewManager::getHCKey(BaseItem* item )
{
	AppearanceItem* a=getAppearance(item);
	return a->getHCKey();
}

AppearanceItem* ModelViewManager::getAppearance(BaseItem* item )
{
	return item->getAppearance();
}

AppearanceItem* ModelViewManager::getAppearance( HC_KEY key )
{
	if(_hcMap.find(key)==_hcMap.end())
		return NULL;
#ifdef _DEBUG
	BaseItem* baseItem=_hcMap[key];
	return baseItem->getAppearance();
#endif
	return _hcMap[key]->getAppearance();
}

BaseItem* ModelViewManager::getBaseItem( HC_KEY key )
{
	AppearanceItem* a=getAppearance(key);
	if(a)
		return a->getBaseItem();
	else
		return NULL;
}

#include "HIOManager.h"
#include "HDB.h"

void ModelViewManager::testStyle()
{

	HC_Open_Segment("/image");

	HInputHandler *reader = HDB::GetHIOManager()->GetInputHandler("jpg");
	HInputHandlerOptions input_options;
	input_options.m_bLocal = true;
	char imagename[MVO_BUFFER_SIZE];
	strcpy(imagename, H_ASCII_TEXT("a"));
	input_options.m_pImageName = imagename;
	HFileInputResult result = InputFail;

	HC_KEY	temp_seg=HC_Open_Segment("p1");
	HC_Close_Segment();
	HC_KEY image_key;

	HC_Close_Segment();

	if (reader) {
		result = reader->FileInputToImageKey(H_ASCII_TEXT("D:/a.jpg"), &image_key, temp_seg, &input_options);
	}

	if( result != InputOK )
	{
		Base::Console().Log("Failed to read the image file. Please choose a different file as texture source");
	}



	// copy this image to TEXTURE_DATA_SEGMENT with a unique name
	float position[3];
	int   size[2];
	char  fmt[MVO_BUFFER_SIZE];
	char	myname[MVO_BUFFER_SIZE];

	HC_Edit_Image_Options(image_key,"name=my_image");
	HC_Show_Image_Size( image_key, &position[0], &position[1], &position[2],
		fmt, &size[0], &size[1]);


	HC_Set_Color("faces = (diffuse = my_image)");

	// DAMN. Can't even get something as simple as the format of the image that easy
	QString image_specs(fmt);
	int name_index = image_specs.find( ',' );
	if( name_index != -1 )
		image_specs = image_specs.left( name_index  );	// get everything except name 

	QString image_name = "A";
	image_specs = image_specs + ", local, name = " + image_name;	// attach new name    
	//// we have the image data, insert in our TEXTURE_DATA_SEGMENT
	//HoopsStyle *currentstyle = m_SelectedStyleWindow->GetStyle();
	//HC_Open_Segment_By_Key(currentstyle->GetStyleLibrary()->GetTextureKey());
	//char tempimagename[4096];
	//char tempimagename2[4096];
	//HoopsTexture::GetImageName(image_key,tempimagename);
	//HC_KEY tempimagekey;
	//bool clash = false;
	//HC_Begin_Contents_Search(".", "images");
	//while (HUtility::FindContents(tempimagekey))
	//{
	//	HoopsTexture::GetImageName(tempimagekey,tempimagename2);
	//	if (strcmp(tempimagename, tempimagename2) == 0)
	//		clash = true;

	//}
	//HC_End_Contents_Search();
	//if (!clash)
	//	HC_Move_By_Key(image_key,".");
	//else
	//	HC_Delete_By_Key(image_key);
	//// define a texture with this image and chosen parameters
	//CString texture_name, texture_specs;
	//texture_name = image_name;
	//texture_name.MakeLower();
	//texture_specs.Format(_T("source = %s, parameter source = world, down-sampling = on, decimation filter = mipmap,  value scale = (0.0,1.0), tiling = repeat"), image_name);
	//HC_Set_Rendering_Options ("perspective correction");
	//HC_Define_Local_Texture( H_ASCII_TEXT(texture_name), H_ASCII_TEXT(texture_specs));
	//CString tname = "faces = (diffuse = red " + texture_name + ", specular = grey)";
	//m_CurrentlySelectedTexture = texture_name;
	//HC_Close_Segment();


	//return true;
}



void ModelViewManager::reset()
{
	clearView();

	openRootSegment();

	//HC_Insert_Distant_Light(0.0, 0.0, 2.0);//
	//HC_Set_Color("lights=(R=0.8,G=0.8,B=0.8)");//
	

	createAll(myDocument()->getActiveItem());
	closeSegment();
}

void ModelViewManager::redraw()
{
	redrawAll(myDocument()->getActiveItem());
}

void ModelViewManager::redrawAll( BaseItem* item )
{
	AppearanceItem* appearance=item->getAppearance();
	HC_KEY key=appearance->getHCKey();
	if(key!=-1){
		HC_Open_Segment_By_Key(key);
		HoopsUpdator()->onItemUpdating(appearance);
		onVisibilityChanged(appearance);
		onApplyMaterial(appearance);
		HC_Close_Segment();
	}

	int n=item->count();
	for(int i=0;i<n;++i)
		redrawAll(item->child(i));
}


void ModelViewManager::clearView()
{
	clearHCKey(myDocument()->getAssembly());
	_hcMap.clear();

	ViewManager::clearView();
}

void ModelViewManager::clearHCKey( BaseItem* item )
{
	AppearanceItem* appItem=item->getAppearance();
	if(appItem){
		appItem->setHCKey(-1);
		appItem->setHCSubKey(0,-1);
		appItem->setHCSubKey(1,-1);
		appItem->setHCSubKey(2,-1);
	}
	int n=item->count();
	for(int i=0;i<n;++i)
		clearHCKey(item->child(i));
}



