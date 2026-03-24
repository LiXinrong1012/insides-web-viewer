
#include <QtGui>
#include <QtNetwork>

#include "updateftp.h"
#include "ui_updateftp.h"

FtpWindow::FtpWindow(QWidget *parent)
	: QDialog(parent), _ftp(0), _networkSession(0)
{
	ui = new Ui::UpdateFtpClass();
	ui->setupUi(this);
	_host = "112.126.65.135";
	_user = "ins_uploader";
	_pass = "ins123456789";
	_path = "app";
	_localDir ="D:/test";
	_currentItem = 0;

	ui->stateLabel = new QLabel(tr("Waitting"));

	ui->updateBtn->setDefault(true);


	connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(downloadFile()));
	connect(ui->updateBtn, SIGNAL(clicked()), this, SLOT(updateAll()));

	setWindowTitle(tr("FTP"));
//	ui->cancelBtn->setEnabled(false);
}

void FtpWindow::updateAll()
{
	if (_ftp) {
		return;
	}

	if (!_networkSession || !_networkSession->isOpen()) {
		if (_manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
			if (!_networkSession) 
			{
				QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
				settings.beginGroup(QLatin1String("QtNetwork"));
				const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
				settings.endGroup();

				QNetworkConfiguration config = _manager.configurationFromIdentifier(id);
				if ((config.state() & QNetworkConfiguration::Discovered) !=
					QNetworkConfiguration::Discovered) {
						config = _manager.defaultConfiguration();
				}

				_networkSession = new QNetworkSession(config, this);
				connect(_networkSession, SIGNAL(opened()), this, SLOT(connectToFtp()));
			}
			ui->updateBtn->setEnabled(false);
			ui->stateLabel->setText(tr("Opening network session."));
			_networkSession->open();
			return;
		}
	}
	connectToFtp();
}

void FtpWindow::connectToFtp()
{
	_ftp = new QFtp(this);
	connect(_ftp, SIGNAL(commandFinished(int,bool)),
		this, SLOT(ftpCommandFinished(int,bool)));
	connect(_ftp, SIGNAL(listInfo(const QUrlInfo &)),
		this, SLOT(addList(const QUrlInfo &)));
	connect(_ftp, SIGNAL(dataTransferProgress(qint64,qint64)),
		this, SLOT(updateProgress(qint64,qint64)));
//	_fileList.clear();
	_currentPath.clear();

	QUrl url(_host);
	if (!_user.isEmpty() && !_pass.isEmpty()) {
		_ftp->connectToHost(_host, 21);
		_ftp->login(_user,_pass);
	} 
	else {
		_ftp->connectToHost(url.host(), url.port(21));

		if (!url.userName().isEmpty())
			_ftp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
		else
			_ftp->login();
		
	}
	if (!_path.isEmpty())
		_ftp->cd(_path);

	ui->updateBtn->setEnabled(false);
	ui->stateLabel->setText(tr("Connecting to FTP server %1...").arg(_host));
}



void FtpWindow::cancelDownload()
{
	if (_ftp != 0)
	{
		_ftp->abort();

	}

	if (_file != NULL)
	{
		if (_file->exists()) {
			_file->close();
			_file->remove();
		}
		delete _file;
	}
	this->close();
}

void FtpWindow::ftpCommandFinished(int, bool error)
{
	if (_ftp->currentCommand() == QFtp::ConnectToHost) {
		if (error) {
			QMessageBox::information(this, tr("FTP"),tr("Unable to connect to the FTP server at %1. Please check that the host name is correct.").arg(_host));
			updateAll();
			return;
		}
		ui->stateLabel->setText(tr("Logged onto %1.").arg(_host));
		ui->updateBtn->setEnabled(true);
		return;
	}

	if (_ftp->currentCommand() == QFtp::Login)
	{
		_ftp->list();
	}
	if (_ftp->currentCommand() == QFtp::Get) {
		if (error) {
			ui->stateLabel->setText(tr("Canceled download of %1.").arg(_file->fileName()));
			_file->close();
		} else {
			ui->stateLabel->setText(tr("Downloaded %1 to current directory.").arg("_file->fileName()"));
//			downloadFile();
			connect(this,SIGNAL(downloadNext()),this,SLOT(downloadFile()));
			if (!_ftp->hasPendingCommands())
			{
				emit downloadNext();
			}
	  	    
		}
		_file->deleteLater();

	}
	else if (_ftp->currentCommand() == QFtp::List) {
//		downloadFile();
	}

}

void FtpWindow::addList(const QUrlInfo &urlInfo)
{
	if (urlInfo.isFile()) { 
		if (urlInfo.isReadable()) { 
			_updateFiles.push_back(urlInfo.name());
		} 
	} 
	else if (urlInfo.isDir() && !urlInfo.isSymLink()) { 
		;
	} 
}


void FtpWindow::updateProgress(qint64 readBytes,qint64 totalBytes)
{
	ui->progressBar->setMaximum(totalBytes);
	ui->progressBar->setValue(readBytes);
	if(readBytes == totalBytes)
	{
		ui->cancelBtn->setEnabled(false);
		//connect(this,SIGNAL(downloadNext()),this,SLOT(downloadFile()));
		//emit downloadNext();
	}
	else
	{
		ui->cancelBtn->setEnabled(true);
	}
}

void FtpWindow::downloadFile()
{

	if (_currentItem < _updateFiles.count())
	{
		_file = new QFile(_localDir + "/" + _updateFiles[_currentItem]);
		if(!_file->open(QIODevice::WriteOnly))
		{
			int a;
		}
		_ftp->get(_updateFiles[_currentItem],_file);
	}
	
}


