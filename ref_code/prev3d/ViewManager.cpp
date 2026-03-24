#include "ViewManager.h"
#include "PreHQWidget.h"

#include "HMaterialLibrary.h"
#include "HIOManager.h"
#include "HDB.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>

#include "precore/appearance.h"
#include "precore/BaseItem.h"

ViewManager::ViewManager(PreHQWidget* w)
	:_preHQWidget(w)
	,_rootKey(-1)
	,_viewType(ViewManager::BaseViewType)
{
}


ViewManager::~ViewManager(void)
{
	if(_rootKey!=-1)
		HC_Delete_By_Key(_rootKey);
}

void ViewManager::clearView()
{
	if(openRootSegment()){
		HC_Flush_Contents(".","everything");
		closeSegment();
	}
}


bool ViewManager::openRootSegment()
{
	if(_rootKey!=-1){
		HC_Open_Segment_By_Key(_rootKey);
		return true;
	}

	if(!_preHQWidget)
		return false;

	HC_KEY rootkey=_preHQWidget->GetHoopsModel()->GetModelKey();
	HC_Open_Segment_By_Key(rootkey);
	_rootKey=HC_Open_Segment("");
	HC_Set_Color("faces=(transmission=black)");

	//HC_Define_System_Options("warnings=on, errors=on");

	HC_Close_Segment();
	HC_Close_Segment();

	return openRootSegment();
}

void ViewManager::closeSegment()
{
	HC_Close_Segment();
}


static void _updateOneColor(const AppearanceItem* item,AppearanceItem::ColorItem t,
	const char* typeStr)
{
	if(item->getUseColor(t)){
		QColor color=item->getColor(t);
		QString str=QString("%4=(R=%1 G=%2 B=%3)")
			.arg(color.redF()).arg(color.greenF()).arg(color.blueF()).arg(typeStr);
		HC_Set_Color(str.toStdString().c_str());
	}
	else
		HC_UnSet_One_Color(typeStr);
}

void ViewManager::updateMaterial( BaseItem* item )
{
	QString tmpStr = item->get("MATERIAL");
	tmpStr = tmpStr.replace("\"","");
	QString tmpFileName = qApp->applicationDirPath()+"/material/"+tmpStr;
	
	if(QFile::exists(tmpFileName))
	{
		QFileInfo info(tmpFileName);
		QString suffix = info.suffix();
		static QMap<QString,QString> textureList;

		if(!textureList.contains(info.fileName()))
		{
			HC_KEY imageKey;
			HC_KEY ttKey = HC_Open_Segment("/image");
			HInputHandler* handler = HDB::GetHIOManager()->GetInputHandler(suffix);
			handler->FileInputToImageKey(tmpFileName.toStdString().c_str(),&imageKey,ttKey,new HInputHandlerOptions());

			char tmpCh[MVO_BUFFER_SIZE];
			sprintf(tmpCh,"name=%s",info.fileName().toStdString().c_str());
			HC_Edit_Image_Options(imageKey,tmpCh); 

			char tmpCh2[MVO_BUFFER_SIZE];
			sprintf(tmpCh2,"tiling=on, parameterization source = uv, source = %s",info.fileName().toStdString().c_str());

			char tmpTextureName[MVO_BUFFER_SIZE];
			sprintf(tmpTextureName,"texture_%s",info.fileName().toStdString().c_str());
			HC_Define_Texture(tmpTextureName,tmpCh2);

			textureList[info.fileName()] = tmpTextureName;
			HC_Close_Segment();
		}
		
		char ch[MVO_BUFFER_SIZE];
		sprintf(ch,"faces=%s",textureList[info.fileName()].toStdString().c_str());
		HC_Set_Color(ch);
	}
	///else中的材质库暂时废弃
	else
	{
		tmpStr = tmpStr.replace(".","/");
		static bool flag = false;
		static HMaterialLibrary hmat;

		if(!flag)
		{
			QString dir = QApplication::applicationDirPath()+"/material_library";
			QDir tmp (dir);
			if(!tmp.exists())
			{
				QMessageBox msg;
				msg.setText("The material library is not exists");
				msg.exec();
				return ;
			}
			hmat.RegisterMaterials (H_FORMAT_TEXT ("%s", dir.toStdString().c_str()));
			flag = true;
		}

		const char* list = hmat.GetMaterialList();
		const char* env_list = hmat.GetEnvironmentList();

		hmat.SetEnvironment ("sea");
		hmat.ApplyStyles();
		hmat.ApplyMaterial (tmpStr.toStdString().c_str());
	}

//	return ;///暂时注释掉下面的灯光更改

	if(item->getAppearance()->getColor(AppearanceItem::Color_Face).isValid())
	{
		char ch[MVO_BUFFER_SIZE];
		char tmpCh[MVO_BUFFER_SIZE];

		float tmpR = (float)item->getAppearance()->getColor(AppearanceItem::Color_Face).red()/255.f;
		float tmpG = (float)item->getAppearance()->getColor(AppearanceItem::Color_Face).green()/255.f;
		float tmpB = (float)item->getAppearance()->getColor(AppearanceItem::Color_Face).blue()/255.f;

		sprintf(tmpCh,"(R=%f G=%f B=%f)",tmpR,tmpG,tmpB);
	//	sprintf(ch,"ambient=%s,specular=%s white,emission=%s",tmpCh,tmpCh,tmpCh);
		sprintf(ch,"ambient=%s",tmpCh);
		HC_Set_Color(ch);
	}
}

