#include "storemgr.h"
#include "ui_storemgr.h"
#include <QDebug>
#include <QSqlQuery>
#include <QPushButton>
#include <QMessageBox>

StoreMgr::StoreMgr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreMgr)
{

    ui->setupUi(this);
    ui->tableWidget->installEventFilter(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{border: 1px solid rgb(200, 200, 200);}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{border: 1px solid rgb(200, 200, 200);}");
    ui->tableWidget->setAlternatingRowColors(true);
    initData();
}



StoreMgr::~StoreMgr()
{

    delete ui;
}

// init Data
void StoreMgr::initData(){

    QString str;
    QTableWidgetItem* item;
    int rowCount = 0;
    ui->tableWidget->clear();


    // init table header
    QString heaerArr[]{"编号","仓库名称"};

    QTableWidgetItem* headerItem;
    // QHeaderView* header;
    // preview set cell width

    for(int i=0; i< 2; i++){

        headerItem = new QTableWidgetItem ;
        headerItem->setTextAlignment(Qt::AlignCenter);
        headerItem->setText(heaerArr[i]);

        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);

    }

    QString sql = "select s.code, s.name from store_info s";
    QString code,name;
    QSqlQuery query(sql);
   // QPushButton* btn;

    while (query.next()) {
        ui->tableWidget->setRowCount(rowCount+1);
        // code
        code = query.value(0).toString();
        item = new QTableWidgetItem;

        item->setText(code);
        ui->tableWidget->setItem(rowCount,0,item);
        // name
        name = query.value(1).toString();
        item = new QTableWidgetItem;
        item->setText(name);
        ui->tableWidget->setItem(rowCount,1,item);

        // contral
//        btn = new QPushButton;
//        btn->setText("删除");
//        // connect(btn,SIGNAL(clicked),this,SLOT(deleteRow(code)));

//        ui->tableWidget->setCellWidget(rowCount,2,btn);

        rowCount++;
    }

    ui->lblCnt->setText(QString::number(rowCount));

    query.finish();
}

void StoreMgr::deleteRow(){

    QList<QTableWidgetItem*> selItemList = ui->tableWidget->selectedItems();

    int itemCnt = selItemList.count();
    if(itemCnt > 0){

        // 计算出涉及到的数据行
        int rowTotal = ui->tableWidget->rowCount();
        char rowIdList[rowTotal];
        QTableWidgetItem* item;

        int n;
        for(int i=0; i<itemCnt; i++){
            item = selItemList[i];
            n = ui->tableWidget->row(item);
            rowIdList[n] = 1;
        }


        // QString
        for(int i= rowTotal-1; i>=0; i--){

            n = rowIdList[i];
            if(n != 1){
                continue;
            }

            ui->tableWidget->removeRow(i);

        }

    }
}



bool StoreMgr::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());

        if(keyEvent->modifiers() == Qt::ControlModifier){
            if(keyEvent->key() == Qt::Key_Delete){
                qDebug() << "Enter delete key ! ";
                this->deleteRow();
            }
        }
        return true;
    } else {
        // standard event processing
        return obj->eventFilter(obj, event);
    }
}

// Create new row
void StoreMgr::on_btnCreate_clicked()
{
    QTableWidget* table = ui->tableWidget;
    int rows = table->rowCount();
    rows ++;
    table->setRowCount(rows);
}

// Delete data
void StoreMgr::on_btnDelete_clicked()
{
    deleteRow();
}

// Save data
void StoreMgr::on_btnSave_clicked()
{
    // Clear old data for database
    QString sqlDel = "delete from store_info";
    QSqlQuery query;
    query.exec(sqlDel);

    // Save current table data to database
    QString sqlInst = "insert into store_info (code,name) values(?,?)";
    query.prepare(sqlInst);

    QTableWidget* table = ui->tableWidget;
    int rows = table->rowCount();
    QString code,name;
    for(int i=0; i<rows; i++){
        code = table->item(i,0)->text();
        name = table->item(i,1)->text();

        if(code.isNull() || code.isEmpty()){
            continue;
        }

        if(name.isNull() || name.isEmpty()){
            continue;
        }

        query.bindValue(0,code);
        query.bindValue(1,name);
        query.exec();
    }

    QMessageBox msgBox;
    msgBox.setText("保存成功！");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

}

// Flush data
void StoreMgr::on_btnFlush_clicked()
{
    initData();
}
