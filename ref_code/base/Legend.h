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


#if !defined(AFX_LEGEND_H__4A73C309_0EAF_4118_AC78_51F2C6F51A24__INCLUDED_)
#define AFX_LEGEND_H__4A73C309_0EAF_4118_AC78_51F2C6F51A24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 


#include "base/base_global.h"
#include <string>
#include <vector>

using namespace std;

namespace Base
{
	
	class BASE_EXPORT Legend  
	{
	public:
		typedef float value_type;

		Legend();
		virtual ~Legend();

		bool isVisual()const{return _visual;}
		void setVisual(bool b){_visual=b;}

		int getColorIndex(float value)const;
		float mapDataToColorIndex(float value)const;

		bool setLevelList(const vector<float>& vec);
		bool setLevelList(const float* vec,int size);

		/*!Get level count.*/
		int getLevelSize()const;

		/*!Get color count. Color count should equal level count add 1.*/
		int getColorSize()const;

		/*!Get a value_type pointer to color data. Size of this pointer equals getColorSize()*3.*/
		const value_type* getColorPtr()const;
		const value_type* getLevelPtr()const;

		void setMinMax(float fmin,float fmax,int levelSize);

		const char* getValueStrFormat()const{return _strNumFormat.c_str();}
		void setValueStrFormat(const char* c){_strNumFormat=c;}
		void setValueStrFormat(const string& c){_strNumFormat=c;}

		/// Get color using a normalized ration.
		void getColor(float fratio,value_type*rgb);

	private:
		enum {MAX_SEGMENT=30};
		bool	_visual;

		int		_levelCount;	/*!< Level Count. */
		value_type _colorVec[MAX_SEGMENT][3];	/*!< Color vector list.*/
		value_type _levelVec[MAX_SEGMENT];		/*!< Level vecotr list.*/

		int		 m_ColorNum;
		float	 m_ColorPos[6];
		float	 m_ColorSet[6][3];

		string  _strNumFormat;

		void resetColorVec();

	};

}
#endif 
