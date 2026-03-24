#include "HoopsUpdator.h"
#include "precore/appearance.h"
#include "precore/precore_data.h"
#include "precore/itemlist.h"
#include "precore/modeldocument.h"
#include "precore/DataExchangeAPI.h"

#include "base/Console.h"
#include "base/ShapeDef.h"
#include "base/AppConfiguration.h"
#include "base/ParametersManager.h"

#include "osg/Vec3d"
#include "osg/Quat"
#include "osg/Matrixd"
#include "osg/Matrixf"

#include "coresps/HoopsUltility.h"
#include "coresps/ShapeManager.h"

#include "precore/BaseItemHelper.h"

#include "BaseItemPosHelper.h"
#include "BaseItemDrawHelper.h"
#include "Hoops3DConfiguration.h"

// hoops related
#include "HDB.h"
#include "HIOManager.h"
#include "parasolid_kernel.h"
#include "hp_bridge.h"

#include <QFile>

using namespace osg;


static void _reset_model_matrix()
{
	static Matrixf ma;
	HC_Set_Modelling_Matrix(ma.ptr());
}

static void update_model_matrix(BaseItem* item)
{
	if(item->getMatrix())
	{
		const INSIDES::Matrix* ma = item->getMatrix();
		HC_Set_Modelling_Matrix(item->getMatrix()->ptr());
	}
}


static void _update_model_marker(AppearanceItem* item)
{
	BaseItem* modelItem=item->getBaseItem();
	BaseItem* parentItem=modelItem->getParent();
	if(parentItem && parentItem->getCategory()==TDY_PRE_CATE_FEMPART)
	{
		if(!Hoops3DConfiguration::instance()->getShowFEMMarker())
			return;
	}

	ShapeManager::instance()->includeShape("Marker");

	//BaseItemPosHelper::updateMarker(modelItem);
	update_model_matrix(modelItem);
}

static BaseItem* getJointMarker(BaseItem* item,const QString& keyName)
{
	QString markerName=item->get(keyName);
	if(markerName.isEmpty())
		return NULL;

	Assembly* parentAssebmly=item->getParentAssembly();
	return myDocument()->findItemWithoutFolder(markerName,parentAssebmly);
}
static void _update_model_joint(AppearanceItem* item)
{
	BaseItem* modelItem=item->getBaseItem();

	if(!Hoops3DConfiguration::instance()->getShowConstraints())
		return;

	QString jointType=modelItem->get("JOINTTYPE");
	bool showIMarker=AppConfiguration::instance()->getParametersManager()->get("ShowIMarker","Display")->getVariant().toBool();
	bool showJMarker=AppConfiguration::instance()->getParametersManager()->get("ShowJMarker","Display")->getVariant().toBool();

		
	BaseItem* IMarker=getJointMarker(modelItem,"I");
	BaseItem* JMarker=getJointMarker(modelItem,"J");

	if(IMarker && showIMarker){
		HC_Open_Segment("I");
		Matrixf matrix;
		//Assembly* assem=BaseItemHelper::getParentAssembly(modelItem);
		//BaseItemPosHelper::getGeneralItemOnOne(IMarker,matrix,assem);
		IMarker->getRelativeMatrix(matrix,modelItem->getParentAssembly());
		HC_Set_Modelling_Matrix(matrix.ptr());
		QString tmp=jointType+".I";
		if(!ShapeManager::instance()->includeShape(tmp.toStdString().c_str()))
			ShapeManager::instance()->includeShape("XXX.I");
		HC_Close_Segment();
	}
	if(JMarker && showJMarker){
		HC_Open_Segment("J");
		Matrixf matrix;
		//Assembly* assem=BaseItemHelper::getParentAssembly(modelItem);
		//BaseItemPosHelper::getGeneralItemOnOne(JMarker,matrix,assem);
		JMarker->getRelativeMatrix(matrix,modelItem->getParentAssembly());
		HC_Set_Modelling_Matrix(matrix.ptr());
		QString tmp=jointType+".J";
		if(!ShapeManager::instance()->includeShape(tmp.toStdString().c_str()))
			ShapeManager::instance()->includeShape("XXX.J");

		HC_Close_Segment();
	}

}

static void _update_model_force(AppearanceItem* item)
{
	BaseItem* modelItem=item->getBaseItem();
	if (!modelItem->hasKey("CMS"))
		return;
	QStringList markerNames=modelItem->get("CMS").split(",");
	std::vector<osg::Vec3f> allPos;
	
	foreach(QString name,markerNames)
	{
		Assembly* parentAssebmly=modelItem->getParentAssembly();
		BaseItem* marker=myDocument()->findItemWithoutFolder(name,parentAssebmly);
		if(marker==NULL)
			continue;

		Matrixf matrix;
		marker->getRelativeMatrix(matrix,modelItem->getParentAssembly());
		osg::Vec3f pos=matrix.getTrans();
		allPos.push_back(pos);
	}

	HC_Open_Segment("muscles");
	
	float lineWidth=3;
	if(modelItem->hasKey("LINEWIDTH"))
		lineWidth=modelItem->get("LINEWIDTH").toFloat();

	HC_Set_Line_Weight(lineWidth);

	//QColor color=path->getLineColor();
	//QString str=QString("%4=(R=%1 G=%2 B=%3)")
	//	.arg(color.redF()).arg(color.greenF()).arg(color.blueF()).arg("line");
	//HC_Set_Color(str.toStdString().c_str());

	for(int i=0;i<allPos.size()-1;i++)
	{
		HC_Insert_Line(allPos[i][0],allPos[i][1],allPos[i][2],allPos[i+1][0],allPos[i+1][1],allPos[i+1][2]);
	}
	HC_Close_Segment();


}

