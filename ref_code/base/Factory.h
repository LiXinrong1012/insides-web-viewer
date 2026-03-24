#pragma once

#include "pre_compile.h"

namespace Base{

	///AbstractProducer is the base class of all class using factory.
	class BASE_EXPORT AbstractProducer
	{
	public:
		virtual void* Produce(void)=0;
	};

	template<class KeyClass>
	class Factory
	{
	public:
		virtual ~Factory();
		/// Adds a new prducer instance
		void AddProducer (const KeyClass& sClassName, AbstractProducer *pcProducer);
		/// returns true if there is a producer for this class registered
		bool CanProduce(const KeyClass& sClassName) const;
		/// returns a list of all registered producer
		std::list<KeyClass> CanProduce() const;
		///Produce a instance with the given name.
		void* Produce (const KeyClass& sClassName) ;
	protected:
		std::map<KeyClass,AbstractProducer*> _mapProducers;
	};

	typedef Factory<std::string> StringFactory;
	typedef Factory<int>		IntFactory;

	class BASE_EXPORT FactorySingleton:public Factory<std::string>
	{
	public:
		static FactorySingleton& Instance(void);
		static void Destruct(void);

	private:
		static FactorySingleton* _factorySingleton;
		FactorySingleton(){}
		~FactorySingleton(){}
	};

	inline FactorySingleton& FactorySingletonInstance(){return FactorySingleton::Instance();}





	template<class KeyClass>
	Factory<KeyClass>::~Factory ()
	{
		for (std::map<KeyClass, AbstractProducer*>::iterator pI = _mapProducers.begin(); pI != _mapProducers.end(); pI++)
			delete pI->second;
	}

	template<class KeyClass>
	void* Factory<KeyClass>::Produce (const KeyClass& sClassName) 
	{
		std::map<KeyClass, AbstractProducer*>::const_iterator pProd;

		pProd = _mapProducers.find(sClassName);
		if (pProd != _mapProducers.end())
			return pProd->second->Produce();
		else
			return NULL;
	}

	template<class KeyClass>
	void Factory<KeyClass>::AddProducer (const KeyClass& sClassName, AbstractProducer *pcProducer)
	{
		_mapProducers[sClassName] = pcProducer;
	}

	template<class KeyClass>
	bool Factory<KeyClass>::CanProduce(const KeyClass& sClassName) const
	{
		return (_mapProducers.find(sClassName) != _mapProducers.end());
	}

	template<class KeyClass>
	std::list<KeyClass> Factory<KeyClass>::CanProduce() const
	{
		std::list<KeyClass> lObjects;

		for (std::map<KeyClass, AbstractProducer*>::const_iterator pI = _mapProducers.begin(); pI != _mapProducers.end(); pI++)
		{
			lObjects.push_back(pI->first);
		}

		return lObjects;
	}


	template<class factory,class realClass,class keyClass>
	class GeneralProducerRegister : Base::AbstractProducer
	{
	public:
		GeneralProducerRegister(const keyClass& keyname){
			factory::instance()->AddProducer(keyname,this);
		}
		virtual void* Produce(void){
			return new realClass();
		}
	};


}//end namespace Base.