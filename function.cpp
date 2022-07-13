#include "function.h"
#include "ui_function.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QDateTime>

function::function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::function)
{
    ui->setupUi(this);
}

function::~function()
{
    delete ui;
}

void function::set_account(account& user){
    _my_account = user;
}

void function::on_check_balance_clicked()
{
    ui->stackedWindows->setCurrentIndex(0);
}

void function::on_deposit_Button_clicked()
{
    ui->stackedWindows->setCurrentIndex(1);
}

void function::on_withdraw_Button_clicked()
{
    ui->stackedWindows->setCurrentIndex(2);
}

//查询当前余额按钮
void function::on_brower_clicked()
{
    QString myID =  _my_account.get_ID();
    QSqlQuery query;
    query.prepare("select  balance from accounts where ID = ? ");
    query.addBindValue(myID);
    //boundValue(const QString &placeholder)
    if(query.exec())//如果成功执行则返回1，未执行则为零
    {
        //            QString result = query.value(0).toString();
        //            qDebug()<<result;
        qDebug()<<"inquire success!!!";
    }
    //query.exec();
    QString result;
    while(query.next()){
        result = query.value(0).toString();
        qDebug()<<result;
    }

    QDateTime time = QDateTime::currentDateTime();
    QString u_time =  time.toString("yyyy-MM-dd ddd hh:mm");
    QString _look_record = u_time + "   当前余额：   "+result + "￥";
    ui->moneyBrowser->clear();
    ui->moneyBrowser->append(_look_record);
}

//存款按钮
void function::on_pushButton_clicked()
{
    QString  str = ui->text_Deposit->toPlainText();
    int saveMoney = str.toInt();

    QString myID =  _my_account.get_ID();
    QSqlQuery query1;
    query1.prepare("select  balance from accounts where ID = ? ");
    query1.addBindValue(myID);
    int result;
    query1.exec();
    while(query1.next()){
        result = query1.value(0).toInt();
        qDebug()<<"当前余额"<<result;
    }

    QSqlQuery query;
    query.prepare("UPDATE accounts set balance=? where ID=?; ");
    query.addBindValue(saveMoney+result);
    query.addBindValue(myID);
    if(query.exec()){
        qDebug()<<"update success!!!";
        ui->text_Deposit->clear();
        QMessageBox::warning(this,"information","存款成功！！！");
    }

    //存储存款信息
    /*		deposit_ID VARCHAR(20)  NOT NULL,		--存款单ID
    deposit_date VARCHAR ( 12 ) NOT NULL,	--存款日期
    deposit_money int  NOT NULL,	--存款金额
    account_ID VARCHAR(20)  NOT NULL,	--账户 ID
*/
    QSqlQuery deposit_query;
    deposit_query.prepare("INSERT INTO deposit_information (deposit_ID, deposit_date, deposit_money,account_ID) "
                          "VALUES (:deposit_ID, :deposit_date, :deposit_money,:account_ID)");
    QDateTime date = QDateTime::currentDateTime();
    QString str_date = date.toString("yyyyMMddhhmmss");
    QString deposit_information_id = "deposit-"+myID+"-"+str_date;
    QString mystr_date = date.toString("yyyy-MM-dd hh:mm:ss");
    deposit_query.bindValue(0, deposit_information_id);
    deposit_query.bindValue(1, mystr_date);
    deposit_query.bindValue(2, saveMoney);
    deposit_query.bindValue(3, myID);
    if(deposit_query.exec())
        qDebug()<< "存储存款信息成功！！！";
}

