#include "mgrgoods.h"
#include "ui_mgrgoods.h"
#include "mydatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


MgrGoods::MgrGoods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MgrGoods)
{
    ui->setupUi(this); 
    db.open();

    // table header
    QTableWidget* tableWiget = ui->tableWidget;
    tableWiget->setColumnCount(8);


    QString heaerArr[]{"编号","数量","单位","仓库","类型","品牌","备注","入库/出库"};

    QColor* bgColor = new QColor(65,65,65,0);
    QBrush* headerBrush = new QBrush(*bgColor);

    for(int i=0; i< 8; i++){

        headerItem = new QTableWidgetItem ;
        headerItem->setTextAlignment(Qt::AlignCenter);
        headerItem->setText(heaerArr[i]);
        headerItem->setFlags(Qt::ItemFlag::NoItemFlags);


        headerItem->setBackground(*headerBrush);
 //       headerItem->setBackgroundColor(bgColor);
        tableWiget->setHorizontalHeaderItem(i,headerItem);

    }

 }

MgrGoods::~MgrGoods()
{
    db.close();
    delete ui;
}


void MgrGoods::on_btn_query_clicked()
{
    QString sql = "select m.id,m.name,m.quantity,m.unti,m.area_code,m.brand,m.kind,m.remark from material m";
    QSqlQuery query(db.db);

    int iv;
    QString str;

    //query.prepare(sql);
    // str = query.executedQuery();
   // if(!query.executedQuery(sql)){
   //     qDebug() << str;
   // }

    if(!query.exec(sql)){
        qDebug() << query.lastError();
    }

    QTableWidget* tableWiget = ui->tableWidget;
    tableWiget->setRowCount(0);
    int rowCount = tableWiget->rowCount();

        while(query.next()){
            rowCount++;
            tableWiget->setRowCount(rowCount);
            for(int i=0; i<8; i++){
                if(i==7){
                    break;
                }

                QTableWidgetItem* item = new QTableWidgetItem;
                str = query.value(i).toString();
                 item->setText(str.toUtf8());

                 qDebug() << str;
                 tableWiget->setItem(rowCount-1,i,item);
            }
        }
     query.finish();
     //ui->tableWidget.set
}
