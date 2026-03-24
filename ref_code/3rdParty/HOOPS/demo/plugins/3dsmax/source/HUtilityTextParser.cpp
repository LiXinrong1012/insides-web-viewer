//
// Copyright (c) 2000 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/3dsmax/source/HUtilityTextParser.cpp,v 1.3 2007-08-30 20:00:38 stage Exp $
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HUtilityTextParser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HUtilityTextParser::HUtilityTextParser()
{
	m_BufferPos		= 0;
	m_pTextBuffer	= 0;
	m_BufferLength	= 0;
	m_OldBufferPos	= 0;

}

HUtilityTextParser::~HUtilityTextParser()
{

}

void HUtilityTextParser::InsertBuffer(const char *buffer, unsigned int bufferlength)
{

	m_pTextBuffer = buffer;
	m_BufferLength = bufferlength;
	m_BufferPos = 0;



}

bool HUtilityTextParser::ParseBuffer(const char *searchbuffer,  char *tempbuf, int &dnum, const delimiter_t *dlist, unsigned int length, bool checkforquote)
{
	InsertBuffer(searchbuffer, strlen(searchbuffer));
	return ParseBuffer(tempbuf, dnum, dlist, length, checkforquote);
}

bool HUtilityTextParser::ParseBuffer(char *tempbuf, int &dnum, const delimiter_t *dlist, unsigned int length, bool checkforquote)
{
 	int tbpos = 0;
	int level = 0;
	bool inquote = false;
	m_OldBufferPos = m_BufferPos;
	SetDelimiterList(dlist, length);
	while (1)
	{
		if (m_BufferPos>=m_BufferLength)
			return false;
		tempbuf[tbpos] = m_pTextBuffer[m_BufferPos];
 		if (checkforquote && tempbuf[tbpos] == 34)
			inquote = !inquote;

		if (!inquote && CheckAllDelimiters(true, tempbuf, tbpos, dnum))
		{
			tempbuf[0] = tempbuf[tbpos];
			tempbuf[1] = 0;
 			tbpos = 1;
			if (m_pDelimiterList[dnum].sd_exclude)
				tbpos = 0;
			m_StartChar = tempbuf[0];
 			m_BufferPos++;
			if (!m_pDelimiterList[dnum].ed)
				return true;

		
			while (1)
			{	
				if (m_BufferPos >= m_BufferLength)
				{
					m_BufferPos = m_OldBufferPos;
					return false;
				}
				tempbuf[tbpos] = m_pTextBuffer[m_BufferPos];
				
				if (checkforquote && tempbuf[tbpos] == 34)
					inquote = !inquote;
				if (!inquote && m_pDelimiterList[dnum].checkopenclose && CheckDelimiter(true, tempbuf, tbpos, dnum))
					level++;
				if (!inquote && CheckDelimiter(false, tempbuf, tbpos, dnum))
				{
					if (level == 0)
					{
						tempbuf[tbpos+1] = 0;
						m_EndChar = tempbuf[tbpos];
 						if (m_pDelimiterList[dnum].ed_exclude)
 							tempbuf[tbpos] = 0;
 
					m_BufferPos++;
					return true;				
					}
					else
						level --;

				}
				tbpos++;
				m_BufferPos++;
 
			}
		}
		tbpos++;
		m_BufferPos++;
		if (m_BufferPos >= m_BufferLength)
		{
			m_BufferPos = m_OldBufferPos;
			return false;
		}


	}
}

unsigned long HUtilityTextParser::FindNextChar(char *text, char c, unsigned long start)
{
	while (1)
	{
		if (text[start] == c)
			return start;
		start++;
		if (start >= strlen(text))
			return start;
	}
}

 

bool HUtilityTextParser::MultiCompare(char *text, char *ctext)
{
	char mc1[256];
	char mc2[256];
	unsigned long i1 = 0;
	unsigned long i2 = 0;
	while (1)
	{
		if ((FindNextChar(ctext, '|', i2) > (i2 + 1)) && strlen(ctext) > 1)
		{ 
			mc1[i1]   = ctext[i2];
			mc2[i1++] = ctext[i2+2];
			i2+=4;
		}
		else
		{
			mc1[i1] = ctext[i2++];
			mc2[i1++] = 0;
			i2++;
		}
		if (i2 >= strlen(ctext))
			break;
	}
	for (unsigned long i=0;i<i1;i++)
	{
		if (mc2[i] == 0)
		{
			if (text[0] == mc1[i])
				return true;
		}
		else
		{
			if (text[0] >= mc1[i] && text[0] <= mc2[i])
				return true;
		}
		
	}
	return false;
}
		
		

bool HUtilityTextParser::CheckDelimiter(bool startdelimiter, char *buf, unsigned int len, int dnum)
{
	buf[len+1] = 0;
	char tbuf[MVO_BUFFER_SIZE];
	char tbuf2[MVO_BUFFER_SIZE];
 	if (startdelimiter)
	{
		if (m_pDelimiterList[dnum].sd)
     		strcpy(tbuf, m_pDelimiterList[dnum].sd);

	}
	else
	{
		if (m_pDelimiterList[dnum].ed)
			strcpy(tbuf, m_pDelimiterList[dnum].ed);
	}

 	if (strlen(buf) > 0)
	{
		tbuf2[0] = buf[strlen(buf) - 1];
 		tbuf2[1] = 0;	
		if (MultiCompare(tbuf2, tbuf))
 			return true;
	}
	return false;
}


bool HUtilityTextParser::CheckAllDelimiters(bool startdelimiter, char *buf, unsigned int len, int &dnum)
{
 	for (unsigned long i=0;i<m_DelimterListLength;i++)
	{
		
		if (CheckDelimiter(startdelimiter, buf, len, i))
		{
			dnum = i;
			return true;
		}
	}
 	return false;
}




void HUtilityTextParser::SetDelimiterList(const delimiter_t *dlist, unsigned int length)
{
 	m_pDelimiterList = dlist;
	m_DelimterListLength = length;

}
