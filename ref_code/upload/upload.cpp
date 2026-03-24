#include "upload.h"
#include <QDomDocument>

#include "ftpconfigdialog.h"

#define UPLOADVERSION "2.0"

UploadDialog::UploadDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	if(!readUploadConfig())
	{
		/*_host = "112.126.65.135";
		_userId = "ins_uploader";
		_password = "ins123456789";
		_ftpRootDir = "app/insides";*/
		onFtpSettingBtnClicked();
		if(_host.isEmpty())
			QTimer::singleShot(1000,qApp,SLOT(quit()));
	}
	
	QDir dir = qApp->applicationDirPath();
	dir.cdUp();
	_projectDir = dir.path();
	_projectDir.replace("\\","/");
	ui.proLineEdit->setText(_projectDir);
	
	autoSetVersion();

	connect(&_ftp,SIGNAL(done(bool)),this,SLOT(ftpDone(bool)));
	connect(&_ftp,SIGNAL(commandFinished ( int , bool)),this,SLOT(onCommandFinished(int,bool)));
	connect(&_ftp,SIGNAL(dataTransferProgress ( qint64, qint64 )),this,SLOT(updateProcess(qint64,qint64)));

	connect(ui.selectBtn,SIGNAL(clicked()),this,SLOT(onSelectBtnClicked()));
	connect(ui.checkBtn,SIGNAL(clicked()),this,SLOT(onCheckBtnClicked()));
	connect(ui.ftpSettingBtn,SIGNAL(clicked()),this,SLOT(onFtpSettingBtnClicked()));

	connect(ui.cancelPushBtn,SIGNAL(clicked()),this,SLOT(onCancelBtnClicked()));
	connect(ui.submitPushBtn,SIGNAL(clicked()),this,SLOT(onSubmitBtnClicked()));

	_fileModel = new FileTableModel(0);
	ui.tableView->setModel(_fileModel);

	connect(this,SIGNAL(resetModel()),_fileModel,SLOT(onResetModel()));
	connect(_fileModel,SIGNAL(tableModelDataChanged()),this,SLOT(onTableModelDataChanged()));

	_checkFtp.connectToHost(_host,21);
	_checkFtp.login(_userId,_password);
	_checkFtp.cd(_ftpRootDir+"/bin");
	_checkFtp.get("version.xml");

	_logFtp.connectToHost(_host,21);
	_logFtp.login(_userId,_password);
	_logFtp.cd(_ftpRootDir+"/bin");
	_logFtp.get("updatelog.txt");

	connect(&_checkDirFtp, SIGNAL(done(bool)), this, SLOT(checkDirFtpDone(bool))); 
	connect(&_checkDirFtp, SIGNAL(listInfo(const QUrlInfo &)), 
		this, SLOT(checkDirFtpListInfo(const QUrlInfo &))); 

	_checkDirFtp.connectToHost(_host,21);
	_checkDirFtp.login(_userId,_password);

	_ftpDirList.append("/"+_ftpRootDir+"/");
	_model = (FileTableModel*)ui.tableView->model();
	processNextDirectory();
}

UploadDialog::~UploadDialog()
{
}

