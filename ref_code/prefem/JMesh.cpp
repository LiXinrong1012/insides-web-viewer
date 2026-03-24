#include "prefem/JMesh.h"
#include "prefem/DBStruct.h"
#include "Mesh_Func.h"

#include <QtCore>


PP_ELTYPE*	JMesh::m_ElType=NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JMesh::JMesh()
{
	// Basic Entity
	m_arNode = NULL;
	m_arElement = NULL;

	m_dwNode = 0;
	m_dwElement = 0;
	m_dwElementNode = 0;
	m_dwElementLink = 0;

	// Element Accumulated Array
	m_arElementCheck = NULL;
	m_arElementNode =  NULL;
	m_arElementLink = NULL;

	m_fRange[0] = m_fRange[1] = m_fRange[2] = 0.0;
	m_fRange[3] = m_fRange[4] = m_fRange[5] = 1.0;

	m_bLoaded = false;
}

JMesh & JMesh::operator =(const JMesh &other)
{
	if(this == &other)
		return *this;
	DeleteAllData();
	DeepCopy(*this,other);
	return *this;
}

JMesh::JMesh( const JMesh& mesh )
{
	DeepCopy(*this,mesh);	
}

void JMesh::DeepCopy( JMesh& dst,const JMesh& mesh )
{
	memcpy(&dst,&mesh,sizeof(JMesh));

	if(dst.m_dwNode>0){
		dst.m_arNode=new PP_NODE[dst.m_dwNode];
		memcpy(dst.m_arNode,mesh.m_arNode,sizeof(PP_NODE)*dst.m_dwNode);
	}
	if(dst.m_dwElement>0){
		dst.m_arElement=new PP_ELEMENT[dst.m_dwElement];
		memcpy(dst.m_arElement,mesh.m_arElement,sizeof(PP_ELEMENT)*dst.m_dwElement);
	}
	if(dst.m_dwElementNode>0){
		dst.m_arElementNode=new DWORD[dst.m_dwElementNode];
		memcpy(dst.m_arElementNode,mesh.m_arElementNode,sizeof(DWORD)*dst.m_dwElementNode);
	}
	if(dst.m_dwElementLink>0){
		dst.m_arElementLink=new DWORD[dst.m_dwElementLink];
		memcpy(dst.m_arElementLink,mesh.m_arElementLink,sizeof(DWORD)*dst.m_dwElementLink);
	}
}

JMesh::~JMesh()
{
	Clear();
}

void JMesh::DeleteAllData()
{
	DELETE_ARRAY(m_arNode)
	DELETE_ARRAY(m_arElement)
	DELETE_ARRAY(m_arElementNode)
	DELETE_ARRAY(m_arElementLink)
}

void JMesh::ResetAllCount()
{
	m_dwNode = 0;
	m_dwElement = 0;
	m_dwElementNode = 0;
	m_dwElementLink = 0;
}


bool JMesh::WriteData(const QString& filename)
{
	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);   // we will serialize the data into the file

	if(!file.isOpen())
		return false;

	bool re=WriteData(&out);

	file.close();
	return re;
}

bool JMesh::WriteData( QDataStream* stream )
{
	if(!stream)
		return false;

	unsigned long		ulSize = 0 ;
	VB_DB_ENTITY		dbEntity ;
	//VersionInfo			version ;

	//version = getVersion() ;

	//dbEntity.dbType   = VB_DB_MESH;
	//dbEntity.dbSize   = sizeof(VB_DB_ENTITY) ; // temporary size
	//dbEntity.dbVersion = version;
	//dbEntity.dbRes1		 = 0 ;
	//dbEntity.dbRes2		 = 0 ;
	//
	//qint64 pos1=stream->device()->pos();
	//stream->writeBytes((char*)&dbEntity,sizeof(VB_DB_ENTITY));

	// Data Count
	(*stream)<<(quint32)(m_dwNode)
		<<(quint32)(m_dwElement)
		<<(quint32)(m_dwElementNode)
		;
	
	stream->writeRawData((char*)m_arNode,sizeof(PP_NODE)*m_dwNode);
	stream->writeRawData((char*)m_arElement,sizeof(PP_ELEMENT)*m_dwElement);
	stream->writeRawData((char*)m_arElementNode,sizeof(DWORD)*m_dwElementNode);

	// recalculate the db size
	//qint64 pos2=stream->device()->pos();
	//ulSize= pos2-pos1 - sizeof(VB_DB_ENTITY) ;

	//dbEntity.dbType   = VB_DB_MESH ;
	//dbEntity.dbSize   = ulSize ;		// original data size 
	//dbEntity.dbVersion = version;
	//dbEntity.dbRes1		 = 0 ;
	//dbEntity.dbRes2		 = 0 ;

	//stream->device()->seek(pos1);
	//stream->writeBytes((char*)&dbEntity,sizeof(VB_DB_ENTITY));

	//stream->device()->seek(pos2);
	
	//WriteAsciiData("asciiMeshdata.txt");
	return true;
}

