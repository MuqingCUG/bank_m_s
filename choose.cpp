#include "choose.h"
#include "ui_choose.h"
//#include "mainwindow.h"
#include "verify.h"
#include "userlogin.h"

Choose::Choose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
}

Choose::~Choose()
{
    delete ui;
}

void Choose::on_administer_clicked()
{
    verify* login = new verify;
    login->show();
}

void Choose::on_client_clicked()
{
    userlogin* acc_login = new userlogin;
    acc_login->show();
}
