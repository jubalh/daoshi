#include "availablelessonsmodel.h"

AvailableLessonsModel::AvailableLessonsModel(QList<OnlineLesson> lessons)
{
   this->list = lessons;
}

int AvailableLessonsModel::rowCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent)
   return list.size();
}

int AvailableLessonsModel::columnCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent)
   return 3;
}

QVariant AvailableLessonsModel::data(const QModelIndex &index, int role) const
{
   if (role == Qt::DisplayRole && list.size() > index.row()) {
      switch (index.column()) {
      case 0:
         return QVariant(list.at(index.row()).getName());
      case 1:
         return QVariant(list.at(index.row()).getLanguage());
      case 2:
         return QVariant(list.at(index.row()).getVersion());
      default:
         return QVariant();
      }
   } else {
      return QVariant();
   }
}

QVariant AvailableLessonsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
         return QVariant("Name");
      case 1:
         return QVariant("Language");
      case 2:
         return QVariant("Version");
      default:
         return QVariant();
      }
   } else {
     return QVariant();
   }
}
