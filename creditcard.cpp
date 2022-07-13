#include "creditcard.h"
#include "ui_creditcard.h"
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDebug>
creditcard::creditcard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::creditcard)
{
    ui->setupUi(this);
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);  //隐藏密码
}

creditcard::~creditcard()
{
    delete ui;
}

void creditcard::on_Button_credit_ok_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO credit_cards (credit_card_number, credit_limit, account_id,credit_password,amount_spent) "
                  "VALUES (:credit_card_number, :credit_limit, :account_id,:credit_password,:amount_spent)");

    QString md5_passwd;
    md5_passwd = QString("%1").arg(QString(QCryptographicHash::hash(ui->lineEdit_passwd->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    qDebug() << "密码的md5值："<< md5_passwd;

    query.bindValue(0, ui->creditcard_ID->toPlainText());
    query.bindValue(1, ui->credit_balance->toPlainText());
    query.bindValue(2, ui->account_ID->toPlainText());
    query.bindValue(3, md5_passwd);

    if(query.exec()){
        qDebug()<<"信用卡创建成功！！！";
    }
}
