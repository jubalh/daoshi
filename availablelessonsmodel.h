#ifndef AVAILABLELESSONSMODEL_H
#define AVAILABLELESSONSMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QVariant>

class AvailableLessonsModel : public QAbstractTableModel
{
private:
   QStringList list;
public:
   AvailableLessonsModel();
   int rowCount(const QModelIndex &parent) const;
   int columnCount(const QModelIndex &parent) const;
   QVariant data(const QModelIndex &index, int role) const;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // AVAILABLELESSONSMODEL_H
