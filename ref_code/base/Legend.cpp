/***************************************************************************
 *   Copyright (c) 2010-2011 Jerry He                                      *
 *                                                                         *
 *   This file is part of the QtMudyPlot development system.               *
 *                                                                         *
 *   All this libraries can be used freely,  with any purpose,             * 
 *   including commercial applications, and to alter it or                 * 
 *   redistribute it.                                                      *
 *                                                                         *
 *   But the following restrictions must be obeyed.                        *
 *                                                                         *
 *   1. The origin of this software must not be misrepresented;            *
 *   you must not claim that you wrote the original software.              * 
 *   If you use this software in a product, an acknowledgment in the       * 
 *   product documentation would be appreciated but is not required.       *
 *                                                                         * 
 *   2. Altered source versions must be plainly marked as such, and        *
 *   must not be misrepresented as being the original software.            *
 *                                                                         *
 *   3. This notice may not be removed or altered from any source          * 
 *   distribution.                                                         *
 *                                                                         *
 *   If you have any problems or advices, you can contact me.              *
 *   E-mail: hejw06@gmail.com                                              *
 *                                                                         *
 ***************************************************************************/





#include "pre_compile.h"
#include "Legend.h"
#include <assert.h>
#include "Console.h"

//to-do: more Jerry 2011.12.12.
//#include "dataIn/dataIn.h"

using namespace  Base;

Legend::Legend()
:_levelCount(5)
{
	_visual=false;

	m_ColorNum = 5;
	m_ColorPos[0] = 0.0f;	
	m_ColorSet[0][0] = 1.0f;
	m_ColorSet[0][1] = 0.0f;
	m_ColorSet[0][2] = 0.0f;
	m_ColorPos[1] = 0.25f;	
	m_ColorSet[1][0] = 1.0f;
	m_ColorSet[1][1] = 1.0f;
	m_ColorSet[1][2] = 0.0f;
	m_ColorPos[2] = 0.5f;	
	m_ColorSet[2][0] = 0.0f;
	m_ColorSet[2][1] = 1.0f;
	m_ColorSet[2][2] = 0.0f;
	m_ColorPos[3] = 0.75f;	
	m_ColorSet[3][0] = 0.0f;
	m_ColorSet[3][1] = 1.0f;
	m_ColorSet[3][2] = 1.0f;
	m_ColorPos[4] = 1.0f;	
	m_ColorSet[4][0] = 0.0f;
	m_ColorSet[4][1] = 0.0f;
	m_ColorSet[4][2] = 1.0f;
	m_ColorPos[5] = 1.0f;	
	m_ColorSet[5][0] = 0.5f;
	m_ColorSet[5][1] = 0.5f;
	m_ColorSet[5][2] = 0.5f;

	_strNumFormat = "%-4.2e";
	setMinMax(0,100,8);
}

Legend::~Legend()
{
}

int Legend::getColorIndex(float value)const
{
	for(int i=0;i<_levelCount;++i)
		if(value<_levelVec[i])
			return i;
	return _levelCount;
}

bool Legend::setLevelList(const vector<float>& vec)
{
	int vecSize=vec.size();
	if(vecSize==0||
		vecSize>MAX_SEGMENT)
		return false;

	for(int i=0;i<vecSize;++i)
		_levelVec[i]=vec[i];
	_levelCount=vecSize;
	resetColorVec();
	return true;
}
bool Legend::setLevelList(const float* vec,int size)
{
	if(size<=0||
		size>MAX_SEGMENT)
		return false;
	for(int i=0;i<size;++i)
		_levelVec[i]=vec[i];
	_levelCount=size;
	resetColorVec();
	return true;
}

int Legend::getLevelSize()const
{
	return _levelCount;
}

/*!Get color count. Color count should equal level count add 1.*/
int Legend::getColorSize()const
{
	return _levelCount+1;
}

/*!Get a value_type pointer to color data. Size of this pointer equals getColorSize()*3.*/
const Legend::value_type* Legend::getColorPtr()const
{
	return (value_type*)_colorVec;
}
const Legend::value_type* Legend::getLevelPtr()const
{
	return _levelVec;
}

void Legend::setMinMax(float fmin,float fmax,int levelSize)
{
	if(levelSize<=0)
		return;
	_levelCount=levelSize;
	if(levelSize==1){
		_levelVec[0]=(fmin+fmax)/2;
		resetColorVec();
		return;
	}
		
	float delta=(fmax-fmin)/(levelSize-1);
	for(int i=0;i<levelSize;++i){
		_levelVec[i]=fmin+delta*i;
	}
	resetColorVec();
}

		
void Legend::resetColorVec()
{
	int colorCount=getColorSize();
	if(colorCount<=0)
		return;
	if(colorCount==1){
		getColor(0,(value_type*)_colorVec);
		return;
	}
	for(int i=0;i<colorCount;++i){
		getColor((float)i/(colorCount-1),&_colorVec[i][0]);
	}
	return;
}

