#include "hc.h"
#include "hp_map.h"
#include "hxhashelt.h"
#include <stdio.h> // for definition of 0
#include <assert.h>
#include <memory.h> // for memset
#include <stdlib.h>
#include "parasolid_kernel.h"
extern unsigned char g_hash_level;

#define HP_HASH_TABLE_SIZE 9997
//#define HP_HASH_TABLE_SIZE 17
//#define HP_HASH_TABLE_SIZE 1

HP_Map::HP_Map()
{
	m_pHP_list = 0;
	m_pPH_list = 0;
	m_TableSize = HP_HASH_TABLE_SIZE;
	m_NumEntries = 0;
}

HP_Map::~HP_Map()
{
	unsigned int i;
	if (m_pHP_list)
	{
		for (i = 0; i < m_TableSize; i++)
		{
			if (m_pHP_list[i])
			{
				delete m_pHP_list[i];
				m_pHP_list[i] = 0;
			}
		}
		delete m_pHP_list;
		m_pHP_list = 0;
	}
	if (m_pPH_list)
	{
		for (i = 0; i < m_TableSize; i++)
		{
			if (m_pPH_list[i])
			{
				delete m_pPH_list[i];
				m_pPH_list[i] = 0;
			}
		}
		delete m_pPH_list;
		m_pPH_list = 0;
	}
	
}

unsigned long HP_Map::Hash(HC_KEY key)
{
	unsigned long temp1, temp2;
	temp1 = key % 0xffff0000;
	temp2 = key % 0x0000ffff;
	return (temp1 * 3 + temp2 * 7) % m_TableSize;
}


unsigned long HP_Map::Hash(PK_ENTITY_t entity)
{
	unsigned long temp1, temp2;
	assert(m_TableSize > 0);
	temp1 = (unsigned long)entity % 0xffff0000;
	temp2 = (unsigned long)entity % 0x0000ffff;
	return (temp1 * 47 + temp2 * 7) % m_TableSize;
}


void HP_Map::ExpandHashTable( unsigned long newTableSize )
{
	unsigned long i;
	HXHashElt** oldAHlist;
	HXHashElt** oldHAlist;
 	unsigned long oldTableSize = m_TableSize;

	assert(m_pHP_list);
	assert(m_pPH_list);

//	assert(newTableSize > m_TableSize);
 
	oldHAlist = m_pHP_list;
	oldAHlist = m_pPH_list;
	
	m_pHP_list = 0;
	m_pPH_list = 0;

	m_pHP_list = new HXHashElt*[newTableSize];
	m_pPH_list = new HXHashElt*[newTableSize];

	assert(m_pHP_list);
	assert(m_pPH_list);

	if (!m_pHP_list) return; // fatal error condition here.
	if (!m_pPH_list) return;

	for (i = 0; i < newTableSize; i++)
	{
		m_pHP_list[i] = 0;
		m_pPH_list[i] = 0;
	}
	// the new hash table is now empty
	m_NumEntries = 0;
	m_TableSize = newTableSize;

	for (i = 0; i < oldTableSize; i++)
	{
		HXHashElt* e;
		
		// examine the old hash table for every entry in it.
		if (oldHAlist[i])
		{
			e = oldHAlist[i];

			// populate the new hash table with every entry found in the old table.
			// note that the new table is populated strictly from the HA map.  Which
			// should be exactly symmetrical to the AH map, so no problem.
			do
			{
				unsigned char sav_hash_level=g_hash_level;
				g_hash_level=e->GetLevel();			 
				AddMapping((HC_KEY)e->GetKey(), (PK_ENTITY_t)((HC_POINTER_SIZED_INT)e->GetData()));
				g_hash_level=sav_hash_level;
				e = e->GetNext();
			}
			while (e);
			
			delete oldHAlist[i]; // this call deletes the entire list whose root is at index i
		}
		if (oldAHlist[i])
		{
			delete oldAHlist[i]; // this call deletes the entire list whose root is at index i
		}
	}
	delete oldAHlist;
	delete oldHAlist;
}


bool HP_Map::AddMapping(HC_KEY key, PK_ENTITY_t entity)
{
	unsigned long index;
	bool result = true;
 

 	// expand hash table if desired.  we're sizing the table fairly generously here.
	if (m_NumEntries > m_TableSize)
		ExpandHashTable(m_TableSize*2);

	if (!m_pPH_list)
	{
		unsigned int i;

		m_pPH_list = new HXHashElt*[m_TableSize];
		if (!m_pPH_list) return false;
		for (i = 0; i < m_TableSize; i++)
		{
			m_pPH_list[i] = 0;
		}

		assert(!m_pHP_list);

		m_pHP_list = new HXHashElt*[m_TableSize];
		if (!m_pHP_list) return false;
		for (i = 0; i < m_TableSize; i++)
		{
			m_pHP_list[i] = 0;
		}

	}

	// insert the mapping in the Hoops-To-Acis hash table
	index = Hash(key);
	if (!m_pHP_list[index])
	{
		m_pHP_list[index] = new HXHashElt((void*)key, (void*)entity);
 		if (!m_pHP_list[index])
		{
			assert(0);
			result = false;
		}
	}
	else
	{
		m_pHP_list[index] = m_pHP_list[index]->AddContent((void*)key, (void*)entity);
	}
	// insert the mapping in the Acis-To-Hoops hash table
	index = Hash(entity);

	if (!m_pPH_list[index])
	{
		m_pPH_list[index] = new HXHashElt((void*)entity, (void*)key);
		if (!m_pPH_list[index])
		{
			assert(0);
			result = false;
		}
	}
	else
	{
		m_pPH_list[index] = m_pPH_list[index]->AddContent((void*)entity, (void*)key);
		assert(result);
	}
	m_NumEntries++;
	return result;
}

	// delete functions return false if item to be deleted could not be found.
