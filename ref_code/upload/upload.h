#ifndef UPLOAD_H
#define UPLOAD_H

#include <QtGui/QDialog>
#include <QFileDialog>
#include <QProgressDialog>
#include <QtCore>
#include <QListView>
#include <QFtp>
#include <QFile>
#include <QTime>
#include <QDate>
#include <QMessageBox>
#include <QEventLoop>
#include <QMapIterator>

#include "ui_upload.h"
#include "filetablemodel.h"

/*!
	@brief   文件信息类
	@date    2015.6.23
	@author  Jianjun
*/
class FileInfo
{
public:
	QString fileName;
	QString fullFileName;
	QString MD5Code;
};


/*!
	@brief   上传程序对话框类
	@date    2015.6.23
	@author  Jianjun
*/
class UploadDialog : public QDialog
{
	Q_OBJECT

public:
	UploadDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~UploadDialog();


private slots:
	///当选择按钮点击时调用
	void onSelectBtnClicked();

	///当复选框被点击时调用
	void onCheckBtnClicked();

	///当取消按钮点击时调用 
	void onCancelBtnClicked();

	///当提交按钮单击时调用
	void onSubmitBtnClicked();

	///当FTP设置按钮单击时调用
	void onFtpSettingBtnClicked();

	///当命令完成时调用
	void onCommandFinished ( int id, bool error ) ;

	///当FTP完成时调用
	void ftpDone(bool error);

	///检测路径FTP完成时调用 
	void checkDirFtpDone(bool error);

	///更新当前上传进度
	void updateProcess(qint64 value,qint64 sum);

	///检测路径列表信息
	void checkDirFtpListInfo(const QUrlInfo &urlInfo);

private:
	///解析下一个路径
	void processNextDirectory();

	///更新日志
	void updateLog();

	///上传文件
	void uploadFile(QString fileName);

	///转换字符串格式到本地
	QString string2Local(const QString& s);

	///处理文件 
	void handelFiles(QStringList& files,QFileInfoList& list);

	///更新表格
	void updateTable();

	///更新XML
	void updateXml();

	///自动设置版本号
	void autoSetVersion();

	///计算MD5码
	inline QString getMD5Code(const QString& fullFileName);

	///读取上传配置
	bool readUploadConfig();

	///保存上传配置
	bool saveUploadConfig();

private:
	Ui::UploadClass ui;

	///存放等待上传的文件名
	QStringList				_fileNames;

	///存放FTP中XML中读到的内容
	QString					_ftpContent;

	///程序根目录
	QString					_projectDir;

	///文件信息列表对应MODEL
	FileTableModel*			_model;

	///打开的文件
	QList<QFile*>			_openFiles;

	///本地文件信处列表
	QList<FileInfo>			_localFileInfoList;

	///FTP的ROOT
	
	///用于上传的ftp
	QFtp					_ftp;

	///用于检测事项的FPT
	QFtp					_checkFtp;

	///处理LOG的FTP
	QFtp					_logFtp;

	///用于检测路径的FTP
	QFtp					_checkDirFtp;

	///文件信处列表对应MODEL
	FileTableModel*			_fileModel;

	///FTP路径列表
	QList<QString>			_ftpDirList;

	///当前路径
	QString					_currentDir;

	///FTP路径
	QStringList				_ftpDirs;

	///FTP读取到的XML内容
	QString					_ftpXmlContents;

	///id与文件名键值对
	QMap<int,QString>		_idFile;

private:
	///ftp配置变量
	///FTP根路径
	QString					_ftpRootDir;

	///FTP地址
	QString					_host;

	///ftp用户名
	QString					_userId;

	///ftp密码
	QString					_password;
};

#endif // UPLOAD_H
