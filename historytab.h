#ifndef HISTORYTAB_H
#define HISTORYTAB_H

#include <QWidget>
#include <QSqlTableModel>

class HistoryTab : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryTab(QWidget *parent = nullptr);
    void refreshDB();
private:
    QSqlTableModel *model;
};

class FormattedModel : public QSqlTableModel {
    using QSqlTableModel::QSqlTableModel;
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
};

#endif // HISTORYTAB_H
