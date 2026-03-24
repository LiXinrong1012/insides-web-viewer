#include "test.h"
#include "precore/precore_data.h"
#include "precore/modeldocument.h"
#include "UAPI_.h"
#include "pretdy/TDYParameters.h"

typedef INSIDES::BaseItem RigidPart;

using namespace INSIDES;

void my_debug_example_crank(Assembly* assembly);
void my_debug_example_fem(Assembly* assembly);

BaseItem* _my_insert_marker()
{
	static int marker_id=1;
	QString name=QString("Marker%1").arg(marker_id++);
	BaseItem* item=new BaseItem(name);
	item->setCategory(TDY_PRE_CATE_MARKER);
	(*item)["QR"]="1,0,0";
	(*item)["XR"]="1,0,0"; 
	(*item)["YR"]="0,1,0"; 
	return item;
}

BaseItem* _my_insert_rigid()
{
	RigidPart* rigid=new RigidPart();
	rigid->setCategory(TDY_PRE_CATE_RIGIDPART);
	(*rigid)["QG"]="1,2,3";
	return rigid;
}


void my_debug_example( Assembly* assembly )
{
	my_debug_example_crank(assembly); 
	//my_debug_example_fem(assembly);
}


Assembly* createExample()
{
	Assembly* assembly=new Assembly();
	my_debug_example_crank(assembly);
	//my_debug_example_fem(assembly);
	return assembly;
}

void my_debug_example_fem( Assembly* assembly )
{
	assembly->setKeyname("Flexible-body example");
	FEMPartBaseItem* fempart=new FEMPartBaseItem();
	fempart->setKeyname("Quad");
	PREI_Add_Item(assembly->getParts(),fempart);

	BaseItem* inst=fempart->createInstance();
	inst->setKeyname("Quad-1");
	PREI_Add_Item(assembly->getInstances(),inst);

}