//取款按钮
void function::on_pushButton_2_clicked()
{
    QString  str = ui->text_Draw->toPlainText();
    int drawMoney = str.toInt();

    QString myID =  _my_account.get_ID();
    QSqlQuery query1;
    query1.prepare("select  balance from accounts where ID = ? ");
    query1.addBindValue(myID);
    int result;
    query1.exec();
    while(query1.next()){
        result = query1.value(0).toInt();
        qDebug()<<"当前余额"<<result;
    }

    QSqlQuery query;
    query.prepare("UPDATE accounts set balance=? where ID=?; ");
    query.addBindValue(result-drawMoney);
    query.addBindValue(myID);
    if(query.exec()){
        qDebug()<<"update success!!!";
        ui->text_Draw->clear();
        QMessageBox::warning(this,"information","取款成功！！！");
    }

    //存储取款信息
    QSqlQuery draw_query;
    draw_query.prepare("INSERT INTO draw_information (draw_ID, draw_date, draw_money,account_ID) "
                       "VALUES (:draw_ID, :draw_date, :draw_money,:account_ID)");
    QDateTime date = QDateTime::currentDateTime();
    QString str_date = date.toString("yyyyMMddhhmmss");
    QString draw_information_id = "draw-"+myID+"-"+str_date;
    QString mystr_date = date.toString("yyyy-MM-dd hh:mm:ss");
    draw_query.bindValue(0, draw_information_id);
    draw_query.bindValue(1, mystr_date);
    draw_query.bindValue(2, drawMoney);
    draw_query.bindValue(3, myID);
    if(draw_query.exec())
        qDebug()<< "存储存款信息成功！！！";
}

void function::on_transfer_Button_clicked()
{
    ui->stackedWindows->setCurrentIndex(3);
}


//转帐按钮
void function::on_transfer_ok_clicked()
{
    QString  str = ui->text_Money->toPlainText();
    int transfer_Money = str.toInt();       //转账金额
    QString  transfer_ID = ui->text_cardnumber->toPlainText();      //收方ID
    QString myID =  _my_account.get_ID();       //转方 ID
    QString my_card_type;       //自己卡的类型
    QString transfer_card_type;         //对方卡的类型
    QSqlQuery query1;
    query1.prepare("select  balance,card_type from accounts,customer where ID = ?  and accounts.ID=customer.customer_id");
    query1.addBindValue(myID);
    int my_cur_balance;        //当前余额
    int transfer_cur_balance;
    query1.exec();
    while(query1.next()){
        my_cur_balance = query1.value(0).toInt();
        my_card_type = query1.value(1).toString();
        qDebug()<<"当前余额"<<my_cur_balance << "转方卡类型："     << my_card_type;
    }
    if(my_cur_balance<transfer_Money){
        QMessageBox::warning(this,"warning","您的余额少于转账金额！！！");

        //TO-DO
        //考虑透支情况
    }
    else{
        //  得到
        QSqlQuery query2;
        query2.prepare("select  balance,card_type from accounts,customer where ID = ?  and accounts.ID=customer.customer_id");
        query2.addBindValue(transfer_ID);
        query2.exec();
        while(query2.next()){
            transfer_cur_balance = query2.value(0).toInt();
            transfer_card_type = query2.value(1).toString();
            qDebug()<<"当前余额"<<transfer_cur_balance   << "收方卡类型："     << transfer_card_type;
        }

        //当my和transfer 卡的类型相同时，同类型的卡号则转帐费用按2%提取
        if(my_card_type==transfer_card_type){
            QSqlQuery query;
            query.prepare("UPDATE accounts set balance=? where ID=?; ");
            query.addBindValue(my_cur_balance-transfer_Money-transfer_Money*0.02);
            query.addBindValue(myID);
            if(query.exec()){
                qDebug()<<"转方   update success!!!";
            }
            QSqlQuery query3;
            query3.prepare("UPDATE accounts set balance=? where ID=?; ");
            query3.addBindValue(transfer_cur_balance+transfer_Money);
            query3.addBindValue(transfer_ID);
            if(query3.exec()){
                qDebug()<<"收方   update success!!!";
                ui->text_cardnumber->clear();
                ui->text_Money->clear();
                QMessageBox::warning(this,"information","转账成功！！！");

                //To-do
                //打印转账单
            }
        }
        //不同类型的卡号则转帐费用按5%提取
        else{
            QSqlQuery query;
            query.prepare("UPDATE accounts set balance=? where ID=?; ");
            query.addBindValue(my_cur_balance-transfer_Money-transfer_Money*0.05);
            query.addBindValue(myID);
            if(query.exec()){
                qDebug()<<"转方   update success!!!";
            }
            QSqlQuery query3;
            query3.prepare("UPDATE accounts set balance=? where ID=?; ");
            query3.addBindValue(transfer_cur_balance+transfer_Money);
            query3.addBindValue(transfer_ID);
            if(query3.exec()){
                qDebug()<<"收方   update success!!!";
                ui->text_cardnumber->clear();
                ui->text_Money->clear();
                QMessageBox::warning(this,"information","转账成功！！！");

                //To-do
                //打印转账单

            }
        }
        /* transfer_information_ID VARCHAR(30)  NOT NULL,		--转账日期+ID
         transfer_date VARCHAR ( 30 ) NOT NULL,
         transfer_money int  NOT NULL,	--转账金额
         my_ID	VARCHAR(20)  NOT NULL,		--转方卡号
         transfer_ID VARCHAR(20)  NOT NULL ,--check(transfer_ID != my_ID),		--收方卡号*/

        //存储转账信息
        QSqlQuery transfer_query;
        transfer_query.prepare("INSERT INTO transfer_information (transfer_information_ID, transfer_date, transfer_money,my_ID,transfer_ID) "
                               "VALUES (:transfer_information_ID, :transfer_date, :transfer_money,:my_ID,:transfer_ID)");
        QDateTime date = QDateTime::currentDateTime();
        QString str_date = date.toString("yyyyMMddhhmmss");
        QString transfer_information_ID = "transfer-"+myID+transfer_ID+"-"+str_date;
        QString mystr_date = date.toString("yyyy-MM-dd hh:mm:ss");
        transfer_query.bindValue(0, transfer_information_ID);
        transfer_query.bindValue(1, mystr_date);
        transfer_query.bindValue(2, transfer_Money);
        transfer_query.bindValue(3, myID);
        transfer_query.bindValue(4, transfer_ID);
        if(transfer_query.exec())
            qDebug()<< "存储转账信息成功！！！";
    }
}

