#pragma once

#include "base/Factory.h"

namespace INSIDES
{

class BaseItemFactorySingleton : public Base::IntFactory
{
public:
	static BaseItemFactorySingleton* instance();

private:
	BaseItemFactorySingleton(void);
	~BaseItemFactorySingleton(void);
};

inline BaseItemFactorySingleton* BaseItemFactory(){return BaseItemFactorySingleton::instance();}

#define REGISTER_BASEITEM_PRODUCER(_key_,_class_) \
class _class_##_key_ : public Base::AbstractProducer \
{  \
public: \
	virtual void* Produce(void){return new _class_();} \
	_class_##_key_(){ BaseItemFactory()->AddProducer(_key_,this); } \
}; \
static _class_##_key_ _class_##_key_##2; 


}