bool JMesh::WriteAsciiData(const QString& lpszFilePath)
{
	QFile data(lpszFilePath);
	if (data.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream out(&data);
		//out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7;

		// Data Count
		out<<"NodeCnt: "<< m_dwNode<<endl;
		out<<"ElementCnt: "<<m_dwElement<<endl;
		out<<"ElementNodeCnt: "<< m_dwElementNode<<endl;
		int i;
		out<<"Node Coor"<<endl;
		for (i=0; i<m_dwNode; i++)
		{
			out<<QString("%1 %2 %3 %4\n").arg(i).arg(m_arNode[i].xyz[0])
				.arg(m_arNode[i].xyz[1]).arg(m_arNode[i].xyz[2]);
		}
		out<<"Elem \n";
		for (i=0; i<m_dwElement; i++)
		{
			out<<QString("%1 %2 %3 %4\n").arg(i).arg(m_arElement[i].TID)
				.arg(m_arElement[i].NSI).arg(m_arElement[i].LSI);
		}
		out<<"ElemNode \n";
		for (i=0; i<m_dwElementNode; i++)
		{
			out<<m_arElementNode[i]<<" ";
		}

		return true;
	}
	else
		return false;
}

bool JMesh::LoadData(const QString& lpszFilePath)
{
	QFile file(lpszFilePath);
	file.open(QIODevice::ReadOnly);
	if(!file.isOpen())
		return false;

	QDataStream in(&file);    // read the data serialized from the file

	return LoadData(&in);
}

bool JMesh::LoadData( QDataStream* stream )
{
	bool bStatus = false ;
	QDataStream& in=*stream;

	//unsigned long		ulSize = 0 ;
	//VB_DB_ENTITY		dbEntity ;
	////VersionInfo			version  ;
	////version = getVersion() ;

	//in.readRawData((char*)&dbEntity,sizeof(VB_DB_ENTITY));

	// 清空原有网格数据
	DeleteAllData();
	ResetAllCount();

	// Data Count
	quint32 tmp;
	in>>tmp; m_dwNode=tmp;
	in>>tmp; m_dwElement=tmp;
	in>>tmp; m_dwElementNode=tmp;

	if(m_dwNode>0){
		m_arNode = new PP_NODE[ m_dwNode ] ;	// 节点数组
		in.readRawData((char*)m_arNode,sizeof(PP_NODE)*m_dwNode);
	}
	if(m_dwElement > 0){
		m_arElement = new PP_ELEMENT[ m_dwElement ];	// 网格数组
		in.readRawData((char*)m_arElement,sizeof(PP_ELEMENT)*m_dwElement);
	}
	if( m_dwElementNode > 0 )
	{
		m_arElementNode = new DWORD[m_dwElementNode];	// 所有单元节点数组
		in.readRawData((char*)m_arElementNode,sizeof(DWORD)*m_dwElementNode);
	}


	CreateLink();
	//CreateFace();
	//CreateLine();

	SetRange();
	return bStatus;
}

// Set Model size Range
void JMesh::SetRange()
{
	DWORD i,j;
	DWORD nNode;

	bool bRangeStart = true;

	for(i=0;i<m_dwElement;i++)
	{
		nNode = m_ElType[m_arElement[i].TID].dwNodeCnt;		// Why here is not NodeCnt?	
		
		for(j=0;j<nNode;j++){
			float* xyz = m_arNode[ m_arElementNode[m_arElement[i].NSI + j] ].xyz;
			if( bRangeStart ){
				m_fRange[0] = m_fRange[3] = xyz[0];
				m_fRange[1] = m_fRange[4] = xyz[1];
				m_fRange[2] = m_fRange[5] = xyz[2];
				bRangeStart = false;
			}
			else{			
				if( xyz[0]  < m_fRange[0] ) m_fRange[0] = xyz[0];
				if( xyz[1]  < m_fRange[1] ) m_fRange[1] = xyz[1];
				if( xyz[2]  < m_fRange[2] ) m_fRange[2] = xyz[2];

				if( xyz[0]  > m_fRange[3] ) m_fRange[3] = xyz[0];
				if( xyz[1]  > m_fRange[4] ) m_fRange[4] = xyz[1];
				if( xyz[2]  > m_fRange[5] ) m_fRange[5] = xyz[2];
				//if( fabs(xyz[0]) > 1e10 ||  fabs(xyz[1]) > 1e10 ||  fabs(xyz[2]) > 1e10 )
				//	xyz[0] = xyz[0];
			}
		}
	}	
}

