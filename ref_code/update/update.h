#ifndef UPDATE_H
#define UPDATE_H

#include <QtGui/QDialog>
#include <QFtp>
#include <QFile>
#include <QProgressBar>
#include <QFileDialog>
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include <QTimer>
#include "ui_update.h"

/*!
	@brief  文件信息
	@date   2015.6.23
	@author Jianjun
*/
class FileInfo
{
public:
	///文件名，包括小目录
	QString fileName;

	///文件大小
	long size;

	///文件MD5值
	QString MD5Code;

	///ftp执行id号
	int currentId;
};

class UpdateDialog : public QDialog
{
	Q_OBJECT

public:
	UpdateDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~UpdateDialog();

signals:
	///下载 完成时发出
	void done();

private slots:
	///与服务器连接是否会出现连接超时
	void onTimeout();

	///当命令开始时
	void onCommandStarted ( int id );

	///当命令完成时
	void onCommandFinished ( int id, bool error );
	
	///开始更新
	void beginUpdate(int id,bool error);

	///更新总更新进度
	void updateProgress(qint64 value,qint64 max);

	///FTP所有更新完成
	void ftpDone(bool error);

	///当取消按钮被点击时调用
	void onCancelBtnClicked();
		
private:
	///初始化表格数据
	void initTableData(QList<FileInfo> fileInfoList);

	///初始化FTP文件信息
	bool initFTPFilesInfo(const QString& ftpXmlContents );

	///获得所有需要更新的文件的信息列表
	QList<FileInfo> getNeedUpdateFilesInfo();

	///通过给定的文件全名获得MD5值
	inline QString getMd5Code(const QString& fullFileName);

	///将字符串转为本地格式
	QString string2Local(const QString& s);

	///自动更新
	void autoUpdate();

	///更新文件
	void updateFile(QString fileName);
	
	///读取update.exe同目录的updateConfig.xml文件，成功返回true
	bool readUpdateConfig();

private:
	Ui::UpdateManger			ui;

	///主下载FTP
	QFtp						_ftp;

	///用来检测更新FTP
	QFtp						_checkFtp;

	///正下载第几个
	int							_progressValue;

	///记录下载version.xml时产生的id号
	int							_versionId;
	
	///存放每个文件对应进度条
	QMap<QString,QProgressBar*>	_fileProBarMap;

	///INSAPP版本号
	QString						_insAppVersion;

	///程序ROOT
	QString						_rootDir;

	///存放FTP的所有文件信息列表
	QList<FileInfo>				_ftpFileInfoList;

	///正在下载的ID
	int							_currentId;

	///要更新的文件
	QList<FileInfo>				_needUpdateFileInfoList;

	///当前正在下载的文件
	QFile*						_currentFile;

	///用来检测连接超时的问题
	QTimer*						_timer;

	///记录程序运行时间
	int							_runTime;

	///正在下载的文件名
	QString						_currentFileName;

private:
	///配置变量
	QString						_host;
	QString						_userId;
	QString						_password;
	QString						_ftpRoot;
	QString						_runExe;
};

#endif // UPDATE_H
