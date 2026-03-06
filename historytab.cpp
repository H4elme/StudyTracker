#include "historytab.h"
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QPushButton>

HistoryTab::HistoryTab(QWidget *parent) {

    auto panel = new QHBoxLayout();
    auto layout = new QVBoxLayout(this);

    model = new FormattedModel(this);
    model->setTable("sessions");
    model->sort(3, Qt::SortOrder::DescendingOrder);
    model->select();
    model->setHeaderData(2, Qt::Horizontal, "Duration");
    model->setHeaderData(3, Qt::Horizontal, "Start");

    auto view = new QTableView(this);
    view->setModel(model);
    view->hideColumn(0);
    view->hideColumn(1);

    startDate = new QDateEdit(QDate::currentDate(), this);
    startDate->setCalendarPopup(true);
    startDate->setButtonSymbols(QAbstractSpinBox::NoButtons);
    endDate = new QDateEdit(QDate::currentDate(), this);
    endDate->setCalendarPopup(true);
    endDate->setButtonSymbols(QAbstractSpinBox::NoButtons);

    auto filterButton = new QPushButton("Filter");
    auto resetButton = new QPushButton("Reset");

    sumLabel = new QLabel(this);

    panel->addWidget(startDate);
    panel->addWidget(endDate);
    panel->addWidget(filterButton);
    panel->addWidget(resetButton);
    layout->addLayout(panel);
    layout->addWidget(view);
    layout->addWidget(sumLabel);

    this->setLayout(layout);

    QHeaderView *header = view->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(filterButton, &QPushButton::pressed,
            this, &HistoryTab::filter);

    connect(resetButton, &QPushButton::pressed,
            this, &HistoryTab::resetFilter);

    refreshDB();
}

void HistoryTab::refreshDB() {
    model->select();
    int s = 0, m = 0, h = 0;

    for (int i = 0; i < model->rowCount(); i++) {
        QString str;
        str = model->data(model->index(i, 2)).toString();
        QTime time = QTime::fromString(str, "HH:mm:ss");
        s += time.second();
        m += time.minute();
        h += time.hour();
    }
    m += s / 60;
    s %= 60;
    h += m / 60;
    m %= 60;
    QString str = QString("Total time: %1:%2:%3")
                      .arg(h, 2, 10, '0')
                      .arg(m, 2, 10, '0')
                      .arg(s, 2, 10, '0');
    sumLabel->setText(str);
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
        QDateTime dateTime = QDateTime::fromString(str, "yyyy-MM-dd HH:mm:ss");
        str = dateTime.toString("dd/MM/yy | HH:mm");
        return str;
    }
    return QSqlTableModel::data(idx, role);
};


void HistoryTab::filter() {
    QString start = startDate->date().toString("yyyy-MM-dd");
    QString end = endDate->date().toString("yyyy-MM-dd");

    QString str = QString("date(start_time) BETWEEN '%1' AND '%2'")
                      .arg(start)
                      .arg(end);

    model->setFilter(str);
    refreshDB();
}

void HistoryTab::resetFilter() {
    model->setFilter("");
    startDate->setDate(QDate::currentDate());
    endDate->setDate(QDate::currentDate());
    refreshDB();
}
