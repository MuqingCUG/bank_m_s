#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginscreen.h"
#include "deleteaccount.h"
#include "exactmatchquery.h"
#include "fuzzymatchquery.h"
#include "creditcard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Button_create_acccount_clicked()
{
    loginScreen * login = new loginScreen;
    login->show();
}

void MainWindow::on_Button_delete_account_clicked()
{
    deleteAccount* _delete_w = new deleteAccount;
    _delete_w->show();
}

void MainWindow::on_Button_exact_inquire_clicked()
{
    exactmatchQuery* exact_inquire = new exactmatchQuery;
    exact_inquire->show();
}

void MainWindow::on_Button_fuzzy_inquire_clicked()
{
    fuzzymatchquery* fuzzy_inquire = new fuzzymatchquery;
    fuzzy_inquire->show();
}

void MainWindow::on_Button_creditcard_clicked()
{
    creditcard* w = new creditcard;
    w->show();
}