void UploadDialog::uploadFile( QString fN )
{
	QString fileName =fN;// string2Local(fN);
	_ftp.cd("/"+_ftpRootDir+"/");
	for (int i=0;i<_ftpDirs.count();i++)
		_ftpDirs[i].remove("/app/insides//");//所有目录
	
	QFile *file = new QFile(_projectDir + "/" + fileName);
	QByteArray ba;
	file->open(QFile::ReadOnly);
	ba = file->readAll();//--------------------------
	QStringList list = fileName.split("/");
	//--------------------------------------
	if (list.count() > 1)
	{
		QStringList dirList; 
		for (int i=0; i<list.count()-1;i++)
		{
			QString temDir;
			for (int j=0; j<=i;j++)
			{
				if (temDir.isEmpty() || temDir.isNull())
					temDir = list[j];
				else
					temDir = temDir + "/" + list[j];
			}
			dirList.push_back(temDir);
		}
		
		for (int i=0; i<dirList.count(); i++)
		{//错在于不可重复创建dir
			bool flag = false;
			//list还未执行 应提前获取
			for(int j=0;j<_ftpDirs.count();j++)
			{
				if (dirList[i] == _ftpDirs[j])
				{
					flag = true;
					break;
				}
			}
			if(flag)
				_ftp.cd("/"+_ftpRootDir+"/"+dirList[i]+"/");
			else
			{
				_ftp.mkdir(list[i]);
				_ftpDirs.push_back(dirList[i]);
				_ftp.cd("/"+_ftpRootDir+"/"+dirList[i]+"/");
			}
		}
		QByteArray tmpArray = (list[list.count()-1]).toUtf8();
		QString tmpFileNamme = QString::fromLatin1(tmpArray);
		int id =_ftp.put(ba,tmpFileNamme);
		_idFile.insert(id,fileName);
	}
	else
	{
		QByteArray tmpArray = (fileName).toUtf8();
		QString tmpFileNamme = QString::fromLatin1(tmpArray);
		int id = _ftp.put(ba,tmpFileNamme);
		_idFile.insert(id,fileName);
	}

	_openFiles.append(file);
}

void UploadDialog::ftpDone( bool error )
{
	bool flag = false;
	if(!_openFiles.isEmpty())
	{
		QMessageBox::information(this,"Info","The upload is finish !");
		flag = true;
	}
	qDeleteAll(_openFiles);
	_openFiles.clear();
	if (flag)
		this->close();
}

void UploadDialog::onCancelBtnClicked()
{
	this->close();
}

void UploadDialog::onSubmitBtnClicked()
{
	ui.submitPushBtn->setEnabled(false);
	_ftp.connectToHost(_host,21);
	_ftp.login(_userId,_password);
	_ftp.cd(_ftpRootDir);
	
	if(!_localFileInfoList.isEmpty())
	{
		updateLog();
		for (int i=0; i< _localFileInfoList.count(); i++)
			uploadFile(_localFileInfoList[i].fileName);

		uploadFile("bin/updatelog.txt");
		uploadFile("bin/version.xml");
	}
	else
	{
		//没有需要更新的
		QMessageBox::information(this,"Sorry","No file need to upload!");
		this->close();
	}

	_ftp.close();
}

void UploadDialog::updateLog()
{
	QFile openFile(_projectDir +"/bin/" + "updatelog.txt");

	QString contents = QString::fromLocal8Bit(_logFtp.readAll());
	_logFtp.close();
	QString newContents = ui.updateInfoTextEdit->toPlainText();
	if (newContents.isEmpty())
		newContents = "No update contents";
	
	QFile writeFile(_projectDir + "/bin/" + "updatelog.txt");
	writeFile.open(QFile::WriteOnly | QFile::Text );
	QTextStream stream(&writeFile);
	QString d = QDate::currentDate().toString("yyyy-MM-dd");
	QString s = QTime::currentTime().toString("hh:mm:ss");
	stream << d + " " + s +"\n";
	stream << "Version :" + ui.versionLineEdit->text()+"\n";
	stream <<newContents ;
	stream <<"\n\n";
	if (!contents.isEmpty())
	{
		stream<<"---------------------------------------------\n\n";
		stream<<contents;
	}

	writeFile.close();
}

void UploadDialog::onCommandFinished( int id, bool error )
{
	QMap<int,QString>::iterator iter = _idFile.find(id);
	if (iter == _idFile.end())
		return;
	
	QString v = iter.value();
	_fileNames.removeOne( iter.value());
	_model->resetTable(_fileNames);
	ui.tableView->scrollToTop();
}

void UploadDialog::checkDirFtpDone( bool error )
{
	processNextDirectory(); 
}

void UploadDialog::checkDirFtpListInfo( const QUrlInfo &urlInfo )
{
	if (urlInfo.isDir() && !urlInfo.isSymLink())
	{ 
		_ftpDirs.push_back(_currentDir + "/" + urlInfo.name());
		_ftpDirList.append(_currentDir + "/" + urlInfo.name()); 
	} 
}

