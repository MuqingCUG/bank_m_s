#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QVector>
namespace Ui {
class loginScreen;
}

class loginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit loginScreen(QWidget *parent = 0);
    ~loginScreen();

private slots:
    void on_quit_clicked();

    void on_save_clicked();

//    void on_customer_ID_textChanged();

//    void on_customer_name_textChanged();

//    void on_brith_date_dateChanged(const QDate &date);

//    void on_address_textChanged();

//    void on_phone_number_textChanged();

//    void on_branch_code_currentTextChanged(const QString &arg1);

private:
    Ui::loginScreen *ui;
    QVector<QString> customer_In;
};

#endif // LOGINSCREEN_H
