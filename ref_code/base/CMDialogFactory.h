#pragma once

#include "base/base_global.h"
#include "base/factory.h"

namespace Base{

/*!
*	@brief 负责创建“创建对话框”和“修改对话框”的工厂。
*	@author Jerry He
*	@date 2014.2.13
*/
class BASE_EXPORT CreatingModifyingDialogFactory :
	public Base::Factory<std::string>
{
public:
	static CreatingModifyingDialogFactory* instance(void);
	static void destruct(void);

private:
	CreatingModifyingDialogFactory(void);
	~CreatingModifyingDialogFactory(void);

	static CreatingModifyingDialogFactory* _factorySingleton;
};

inline Base::CreatingModifyingDialogFactory* CMFactory(){
	return Base::CreatingModifyingDialogFactory::instance();}



template<class T>
class CMDialogProducer : public Base::AbstractProducer
{
public:
	CMDialogProducer(const char* keyname):_dialog(NULL){
		Base::CMFactory()->AddProducer(keyname,this);
	}
	virtual void* Produce(void){
		if(!_dialog)
			_dialog=new T();
		return _dialog;
	}
private:
	T*	_dialog;
};

}
//#define REGISTER_CM_DIALOG(_key_,_class_) static CMDialogProducer<_class_> _class_#111(#_key_);
