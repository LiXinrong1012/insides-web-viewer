#pragma once

#include <QStringList>
#include <QDomElement>

namespace INSEditor{

/*!
	@brief 代表Solution或者Project文件夹。
	@author	Jerry He
	@date	2014.11.4
	*/
class Folder
{
public:
	Folder(void);
	~Folder(void);

	///获得文件夹列表
	const QList<QStringList>& getFolderList()const{return _folders;}

	///添加文件夹通过给定的folders
	void addFolders(const QStringList& folders);

	///删除文件夹通过给定的folders
	void removeFolders(const QStringList& folders);

private:
	QList<QStringList> _folders;
};


} // end namespace INSEditor