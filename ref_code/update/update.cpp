#include <QDomDocument>
#include <QCryptographicHash>
#include <QProcess>

#include "update.h"

#define LINK_TIMEOUT 10
#define UPDATER_VERSION "2.0"

UpdateDialog::UpdateDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
	,_progressValue(0)
	,_currentId(0)
	,_runTime(1)
{
	ui.setupUi(this);

	if(!readUpdateConfig())
	{
		/*_host = "112.126.65.135";
		_userId = "ins_uploader";
		_password = "ins123456789";
		_ftpRoot = "app/insides";*/
		QMessageBox::warning(this,"Config Error","The app will exit.");
		QTimer::singleShot(1000,qApp,SLOT(quit()));
	}
	
	this->setWindowTitle("INSIDES-Update");
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  
	ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 

	connect(&_ftp,SIGNAL(done(bool)),this,SLOT(ftpDone(bool)));
	connect(&_ftp,SIGNAL(listInfo(const QUrlInfo&)),this,SLOT(ftpListInfo(const QUrlInfo&)));
	connect(ui.cancelBtn,SIGNAL(clicked()),this,SLOT(onCancelBtnClicked()));

	connect(&_ftp,SIGNAL(dataTransferProgress ( qint64 , qint64 )),this,SLOT(updateProgress(qint64,qint64)));
	connect(&_ftp,SIGNAL(commandStarted ( int)),this,SLOT(onCommandStarted(int)));
	connect(&_ftp,SIGNAL(commandFinished ( int, bool)),this,SLOT(onCommandFinished(int,bool)));

	_checkFtp.connectToHost(_host,21);
	_checkFtp.login(_userId,_password);
	_checkFtp.cd(_ftpRoot);
	_versionId = _checkFtp.get("bin/version.xml");
	connect(&_checkFtp,SIGNAL(commandFinished(int,bool)),this,SLOT(beginUpdate(int,bool)));

	_timer = new QTimer(this);
	connect(_timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
	_timer->start(1000);
}

bool UpdateDialog::readUpdateConfig()
{
	QFile file(qApp->applicationDirPath() + "/updateConfig.xml");
	if(!file.open(QIODevice::Text|QIODevice::ReadOnly))
		return false;

	QDomDocument doc;
	doc.setContent(&file);
	file.close();

	if(doc.toString().isEmpty())
		return false;

	QDomElement rootElement = doc.firstChildElement("config");
	if(rootElement.isNull())
		return false;

	QDomElement hostElement = rootElement.firstChildElement("host");
	if(hostElement.isNull() || hostElement.tagName().compare("host",Qt::CaseInsensitive) || hostElement.text().isEmpty())
		return false;

	_host = hostElement.text();

	QDomElement userIdElement = hostElement.nextSiblingElement("userId");
	if(userIdElement.isNull() || userIdElement.tagName().compare("userId",Qt::CaseInsensitive))
		return false;

	_userId = userIdElement.text();

	QDomElement passwordElement = userIdElement.nextSiblingElement("password");
	if(passwordElement.isNull() || passwordElement.tagName().compare("password",Qt::CaseInsensitive))
		return false;

	_password = passwordElement.text();

	QDomElement ftpRootElement = passwordElement.nextSiblingElement("ftpRoot");
	if(ftpRootElement.isNull() || ftpRootElement.tagName().compare("ftpRoot",Qt::CaseInsensitive))
		return false;

	_ftpRoot = ftpRootElement.text();

	QDomElement runExeElement = ftpRootElement.nextSiblingElement("runExe");
	if(runExeElement.isNull() || runExeElement.tagName().compare("runExe",Qt::CaseInsensitive) || runExeElement.text().isEmpty())
		return false;

	_runExe = runExeElement.text();

	return true;
}

UpdateDialog::~UpdateDialog()
{
}

void UpdateDialog::ftpDone( bool error )
{
	ui.label->setText(tr("Update complete."));
	QMapIterator<QString,QProgressBar*> it(_fileProBarMap);

	QMessageBox box;
	box.setText(tr("Update complete.")
		+tr("\nThe current version is ")
		+ _insAppVersion );
	QPushButton* openBtn = box.addButton(tr("Run"),QMessageBox::AcceptRole);
	QPushButton* showLogBtn = box.addButton(tr("Check log"),QMessageBox::ActionRole);
	QPushButton* canelBtn = box.addButton(tr("Close"),QMessageBox::RejectRole);

	box.exec();
	if (box.clickedButton() == openBtn)
	{
		QProcess* pro = new QProcess(this);
		QString dir = qApp->applicationDirPath();
		QDir tmpDir(dir);
		tmpDir.cd("..");
		dir = tmpDir.absolutePath()+_runExe;
		if(QFile::exists(dir))
			pro->startDetached(dir);
		else
			QMessageBox::warning(this,"File Error","The program start faild.");
	}
	else if(box.clickedButton() == showLogBtn)
		QDesktopServices::openUrl(QUrl(_rootDir+"/bin/updatelog.txt"));
	
	this->close();
}

void UpdateDialog::onCancelBtnClicked()
{
	this->close();
}

void UpdateDialog::updateProgress( qint64 value,qint64 max )
{
	qint64 kbValue = value / 1024;
	qint64 suDuValue = kbValue / _runTime;
	ui.label->setText(QString(tr("Updating: %1 (%2/%3)  \n"))
		.arg(_currentFileName).arg(_progressValue).arg(_needUpdateFileInfoList.count()));
	ui.speedLabel->setText(QString(tr("Speed: %1 kb/s")).arg(suDuValue));
	
	if(!_currentFileName.isEmpty())
		_fileProBarMap[_currentFileName]->setValue(value);
}

void UpdateDialog::onCommandStarted( int id )
{
	_runTime = 1;
	for (int i=0;i<_needUpdateFileInfoList.count();i++)
	{
		if (_needUpdateFileInfoList[i].currentId != id)
			continue;
		
		//开始下载这个文件
		_currentFileName = _needUpdateFileInfoList[i].fileName;
		_progressValue++;
		for (int j=0;j<ui.tableWidget->rowCount();j++)
		{
			if(ui.tableWidget->item(j,0)->text().compare(_currentFileName))
				continue;
			ui.tableWidget->scrollToItem(ui.tableWidget->item(j,0));
			break;
		}

		break;	
	}
}

void UpdateDialog::onCommandFinished( int id, bool error )
{
	//下完一个暂时
	static int cu =0;
	if (_currentId != id)
		return;
	
	if (cu == _needUpdateFileInfoList.count())
	{
		_currentFile->close();
		delete _currentFile;
		_ftp.close();
		emit done();
	}
	else
	{
		_runTime = 1;
		_currentFile->close();
		delete _currentFile;
		updateFile(_needUpdateFileInfoList[cu].fileName);
		cu++;
	}
}

void UpdateDialog::beginUpdate( int id,bool error )
{
	if (id != _versionId)
		return;
	
	QByteArray tmp = _checkFtp.readAll();
	QString ftpContent = QString::fromLocal8Bit(tmp);
		
	if(ftpContent.isEmpty())
	{
		//无更新
		_timer->stop();
		QMessageBox::information(this,tr("Warning"),
			tr("Failed to read update information. Please try again or contact the developer."));
		this->close();
	}

	bool flag = initFTPFilesInfo(ftpContent);
	if(flag)
		autoUpdate();
	else
		this->close();
}

void UpdateDialog::autoUpdate()
{
	_needUpdateFileInfoList = getNeedUpdateFilesInfo();

	if(!_needUpdateFileInfoList.isEmpty())
	{
		//初始表格
		initTableData(_needUpdateFileInfoList);
		
		//去更新
		_ftp.connectToHost(_host,21);
		_ftp.login(_userId,_password);
		updateFile("bin/updatelog.txt");
	}
	else
	{
		//无更新
		_timer->stop();
		QMessageBox::information(this,"Message","This software is the latest.");
		this->close();
	}
}

void UpdateDialog::updateFile(QString fileName)//  lib/ a.dll
{
	for (int i=0; i<10; i++)
		_ftp.cd("..");
	
	_ftp.cd(_ftpRoot);

	int currentId;
	
	QStringList list = fileName.split("/");
	//count > 1 意思为文件名中含子目录

	QFile *file = new QFile(_rootDir + "/" + fileName);
	
	if (list.count() > 1)
	{
		QString tempDir = _rootDir;
		for (int i = 0; i < list.count()-1; i++)
		{
			tempDir = tempDir+"/"+list[i];
			QDir dir(tempDir);
			if (dir.exists())
				dir.cd(list[i]);
			else
			{
				dir.mkdir(tempDir);
				dir.cd(list[i]);
			}

		}
		if (!file->open(QIODevice::WriteOnly))
			//文件打开错误
			return ;
		QByteArray tmpArray = (fileName).toUtf8();
		QString tmpFileNamme = QString::fromLatin1(tmpArray);
		currentId =_ftp.get(tmpFileNamme,file);
	}
	else
	{
		if (!file->open(QIODevice::WriteOnly))
			//文件打开错误
			return ;
		QByteArray tmpArray = (fileName).toUtf8();
		QString tmpFileNamme = QString::fromLatin1(tmpArray);
		currentId =_ftp.get(tmpFileNamme,file);
	}
	_currentId = currentId;
	for (int i=0;i<_needUpdateFileInfoList.count();i++)
	{
		if (!_needUpdateFileInfoList[i].fileName.contains(fileName))
			continue;
		
		_needUpdateFileInfoList[i].currentId = currentId;
		break;
	}
	_currentFile = file;
}

bool UpdateDialog::initFTPFilesInfo( const QString& ftpXmlContents )
{
	_ftpFileInfoList.clear();
	QDomDocument ftpDocument;
	ftpDocument.setContent(ftpXmlContents);
	QDomElement ftpVersionElement = ftpDocument.firstChildElement();
	QString update_version = ftpVersionElement.attribute("update_version");
	_insAppVersion = ftpVersionElement.attribute("id");

	if(!update_version.compare(UPDATER_VERSION,Qt::CaseInsensitive))
	{
		QDomNodeList ftpItems = ftpVersionElement.childNodes();
		QDomElement item = ftpVersionElement.firstChildElement("item");
		while(!item.isNull())
		{
			FileInfo info;
			info.fileName = item.attribute("file");
			info.size = item.attribute("size").toLong();
			info.MD5Code = item.attribute("id");
			_ftpFileInfoList.push_back(info);

			item = item.nextSiblingElement("item");
		}
		return true;
	}
	else
	{
		_timer->stop();
		QMessageBox::information(this,
			tr("Message"),
			tr("The update application has been deprecated. Contact the developer (hejw06@gmail.com) to get a new one."));
		return false;
	}
}

QList<FileInfo> UpdateDialog::getNeedUpdateFilesInfo()
{
	QList<FileInfo> fileInfoList;
	QString dirStr = qApp->applicationDirPath();
	QDir dir(dirStr);
	dir.cd("..");
	
	_rootDir = dir.path();//D:/tsinghuaDir/INSEditor/Win32 下面有bin,doc等

	foreach(FileInfo info,_ftpFileInfoList)
	{
		if(!info.fileName.compare("bin/update.exe",Qt::CaseInsensitive))
			continue;

		QString localFileMD5 = getMd5Code(_rootDir + "/" + info.fileName);
		if (localFileMD5 != info.MD5Code)
			fileInfoList.push_back(info);
	}
	
	return fileInfoList;
}

QString UpdateDialog::getMd5Code( const QString& fullFileName )
{
	QFile theFile(fullFileName);
	if(!theFile.open(QIODevice::ReadOnly))
		return QString();

	QByteArray ba = QCryptographicHash::hash(theFile.readAll(),QCryptographicHash::Md5);
	theFile.close();
	return ba.toHex();
}

void UpdateDialog::onTimeout()
{
	_runTime++;
	if (_runTime == LINK_TIMEOUT && ui.label->text().contains("Waiting..."))
	{
		QMessageBox::warning(this,
			tr("Message"),
			tr("Network connection error."));
		this->close();
	}
}

QString UpdateDialog::string2Local( const QString& s )
{
#ifdef Q_OS_WIN  
	return QString::fromLatin1(s.toLocal8Bit());  
#else  
	QTextCodec *codec= QTextCodec::codecForName("gbk");  
	if (codec)  
		return QString::fromLatin1(codec->fromUnicode(s));  
	else  
		return QString("");  
#endif  
}

void UpdateDialog::initTableData( QList<FileInfo> fileInfoList )
{
	ui.tableWidget->setRowCount(fileInfoList.count());
	for (int i=0;i<fileInfoList.count();i++)
	{
		FileInfo* info = &fileInfoList[i];
		ui.tableWidget->setItem(i,0,new QTableWidgetItem(info->fileName));
		ui.tableWidget->setItem(i,1,new QTableWidgetItem(QString("%1 Kb").arg(info->size/1024)));

		QProgressBar* bar = new QProgressBar;
		bar->setRange(0,info->size);
		bar->setValue(0);

		ui.tableWidget->setCellWidget(i,2,bar);
		_fileProBarMap[info->fileName] = bar;
	}
}