bool HP_Map::DeleteMapping(HC_KEY key)
{
	// delete the mapping beween the given HOOPS key and any solid modeler entities
	// it's been mapped to
	unsigned long HPindex;
 	HXHashElt* found;
	HPindex = Hash(key);

	if (!m_pHP_list[HPindex])
		return false;
	
	// determine which solid modeler entities this key has been mapped to
	found = m_pHP_list[HPindex]->FindContent((void*)key);

	if (!found) return false;
	do
	{
		unsigned long PHindex;
		PHindex = Hash((PK_ENTITY_t)((HC_POINTER_SIZED_INT)found->GetData()));
		// for each solid modeler entity, delete the mapping from 
		// the solid modeler entity to this key.  These mappings should
		// exist, hence the assert.
		m_pPH_list[PHindex] = m_pPH_list[PHindex]->DeleteContent(found->GetData(), found->GetKey());

		found = found->GetNext();
		assert(m_NumEntries > 0);
		m_NumEntries--;
	}
	while (found && (found->GetKey() == (void*)key));

	m_pHP_list[HPindex] = m_pHP_list[HPindex]->DeleteContent((void*)key);
	return true;
}

bool HP_Map::DeleteMapping(PK_ENTITY_t entity)
{
	// delete the mapping beween the given HOOPS key and any solid modeler entities
	// it's been mapped to
	unsigned long PHindex;

	HXHashElt* found;
	PHindex = Hash(entity);
 	// determine which keys this solid modeler entity has been mapped to
	found = m_pPH_list[PHindex]->FindContent((void*)entity);

	if (!found) return false;
	do
	{
		unsigned long HPindex;
		HPindex = Hash((HC_KEY)found->GetData());
		// for each key, delete the mapping from 
		// the key to this solid modeler entity.  These mappings should
		// exist, hence the assert.
		m_pHP_list[HPindex] = m_pHP_list[HPindex]->DeleteContent(found->GetData(), found->GetKey());

		found = found->GetNext();
		assert(m_NumEntries > 0);
		m_NumEntries--;
	}
	while (found->GetKey() == (void*)entity);

	m_pPH_list[PHindex] = m_pPH_list[PHindex]->DeleteContent((void*)entity);
	return true;
}

bool HP_Map::DeleteMapping(HC_KEY key, PK_ENTITY_t entity)
{
	unsigned long index;
	bool result = true;
 
	if (entity == 0)
		return false;

	if (key == -1)
		return false;

	if (key == 0)
		return false;

	if (!m_pPH_list || !m_pHP_list)
	{
		return false;
	}

	
	// delete the mapping from the Hoops-To-Acis hash table
	index = Hash(key);

	if (!m_pHP_list[index])
	{
		result = false;
	}
	else
	{
		m_pHP_list[index] = m_pHP_list[index]->DeleteContent((void*)key, (void*)entity);
	}
	// delete the mapping from the Acis-To-Hoops hash table
	index = Hash(entity);

	if (!m_pPH_list[index])
	{
		result = false;
	}
	else
	{
		m_pPH_list[index] = m_pPH_list[index]->DeleteContent((void*)entity, (void*)key);
	}

	assert(m_NumEntries > 0);
	m_NumEntries--;
	return result;
}
	// returns zero if entity not found
HC_KEY HP_Map::FindMapping(PK_ENTITY_t entity)
{
	unsigned long index;

	if (!m_pPH_list)
		return 0;
	index = Hash(entity);
	if (m_pPH_list[index])
	{
		HXHashElt* content;
		content = m_pPH_list[index]->FindContent((void*)entity);
		if (content)
			return (HC_KEY)content->GetData();
		else
			return 0;
	}
	else
		return 0;

}
	// returns zero if entity not found

unsigned long HP_Map::FindMapping(PK_ENTITY_t entity, HC_KEY* keys, unsigned long count)
{
	unsigned long index;
	unsigned int num_keys_mapped_to_entity = 0;

	if (!m_pPH_list)
		return 0;

	index = Hash(entity);

	if (m_pPH_list[index])
	{
		HXHashElt* content;
		content = m_pPH_list[index]->FindContent((void*)entity);
		while (content && (content->GetKey() == (void*)entity && content->GetLevel()==g_hash_level) && (num_keys_mapped_to_entity < count))
		{
			keys[num_keys_mapped_to_entity] = (HC_KEY)content->GetData();
			num_keys_mapped_to_entity++;
			content = content->GetNext();
		}
		return num_keys_mapped_to_entity;
	}
	else
		return 0;

}

	// returns 0 if key not found
PK_ENTITY_t HP_Map::FindMapping(HC_KEY key)
{
	unsigned long index;

	if (!m_pHP_list)
		return 0;

	index = Hash(key);

	if (m_pHP_list[index])
	{
		HXHashElt* content;
		content = m_pHP_list[index]->FindContent((void*)key);
		if (content)
			return (PK_ENTITY_t)((HC_POINTER_SIZED_INT)content->GetData());
		else
			return 0;
	}
	else
		return 0;

}


int HP_Map::CheckConsistency()
{
	int count1=0;
	int count2=0;
	HXHashElt* e;
	unsigned int i;

	if (!m_pHP_list)
		return 0;

	for (i = 0; i < m_TableSize; i++)
	{
		e=m_pHP_list[i];
		while (e)
		{
		 
			if (e->GetLevel()==1)
				count1++;
			e=e->GetNext();
		}
	}
	for (i = 0; i < m_TableSize; i++)
	{

		e=m_pPH_list[i];
 

		while (e)
		{			 
		
			if (e->GetLevel()==1)
				count2++;			 
			e=e->GetNext();
		}

	} 
 	return count1+count2;
}