BOOL JMesh::CompareElementLink(DWORD dwA, DWORD dwB)
{
	DWORD i, j, cnt = 0;
	DWORD dwEA = getLowBit5(dwA);
	DWORD dwEB = getLowBit5(dwB);

	DWORD dwDA = getUpBit5(dwA);
	DWORD dwDB = getUpBit5(dwB);

	DWORD dwNA = m_ElType[m_arElement[dwEA].TID].dwLinkNodeCnt[dwDA];
	DWORD dwNB = m_ElType[m_arElement[dwEB].TID].dwLinkNodeCnt[dwDB];

	if( dwNA != dwNB ) return FALSE;

	for(i=0;i<dwNA;i++)
		for(j=0;j<dwNA;j++){
			if( m_arElementNode[ m_arElement[dwEA].NSI + m_ElType[m_arElement[dwEA].TID].dwLinkNode[dwDA][i] ]
				== m_arElementNode[ m_arElement[dwEB].NSI + m_ElType[m_arElement[dwEB].TID].dwLinkNode[dwDB][j] ] ) cnt++;
		}
	if( cnt == dwNA ) return TRUE;

	return FALSE;
}



/************************************************************************/
/* Function: Create element link relationship
	comment: Store element link relationship in array m_arElementLink. 
		Each face(for 3D element) or line(for 2D element) has a linked 
		element. if no element with that face or line, m_arElementLink
		to the face or line is 0xffffffff
                                                                        */
/************************************************************************/
BOOL JMesh::CreateLink()
{
	DWORD i, j, k;
	DWORD dwSum;


	// Check Data is available
	if( m_dwElement == 0 || m_dwNode == 0 ) return TRUE;
	
	DWORD dwLink = 0;
	for(i=0;i<m_dwElement;i++)
	{
		if (m_arElementCheck && m_arElementCheck[i]!=0)
		{
			continue;
		}
		m_arElement[i].LSI = dwLink;
		dwLink += m_ElType[m_arElement[i].TID].dwLinkCnt;
	}
	m_dwElementLink = dwLink;

	// temperary Hash Table generation
	PP_HASHITEM * arHashTable = new PP_HASHITEM [HASH_TABLE_SIZE];
	memset( arHashTable, 0, sizeof(PP_HASHITEM) * HASH_TABLE_SIZE );

	DWORD	nTID;	// Type
	DWORD   nLink;	// Link Number 

	// Start Element Loop
	for(i=0; i<m_dwElement; i++)
	{
		if (m_arElementCheck && m_arElementCheck[i]!=0)
		{
			continue;
		}
		nTID = m_arElement[i].TID;
		nLink = m_ElType[nTID].dwLinkCnt;

		for(j=0; j<nLink; j++)
		{
			dwSum = 0;
			for(k=0;k<m_ElType[nTID].dwLinkNodeCnt[j];k++)
			{
				dwSum += m_arElementNode[m_arElement[i].NSI + m_ElType[nTID].dwLinkNode[j][k]];
			}
			AddHashItem(arHashTable, dwSum % HASH_TABLE_SIZE, makeBit5(j,i));
		}
	}

	///////////////////////////
	// Create Link

	// Link Array Initialize
	DELETE_ARRAY(m_arElementLink)
	m_arElementLink = new DWORD [ m_dwElementLink ];
	memset( m_arElementLink, 0xff, sizeof(DWORD) * m_dwElementLink );
	
	// Compare
	DWORD dwTemp;

	for(i=0;i<HASH_TABLE_SIZE;i++)
	{
		for(j=0;j<arHashTable[i].nCnt;j++)
		{
			for(k=j+1;k<arHashTable[i].nCnt;k++){

				if( CompareElementLink( arHashTable[i].pData[j], arHashTable[i].pData[k] ) ){
					
					// Set Link [j] and [k]
					m_arElementLink[ m_arElement[getLowBit5(arHashTable[i].pData[j])].LSI + getUpBit5(arHashTable[i].pData[j])] = arHashTable[i].pData[k];
					m_arElementLink[ m_arElement[getLowBit5(arHashTable[i].pData[k])].LSI + getUpBit5(arHashTable[i].pData[k])] = arHashTable[i].pData[j];

					// swap [j+1] and [k]
					dwTemp = arHashTable[i].pData[j+1];
					arHashTable[i].pData[j+1] = arHashTable[i].pData[k];
					arHashTable[i].pData[k] = dwTemp;
			
					j++;
					break;
				}
			}
		}
	}

	// Delete Hash Table
	DeleteHashTable(arHashTable);

	return TRUE;

}

