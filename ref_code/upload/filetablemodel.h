#ifndef FILETABLEMODEL_H
#define FILETABLEMODEL_H

#include <QAbstractTableModel>
#include <QtCore>

/*!
	@brief   上传程序文件列表的MODEL
	@date    2015.6.23
	@author  Jianjun
*/
class FileTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	FileTableModel(QObject *parent);
	~FileTableModel();

	///刷新MODEL数据
	void resetTable(const QStringList& list);

	///行数目
	virtual int rowCount(const QModelIndex &parent) const;

	///列数目
	virtual int columnCount(const QModelIndex &parent) const;

	///表格数据
	virtual QVariant data(const QModelIndex &index, int role) const;

	///表头数据
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
	///存放待上传的所有文件
	QStringList _files;
	
};

#endif // FILETABLEMODEL_H