void function::on_loan_Button_clicked()
{
    ui->stackedWindows->setCurrentIndex(4);
}

void function::on_repayment_Button_clicked()
{
    ui->stackedWindows->setCurrentIndex(5);
}

void function::on_loan_OK_clicked()
{/*
    loan_ID VARCHAR(50)  NOT NULL,
    loan_date VARCHAR ( 30 ) NOT NULL,
    loan_amount int  NOT NULL CHECK ( loan_amount >= 1000.00 AND loan_amount < 99999.00 ),
    --loan_type VARCHAR ( 30 ) NOT NULL,
    loan_duration_months int  NOT NULL,
    interest_rate int  NOT NULL CHECK ( interest_rate > 00.00 AND interest_rate < 50.00 ),		--双方谈判
    monthly_payment_due_date int  NOT NULL CHECK ( monthly_payment_due_date >= 01 AND monthly_payment_due_date <= 31 ),
    monthly_minimum_payment int  NOT NULL,
    --payment_method VARCHAR ( 20 ) NOT NULL,
    account_id VARCHAR(20)  NOT NULL,*/
    QSqlQuery query;
    query.prepare("INSERT INTO loans (loan_ID, loan_date,loan_amount, loan_duration_months,interest_rate,monthly_payment_due_date,monthly_minimum_payment,account_id) "
                  "VALUES (:loan_ID,:loan_date, :loan_amount, :loan_duration_months,:interest_rate,:monthly_payment_due_date,:monthly_minimum_payment,:account_id)");

    QString myID =  _my_account.get_ID();       //贷款方 ID
    QDateTime date = QDateTime::currentDateTime();
    QString str_date = date.toString("yyyyMMddhhmmss");
    QString loan_information_ID = "loan-"+myID+"-"+str_date;
    QString mystr_date = date.toString("yyyy-MM-dd hh:mm:ss");
    query.bindValue(0, loan_information_ID);
    query.bindValue(1, mystr_date);
    query.bindValue(2, (ui->loan_amount->toPlainText()).toInt());   //贷款额
    query.bindValue(3, (ui->loan_duration_months->toPlainText()).toInt());
    query.bindValue(4, (ui->loan_interst->toPlainText()).toInt());
    query.bindValue(5, (ui->loan_month_due_date->toPlainText()).toInt());
    query.bindValue(6, (ui->loan_min_payment->toPlainText()).toInt());
    query.bindValue(7, myID);

    QSqlQuery query1;
    query1.prepare("select  balance from accounts where ID = ? ");
    query1.addBindValue(myID);
    int result;
    query1.exec();
    while(query1.next()){
        result = query1.value(0).toInt();
        qDebug()<<"当前余额"<<result;
    }
    int loan_money = (ui->loan_amount->toPlainText()).toInt();
    QSqlQuery query2;
    query2.prepare("UPDATE accounts set balance=? where ID=?; ");
    query2.addBindValue(loan_money+result);
    query2.addBindValue(myID);
    if(query.exec()&&query2.exec()){
        //qDebug()<<"update success!!!";
        QMessageBox::warning(this,"information","贷款成功！！！");
    }

}

