#ifndef HISTORYTAB_H
#define HISTORYTAB_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDateEdit>

class HistoryTab : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryTab(QWidget *parent = nullptr);
    void refreshDB();
    void filter();
    void resetFilter();
private:
    QSqlTableModel *model;
    QDateEdit *startDate, *endDate;
};

class FormattedModel : public QSqlTableModel {
    using QSqlTableModel::QSqlTableModel;
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
};

#endif // HISTORYTAB_H
