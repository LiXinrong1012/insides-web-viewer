
/*
* Copyright (c) 1998 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.	 Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.  Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
* $Id: vheap.h,v 1.20 2010-12-06 22:06:36 jason Exp $
*/

#ifndef VHEAP_H
#define VHEAP_H

#include "varray.h"
#include "vhash.h"
 
#ifdef __cplusplus
extern "C++" {

#define VHEAP_COMPILE_TIME_ASSERT(condition) \
	do { class message { char array[condition ? 1 : -1]; }; } while(0) 

#define VHEAP_PARENT(_i_) (((_i_)-1)/2)
#define VHEAP_LEFT(i) (2*(i)+1)
#define VHEAP_RIGHT(i) (2*(i)+2)


template <typename T1, typename T2, bool largest_out_first, bool can_update> class VHeap 
#ifdef HOOPS_DEFINED
	: public CMO_Pooled
#endif
{

private:

	class Element 
#ifdef HOOPS_DEFINED
		: public CMO_Pooled
#endif
	{
		public:
			Element(T1 item, T2 key) {_item=item;_key=key;_i=-1;};
			T1 _item;
			T2 _key;
			int _i;
	};

typedef VArray<Element*> ElementsData;
typedef VHash<T1,Element*> UpdateHash;

#ifdef HOOPS_DEFINED
	Memory_Pool * m_pool;
#endif

	ElementsData *	elements;
	UpdateHash *	update_hash;

	void down(int i) {

		int	c, l, r, m;

		c = elements->Count();
		l = VHEAP_LEFT(i);
		r = VHEAP_RIGHT(i);

		while (l < c) {

			if (r >= c)	/* careful: right leaf may not exist */
				m = l;
			else {
				if (largest_out_first) {
					if (elements->GetData(l)->_key > elements->GetData(r)->_key)
						m = l;
					else
						m = r;
				} else {
					if (elements->GetData(l)->_key < elements->GetData(r)->_key)
						m = l;
					else
						m = r;
				}
			}

			if (largest_out_first) {
				if (elements->GetData(m)->_key > elements->GetData(i)->_key) {
					elements->Swap(i, m);
					if (can_update) {
						elements->GetData(i)->_i = i;
						elements->GetData(m)->_i = m;
					}
					i = m;
					l = VHEAP_LEFT(i);
					r = VHEAP_RIGHT(i);
				}
				else
					break;
			}
			else {
				if (elements->GetData(m)->_key < elements->GetData(i)->_key) {
					elements->Swap(i, m);
					if (can_update) {
						elements->GetData(i)->_i = i;
						elements->GetData(m)->_i = m;
					}
					i = m;
					l = VHEAP_LEFT(i);
					r = VHEAP_RIGHT(i);
				}
				else
					break;
			}
		}
	}

	void up(int i) {

		int p = VHEAP_PARENT(i);

		if (largest_out_first) {
			while (i > 0 && elements->GetData(i)->_key > elements->GetData(p)->_key) {
				elements->Swap(i, p);
				if (can_update) {
					elements->GetData(i)->_i = i;
					elements->GetData(p)->_i = p;
				}
				i = p;
				p = VHEAP_PARENT(i);
			}
		}
		else {
			while (i > 0 && elements->GetData(i)->_key < elements->GetData(p)->_key) {
				elements->Swap(i, p);
				if (can_update) {
					elements->GetData(i)->_i = i;
					elements->GetData(p)->_i = p;
				}
				i = p;
				p = VHEAP_PARENT(i);
			}
		}
	}

public:

#ifdef HOOPS_DEFINED
	VHeap(Memory_Pool * memory_pool, int initial_size=16) : m_pool(memory_pool), update_hash(0) {
		elements = POOL_NEW(m_pool, ElementsData)(m_pool, initial_size);
		if (can_update)
			update_hash = POOL_NEW(m_pool, UpdateHash)(m_pool);
		VHEAP_COMPILE_TIME_ASSERT(sizeof(T1) <= sizeof(void *));	
		VHEAP_COMPILE_TIME_ASSERT(sizeof(T2) <= sizeof(void *));
	}
#else	
	VHeap(int initial_size=16) : update_hash(0) {
		elements = new ElementsData(initial_size);
		if (can_update)
			update_hash = NEW (UpdateHash)();
		VHEAP_COMPILE_TIME_ASSERT(sizeof(T1) <= sizeof(void *));	
		VHEAP_COMPILE_TIME_ASSERT(sizeof(T2) <= sizeof(void *));
	};	
#endif
	
	virtual ~VHeap() {

		while(elements->Count()>0)
			delete elements->Pop();

		delete elements;
		if (can_update)
			delete update_hash;
	}; 

	int Count() const {
		return elements->Count();
	};


	Element * GetElement(T1 item, T2 key) {
#ifdef HOOPS_DEFINED
		return POOL_NEW(m_pool, Element)(item, key);
#else
		return new Element(item, key);
#endif
	}

	void Push(T1 item, T2 key) {

		int i = elements->Count();

		Element * element = GetElement(item, key);
		elements->Append(element);

		if (can_update) {
			update_hash->InsertItem(item, element);
			element->_i = i;
		}

		up(i);

	};

	bool Peek(T1 * item, T2 * key=0) {

		int c = elements->Count();

		if (c == 0)
			return false;

		Element * element = elements->GetData(0);

		*item = element->_item;
		if (key != null)
			*key = element->_key;

		return true;
	}

	bool PeekKey(T2 * key) {

		int c = elements->Count();

		if (c == 0)
			return false;

		Element * element = elements->GetData(0);

		*key = element->_key;

		return true;
	}


	bool Pop(T1 * item=0, T2 * key=0) {

		int c = elements->Count();

		if (c == 0)
			return false;

		Element * element = elements->GetData(0);

		if (can_update)
			update_hash->RemoveItem(element->_item);

		if (item)
			*item = element->_item;
		if (key != null)
			*key = element->_key;

		c--;
		if (c > 0) {

			elements->Swap(0, c);
			if (can_update) 
				elements->GetData(0)->_i = 0;
			elements->Pop(); 

			down(0);	
		}
		else
			elements->Pop(); 

		delete element;

		return true;
	};


	bool Update(T1 item, T2 key) {

		if (can_update) {

			Element * element = 0;
			update_hash->LookupItem(item, &element);

			if (!element)
				return false;

			if (element->_key != key) {

				T2 old_key = element->_key;
				element->_key = key;
	
				if (largest_out_first) {
					if (key > old_key)
						up(element->_i);
					else 
						down(element->_i);
				}
				else {
					if (key < old_key)
						up(element->_i);
					else 
						down(element->_i);
				}
			}
			return true;
		}

		return false;
	};

};

} /* extern "C++" */
#endif

#endif 



