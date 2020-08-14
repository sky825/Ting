#ifndef GOODSINFO_H
#define GOODSINFO_H

#include <QWidget>
#include <QComboBox>
#include <QKeyEvent>

namespace Ui {
class GoodsInfo;
}

class GoodsInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GoodsInfo(QWidget *parent = nullptr);
    ~GoodsInfo();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_btnCreate_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

    void on_btnFlush_clicked();

    void editGoodsKind(int row, int column);
private:
    Ui::GoodsInfo *ui;
    void initData();
    void deleteRow();

    QComboBox combo;
};

#endif // GOODSINFO_H