void my_debug_example_crank( Assembly* assembly )
{
	assembly->setKeyname("Crank");
	ParametersBaseItem* paraItem=(ParametersBaseItem*)assembly->getOrCreateParameters();
	TDYParameters* paras=new TDYParameters();
	paras->add("L1","1");
	paras->add("L2","2");
	paras->add("ANGLE","PI");
	paraItem->setTDYParameters(paras);
	paraItem->refreshChildren();

	// Çú±ú
	BaseItem* partHead=assembly->getParts();
	BaseItem* rigidQubing=_my_insert_rigid();
	rigidQubing->setKeyname("Qubing");
	(*rigidQubing)["IP"]="1,1,1";
	(*rigidQubing)["QG"]="0,0,0";
	(*rigidQubing)["MASS"]="1";
	PREI_Add_Item(partHead,rigidQubing);

	paraItem=new ParametersBaseItem();
	paras=new TDYParameters();
	paras->add("L1","1");
	paraItem->setTDYParameters(paras);
	paraItem->refreshChildren();
	PREI_Add_Item(rigidQubing,paraItem);

	BaseItem* marker1_1=new BaseItem("marker_1");
	marker1_1->setCategory(TDY_PRE_CATE_MARKER);
	(*marker1_1)["QR"]="-$L1/2,0,0";
	PREI_Add_Item(rigidQubing,marker1_1);

	BaseItem* marker1_2=new BaseItem("marker_2");
	marker1_2->setCategory(TDY_PRE_CATE_MARKER);
	(*marker1_2)["QR"]="$L1/2,0,0";
	PREI_Add_Item(rigidQubing,marker1_2);

	BaseItem* qubingShape=new BaseItem("Display");
	qubingShape->setCategory(TDY_PRE_CATE_SHAPE);
	(*qubingShape)["SHAPEKEYNAME"]="Cylinder";
	(*qubingShape)["DATAVEC"]="0.05,$L1";
	(*qubingShape)["ZR"]="1,0,0";
	(*qubingShape)["XR"]="0,1,0";
	PREI_Add_Item(rigidQubing,qubingShape);

	BaseItem* qubingInstance=rigidQubing->createInstance();
	qubingInstance->setKeyname("Qubing_1");
	(*qubingInstance)["CENTER"]="$L1/2,0,0";
	PREI_Add_Item(assembly->getInstances(),qubingInstance);


	// Á¬¸Ë
	BaseItem* rigidLiangan=_my_insert_rigid();
	rigidLiangan->setKeyname("LianGan");
	(*rigidLiangan)["IP"]="1,1,1";
	(*rigidLiangan)["QG"]="0,0,0";
	(*rigidLiangan)["MASS"]="1";
	PREI_Add_Item(partHead,rigidLiangan);

	paraItem=new ParametersBaseItem();
	paras=new TDYParameters();
	paras->add("L2","2");
	paraItem->setTDYParameters(paras);
	paraItem->refreshChildren();
	PREI_Add_Item(rigidLiangan,paraItem);

	BaseItem* marker2_1=new BaseItem("marker_1");
	marker2_1->setCategory(TDY_PRE_CATE_MARKER);
	(*marker2_1)["QR"]="-$L2/2,0,0";
	PREI_Add_Item(rigidLiangan,marker2_1);

	BaseItem* marker2_2=new BaseItem("marker_2");
	marker2_2->setCategory(TDY_PRE_CATE_MARKER);
	(*marker2_2)["QR"]="$L2/2,0,0";
	PREI_Add_Item(rigidLiangan,marker2_2);

	BaseItem* lianganShape=new BaseItem("Display");
	lianganShape->setCategory(TDY_PRE_CATE_SHAPE);
	(*lianganShape)["SHAPEKEYNAME"]="Cylinder";
	(*lianganShape)["DATAVEC"]="0.05,$L2";
	(*lianganShape)["ZR"]="1,0,0";
	(*lianganShape)["XR"]="0,0,1";
	PREI_Add_Item(rigidLiangan,lianganShape);

	BaseItem* lianganInstance=rigidLiangan->createInstance();
	(*lianganInstance)["CENTER"]="$L1+$L2/2,0,0";
	lianganInstance->setKeyname("Liangan_1");
	PREI_Add_Item(assembly->getInstances(),lianganInstance);


	// »¬¿é
	BaseItem* rigidHuakuai=_my_insert_rigid();
	rigidHuakuai->setKeyname("Huakuai");
	(*rigidHuakuai)["IP"]="1,1,1";
	(*rigidHuakuai)["QG"]="0,0,0";
	(*rigidHuakuai)["MASS"]="1";
	PREI_Add_Item(partHead,rigidHuakuai);

	BaseItem* marker3_1=new BaseItem("marker_1");
	marker3_1->setCategory(TDY_PRE_CATE_MARKER);
	(*marker3_1)["QR"]="0,0,0";
	PREI_Add_Item(rigidHuakuai,marker3_1);

	BaseItem* marker3_2=new BaseItem("marker_2");
	marker3_2->setCategory(TDY_PRE_CATE_MARKER);
	(*marker3_2)["QR"]="0,0,0";
	(*marker3_2)["ZG"]="1,0,0";
	(*marker3_2)["XG"]="0,1,0";
	PREI_Add_Item(rigidHuakuai,marker3_2);

	BaseItem* huakuaiShape=new BaseItem("Display");
	huakuaiShape->setCategory(TDY_PRE_CATE_SHAPE);
	(*huakuaiShape)["SHAPEKEYNAME"]="Box";
	(*huakuaiShape)["DATAVEC"]="0.2,0.2,0.2";
	(*huakuaiShape)["ZR"]="1,0,0";
	(*huakuaiShape)["XR"]="0,0,1";
	PREI_Add_Item(rigidHuakuai,huakuaiShape);

	BaseItem* huakuaiInstance=rigidHuakuai->createInstance();
	(*huakuaiInstance)["CENTER"]="$L1+$L2,0,0";
	huakuaiInstance->setKeyname("Huakuai_1");
	PREI_Add_Item(assembly->getInstances(),huakuaiInstance);


	// Ground
	BaseItem* myground=new BaseItem("Ground");
	myground->setCategory(TDY_PRE_CATE_GROUND);
	PREI_Add_Item(assembly,myground,4);

	//marker / 1, ground, qg = 0, 0, 0
	//marker / 2, ground, qg = 0, 0, 0, zg = 1, 0, 0, xg = 0, 1, 0
	BaseItem* markerG_1=new BaseItem("marker_1");
	markerG_1->setCategory(TDY_PRE_CATE_MARKER);
	(*markerG_1)["QG"]="0,0,0";
	PREI_Add_Item(myground,markerG_1);

	BaseItem* markerG_2=new BaseItem("marker_2");
	markerG_2->setCategory(TDY_PRE_CATE_MARKER);
	(*markerG_2)["QG"]="0,0,0";
	(*markerG_2)["ZG"]="1,0,0";
	(*markerG_2)["XG"]="0,1,0";
	PREI_Add_Item(myground,markerG_2);

	//marker / 3, part=qubing_1, qg = 0, 0, 0, zg = 1, 0, 0, xg = 0, 1, 0
	BaseItem* markerQubing_1=new BaseItem("markerQubing_1");
	markerQubing_1->setCategory(TDY_PRE_CATE_MARKER);
	(*markerQubing_1)["QG"]="0,0,0";
	(*markerQubing_1)["ZG"]="1,0,0";
	(*markerQubing_1)["XG"]="0,1,0";
	PREI_Add_Item(qubingInstance,markerQubing_1);

	//joint / 1, I = qubing_1.marker_1,  J = marker_1 , revolute
	//joint / 2, I = qubing_1.marker_2,  J = liangan_1.marker_1, revolute
	//joint / 3, I = liangan_1.marker_2, J = huakuai_1.marker_1, inline
	//joint / 4, I = huakuai_1.marker_2, J = marker_2, translational
	//motion / 1, joint = joint_1, function = "step(time, 0, 0, 10, $angle)"
	BaseItem* constraints=assembly->child(7);
	BaseItem* joint1=new BaseItem("joint1");
	joint1->setCategory(TDY_PRE_CATE_JOINT);
	(*joint1)["I"]="qubing_1.marker_1";
	(*joint1)["J"]="marker_1";
	(*joint1)["TYPE"]="revolute";
	PREI_Add_Item(constraints,joint1);

	BaseItem* joint2=new BaseItem("joint2");
	joint2->setCategory(TDY_PRE_CATE_JOINT);
	(*joint2)["I"]="qubing_1.marker_1";
	(*joint2)["J"]="liangan_1.marker_1";
	(*joint2)["TYPE"]="revolute";
	PREI_Add_Item(constraints,joint2);

	BaseItem* joint3=new BaseItem("joint3");
	joint3->setCategory(TDY_PRE_CATE_JOINT);
	(*joint3)["I"]="liangan_1.marker_2";
	(*joint3)["J"]="huakuai_1.marker_1";
	(*joint3)["TYPE"]="inline";
	PREI_Add_Item(constraints,joint3);

	BaseItem* joint4=new BaseItem("joint4");
	joint4->setCategory(TDY_PRE_CATE_JOINT);
	(*joint4)["I"]="huankuai_1.marker_2";
	(*joint4)["J"]="marker_2";
	(*joint4)["TYPE"]="translational";
	PREI_Add_Item(constraints,joint4);

	BaseItem* motion=new BaseItem("motion_1");
	motion->setCategory(TDY_PRE_CATE_MOTION);
	(*motion)["JOINT"]="joint1";
	(*motion)["FUNCTION"]="\"step(time,0,0,10,$angle)\"";

	PREI_Add_Item(constraints,motion);

	//INTPAR / start_t = 0, end_t = 10, error = 1e-3, hmax = 1
	BaseItem* intPara=new BaseItem("sol");
	intPara->setCategory(TDY_PRE_CATE_INTPAR);
	(*intPara)["START_T"]="0";
	(*intPara)["END_T"]="10";
	(*intPara)["ERROR"]="1e-3";
	(*intPara)["HMAX"]="1";
	BaseItem* intParas=assembly->child(assembly->count()-1);
	PREI_Add_Item(intParas,intPara);

}
