#include "userlogin.h"
#include "ui_userlogin.h"
#include"function.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include "account.h"
#include <QCryptographicHash>

userlogin::userlogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userlogin)
{
    ui->setupUi(this);
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);  //隐藏密码
}

userlogin::~userlogin()
{
    delete ui;
}

void userlogin::on_pushButton_ok_clicked()
{
    QString  card_ID = ui->text_cardnumber->toPlainText();
    QString  card_passwd = ui->lineEdit_passwd->text();//ui->text_Passwd->toPlainText();

    //MD5 加密密码存储到数据库
    QString md5_passwd;
    md5_passwd = QString("%1").arg(QString(QCryptographicHash::hash(ui->lineEdit_passwd->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    qDebug() << "密码的md5值："<< md5_passwd;

    QSqlQuery q("select * from accounts");
    QSqlRecord rec = q.record();

    QString sqlcard_ID, sqlcard_password;        //存储查询得到的密码
    QVector<QString> sqlcardID_data;
    QVector<QString> sqlcardpassword_data;
    int nameCol = rec.indexOf("ID"); // index of the field "name"
    int passCol = rec.indexOf("password");
    while (q.next()){
        sqlcard_ID = q.value(nameCol).toString();
        sqlcard_password = q.value(passCol).toString();
        sqlcardID_data.append(sqlcard_ID);
        sqlcardpassword_data.append(sqlcard_password);
    }

    if(sqlcardID_data.contains(card_ID)){
        int index = sqlcardID_data.indexOf(card_ID);
        sqlcard_password = sqlcardpassword_data[index];
        if(sqlcard_password == md5_passwd){     //比对 MD5 值
            account _acc_user(card_ID);
            ui->text_cardnumber->clear();
            ui->lineEdit_passwd->clear();
            function *account_login = new function;
            account_login->set_account(_acc_user);
            account_login->show();
        }
        else{
            QMessageBox::warning(this,"warning","密码错误！！！");
        }
    }
    else
    {
    QMessageBox::warning(this,"warning","此卡号不存在！！！");
    }
}