void function::on_button_payback_loan_clicked()
{
    QString str_payback_money = ui->loan_back_money->toPlainText();
    int payback_money = str_payback_money.toInt();

    QString myID =  _my_account.get_ID();
    QSqlQuery query;
    query.prepare("select loan_amount  from loans where account_id = ? ");
    query.addBindValue(myID);

    if(query.exec())//如果成功执行则返回1，未执行则为零
    {
        qDebug()<<"inquire success!!!";
    }
    //query.exec();
    int cur_loan;
    while(query.next()){
        cur_loan = query.value(0).toInt();
        //qDebug()<<result;
    }
    //int cur_loan = str_cur_loan.toInt();      //当前贷款
    QSqlQuery query2;
    query2.prepare("UPDATE loans set loan_amount=? where account_id=?; ");
    query2.addBindValue(cur_loan - payback_money);
    query2.addBindValue(myID);
    if(query2.exec()){
        //qDebug()<<"update success!!!";
        QMessageBox::warning(this,"information","还款成功！！！");
    }

    QSqlQuery query1;
    query1.prepare("select  balance from accounts where ID = ? ");
    query1.addBindValue(myID);
    int cur_balance;
    query1.exec();
    while(query1.next()){
        cur_balance = query1.value(0).toInt();
        qDebug()<<"当前余额"<<cur_balance;
    }
    QSqlQuery query3;
    query3.prepare("UPDATE accounts set balance=? where ID=?; ");
    query3.addBindValue(cur_balance-payback_money);
    query3.addBindValue(myID);
    query3.exec();
    //    QDateTime time = QDateTime::currentDateTime();
    //    QString u_time =  time.toString("yyyy-MM-dd ddd hh:mm");
    //    QString _look_record = u_time + "   当前贷款：   "+result + "￥";
    //    ui->cur_loan_brower->clear();
    //    ui->cur_loan_brower->append(_look_record);

}

void function::on_button_look_cur_loan_clicked()
{
    QString myID =  _my_account.get_ID();
    QSqlQuery query;
    query.prepare("select loan_amount  from loans where account_id = ? ");
    query.addBindValue(myID);

    if(query.exec())//如果成功执行则返回1，未执行则为零
    {
        qDebug()<<"loan inquire success!!!";
    }
    //query.exec();
    QString result;
    while(query.next()){
        result = query.value(0).toString();
        qDebug()<<result;
    }

    QDateTime time = QDateTime::currentDateTime();
    QString u_time =  time.toString("yyyy-MM-dd ddd hh:mm");
    QString _look_record = u_time + "   当前贷款：   "+result + "￥";
    ui->cur_loan_brower->clear();
    ui->cur_loan_brower->append(_look_record);
}
