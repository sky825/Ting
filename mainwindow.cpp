#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "mgrgoods.h"

#include "storemgr.h"
#include "goodskindmgr.h"
#include "goodsinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //menuBar->addMenu(tr("&Store"));
    createMenus();
}

MainWindow::~MainWindow()
{
    if(workPage != 0){
        // workPage->close();
        delete workPage;
    }
    delete ui;
}


void MainWindow::on_action_mgr_goods_triggered()
{    
    changePage(new MgrGoods);
}

void MainWindow::changePage(QWidget* page){

    ui->workspace->layout()->removeWidget(workPage);

    if(workPage != 0){
        delete workPage;
    }

    ui->workspace->layout()->addWidget(page);
    workPage = page;
    workPage->show();
}

/**
  创建菜单栏
 * @brief MainWindow::createMenus
 */
void MainWindow::createMenus(){

   storeMenu = menuBar()->addMenu(tr("&仓库"));
   storeMenu->addAction(ui->action_store_mgr);

   // 物品管理
   goodsMenu = menuBar()->addMenu(tr("&物品"));

   // 物品类型管理
   goodsMenu->addAction(ui->action_add_kind);
   goodsMenu->addAction(ui->action_goods_info);
}


// Store manage
void MainWindow::on_action_store_mgr_triggered()
{
    changePage(new StoreMgr(this));
}

void MainWindow::on_action_add_kind_triggered()
{
    changePage(new GoodsKindMgr(this));
}

void MainWindow::on_action_goods_info_triggered()
{
    changePage(new GoodsInfo(this));
}
