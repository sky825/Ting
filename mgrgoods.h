#ifndef MGRGOODS_H
#define MGRGOODS_H

#include <QWidget>
#include <mydatabase.h>
#include <QSqlTableModel>
#include <QTableWidgetItem>

namespace Ui {
class MgrGoods;
}

class MgrGoods : public QWidget
{
    Q_OBJECT

public:
    explicit MgrGoods(QWidget *parent = nullptr);
    ~MgrGoods();

private slots:

    void on_btn_query_clicked();

private:
    Ui::MgrGoods *ui;

    MyDatabase db;

    QTableWidgetItem* headerItem;
//    QColor bgColor = QColor(65,65,65,0);
//    QBrush headerBrush = QBrush(bgColor);
};

#endif // MGRGOODS_H
