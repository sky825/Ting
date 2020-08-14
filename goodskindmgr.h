#ifndef GOODSKINDMGR_H
#define GOODSKINDMGR_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class GoodsKindMgr;
}

class GoodsKindMgr : public QWidget
{
    Q_OBJECT

public:
    explicit GoodsKindMgr(QWidget *parent = nullptr);
    ~GoodsKindMgr();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_btnCreate_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

    void on_btnFlush_clicked();

private:
    Ui::GoodsKindMgr *ui;

    void initData();
    void deleteRow();
};

#endif // GOODSKINDMGR_H
