#include "verify.h"
#include "ui_verify.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"
#include <QVector>
#include <QCryptographicHash>
verify::verify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::verify)
{
    ui->setupUi(this);
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);  //隐藏密码
}

verify::~verify()
{
    delete ui;
}

void verify::on_pushButton_2_clicked()
{
    this->close();
}

void verify::on_pushButton_clicked()
{
    QString  str1 = ui->text_cardnumber->toPlainText();
    std::string ID = str1.toStdString();

//    QString  str2 = ui->text_Passwd->toPlainText();
//    std::string passwd = str2.toStdString();
    QString  str_passwd = ui->lineEdit_passwd->text();//ui->text_Passwd->toPlainText();

    //MD5 加密密码存储到数据库
    QString md5_passwd;
    md5_passwd = QString("%1").arg(QString(QCryptographicHash::hash(ui->lineEdit_passwd->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    qDebug() << "密码的md5值："<< md5_passwd;

    QSqlQuery q("select * from administrators");
    QSqlRecord rec = q.record();

    QString sqlname, sqlpassword;        //存储查询得到的密码
    QVector<QString> sqlname_data;
    QVector<QString> sqlpassword_data;
    int nameCol = rec.indexOf("name"); // index of the field "name"
    int passCol = rec.indexOf("password");
    while (q.next()){
        // qDebug() << q.value(nameCol).toString(); // output all names
        //q.next();
        sqlname = q.value(nameCol).toString();
        sqlpassword = q.value(passCol).toString();
        sqlname_data.append(sqlname);
        sqlpassword_data.append(sqlpassword);
    }
    if(sqlname_data.contains(str1)){
        //int passCol = rec.indexOf("password");
        int index = sqlname_data.indexOf(str1);
        sqlpassword = sqlpassword_data[index];
        //break;
        if(sqlpassword == md5_passwd){//比对MD5值
            ui->text_cardnumber->clear();
            ui->lineEdit_passwd->clear();
            MainWindow *afterlogin = new MainWindow;
            afterlogin->show();
        }
        else{
            QMessageBox::warning(this,"warning","密码错误！！！");
        }
    }
    else
    {
    QMessageBox::warning(this,"warning","此用户不存在！！！");
    }

}
