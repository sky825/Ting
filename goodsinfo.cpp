#include "goodsinfo.h"
#include "ui_goodsinfo.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

GoodsInfo::GoodsInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoodsInfo)
{
    ui->setupUi(this);
    ui->tableWidget->installEventFilter(this);
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{border: 1px solid rgb(200, 200, 200);}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{border: 1px solid rgb(200, 200, 200);}");
    ui->tableWidget->setAlternatingRowColors(true);

    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(editGoodsKind(int,int)));

        QString code,name;
        QString sql = "select code ,name from goods_kind order by code";
        QSqlQuery query1(sql);

        QStringList kindList;
        while(query1.next()){
            code = query1.value(0).toString();
            name = query1.value(1).toString();

            combo.addItem(name,code);
        }

    initData();
}

GoodsInfo::~GoodsInfo()
{
    delete ui;
}

void GoodsInfo::editGoodsKind(int row, int column){

    if(column == 1){
        ui->tableWidget->setCellWidget(row,column,&combo);
    }
    // qDebug() << "adfds";
}

// init Data
void GoodsInfo::initData(){

    QString str;
    QTableWidgetItem* item;
    int rowCount = 0;
    ui->tableWidget->clear();


    // init table header
    QString heaerArr[]{"物品编码","类型","单位","品牌","备注"};

    QTableWidgetItem* headerItem;
    // QHeaderView* header;
    // preview set cell width

    for(int i=0; i< 5; i++){

        headerItem = new QTableWidgetItem ;
        headerItem->setTextAlignment(Qt::AlignCenter);
        headerItem->setText(heaerArr[i]);

        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);

    }

    // 查询出所有类型
    QString code,name;


    //

    QString sql = "select g.code,k.name, g.unti,g.brand,g.remark from goods_info g left join goods_kind k on g.kind_code = k.code order by code";
    // QString str;
    QSqlQuery query(sql);
   // QPushButton* btn;

    while (query.next()) {

        ui->tableWidget->setRowCount(rowCount+1);

        for(int i=0; i<5; i++){

            str = query.value(i).toString();
            item = new QTableWidgetItem;
            item->setText(str);
            ui->tableWidget->setItem(rowCount,i,item);

        }

        rowCount++;
    }


    // ui->lblCnt->setText(QString::number(rowCount));

}

void GoodsInfo::deleteRow(){

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

bool GoodsInfo::eventFilter(QObject *obj, QEvent *event){
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
void GoodsInfo::on_btnCreate_clicked()
{
    QTableWidget* table = ui->tableWidget;
    int rows = table->rowCount();
    rows ++;
    table->setRowCount(rows);
}

// Delete data
void GoodsInfo::on_btnDelete_clicked()
{
    deleteRow();
}

// Save data
void GoodsInfo::on_btnSave_clicked()
{
    // Clear old data for database
    QString sqlDel = "delete from goods_kind";
    QSqlQuery query;
    query.exec(sqlDel);

    // Save current table data to database
    QString sqlInst = "insert into goods_kind (code,name) values(?,?)";
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
void GoodsInfo::on_btnFlush_clicked()
{
    initData();
}
