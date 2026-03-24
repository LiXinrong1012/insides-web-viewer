#pragma once
#include "pre_compile.h"

/// define Property Macro.
#define J_PROPERTY_HEADER() \
public: \
	virtual bool getProperty(Base::Property* p); \
	virtual bool setProperty(const Base::Property*p); \
	virtual const Base::PropertyContainer* getPropertyContainer(); \
	static void initProperty(); \
	static void initProperty(Base::PropertyContainer* p); \
private: \
	static Base::PropertyContainer propertyContainer;

#define J_PROPERTY_SOURCE_P(_class_) \
	Base::PropertyContainer _class_::propertyContainer=Base::PropertyContainer(); \
	const Base::PropertyContainer* _class_::getPropertyContainer(){ \
	return &propertyContainer;}  \
	void _class_::initProperty(){ \
	_class_::initProperty(&propertyContainer);} 

#define J_PROPERTY_SOURCE(_class_) \
	J_PROPERTY_SOURCE_P(_class_)


#define J_NOPROPERTY_HEADER() \
public: \
	static void initProperty(); \
	static void initProperty(Base::PropertyContainer* p); 

#define J_NOPROPERTY_SOURCE_P(_class_) \
	void _class_::initProperty(){} \
	void _class_::initProperty(Base::PropertyContainer* p){}

#define J_NOPROPERTY_SOURCE(_class_,_parentClass_) \
	void _class_::initProperty(){} \
	void _class_::initProperty(Base::PropertyContainer* p){ \
	_parentClass_::initProperty(p);}


/// define for subclassing Base::BaseClass
#define TYPESYSTEM_HEADER() \
public: \
	static Base::Type getClassTypeId(void); \
	virtual Base::Type getTypeId(void) const; \
	static void init(void);\
	static void *create(void);\
private: \
	static Base::Type classTypeId; \
	static bool isInitialized;




/// define to implement a  subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE_P(_class_) \
	Base::Type _class_::getClassTypeId(void) { return _class_::classTypeId; } \
	Base::Type _class_::getTypeId(void) const { return _class_::classTypeId; } \
	Base::Type _class_::classTypeId = Base::Type::badType();  \
	bool _class_::isInitialized=false; \
	void * _class_::create(void){\
	return new _class_ ();\
}

/// define to implement a  subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE_ABSTRACT_P(_class_) \
	Base::Type _class_::getClassTypeId(void) { return _class_::classTypeId; } \
	Base::Type _class_::getTypeId(void) const { return _class_::classTypeId; } \
	Base::Type _class_::classTypeId = Base::Type::badType();  \
	bool _class_::isInitialized=false; \
	void * _class_::create(void){return 0;}


/// define to implement a subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE(_class_, _parentclass_) \
	TYPESYSTEM_SOURCE_P(_class_);\
	void _class_::init(void){\
	if(_class_::classTypeId!=Base::Type::badType()) \
		return; \
	_parentclass_::init(); \
	initSubclass(_class_::classTypeId, #_class_ , #_parentclass_, &(_class_::create) ); \
}

/// define to implement a subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE_ABSTRACT(_class_, _parentclass_) \
	TYPESYSTEM_SOURCE_ABSTRACT_P(_class_);\
	void _class_::init(void){\
	initSubclass(_class_::classTypeId, #_class_ , #_parentclass_, &(_class_::create) ); \
}


/*! because the _full_class_name_ has character ":", so I have 
*	to add a second parameter _class_name.
*	In fact: the _class_name_ needn't to be the real class name,
*	just use a unique name. 
*/

#define REGISTER_CLASS_TYPE(_full_class_name_,_class_name_) \
class Register_##_class_name_##_Type{ \
public:  \
	Register_##_class_name_##_Type(){\
	_full_class_name_::init(); }\
};	Register_##_class_name_##_Type _register_##_class_name_##_Type;


#define J_TYPE_PROPERTY_HEADER() \
	TYPESYSTEM_HEADER() \
	J_PROPERTY_HEADER() 

#define J_TYPE_NOPROPERTY_HEADER() \
	TYPESYSTEM_HEADER() \
	J_NOPROPERTY_HEADER() 


#define J_TYPE_PROPERTY_SOURCE(_class_,_parentClass_) \
	TYPESYSTEM_SOURCE_P(_class_); \
	void _class_::init(void){ \
	if(_class_::getClassTypeId()!=Base::Type::badType()) \
	return; \
	_parentClass_::init(); \
	initProperty(); \
	initSubclass(_class_::classTypeId, #_class_ , #_parentClass_, &(_class_::create) );  \
	} \
	J_PROPERTY_SOURCE(_class_) 

#define J_TYPE_PROPERTY_SOURCE2(_class_,_parentClass_,_type_) \
	TYPESYSTEM_SOURCE_P(_class_); \
	void _class_::init(void){ \
	if(_class_::getClassTypeId()!=Base::Type::badType()) \
	return; \
	_parentClass_::init(); \
	initProperty(); \
	initSubclass(_class_::classTypeId, #_class_ , #_parentClass_, &(_class_::create) );  \
	} \
	J_PROPERTY_SOURCE(_class_) \
	REGISTER_CLASS_TYPE(_class_,_type_)

#define J_TYPE_NOPROPERTY_SOURCE(_class_,_parentClass_) \
	TYPESYSTEM_SOURCE(_class_,_parentClass_) \
	J_NOPROPERTY_SOURCE(_class_,_parentClass_) 
	//REGISTER_CLASS_TYPE(_class_)

#define J_TYPE_NOPROPERTY_SOURCE2(_class_,_parentClass_,_type_) \
	TYPESYSTEM_SOURCE(_class_,_parentClass_) \
	J_NOPROPERTY_SOURCE(_class_,_parentClass_) \
	REGISTER_CLASS_TYPE(_class_,_type_)


namespace Base
{
	struct TypeData;

	class  BASE_EXPORT Type
	{
	public:
		/// Construction
		Type(const Type& type);
		Type(void);
		/// Destruction
		virtual ~Type();

		/// creates a instance of this type
		void *createInstance(void);
		/// creates a instance of the named type
		static void *createInstanceByName(const char* TypeName, bool bLoadModule=false);


	public:
		typedef void * (*instantiationMethod)(void);

		static Type fromName(const char *name);
		const char *getName(void) const;
		const Type getParent(void) const;
		bool isDerivedFrom(const Type type) const;

		static int getAllDerivedFrom(const Type type, std::vector<Type>& List);

		static int getNumTypes(void);

		static const Type createType(const Type parent, const char *name,instantiationMethod method = 0);

		int getKey(void) const;
		bool isBad(void) const;

		void operator =  (const Type type); 
		bool operator == (const Type type) const;
		bool operator != (const Type type) const;

		bool operator <  (const Type type) const;
		bool operator <= (const Type type) const;
		bool operator >= (const Type type) const;
		bool operator >  (const Type type) const;

		static Type badType(void);
		//static void init(void);
		static void destruct(void);

	protected:
		static std::string getModuleName(const char* ClassName);


	private:

		int index;
		static std::map<std::string,unsigned int> typemap;
		static std::vector<TypeData*>     typedata;
		static std::set<std::string>  loadModuleSet;
	};

}//end namespace Base.