void ViewManager::updateVisibility( const AppearanceItem* item )
{
	if(item->isVisibilityUndefined()){
		HC_UnSet_Visibility();
	}
	else{
		static char paras[128];
		for(int i=0;i<AppearanceItem::Count;++i){
			AppearanceItem::VisibilityType t=item->getVisibilityType((AppearanceItem::VisibilityItem)i);
			if(t==AppearanceItem::Visual){
				sprintf(paras,"%s=on",item->getVisibilityHoopsKey((AppearanceItem::VisibilityItem)i));
				HC_Set_Visibility(paras);
			}
			else if(t==AppearanceItem::Invisual){
				sprintf(paras,"%s=off",item->getVisibilityHoopsKey((AppearanceItem::VisibilityItem)i));
				HC_Set_Visibility(paras);
			}
			else
				HC_UnSet_One_Visibility(item->getVisibilityHoopsKey((AppearanceItem::VisibilityItem)i));
		}
	}

	_updateOneColor(item,AppearanceItem::Color_Edge,"edges");
	_updateOneColor(item,AppearanceItem::Color_Face,"faces");
	_updateOneColor(item,AppearanceItem::Color_Line,"lines");
	_updateOneColor(item,AppearanceItem::Color_Point,"vertices");

	float trans=item->getTransparency();
	if(trans==0){
		;//HC_UnSet_One_Color("faces=transmission");
	}
	else{
		QString str=QString("face=(transmission=(r=%1 g=%2 b=%3))")
			.arg(trans)
			.arg(trans)
			.arg(trans);
		HC_Set_Color(str.toStdString().c_str());
	}
}

void ViewManager::onVisibilityChanged(BaseItem* item )
{
	AppearanceItem* appItem=getAppearance(item);
	HC_KEY key=appItem->getHCKey();
	if(key!=-1 && !appItem){
		HC_Open_Segment_By_Key(key);
		updateVisibility(appItem);
		HC_Close_Segment();
	}
}

void ViewManager::onVisibilityChanged( AppearanceItem* item )
{
	HC_KEY key=item->getHCKey();
	if(key==-1)
		return;
	HC_Open_Segment_By_Key(key);
	updateVisibility(item);
	HC_Close_Segment();
}

void ViewManager::onApplyMaterial( BaseItem* item )
{
	if(item->get("MATERIAL").isEmpty())
		return;

	AppearanceItem* appItem=getAppearance(item);
	HC_KEY key=appItem->getHCKey();
	if(key!=-1 && !appItem)
	{
		HC_Open_Segment_By_Key(key);
		updateMaterial(item);
		HC_Close_Segment();
	}
}

void ViewManager::onApplyMaterial( AppearanceItem* item )
{
	BaseItem* baseItem = item->getBaseItem();
	if(!baseItem)
		return;

	if(baseItem->get("MATERIAL").isEmpty())
		return;

	HC_KEY key = item->getHCKey();
	if(key == -1)
		return;
	HC_Open_Segment_By_Key(key);
	updateMaterial(baseItem);
	HC_Close_Segment();
}

HC_KEY ViewManager::getHCKey( BaseItem* item )
{
	AppearanceItem* a=getAppearance(item);
	return a?a->getHCKey():-1;
}

BaseItem* ViewManager::getBaseItem( HC_KEY key )
{
	AppearanceItem* a=getAppearance(key);
	return a?a->getBaseItem():NULL;
}

void ViewManager::insertTitleText(const QString& text,float textSize)
{
	HPoint pos(0.0, 0.0, 1.0), target(0.0, 0.0, -1.0), up(0.0, 1.0, 0.0);
	float acpect=(float)(5/3.0);
	float height=1.0;
	float width=1.0;
	HC_Set_Camera( &pos, &target, &up, width, height, "orthographic" );
	//HC_Set_Handedness("left");
	HC_Set_Selectability("geometry=off");
	HC_Set_Visibility("cutting planes = off");
	HC_Set_Rendering_Options("depth range = (0,1e-4), simple shadow=off, anti-alias = text");
	HC_Set_Heuristics("no backplane culls");
	HC_Set_Color("edge=line=text=R=0 G=0 B=0");
	HC_Set_Camera_Projection("stretched");

	QString tmp=QString("size=%1 oru, size tolerance=0 points, no transforms, line spacing=1").arg(textSize);
	HC_Set_Text_Font(tmp.toStdString().c_str());
	HC_Set_Text_Alignment("<^");

	QString str=text;

	HC_Insert_Text( -width*0.45, height*0.45, 0.0f, str.toStdString().c_str());
}
