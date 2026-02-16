#include "historytab.h"
#include <QListView>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include <QHeaderView>

HistoryTab::HistoryTab(QWidget *parent) {
    model = new FormattedModel(this);
    model->setTable("sessions");
    model->select();
    model->setHeaderData(2, Qt::Horizontal, "Duration");
    model->setHeaderData(3, Qt::Horizontal, "Start");

    auto view = new QTableView(this);
    view->setModel(model);
    view->resize(720, 720);
    view->hideColumn(0);
    view->hideColumn(1);
    view->show();

    QHeaderView *header = view->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);

    refreshDB();
}

void HistoryTab::refreshDB() {
    model->select();

}


QVariant FormattedModel::data(const QModelIndex &idx, int role) const {
    if (idx.column() == 2 && role == Qt::DisplayRole) {
        int curSeconds = QSqlTableModel::data(idx, role).toInt();
        int h = curSeconds / 3600;
        int m = curSeconds % 3600 / 60;
        int s = curSeconds % 60;
        QString str = QString("%1:%2:%3")
                          .arg(h, 2, 10, '0')
                          .arg(m, 2, 10, '0')
                          .arg(s, 2, 10, '0');
        return str;
    }
    if (idx.column() == 3 && role == Qt::DisplayRole) {
        QString str = QSqlTableModel::data(idx, role).toString();
        QString y = str.mid(2, 2);
        QString m = str.mid(5, 2);
        QString d = str.mid(8, 2);
        QString time_ = str.mid(11, 5);
        str = QString("%1/%2/%3 | %4")
                  .arg(d)
                  .arg(m)
                  .arg(y)
                  .arg(time_);
        return str;
    }
    return QSqlTableModel::data(idx, role);
};
