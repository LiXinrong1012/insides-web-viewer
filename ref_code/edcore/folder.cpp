#include "folder.h"

namespace INSEditor{


Folder::Folder(void)
{
}

Folder::~Folder(void)
{
}

void Folder::addFolders( const QStringList& folders )
{
	if(!_folders.contains(folders))
		_folders.push_back(folders);
}

void Folder::removeFolders( const QStringList& folders )
{
	_folders.removeOne(folders);
}

} // end namespace INSEditor