void Legend::getColor(float fratio,value_type*rgb)
{
	//return pp::getColor(fratio,rgb);

	float value = 1.0f - fratio;
	value_type* m_colBuff=rgb;

	int i;

	if( value < 0. ){
		memcpy( m_colBuff, m_ColorSet[0], 3 * sizeof(float) );
		return;
	}

	for( i=1; i < m_ColorNum; i++ ){

		if( value < m_ColorPos[i] ){
			m_colBuff[0] =  
				m_ColorSet[i-1][0] + 
				( ( m_ColorSet[i][0] - m_ColorSet[i-1][0] ) /
				( m_ColorPos[i] - m_ColorPos[i-1] ) )
				* ( value - m_ColorPos[i-1] ) ;
			m_colBuff[1] =  
				m_ColorSet[i-1][1] + 
				( ( m_ColorSet[i][1] - m_ColorSet[i-1][1] ) /
				( m_ColorPos[i] - m_ColorPos[i-1] ) )
				* ( value - m_ColorPos[i-1] ) ;
			m_colBuff[2] =  
				m_ColorSet[i-1][2] + 
				( ( m_ColorSet[i][2] - m_ColorSet[i-1][2] ) /
				( m_ColorPos[i] - m_ColorPos[i-1] ) )
				* ( value - m_ColorPos[i-1] );
			return;
		}
	}
	if( value > 1.0f ){
		memcpy( m_colBuff, m_ColorSet[m_ColorNum], 3 * sizeof(float) );
		return;
	}

	if( value == 1. ){
		memcpy( m_colBuff, m_ColorSet[m_ColorNum-1], 3 * sizeof(float) );
		return;
	}

	m_colBuff[0]=m_colBuff[1]=m_colBuff[2]=1.0f;
	return;
}
/*
void Legend::SetMinMax( float fMin, float fMax ) 
{
	m_fMin = fMin;
	m_fMax = fMax; 

	float range = m_fMax - m_fMin;
	int i;
	for(i=0; i<m_legendNum; i++)
	{
		
	}

	m_colSegment[0] = RGB(0,0,255);
	m_colSegment[m_legendNum] = RGB(255,0,0);
	for(i=1;i< m_legendNum; i++){
		m_colSegment[i] = GetColor( (float)(i-1) / (float)(m_legendNum - 2 )   );
	}
}

COLORREF Legend::GetColor(float fRatio)
{
	float value = 1.0f - fRatio;

	float m_colBuff[3];

	int i;

	if( value < 0. ){
		memcpy( m_colBuff, m_ColorSet[0], 3 * sizeof(float) );
		return RGB( (int)(m_colBuff[0] * 255),  (int)(m_colBuff[1] * 255), (int)(m_colBuff[2] * 255) );
	}

	for( i=1; i < m_ColorNum; i++ ){

		if( value < m_ColorPos[i] ){
			m_colBuff[0] =  
				m_ColorSet[i-1][0] + 
				( ( m_ColorSet[i][0] - m_ColorSet[i-1][0] ) /
				( m_ColorPos[i] - m_ColorPos[i-1] ) )
				* ( value - m_ColorPos[i-1] ) ;
			m_colBuff[1] =  
				m_ColorSet[i-1][1] + 
				( ( m_ColorSet[i][1] - m_ColorSet[i-1][1] ) /
				( m_ColorPos[i] - m_ColorPos[i-1] ) )
				* ( value - m_ColorPos[i-1] ) ;
			m_colBuff[2] =  
				m_ColorSet[i-1][2] + 
				( ( m_ColorSet[i][2] - m_ColorSet[i-1][2] ) /
				( m_ColorPos[i] - m_ColorPos[i-1] ) )
				* ( value - m_ColorPos[i-1] );
			return RGB( (int)(m_colBuff[0] * 255),  (int)(m_colBuff[1] * 255), (int)(m_colBuff[2] * 255) );
		}
	}
	if( value > 1.0f ){
		memcpy( m_colBuff, m_ColorSet[m_ColorNum], 3 * sizeof(float) );
		return RGB( (int)(m_colBuff[0] * 255),  (int)(m_colBuff[1] * 255), (int)(m_colBuff[2] * 255) );
	}

	if( value == 1. ){
		memcpy( m_colBuff, m_ColorSet[m_ColorNum-1], 3 * sizeof(float) );
		return RGB( (int)(m_colBuff[0] * 255),  (int)(m_colBuff[1] * 255), (int)(m_colBuff[2] * 255) );
	}

	return RGB(255,255,255);
}


void Legend::SetLevel(int levelNum,float* levelData)
{
	assert(levelNum>2);
	m_legendNum=levelNum;
	delete[]m_fSegmentVal;
	delete[]m_colSegment;
	m_fSegmentVal=new float[levelNum];
	
	m_colSegment=new COLORREF[levelNum+1];
	int i;
	for( i=0; i<m_legendNum; i++)
	{
		m_fSegmentVal[i] = levelData[i];
	}
	m_colSegment[0] = RGB(0,0,255);
	m_colSegment[m_legendNum] = RGB(255,0,0);
	for(i=1;i< m_legendNum; i++){
		m_colSegment[i] = GetColor( (float)(i-1) / (float)(m_legendNum - 2 )   );
	}
}
*/


float Base::Legend::mapDataToColorIndex( float value ) const
{
	if(value<_levelVec[0])
		return 0.0f;
	if(value>_levelVec[_levelCount-1])
		return _levelCount;

	int i;
	for(i=1;i<_levelCount;++i)
	{
		if(value<_levelVec[i])
			break;
	}
	if(i==_levelCount)
		return _levelCount-1;

	return (value - _levelVec[i-1]) / (_levelVec[i] - _levelVec[i-1]) +i;
}


