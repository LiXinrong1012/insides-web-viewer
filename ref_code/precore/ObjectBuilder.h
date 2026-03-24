#pragma once

#include "precore/precore_global.h"
#include "precore/BaseItem.h"


namespace INSIDES
{

class BaseItemFactorySingleton;

class PRECORE_EXPORT ObjectBuilder
{
public:
	static ObjectBuilder* instance();

	BaseItem* createObject(int category);

private:
	ObjectBuilder(void);
	~ObjectBuilder(void);
	Q_DISABLE_COPY(ObjectBuilder);

	BaseItemFactorySingleton* _creator;
};

inline ObjectBuilder* myObjectBuilder(){
	return ObjectBuilder::instance();
}

}