static bool _readX_TFile(const QString& fileName)
{
	PK_PART_receive_o_t options;
	PK_ERROR_code_t		result;

	PK_PART_receive_o_m(options);

	QString s = fileName;

	options.transmit_format = PK_transmit_format_text_c;

	result = HP_Read_Xmt_File(s.toStdString().c_str(), 0, 0,0, &options);
	return result==0;
}

static void _update_model_stl(AppearanceItem* item)
{
	static bool init_hp=false;
	if(!init_hp)
	{
		QString path="D:/tsinghuaDir/INSViewerPlugins/src/hp_bridge/schema";
		HP_Init(path.toStdString().c_str(),PK_LOGICAL_false);
		init_hp=true;
	}

	QString path=item->getBaseItem()->get("FILENAME");
	if(path.isEmpty()){
		Base::Console().Warning("No file name assigned while updating stl item.");
		return;
	}

	if(!QFile::exists(path)){
		QString a=QString("No file name£º%1").arg(path);
		Base::Console().Warning(a.toStdString().c_str());
		return;
	}
	QString ext=path.right(3);

	HC_KEY hckey=item->getHCKey();
	HInputHandler* h=NULL;
	if(!ext.compare("stl",Qt::CaseInsensitive))
		h=HDB::GetHIOManager()->GetInputHandler("stl");
	else if(!ext.compare("hsf",Qt::CaseInsensitive))
		h=HDB::GetHIOManager()->GetInputHandler("hsf");
	else if(!ext.compare("ply",Qt::CaseInsensitive))
		h=HDB::GetHIOManager()->GetInputHandler("ply");
	else if(!ext.compare("x_t",Qt::CaseInsensitive))
	{
		if(!_readX_TFile(path))
			Base::Console().Error("No X_T file.");
	}

	if(h)
	{
		HInputHandlerOptions options;
		h->FileInputByKey(path.toStdString().c_str(),hckey,&options);
	}


	//QString scale=item->getBaseItem()->get("SCALE");
	//if(!scale.isEmpty()){
	//	float vScale[1];
	//	DataExchangeAPI::String2Vec(NULL,scale,vScale,1);
	//	BaseItemPosHelper::updateGraphic(item->getBaseItem(),vScale[0]);
	//}
	//else
	//	BaseItemPosHelper::updateGraphic(item->getBaseItem());

	update_model_matrix(item->getBaseItem());
}

static void _update_model_shape(AppearanceItem* item)
{
	BaseItem* modelItem=item->getBaseItem();
	QString shapeKeyName=modelItem->get("SHAPEKEYNAME");
	QString dataVec=modelItem->get("DATAVEC");
	vector<float> floatVec;
	
	DataExchangeAPI::PString2FloatVec(modelItem,dataVec,floatVec);

	Base::ShapeInput shapeInput(shapeKeyName.toStdString(),floatVec);
	ShapeManager::instance()->importShape(&shapeInput);

	item->setVisibilityType(AppearanceItem::Edge,AppearanceItem::Invisual);
	item->setVisibilityType(AppearanceItem::Marker,AppearanceItem::Invisual);
	item->setVisibilityType(AppearanceItem::Vertex,AppearanceItem::Invisual);

	//BaseItemPosHelper::updateGraphic(modelItem);
	update_model_matrix(modelItem);
}

static void _update_model_rigidpart(AppearanceItem* item)
{
	BaseItem* modelItem=item->getBaseItem();

	//BaseItemPosHelper::updateInstanceRigid(modelItem);
	update_model_matrix(modelItem);
}

static void _update_model_assembly(AppearanceItem* item)
{
	BaseItem* modelItem=item->getBaseItem();

	//BaseItemPosHelper::updateInstance(modelItem);
	update_model_matrix(modelItem);
}



static void _update_model_fempart(AppearanceItem* item)
{
	HC_Flush_Geometry(".");
	BaseItem* modelItem=item->getBaseItem();

	//BaseItemPosHelper::updateInstance(modelItem);
	update_model_matrix(modelItem);

	BaseItemDrawHelper::drawFEMPart((FEMPartBaseItem*)modelItem,item);

	HC_Set_Visibility("face=off");
}


void registerModelUpdatingFunctions()
{
	HoopsUpdatorSingleton* updator=HoopsUpdator();
	updator->registerItemUpdating(TDY_PRE_CATE_MARKER,_update_model_marker);
	updator->registerItemUpdating(TDY_PRE_CATE_STL,_update_model_stl);
	updator->registerItemUpdating(TDY_PRE_CATE_SHAPE,_update_model_shape);
	updator->registerItemUpdating(TDY_PRE_CATE_RIGIDPART,_update_model_rigidpart);
	updator->registerItemUpdating(TDY_PRE_CATE_ASSEMBLY,_update_model_assembly);
	updator->registerItemUpdating(TDY_PRE_CATE_FEMPART,_update_model_fempart);
	updator->registerItemUpdating(TDY_PRE_CATE_JOINT,_update_model_joint);
	updator->registerItemUpdating(TDY_PRE_CATE_LOAD,_update_model_force);

}
