#pragma once

#include "Base/Factory.h"

namespace Base{

class BASE_EXPORT InputWidgetFactory :
	public Base::Factory<std::string>
{
public:
	static InputWidgetFactory* instance(void);
	static void destruct(void);

private:
	InputWidgetFactory(void);
	~InputWidgetFactory(void);

	static InputWidgetFactory* _factorySingleton;
};

#define REGISTER_CLASS_PRODUCER(_class_,_key_) \
class _class_##1 : public Base::AbstractProducer \
{  \
public: \
	virtual void* Produce(void){return new _class_();} \
	_class_##1(){ Base::InputWidgetFactory::instance()->AddProducer(#_key_,this); } \
}; \
	static _class_##1 _class_##2; 




}