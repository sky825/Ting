#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void changePage(QWidget* page);

private slots:

    void on_action_mgr_goods_triggered();



    void on_action_store_mgr_triggered();

    void on_action_add_kind_triggered();

    void on_action_goods_info_triggered();

private:

    Ui::MainWindow *ui;
    QWidget *workPage = 0; // 工作页面

    void createMenus();

    QMenu* storeMenu;
    QMenu* goodsMenu;
    QMenu* settingMenu;

};
#endif // MAINWINDOW_H
