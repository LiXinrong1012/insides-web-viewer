#ifndef PP_PROS_EXTEND_MAP_H_
#define PP_PROS_EXTEND_MAP_H_

#include "base/base_global.h"
#include <map>
#include <assert.h>

namespace Base{

void BASE_EXPORT tmpDebug(bool f);

/*! ExtendMap only services for that one to one map. */
template<class K1,class K2>
class  ExtendMap
{
public:
	typedef std::map<K1,K2> K1_2_K2;
	typedef std::map<K2,K1> K2_2_K1;


	K1 getKey1(K2 key2){
		tmpDebug(findKey1(key2));
		void* p=NULL;
		K2_2_K1::iterator f=_k2_2_k1_map.find(key2);
		return f->second;
	}
	K2 getKey2(K1 key1){
		tmpDebug(findKey2(key1));
		K1_2_K2::iterator f=_k1_2_k2_map.find(key1);
		return f->second;
	}
	bool findKey1(K2 key2){
		return _k2_2_k1_map.find(key2)!=_k2_2_k1_map.end();
	}
	bool findKey2(K1 key1){
		return _k1_2_k2_map.find(key1)!=_k1_2_k2_map.end();
	}
	void insertItem(K1 key1,K2 key2){
		tmpDebug(!findKey2(key1));
		tmpDebug(!findKey1(key2));

		_k1_2_k2_map[key1]=key2;
		_k2_2_k1_map[key2]=key1;
	}
	void removeItemByKey1(K1 key1){
		_k2_2_k1_map.erase(getKey2(key1));
		_k1_2_k2_map.erase(key1);
	}
	void removeItemByKey2(K2 key2){
		_k1_2_k2_map.erase(getKey1(key2));
		_k2_2_k1_map.erase(key2);
	}
	void clear(){
		_k1_2_k2_map.clear();
		_k2_2_k1_map.clear();
	}
	/*! used to traverse the whole item. */
	K1_2_K2& getKey1Map(){return _k1_2_k2_map;}
	K2_2_K1& getKey2Map(){return _k1_2_k2_map;}

private:

	K1_2_K2 _k1_2_k2_map;
	K2_2_K1 _k2_2_k1_map;
};


}//end namespace.



#endif