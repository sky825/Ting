#ifndef STOREMGR_H
#define STOREMGR_H

#include <QWidget>
#include <QKeyEvent>


namespace Ui {
class StoreMgr;
}

class StoreMgr : public QWidget
{
    Q_OBJECT

public:
    explicit StoreMgr(QWidget *parent = nullptr);
    ~StoreMgr();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::StoreMgr *ui;
    void initData();
    void deleteRow();

private slots:
    void on_btnCreate_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

    void on_btnFlush_clicked();

};

#endif // STOREMGR_H