void UploadDialog::processNextDirectory()
{
	if (_ftpDirList.isEmpty()) 
		return;

	_currentDir = _ftpDirList.takeFirst(); 
	_checkDirFtp.cd(_currentDir); 
	_checkDirFtp.list(); 
}

void UploadDialog::updateProcess( qint64 value,qint64 sum )
{
	ui.progressBar->setMaximum(sum);
	ui.progressBar->setValue(value);
}

QString UploadDialog::string2Local( const QString& s )
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

void UploadDialog::onSelectBtnClicked()
{
	QString rDir = QFileDialog::getExistingDirectory(this,"Upload root dir",".",QFileDialog::ShowDirsOnly);
	if(rDir.isEmpty())
		return;

	QDir dir(rDir);
	if(!dir.exists())
		return;
	
	_projectDir = rDir;
	_projectDir.replace("\\","/");
	ui.proLineEdit->setText(rDir);
}

void UploadDialog::onCheckBtnClicked()
{
	QFileInfoList fileInfos;
	QStringList files;
	QDir dir(_projectDir);
	fileInfos = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
	handelFiles(files,fileInfos);

	for (int i=0;i<files.count();i++)
	{
		if(files[i].contains("updatelog.txt") || files[i].contains("version.xml"))
			continue;

		FileInfo tmp;
		tmp.fullFileName = files[i];
		files[i].remove(_projectDir + "/");
		tmp.fileName = files[i];
		tmp.MD5Code = getMD5Code(tmp.fullFileName);
		_localFileInfoList.push_back(tmp);
	}

	updateXml();
	
	QByteArray tmp = _checkFtp.readAll();
	QString tmpStr = QString::fromLocal8Bit(tmp);
	if(!tmpStr.isEmpty())
		_ftpContent = tmpStr;

	if(!_ftpContent.isEmpty())
	{
		QDomDocument doc;
		doc.setContent(_ftpContent);
		QDomElement root = doc.firstChildElement("version");
		QDomElement item = root.firstChildElement("item");
		while(!item.isNull())
		{
			QString fileName = item.attribute("file");
			QString id = item.attribute("id");
			
			for(int i=0;i<_localFileInfoList.count();i++)
			{
				if(!_localFileInfoList[i].fileName.compare(fileName) && !_localFileInfoList[i].MD5Code.compare(id))
				{
					_localFileInfoList.removeAt(i);
					break;
				}
			}
		
			item = item.nextSiblingElement("item");
		}
	}

	if(_localFileInfoList.isEmpty())
	{
		QMessageBox::information(this,"Upload","No files need to upload ,the application will exit.");
		this->close();
	}

	updateTable();
}

void UploadDialog::handelFiles( QStringList& files,QFileInfoList& list )
{
	foreach(QFileInfo info,list)
	{
		if(info.isFile())
		{
			QString s = info.absoluteFilePath();
			files.push_back(info.absoluteFilePath());
		}
		else if(info.isDir())
		{
			QString s = info.absoluteFilePath();
			QDir tmpDir(s);
			handelFiles(files,tmpDir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot));
		}
	}
}

void UploadDialog::updateTable()
{
	foreach(FileInfo info,_localFileInfoList)
		_fileNames.push_back(info.fileName);

	_model->resetTable(_fileNames);
}

void UploadDialog::updateXml()
{
	QDomDocument doc;
	QDomElement versionElement = doc.createElement("version");
	versionElement.setAttribute("id",ui.versionLineEdit->text());
	versionElement.setAttribute("update_version",UPLOADVERSION);
	doc.appendChild(versionElement);
	foreach(FileInfo info,_localFileInfoList)
	{
		QDomElement tmpItemElement = doc.createElement("item");
		tmpItemElement.setAttribute("file",info.fileName);
		QFile file(info.fullFileName);
		tmpItemElement.setAttribute("size",file.size());
		tmpItemElement.setAttribute("id",info.MD5Code);
		versionElement.appendChild(tmpItemElement);
	}
	
	QString fileFullName = _projectDir + "/bin/version.xml";
	QFile xmlFile(fileFullName);
	xmlFile.open(QIODevice::Text | QIODevice::WriteOnly);
	QTextStream stream(&xmlFile);
	QString ss = doc.toString();
	stream << doc.toString();
	xmlFile.close();
}

