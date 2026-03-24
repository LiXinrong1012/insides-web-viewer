#ifndef BATFILEMANAGER_H
#define BATFILEMANAGER_H

#include <QThread>
#include <QString>
#include <QStringList>


/*!
	@brief   建立一个批处理文件，通过给定的路径和内容，可以控制建立完成后是否运行,运行完成后是否删除，以及多久后删除(ms)
	@date    2015.1.22
	@author  Jianjun
*/
class BatFileManager : public QThread
{
	Q_OBJECT
public:
	///批处理文件的全文件名fullFileName,需要写入文件的内容list,默认开启自动运行，默认运行完成后自动删除
	BatFileManager(const QString& fullFileName,const QStringList& list ,bool run = true,bool remove = true);
	~BatFileManager();

	///重写线程的run方法
   virtual void run();

private:
	///存储批处理文件的全文件名
	QString _fullFileName;
	
	///内容
	QString _content;
	
	///文件 列表 
	QStringList _entityList;
	
	///是否自动运行
	bool _run;

	///运行完成后是否删除
	bool _remove;

	///是否已完成
	bool _finished;

	///运行文件名
	QString _runFileName;

	///log文件名
	QString _logsFileName;

private slots:
	///检测是否完成
	void checkFinished();

};

#endif // BATFILEMANAGER_H
