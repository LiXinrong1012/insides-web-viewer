
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
* $Id: varray.h,v 1.43 2010-12-06 22:06:36 jason Exp $
*/

#ifndef VARRAY_H
#define VARRAY_H

#include <stdlib.h>
#include <string.h>

#include <new>

 
#ifdef __cplusplus
extern "C++" {

#define VARRAY_COMPILE_TIME_ASSERT(condition) /*\
	do { class message { char array[condition ? 1 : -1]; }; } while(0) */

template <typename T> class VArray
#ifdef HOOPS_DEFINED
: public CMO_Pooled
#endif
{
public:
	
#ifdef HOOPS_DEFINED
	Memory_Pool * m_pool;

	VArray(Memory_Pool * memory_pool, int size=1):m_pool(memory_pool),count(0),allocated(0),data(0) {
		EnsureSize(size);
		VARRAY_COMPILE_TIME_ASSERT(sizeof(T) <= sizeof(void *));	
	};

	VArray(Memory_Pool * memory_pool, VArray<T> &original):m_pool(memory_pool),count(0),allocated(0),data(0) {
		EnsureSize(original.Count());
		count = original.Count();
		if(!TypeTraits<T>::IsFundamental){
			for(int i=0; i<count; ++i)
				data[i]=original.data[i];
		}else
			memcpy(data, original.data, count*sizeof(T));
		VARRAY_COMPILE_TIME_ASSERT(sizeof(T) <= sizeof(void *));	
	};

	VArray(Memory_Pool * memory_pool, VArray<T> *original):m_pool(memory_pool),count(0),allocated(0),data(0) {
		EnsureSize(original->Count());
		count = original->Count();
		if(!TypeTraits<T>::IsFundamental) {
			for(int i=0; i<count; ++i)
				data[i]=original->data[i];
		}
		else
			memcpy(data, original->data, count*sizeof(T));
		VARRAY_COMPILE_TIME_ASSERT(sizeof(T) <= sizeof(void *));	
	};
#else
	VArray(int size=1):count(0),allocated(0),data(0) {
		EnsureSize(size);
		VARRAY_COMPILE_TIME_ASSERT(sizeof(T) <= sizeof(void *));	
	};

	VArray(VArray<T> &original):count(0),allocated(0),data(0) {
		EnsureSize(original.Count());
		count = original.Count();
		memcpy(data, original.data, count*sizeof(T));
		VARRAY_COMPILE_TIME_ASSERT(sizeof(T) <= sizeof(void *));	
	};

	VArray(VArray<T> *original):count(0),allocated(0),data(0) {
		EnsureSize(original->Count());
		count = original->Count();
		memcpy(data, original->data, count*sizeof(T));
		VARRAY_COMPILE_TIME_ASSERT(sizeof(T) <= sizeof(void *));	
	};
#endif
	
	virtual ~VArray() {
		TrimSize(0);
	}; 
	
 	inline int Count() const { return count; }
 	inline int Size() const { return allocated; }

	/* If T is a char, you can use this class like so...
	 *    VCharArray buf(BUFFER_SIZE);
	 *    HC_Show_Rendering_Options(buf);
	 */
	operator T * () {
		return this->data;
	};

#if 0
	operator T const * () {
		return (T const *)this->data;
	};
#endif

	T& operator [] (int i){
		
		if(i >= count){
			EnsureSize(i+1);
			count=i+1;
		}
		return data[i];
	};

	T const& operator [] (int i) const {
		
		if(i >= count){
			EnsureSize(i+1);
			count=i+1;
		}
		return data[i];
	};

	bool Append(T const & item) {
		EnsureSize(count+1);
		data[count++] = item;
		return true;
	};

	void AppendArray(T const *item_array, int n_items) {
		if(n_items == 0) 
			return;
		EnsureSize(n_items+count);
#ifdef HOOPS_DEFINED
		if(!TypeTraits<T>::IsFundamental){
			for(int i=0; i<n_items; ++i)
				data[count+i]=item_array[i];
		}else
#endif
			memcpy(&data[count], item_array, n_items*sizeof(T));
		count+=n_items;
	};

 	T & GetData(int i) {
		return data[i];
	};

	void GetArrayCopy(T *new_item_array) {
#ifdef HOOPS_DEFINED
		if(!TypeTraits<T>::IsFundamental){
			for(int i=0; i<count; ++i)
				new_item_array[i]=data[i];
		}else
#endif		
			memcpy(new_item_array,data,count*sizeof(T));
	};


 	T Pop() {

#ifdef HOOPS_DEFINED
		if(!TypeTraits<T>::IsFundamental){
			T temp = data[--count];
			new(&data[count]) T();
			return temp;
		}
#endif

		return data[--count];
	};

	void InsertAt(T const & item, int i) {

		if(i >= count) {
			EnsureSize(i+1);
			count=i+1;
		}else{
			EnsureSize(count+1);
#ifdef HOOPS_DEFINED
			if(!TypeTraits<T>::IsFundamental) {
				char swap_buffer[sizeof(T)];
				memcpy(swap_buffer, &data[count], sizeof(T));
				memmove(&data[i+1], &data[i], (count-i)*sizeof(T));
				memcpy(&data[i], swap_buffer, sizeof(T));
			}else
#endif
				memmove(&data[i+1], &data[i], (count-i)*sizeof(T));
			count++;
		}
		data[i] = item;
	};

	void InsertAt(int n_items, T const *item_array, int i) {

		if(n_items <= 0)
			return;
		if(i >= count) {
			EnsureSize(i+n_items);
			count=i+n_items;
		}else{
			EnsureSize(n_items+count);
#ifdef HOOPS_DEFINED
			if(!TypeTraits<T>::IsFundamental) {
				char * swap_buffer =  new char[n_items*sizeof(T)];
				memcpy(swap_buffer, &data[count], n_items*sizeof(T));
				memmove(&data[i+n_items], &data[i], (count-i)*sizeof(T));
				memcpy(&data[i], swap_buffer, n_items*sizeof(T));
				delete [] swap_buffer;
			}
			else
#endif
				memmove(&data[i+1], &data[i], (count-i)*sizeof(T));
			count += n_items;
		}

#ifdef HOOPS_DEFINED
		if(!TypeTraits<T>::IsFundamental)
			for(int j=0; j<n_items; ++j)
				data[i+j]=item_array[j];
		else
#endif
			memcpy(&data[i], item_array, n_items*sizeof(T));
	};

	bool RemoveAt(int i, T * old_item=0) {

		if(i>=count) 
			return false;
		count--;
		if(old_item)
			*old_item = data[i];
#ifdef HOOPS_DEFINED
		if(!TypeTraits<T>::IsFundamental) {
			data[i].~T();
			if(i!=count)
				memmove(&data[i], &data[i+1], (count-i)*sizeof(T));
			new(&data[count]) T();
		}else
#endif		
			if(i!=count)
				memmove(&data[i], &data[i+1], (count-i)*sizeof(T)); 
		return true;
	};

	bool RemoveAt(int in_count, int i) {

		if(i>=count)
			return false;
		bool removing_to_end = false;
		if(i + in_count >= count) {
			in_count = count - i;
			removing_to_end = true;
		}
		count -= in_count;
#ifdef HOOPS_DEFINED
		if(!TypeTraits<T>::IsFundamental) {
			for(int j=0; j<in_count; ++j)
				data[i+j].~T();
			if(!removing_to_end)
				memmove(&data[i], &data[i+in_count], (count-i)*sizeof(T));
			for(int j=0; j<in_count; ++j)
				new(&data[count+j]) T();
		} else
#endif
			if(!removing_to_end)
				memmove(&data[i], &data[i+in_count], (count-i)*sizeof(T));
		return true;
	};

	bool RemoveAt(int i, T & old_item) {
		return RemoveAt(i,&old_item);
	};

	bool ReplaceAt(T const & item, int i, T * old_item=0) {

		if(i>=count){
			EnsureSize(i+1);
			count=i+1;
			data[i]=item;
			return false;
		}
		if(old_item) *old_item = data[i];
		data[i].~T();
		data[i]=item;
		return true;
	};

	bool ReplaceAt(int n_items, T const *item_array, int i) {

		int j;
		if(i+n_items>=count)
			EnsureSize(i+n_items);
		if(i>=count){
			count=i+n_items;
			for(j=0; j<n_items; ++j)
				data[i+j]=item_array[j];
			return false;
		}

		for(j=0; j<n_items && i+j<count; ++j) {
			data[i+j].~T();
			new(&data[i+j]) T();
			data[i+j]=item_array[j];
		}
		for(; j<n_items; ++j)
			data[i+j]=item_array[j];

		if(count<i+n_items) count=i+n_items;

		return true;
	};

	bool ReplaceAt(T const & item, int i, T & old_item) {
		return ReplaceAt(item,i,&old_item);
	};

	bool Swap(int i, int j) {

		if (i>=count||j>=count)
			return false;

		T	temp = data[i];
		data[i] = data[j];
		data[j] = temp;

		return true;
	};

 	void SetCount(int in_count) { 
		EnsureSize(in_count);
		count=in_count;
	};

	void Reverse() {
		T	temp;
		T *	start;
		T *	end;

		start = data;
		end = data + count - 1;
		while (start < end) {
			temp = *start;
			*start = *end;
			*end = temp;
			start++;
			end--;
		}
	};

	void MapFunction(void(*function)(T, void*), void * user_data) const{
		for(int i=0;i<count;i++)
			(*function)(data[i],user_data);
	};

	void MapFunction(void(*function)(T&, void*), void * user_data) {
		for(int i=0;i<count;i++)
			(*function)(data[i],user_data);
	};

	void MapFunction(void(*function)(T const &, void*), void * user_data) const{
		for(int i=0;i<count;i++)
			(*function)(data[i],user_data);
	};

	void TrimSize(int size=-1) {
		if (size == -1)
			size = count;
		MakeSize(size);
	};

	void EnsureSize(int size) const {
		if(size<=allocated) 
			return;
		MakeSize(size + (size>>2) + 4);
	};
	
protected:

	void MakeSize(int size) const {

#ifdef HOOPS_DEFINED
		int old_allocated = allocated;
#endif
		allocated = size;
	
		T * new_data = 0;
		if (allocated > 0) {
#ifdef HOOPS_DEFINED
#ifdef VALIDATE_MEMORY
			new_data = (T *)operator new(allocated*sizeof(T), m_pool, "VArray_T", __FILE__, __LINE__);
#else
			new_data = (T *)operator new(allocated*sizeof(T), m_pool, 0, 0, 0);
#endif
			if(!TypeTraits<T>::IsFundamental){
				for(int i=count; i<allocated; ++i)
					new(&new_data[i]) T();
			}
#else
			new_data = new T[allocated];
#endif
		}

		if (size < count)
			count = size;

		if (data != 0) {
			if(allocated > 0)
				memcpy(new_data, data, count*sizeof(T));
#ifdef HOOPS_DEFINED
			if(!TypeTraits<T>::IsFundamental) {
				for(int i=count; i<old_allocated; ++i)
					data[i].~T();
			}
			operator delete(data, old_allocated*sizeof(T));
#else
			delete[] data;
#endif

		}
		data=new_data;
	};

	mutable int count;   
	mutable int allocated;
	mutable T *data;

}; 

typedef VArray<char> VCharArray;
typedef VArray<int> VIntArray;
typedef VArray<float> VFloatArray;

} /* extern "C++" */
#endif

#endif 




