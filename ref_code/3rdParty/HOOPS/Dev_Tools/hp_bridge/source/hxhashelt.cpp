#include "hxhashelt.h"
#include <stdio.h> // for definition of 0
#include <assert.h>


extern unsigned char g_hash_level;

HXHashElt::HXHashElt(void* key, void* data)
{
 	m_Key = key;
	m_Data = data;
	m_Level = g_hash_level;
	m_pNext = 0;
}

HXHashElt::~HXHashElt()
{
	if (m_pNext)
		delete m_pNext;
}

HXHashElt* HXHashElt::FindContent( void* key )
{
	if (key == m_Key && m_Level==g_hash_level)
		return this;
	else
	{
		HXHashElt* e = m_pNext;
		while(e)
		{
			if (e->m_Key == key && e->m_Level==g_hash_level)
				return e;
			e = e->m_pNext;
		}

	}

	return 0;
}

HXHashElt* HXHashElt::AddContent( void* key, void* data )
{
	// add elements, sort ascending on key
	HXHashElt* e;
	HXHashElt* prev;
	HXHashElt* newElt;
	newElt = new HXHashElt(key, data);
	newElt->m_Level=g_hash_level;

 
	assert(newElt);
	if (key <= m_Key && m_Level==g_hash_level)
	{
		newElt->m_pNext = this;
		return newElt; // make this the new root of the list
	}
	else
	{
		e = this;
		do
		{
			prev = e;
			e = e->m_pNext;
		}
		while (e && (key > e->m_Key || e->m_Level!=g_hash_level));
		prev->m_pNext = newElt;
		newElt->m_pNext = e;
	}

	return this;
}

HXHashElt* HXHashElt::DeleteContent( void* key, void* data )
{
	HXHashElt* e;
	HXHashElt* prev;
	// delete only the element which contains both key and data

	if ((key == m_Key) && (data == m_Data) && (m_Level==g_hash_level))
	{
		e = m_pNext;
		m_pNext = 0; // prevent recursive delete
		delete this;
		return e;
	}
	else
	{
		e = this;
		do
		{
			prev = e;
			e = e->m_pNext;
		}
		while (e && ((key != e->m_Key) || (data != e->m_Data)  || (e->m_Level!=g_hash_level)));
		if (e)
		{
			// we have a match; delete it
			prev->m_pNext = e->m_pNext;
			e->m_pNext = 0; // prevent recursive delete
			delete e;
		}
		else
		{
			assert(0); // not found
		}
		return this;
	}
}

HXHashElt* HXHashElt::DeleteContent( void* key )
{
	// delete all elements with the given key
	HXHashElt* e;
	HXHashElt* prev;

	if (key == m_Key && m_Level==g_hash_level)
	{
		// we have a match; delete it and all following 
		// elements with the same key (all should be clustered here)
		e = this;
		do
		{
			prev = e;
			e = e->m_pNext;
			prev->m_pNext = 0; // prevent recursive delete
			delete prev;
		}
		while (e && (key == e->m_Key && e->m_Level==g_hash_level));
		return e;
	}
	else
	{
		e = this;
		do
		{
			prev = e;
			e = e->m_pNext;
		}
		while (e && (key != e->m_Key || e->m_Level!=g_hash_level));
		if (e)
		{
			// we have a match; delete it and all following 
			// elements with the same key (all should be clustered here)
			do
			{
				prev->m_pNext = e->m_pNext;
				e->m_pNext = 0; // prevent recursive delete
				delete e;
				e = prev->m_pNext;
			}
			while (e && (key == e->m_Key && e->m_Level==g_hash_level));
		}
		else
		{
			assert(0); // not found
		}
		return this;
	}
}

