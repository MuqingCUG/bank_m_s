#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Button_create_acccount_clicked();

    void on_Button_delete_account_clicked();

    void on_Button_exact_inquire_clicked();

    void on_Button_fuzzy_inquire_clicked();

    void on_Button_creditcard_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