void UploadDialog::autoSetVersion()
{
	QString d = QDate::currentDate().toString("yyyyMMdd");
	QString s = QTime::currentTime().toString("hhmm");
	ui.versionLineEdit->setText(d+s);
}

void UploadDialog::onFtpSettingBtnClicked()
{
	FtpConfig config(_host,_userId,_password,_ftpRootDir);
	FtpConfigDialog dialog(this,config);
	dialog.exec();
	if(dialog.okBtnIsClicked())
		config = dialog.getConfig();
	else
		return;

	_host = config._host;
	_userId = config._userId;
	_password = config._password;
	_ftpRootDir = config._ftpRootDir;

	saveUploadConfig();
}

QString UploadDialog::getMD5Code( const QString& fullFileName )
{
	QFile theFile(fullFileName);
	if(!theFile.open(QIODevice::ReadOnly))
		return QString();

	QByteArray ba = QCryptographicHash::hash(theFile.readAll(),QCryptographicHash::Md5);
	theFile.close();

	return ba.toHex();
}

bool UploadDialog::readUploadConfig()
{
	QFile file(qApp->applicationDirPath()+"/uploadConfig.xml");
	if(!file.open(QIODevice::Text|QIODevice::ReadOnly))
		return false;

	QDomDocument doc;
	doc.setContent(&file);
	file.close();

	QDomElement rootElement = doc.firstChildElement("config");
	if(rootElement.isNull())
		return false;

	QDomElement hostElement = rootElement.firstChildElement("host");
	if(hostElement.isNull() || hostElement.text().isEmpty())
		return false;

	_host = hostElement.text();

	QDomElement userIdElement = hostElement.nextSiblingElement("userId");
	if(userIdElement.isNull())
		return false;

	_userId = userIdElement.text();

	QDomElement passwordElement = userIdElement.nextSiblingElement("password");
	if(passwordElement.isNull())
		return false;

	_password = passwordElement.text();

	QDomElement ftpRootElement = passwordElement.nextSiblingElement("ftpRoot");
	if(ftpRootElement.isNull())
		return false;

	_ftpRootDir = ftpRootElement.text();

	return true;
}

bool UploadDialog::saveUploadConfig()
{
	QFile file(qApp->applicationDirPath()+"/uploadConfig.xml");
	file.open(QIODevice::Text|QIODevice::WriteOnly);
	QDomDocument doc;
	QDomElement rootElement = doc.createElement("config");
	rootElement.setAttribute("version","2.0");
	doc.appendChild(rootElement);

	QDomElement hostElement = doc.createElement("host");
	QDomNode hostDomNode = doc.createTextNode(_host);
	hostElement.appendChild(hostDomNode);
	rootElement.appendChild(hostElement);

	QDomElement userIdElement = doc.createElement("userId");
	QDomNode useridDomNode = doc.createTextNode(_userId);
	userIdElement.appendChild(useridDomNode);
	rootElement.appendChild(userIdElement);

	QDomElement passwordElement = doc.createElement("password");
	QDomNode passwordDomNode = doc.createTextNode(_password);
	passwordElement.appendChild(passwordDomNode);
	rootElement.appendChild(passwordElement);

	QDomElement ftpRootElement = doc.createElement("ftpRoot");
	QDomNode ftpRootDomNode = doc.createTextNode(_ftpRootDir);
	ftpRootElement.appendChild(ftpRootDomNode);
	rootElement.appendChild(ftpRootElement);

	QTextStream stream(&file);
	stream << doc.toString();
	file.close();

	return true;
}
