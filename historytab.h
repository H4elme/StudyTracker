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

#endif // HISTORYTAB_H
