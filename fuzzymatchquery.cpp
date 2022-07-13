#include "fuzzymatchquery.h"
#include "ui_fuzzymatchquery.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QVector>

fuzzymatchquery::fuzzymatchquery(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fuzzymatchquery)
{
    ui->setupUi(this);
}

fuzzymatchquery::~fuzzymatchquery()
{
    delete ui;
}

void fuzzymatchquery::on_pushButton_clicked()
{
    int index =  ui->inquire_condition->currentIndex();

    QString condition;
    if(index==0){
        //根据名字进行模糊查询
        condition = ui->inquire_content->toPlainText();
        QSqlQuery q;
        QString inquire_ID;
        q.prepare("select customer_id from customer where name like ?+'%' ");
        q.addBindValue(condition);
        q.exec();
        while(q.next()){
            inquire_ID = q.value(0).toString();
            qDebug()<<"模糊查询得到的 ID："<<inquire_ID;
        }

        QSqlQuery sql_inquire_loan;
        sql_inquire_loan.prepare("select * from loans where loans.account_id=?");
        sql_inquire_loan.addBindValue(inquire_ID);
        if(sql_inquire_loan.exec()){
            qDebug() << " 根据名字查询贷款信息成功！！！";
        }
        /*
    loan_ID VARCHAR(50)  NOT NULL,
    loan_date VARCHAR ( 30 ) NOT NULL,	--贷款时间
    loan_amount int  NOT NULL ,--CHECK ( loan_amount >= 1000.00 AND loan_amount < 99999.00 ),
    --loan_type VARCHAR ( 30 ) NOT NULL,
    loan_duration_months int  NOT NULL,
    interest_rate int  NOT NULL CHECK ( interest_rate > 00.00 AND interest_rate < 50.00 ),		--双方谈判
    monthly_payment_due_date int  NOT NULL CHECK ( monthly_payment_due_date >= 01 AND monthly_payment_due_date <= 31 ),
    monthly_minimum_payment int  NOT NULL,
    --payment_method VARCHAR ( 20 ) NOT NULL,
    account_id VARCHAR(20)  NOT NULL,*/
        ui->information_brower->clear();
        while (sql_inquire_loan.next()){
            QString loan_information =
                    "贷款单ID："+sql_inquire_loan.value(0).toString()+'\n'
                    +"贷款时间："+sql_inquire_loan.value(1).toString()+'\n'
                    +"贷款金额（￥）："+sql_inquire_loan.value(2).toString()+'\n'
                    +"贷款周期："+sql_inquire_loan.value(3).toString()+'\n'
                    +"贷款利率："+sql_inquire_loan.value(4).toString()+'\n'
                    +"每月贷款还款日期："+sql_inquire_loan.value(5).toString()+'\n'
                    +"每月最小还款："+sql_inquire_loan.value(6).toString()+'\n'
                    +"用户ID："+sql_inquire_loan.value(7).toString()+'\n'
                    ;
            ui->information_brower->append(loan_information);
        }

    }
    else if(index == 1){
        QString inquire_ID = ui->inquire_content->toPlainText();
        QSqlQuery sql_inquire_loan;
        sql_inquire_loan.prepare("select * from loans where loans.account_id=?");
        sql_inquire_loan.addBindValue(inquire_ID);
        if(sql_inquire_loan.exec()){
            qDebug() << " 根据ID查询贷款信息成功！！！";
        }
        ui->information_brower->clear();
        while (sql_inquire_loan.next()){
            QString loan_information =
                    "贷款单ID："+sql_inquire_loan.value(0).toString()+'\n'
                    +"贷款时间："+sql_inquire_loan.value(1).toString()+'\n'
                    +"贷款金额（￥）："+sql_inquire_loan.value(2).toString()+'\n'
                    +"贷款周期："+sql_inquire_loan.value(3).toString()+'\n'
                    +"贷款利率："+sql_inquire_loan.value(4).toString()+'\n'
                    +"每月贷款还款日期："+sql_inquire_loan.value(5).toString()+'\n'
                    +"每月最小还款："+sql_inquire_loan.value(6).toString()+'\n'
                    +"用户ID："+sql_inquire_loan.value(7).toString()+'\n'
                    ;
            ui->information_brower->append(loan_information);
        }
    }
}
