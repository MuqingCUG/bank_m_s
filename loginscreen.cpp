#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <QSqlQuery>
#include <QDebug>
#include <QCryptographicHash>
loginScreen::loginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginScreen)
{
    ui->setupUi(this);
}

loginScreen::~loginScreen()
{
    delete ui;
}


void loginScreen::on_quit_clicked()
{
    this->close();
}

void loginScreen::on_save_clicked()
{
    /*customer_id VARCHAR(20)  NOT NULL,
    name VARCHAR ( 50 ) NOT NULL,
    birth_date VARCHAR ( 12 ) NOT NULL,
    address VARCHAR ( 30 ) NOT NULL,
    phone_number VARCHAR(20) NOT NULL,
    branch_name VARCHAR ( 20 ) NOT NULL, --银行
    card_type VARCHAR ( 10 ) NOT NULL,		--银行卡类型，开户时选择*/
    QSqlQuery query;
    query.prepare("INSERT INTO customer (customer_id, name, birth_date,address,phone_number,branch_name,card_type) "
                  "VALUES (:id, :name, :date,:address,:phone_number,:branch_name,:card_type)");

    customer_In.push_back( ui->customer_ID->toPlainText());
    customer_In.push_back(ui->customer_name->toPlainText());

    QDate date = ui->brith_date->date();
    QString str_birth_date = date.toString("yyyy-MM-dd");
    customer_In.push_back(str_birth_date);

    customer_In.push_back(ui->address->toPlainText());
    customer_In.push_back(ui->phone_number->toPlainText());
    customer_In.push_back(ui->branch_name->currentText());  //下拉框选择

    customer_In.push_back(ui->card_type->toPlainText());

    query.bindValue(0, customer_In[0]);
    query.bindValue(1, customer_In[1]);
    query.bindValue(2, customer_In[2]);
    query.bindValue(3, customer_In[3]);
    query.bindValue(4, customer_In[4]);
    query.bindValue(5, customer_In[5]);
    query.bindValue(6, customer_In[6]);

    QSqlQuery query2;
    query2.prepare("INSERT INTO accounts (ID, balance, password) "
                  "VALUES (:id, :balance, :password)");
    QString str_balance = ui->balance->toPlainText();
    int _balance = str_balance.toInt();
    query2.bindValue(0, customer_In[0]);
    query2.bindValue(1, _balance);

    //存储 md5 加密后的密码
    //lineEdit_passwd
    QString md5_passwd;
    md5_passwd = QString("%1").arg(QString(QCryptographicHash::hash(ui->lineEdit_passwd->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    qDebug() << "密码的md5值："<< md5_passwd;
    query2.bindValue(2, md5_passwd);

    bool flag = query.exec();
    bool flag1 = query2.exec();
    if(flag&&flag1){
        qDebug()<<"sql query success!!!";
        this->close();
    }
}

//void loginScreen::on_customer_ID_textChanged()
//{
//    QString str_id = ui->customer_ID->toPlainText();
//    customer_In.push_back(str_id);
//}

//void loginScreen::on_customer_name_textChanged()
//{
//    QString str_name = ui->customer_name->toPlainText();
//    customer_In.push_back(str_name);
//}

//void loginScreen::on_brith_date_dateChanged(const QDate &date)
//{
//    QString str_birth_date = date.toString();
//    customer_In.push_back(str_birth_date);
//}

//void loginScreen::on_address_textChanged()
//{
//    QString str = ui->address->toPlainText();
//    customer_In.push_back(str);
//}

//void loginScreen::on_phone_number_textChanged()
//{
//    QString str = ui->phone_number->toPlainText();
//    customer_In.push_back(str);
//}

//void loginScreen::on_branch_code_currentTextChanged(const QString &arg1)
//{
//    QString str = ui->branch_code->currentText();
//    customer_In.push_back(str);
//}
