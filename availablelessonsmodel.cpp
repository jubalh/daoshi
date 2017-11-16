#include "availablelessonsmodel.h"

AvailableLessonsModel::AvailableLessonsModel()
{
   list << "name" << "something";
}

int AvailableLessonsModel::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent)
   return 1;
}

int AvailableLessonsModel::columnCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent)
   return list.length();
}

QVariant AvailableLessonsModel::data(const QModelIndex &index, int role) const
{
   if (role == Qt::DisplayRole) {
      QString s = list.at(index.column());
      return QVariant(s);
   } else {
      return QVariant();
   }
}

QVariant AvailableLessonsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
      if (section == 0) {
         return QVariant("n");
      } else if (section == 1) {
         return QVariant("s");
      }
   } else {
      return QVariant();
   }
}
