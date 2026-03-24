#include "Type.h"

using namespace std;

namespace Base
{
	struct TypeData 
	{
		TypeData(const char *theName,
			const Type type = Type::badType(),
			const Type theParent = Type::badType(),
			Type::instantiationMethod method = 0
			):name(theName),parent(theParent),type(type),instMethod(method) { }

		std::string name;
		Type parent;
		Type type;
		Type::instantiationMethod instMethod;
	};

	map<string,unsigned int> Type::typemap;
	vector<TypeData*>        Type::typedata;
	set<string>              Type::loadModuleSet;



	inline int Type::getKey(void) const
	{
		return this->index;
	}

	inline bool Type::operator != (const Type type) const
	{
		return (this->getKey() != type.getKey());
	}

	inline void Type::operator = (const Type type) 
	{
		this->index = type.getKey();
	}

	inline bool Type::operator == (const Type type) const
	{
		return (this->getKey() == type.getKey());
	}

	inline bool Type::operator <  (const Type type) const
	{
		return (this->getKey() < type.getKey());
	}

	inline bool Type::operator <= (const Type type) const
	{
		return (this->getKey() <= type.getKey());
	}

	inline bool Type::operator >= (const Type type) const
	{
		return (this->getKey() >= type.getKey());
	}

	inline bool Type::operator >  (const Type type) const
	{
		return (this->getKey() > type.getKey());
	}

	inline bool Type::isBad(void) const
	{
		return (this->index == -1);
	}



	//**************************************************************************
	// Construction/Destruction

	/**
	* A constructor.
	* A more elaborate description of the constructor.
	*/
	Type::Type()
		: index(-1)
	{
	}


	Type::Type(const Type& type)
		:index(type.index)
	{
	}


	/**
	* A destructor.
	* A more elaborate description of the destructor.
	*/
	Type::~Type()
	{
	}

	void *Type::createInstance(void)
	{
		return (typedata[index]->instMethod)();
	}


	void *Type::createInstanceByName(const char* TypeName, bool bLoadModule)
	{
		// if not allready, load the module
		if(bLoadModule)
		{
			// cut out the module name 
			string Mod = getModuleName(TypeName);
			// ignore base modules
			if(Mod != "App" && Mod != "Gui" && Mod != "Base")
			{
				// remember allready loaded modules
				set<string>::const_iterator pos = loadModuleSet.find(Mod);
				if(pos == loadModuleSet.end())
				{
#ifdef FC_LOGLOADMODULE
					Console().Log("Act: Module %s loaded through class %s \n",Mod.c_str(),TypeName);
#endif
					loadModuleSet.insert(Mod);
				}
			}
		}

		// now the type should be in the type map
		Type t = fromName(TypeName);
		if(t == badType())
			return 0;

		return t.createInstance();

	}

	string Type::getModuleName(const char* ClassName)
	{
		string temp(ClassName);
		std::string::size_type pos = temp.find_first_of("::");

		if(pos != std::string::npos)
			return string(temp,0,pos);
		else
			return string();
	}

	Type Type::badType(void)
	{
		Type bad;
		bad.index = -1;
		return bad;
	}


	const Type Type::createType(const Type parent, const char *name, instantiationMethod method)
	{
		Type newType;
		newType.index = Type::typedata.size();
		TypeData * typeData = new TypeData(name, newType, parent,method);
		Type::typedata.push_back(typeData);

		// add to dictionary for fast lookup
		Type::typemap[name] = newType.getKey();

		return newType;
	}


	/*void Type::init(void)
	{
		assert(Type::typedata.size() == 0);


		Type::typedata.push_back(new TypeData("BadType"));
		Type::typemap["BadType"] = 0;
	}*/

	void Type::destruct(void)
	{
		for(std::vector<TypeData*>::const_iterator it = typedata.begin();it!= typedata.end();++it)
			delete *it;
	}

	Type Type::fromName(const char *name)
	{
		std::map<std::string,unsigned int>::const_iterator pos;

		pos = typemap.find(name);
		if(pos != typemap.end())
			return typedata[pos->second]->type;
		else
			return Type::badType();
	}

	const char *Type::getName(void) const
	{
		return typedata[index]->name.c_str();
	}

	const Type Type::getParent(void) const
	{
		return typedata[index]->parent;
	}

	bool Type::isDerivedFrom(const Type type) const
	{

		Type temp(*this);
		do {
			if(temp == type)
				return true;
			temp = temp.getParent();
		} while (temp != badType());

		return false;
	}

	int Type::getAllDerivedFrom(const Type type, std::vector<Type> & List)
	{
		int cnt = 0;

		for(std::vector<TypeData*>::const_iterator it = typedata.begin();it!= typedata.end();++it)
		{
			if((*it)->type.isDerivedFrom(type))
			{
				List.push_back((*it)->type);
				cnt++;
			}
		}
		return cnt;
	}

	int Type::getNumTypes(void)
	{
		return typedata.size();
	}




}//end namespace Base.