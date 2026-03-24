#pragma once

#include <QSharedPointer>

namespace pp{
	class DataStreamReader;
	class DataStreamWriter;
	class DataBlock;
}

namespace INSIDES
{

class IResults;
class IResultItem;

class ResultExchangeVersion1_0
{
public:
	ResultExchangeVersion1_0(void);
	~ResultExchangeVersion1_0(void);

	IResults* loadGeneralInfo(pp::DataBlock* reader);
	void load(IResults* result,pp::DataBlock* reader);

	void saveGeneralInfo(IResults* results,QSharedPointer<pp::DataStreamWriter> writer);
	void save(IResults* results,QSharedPointer<pp::DataStreamWriter> writer);


private:
	void saveOne(IResultItem* item);
	void saveData(IResultItem* item);

	void saveRigidItem(IResultItem* item);
	void saveRigidSec(IResultItem* item,bool realData=true);

	void saveFlexItem(IResultItem* item);
	void saveFlexSec(IResultItem* item,bool realData=true);

	void loadOne(pp::DataBlock* dataBlock);
	void loadRigid(pp::DataBlock* dataBlock);

	int _frameCount;
	QSharedPointer<pp::DataStreamWriter>	_writer;
	IResults*		_results;
};

}