void JMesh::MakeHex()
{
	DeleteAllData();
	ResetAllCount();
	
	// Data Count
	const int nodeCnt = 10;
	m_dwNode = nodeCnt;
	m_dwElement = 2;
	m_dwElementNode = 12;
	
	int i,j;
	float hexnode[nodeCnt][3] = {
		-1,-1,-1,
		1,-1,-1,
		1,1,-1,
		-1,1,-1,
		-1,-1,1,
		1,-1,1,
		1,1,1,
		-1,1,1,
		-1,-2,-1,
		1,-2,-1
	};
	m_arNode = new PP_NODE[ m_dwNode ] ;
	for( i=0; i<m_dwNode; i++ )
	{
		m_arNode[i].NID = i+1;
		for( j=0; j<3; j++)
			m_arNode[i].xyz[j] = hexnode[i][j];
	}
	m_arElement = new PP_ELEMENT[ m_dwElement ];
	m_arElement[0].EID = 1;
	m_arElement[0].TID = EL_HEX8;
	m_arElement[0].NSI = 0;
	m_arElement[0].LSI = 0;

	m_arElement[1].EID = 2;
	m_arElement[1].TID = EL_QUAD4;
	m_arElement[1].NSI = 8;
	m_arElement[1].LSI = 0;

	m_arElementNode = new DWORD[m_dwElementNode];
	for( i=0; i<8; i++ )
	{
		m_arElementNode[i] = i;
	}
	m_arElementNode[8] = 0;
	m_arElementNode[9] = 8;
	m_arElementNode[10] = 9;
	m_arElementNode[11] = 1;
	
	CreateLink();
	//CreateFace();
	//CreateLine();
	
	SetRange();
	
}


void JMesh::resetFace(int * arElementCheck)
{
	m_arElementCheck = arElementCheck;

	CreateLink();
	//CreateFace();
	//CreateLine();
}

DWORD JMesh::getNodeIndexfromId( DWORD id )
{
	DWORD i;
	for (i=0; i<m_dwNode; i++)
	{
		if( m_arNode[i].NID == id )
			return i;
	}
	return -1;
}

DWORD JMesh::getElemIndexfromId( DWORD id )
{
	DWORD i;
	for (i=0; i<m_dwElement; i++)
	{
		if( m_arElement[i].EID == id )
			return i;
	}
	return -1;
}


bool JMesh::EndImportData()
{

	CreateLink();

	SetRange();

	SetLoaded(true);
	return true;
}

float JMesh::GetRangeLength()
{
	float* sizeRagnge = GetSizeRange();

	float len = sqrt( (sizeRagnge[3]-sizeRagnge[0])*(sizeRagnge[3]-sizeRagnge[0]) +
		(sizeRagnge[4]-sizeRagnge[1])*(sizeRagnge[4]-sizeRagnge[1]) +
		(sizeRagnge[5]-sizeRagnge[2])*(sizeRagnge[5]-sizeRagnge[2]) );
	
	return len;
}

void JMesh::GetElementCenter(DWORD eInd, double &cX, double &cY, double &cZ)
{
	cX = cY = cZ = 0;
	int nTID = m_arElement[eInd].TID;
	int cnt = m_ElType[nTID].dwNodeCnt;
	if (cnt <= 0)
	{
		return;
	}
	int i;
	for (i=0; i<cnt; i++)
	{
		cX += m_arNode[m_arElementNode[m_arElement[eInd].NSI+i]].xyz[0];
		cY += m_arNode[m_arElementNode[m_arElement[eInd].NSI+i]].xyz[1];
		cZ += m_arNode[m_arElementNode[m_arElement[eInd].NSI+i]].xyz[2];
	}
	cX /= cnt;
	cY /= cnt;
	cZ /= cnt;
}

DWORD JMesh::GetMaxNodeId()
{
	DWORD CurMaxNodeID = 0;
	for(int i=0;i<m_dwNode;i++)
	{
		if(CurMaxNodeID<m_arNode[i].NID)
			CurMaxNodeID = m_arNode[i].NID;
	}
	return CurMaxNodeID;
}

