#ifndef FTPCONFIGDIALOG_H
#define FTPCONFIGDIALOG_H

#include <QDialog>
namespace Ui {class FtpConfigDialog;};

/*!
	@brief   FTP配置类
	@date    2015.6.23
	@author  Jianjun
*/
class FtpConfig{
public:
	FtpConfig(const QString& host,const QString& userId,const QString& password,const QString& ftpRootDir)
		:_host(host)
		,_userId(userId)
		,_password(password)
		,_ftpRootDir(ftpRootDir)
	{
	}

	///地址
	QString _host;

	///用户名
	QString _userId;

	///密码
	QString _password;

	///FTP根路径
	QString _ftpRootDir;
};


/*!
	@brief   FTP配置对话框
	@date    2015.6.23
	@author  Jianjun
*/
class FtpConfigDialog : public QDialog
{
	Q_OBJECT

public:
	FtpConfigDialog(QWidget *parent,const FtpConfig& config);
	~FtpConfigDialog();
	
	///获得当前FTP配置
	FtpConfig getConfig();

	///是否点击了OK按钮
	bool okBtnIsClicked(){return _okBtnClicked;}

private slots:
	///OK按钮单击对应槽 
	void onOkBtnClicked();

private:
	Ui::FtpConfigDialog *ui;
	
	///ok按钮是否被点击
	bool _okBtnClicked;
};

#endif // FTPCONFIGDIALOG_H
