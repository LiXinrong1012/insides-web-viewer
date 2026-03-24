
#include <QtCore/QCoreApplication>
#include <QtCore>
#include <cstdio>
#include <iostream>
#include <memory>


#include "pp_xml/DataStreamReader.h"
#include "pp_xml/DataStreamWriter.h"

using namespace std;

void write()
{
	QFile file("testDataStream.dat");  
	if (!file.open(QIODevice::WriteOnly)) {  
		std::cerr << "Cannot open file for writing: " 
			<< qPrintable(file.errorString()) << std::endl;  
		return;  
	}  

	QDataStream out(&file);  
	out.setVersion(QDataStream::Qt_4_8);  
	QIODevice* de=out.device();

	std::cout<<de->pos()<<std::endl;
	QString mySring("Hello!");
	out<<mySring;
	std::cout<<de->pos()<<std::endl;
	out<<24;
	file.close();
}

void read()
{
	QFile file("testDataStream.dat");  
	if (!file.open(QIODevice::ReadOnly)) {  
		std::cerr << "Cannot open file for writing: " 
			<< qPrintable(file.errorString()) << std::endl;  
		return;  
	}  

	QDataStream fin(&file);  
	fin.setVersion(QDataStream::Qt_4_8);  
	QString mySring;
	//fin>>mySring;

	fin.device()->seek(16);
	int a;
	fin>>a;
	file.close();

	qDebug("%s, %d",mySring.toAscii().constData(),
		a);
}

void testDataStream()
{
	DataStreamWriter writer;
	writer.open("testDataStreamWriter.dat");
	writer.startBlock(1);
	(*writer.getDataStream())<<"Hello world";
	writer.stopBlock();

	writer.startBlock(2);
	(*writer.getDataStream())<<"Hello, Jerry";
	writer.stopBlock();

	writer.close();

	DataStreamReader reader;
	reader.addFile("testDataStreamWriter.dat");
	DataBlock* block=reader.findBlock(1);
}

class MyObject:public QObject
{
	;
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//write();
	//read();

	QWeakPointer<MyObject> wp1;
	wp1=QWeakPointer<MyObject>(new MyObject());

	MyObject* obj3=new MyObject();
	MyObject * obj4=obj3;
	QWeakPointer<MyObject> wp3=QWeakPointer<MyObject>(obj4);

	cout<<"wp1 is null? "<<wp1.isNull()<<endl;
	QWeakPointer<MyObject> wp2=wp1;
	wp2.clear();
	cout<<"wp1 is null? "<<wp1.isNull()<<endl;
	cout<<"wp2 is null? "<<wp2.isNull()<<endl;

	cout<<"delete object..."<<endl;
	delete wp1.data();
	cout<<"wp1 is null? "<<wp1.isNull()<<endl;

	tr1::shared_ptr<QObject> ccc=tr1::shared_ptr<QObject>(new QObject());
	cout<<"tr1::shared_ptr is null ?"<<(ccc==0)<<endl;
	{
		tr1::shared_ptr<QObject> ccc2=ccc;
		cout<<"tr1::shared_ptr use count = "<<ccc.use_count()<<endl;
	}
	cout<<"tr1::shared_ptr use count = "<<ccc.use_count()<<endl;
	cout<<"size of shared_ptr "<<sizeof(tr1::shared_ptr<QObject>)<<endl;

	return a.exec();
}