DWORD JMesh::GetMaxElemId()
{
	DWORD CurMaxElemID = 0;
	for(int i=0;i<m_dwElement;i++)
	{
		if(CurMaxElemID<m_arElement[i].EID)
			CurMaxElemID = m_arElement[i].EID;
	}
	return CurMaxElemID;
}

void JMesh::SetNodeCnt( DWORD dwN )
{
	m_dwNode = dwN; 
}

void JMesh::AddNodeCnt( DWORD dwN )
{
	PP_NODE* pTemp = new PP_NODE[dwN];
	for(int i=0;i<dwN;i++)
	{
		if(i<m_dwNode)
		{
			pTemp[i].NID = m_arNode[i].NID;
			pTemp[i].xyz[0] = m_arNode[i].xyz[0];
			pTemp[i].xyz[1] = m_arNode[i].xyz[1];
			pTemp[i].xyz[2] = m_arNode[i].xyz[2];
		}

		else
		{
		pTemp[i].NID = m_arNode[m_dwNode-1].NID;
		pTemp[i].xyz[0] = m_arNode[m_dwNode-1].xyz[0];
		pTemp[i].xyz[1] = m_arNode[m_dwNode-1].xyz[1];
		pTemp[i].xyz[2] = m_arNode[m_dwNode-1].xyz[2];
		}
			
	}
	
	delete [] m_arNode;
	m_arNode = pTemp;
	m_dwNode = dwN; 
}

void JMesh::createShellMesh()
{
	DeleteAllData();
	ResetAllCount();

	int width=10;
	int height=50;
	int nodeCnt=width*height;
	PP_NODE* nodes=new PP_NODE[nodeCnt];
	for(int i=0;i<width;++i)
	{
		for(int j=0;j<height;++j)
		{
			PP_NODE& node=nodes[j*width+i];
			node.xyz[0]=i;
			node.xyz[1]=j;
			node.xyz[2]=0;
			node.NID=j*width+i;
		}
	}

	int elemCnt=(width-1)*(height-1);
	PP_ELEMENT* elements=new PP_ELEMENT[elemCnt];
	memset(elements,0,sizeof(PP_ELEMENT)*elemCnt);
	int elemNodeCnt=elemCnt*4;
	DWORD*	elemNodes=new DWORD[elemNodeCnt];
	for(int i=1;i<width;++i)
	{
		for(int j=1;j<height;++j)
		{
			int index=(j-1)*(width-1)+(i-1);
			PP_ELEMENT& elem=elements[index];
			elem.EID=index;
			elem.TID=EL_QUAD4;
			elem.NSI=index*4;

			int a=index*4;
			elemNodes[a]=(j-1)*width+(i-1);
			elemNodes[a+1]=(j)*width+(i-1);
			elemNodes[a+2]=(j)*width+(i);
			elemNodes[a+3]=(j-1)*width+(i);
		}
	}

	m_dwNode=nodeCnt;
	m_dwElement=elemCnt;
	m_dwElementNode=elemNodeCnt;
	m_arNode=nodes;
	m_arElement=elements;
	m_arElementNode=elemNodes;
	CreateLink();

	SetRange();

	//WriteData("planner_shell.dat");
}

void JMesh::createLineMesh()
{
	DeleteAllData();
	ResetAllCount();

	int nodeCnt=21;
	PP_NODE* nodes=new PP_NODE[nodeCnt];
	for(int i=0;i<nodeCnt;++i)
	{
		PP_NODE& node=nodes[i];
		node.xyz[0]=2.0*i/nodeCnt;
		node.xyz[1]=2.0*i/nodeCnt;
		node.xyz[2]=0;
		node.NID=i+1;
	}

	int elemCnt=nodeCnt-1;
	PP_ELEMENT* elements=new PP_ELEMENT[elemCnt];
	memset(elements,0,sizeof(PP_ELEMENT)*elemCnt);
	int elemNodeCnt=elemCnt*2;
	DWORD*	elemNodes=new DWORD[elemNodeCnt];
	for(int i=0;i<elemCnt;++i)
	{
		PP_ELEMENT& elem=elements[i];
		elem.EID=i;
		elem.TID=EL_LINE2;
		elem.NSI=2*i;

		int a=i*2;
		elemNodes[a]=i;
		elemNodes[a+1]=i+1;
	}

	m_dwNode=nodeCnt;
	m_dwElement=elemCnt;
	m_dwElementNode=elemNodeCnt;
	m_arNode=nodes;
	m_arElement=elements;
	m_arElementNode=elemNodes;
	CreateLink();

	SetRange();
}

void JMesh::Clear()
{
	DeleteAllData();
	ResetAllCount();
}
