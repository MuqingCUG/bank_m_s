#include "exactmatchquery.h"
#include "ui_exactmatchquery.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
exactmatchQuery::exactmatchQuery(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exactmatchQuery)
{
    ui->setupUi(this);
}

exactmatchQuery::~exactmatchQuery()
{
    delete ui;
}

void exactmatchQuery::on_Button_deposit_inquire_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void exactmatchQuery::on_deposit_inquire_clicked()
{
    QString str_deposit_ID = ui->text_deposit_ID->toPlainText();
    QString str_account_ID = ui->text_account_ID->toPlainText();
    QString str_deposit_date = ui->text_deposit_date->toPlainText();

    //deposit_ID ,deposit_date ,deposit_money ,account_ID
    QSqlQuery q;
    q.prepare("select  * from deposit_information where deposit_information.deposit_ID = ? and deposit_information.account_ID = ? ");
    q.addBindValue(str_deposit_ID);
    q.addBindValue(str_account_ID);
    //query.exec();       // 执行sql语句

    //QSqlRecord rec = q.record();

    QString sqldeposit_ID,  sqldeposit_date, sqldeposit_money, sqlaccount_ID;
    //存储查询得到的存款信息
    QVector<QString> sqldeposit_ID_data;
    QVector<QString> sqldeposit_date_data;
    QVector<QString> sqldeposit_money_data;
    QVector<QString> sqlaccount_ID_data;
    //    int deposit_ID_Col = rec.indexOf("deposit_ID");
    //    int deposit_date_Col = rec.indexOf("deposit_date");
    //    int deposit_money_Col = rec.indexOf("deposit_money");
    //    int account_ID_Col = rec.indexOf("account_ID");
    if(q.exec()){
        qDebug() << " 查询存款单成功！！！";
    }
    while (q.next()){
        sqldeposit_ID = q.value(0).toString();
        sqldeposit_date = q.value(1).toString();
        sqldeposit_money = q.value(2).toString();
        sqlaccount_ID = q.value(3).toString();

        sqldeposit_ID_data.append(sqldeposit_ID);
        sqldeposit_date_data.append(sqldeposit_date);
        sqldeposit_money_data.append(sqldeposit_money);
        sqlaccount_ID_data.append(sqlaccount_ID);
    }

    //QString information;
    ui->deposit_information_brower->clear();
    for(int i =0; i < sqlaccount_ID_data.size();i++){
        ui->deposit_information_brower->append("存款单ID："+sqldeposit_ID_data[i]);
        ui->deposit_information_brower->append("存款日期："+sqldeposit_date_data[i]);
        ui->deposit_information_brower->append("存款金额："+sqldeposit_money_data[i]);
        ui->deposit_information_brower->append( "账户ID："+sqlaccount_ID_data[i]);
    }

}











