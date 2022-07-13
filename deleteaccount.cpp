#include "deleteaccount.h"
#include "ui_deleteaccount.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QCryptographicHash>

deleteAccount::deleteAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deleteAccount)
{
    ui->setupUi(this);
}

deleteAccount::~deleteAccount()
{
    delete ui;
}

void deleteAccount::on_pushButton_clicked()
{
    QString  card_ID = ui->text_cardnumber->toPlainText();
    QString  str_card_passwd = ui->text_Passwd->toPlainText();
    QString  str_card_passwd2 = ui->text_Passwd_2->toPlainText();
    QString card_passwd;
    card_passwd = QString("%1").arg(QString(QCryptographicHash::hash(str_card_passwd.toUtf8(),QCryptographicHash::Md5).toHex()));
    qDebug() << "密码的md5值："<< card_passwd;

    QString  card_passwd2 ;
    card_passwd2 = QString("%1").arg(QString(QCryptographicHash::hash(str_card_passwd2.toUtf8(),QCryptographicHash::Md5).toHex()));
    //qDebug() << "密码的md5值："<< card_passwd2;
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

        if(sqlcard_password == card_passwd){
            if(card_passwd!=card_passwd2)
            {
                QMessageBox::warning(this,"warning","两次输入的密码不一致！！！");
            }
            else{
                QSqlQuery query;
                query.prepare("delete from accounts where ID = ? ");
                query.addBindValue(card_ID);
                QSqlQuery query1;
                query1.prepare("delete from customer where customer_id = ? "/*+card_ID*/);
                query1.addBindValue(card_ID);
                if(query.exec()&&query1.exec())//如果成功执行则返回1，未执行则为零
                    qDebug()<<"delete success!!!";
                QMessageBox::warning(this,"warning","销户成功！！！");
                this->close();
            }
        }
        else{
            QMessageBox::warning(this,"warning","密码错误！！！");
        }
    }
    else
    {
        QMessageBox::warning(this,"warning","此卡号不存在！！！");
    }

//    if(card_passwd!=card_passwd2)
//    {
//        QMessageBox::warning(this,"warning","两次输入的密码不一致！！！");
//    }

//    QMessageBox::warning(this,"warning","销户成功！！！");
//    this->close();
}


void deleteAccount::on_close_delete_windows_clicked()
{
    this->close();  //关闭销户窗口
}
