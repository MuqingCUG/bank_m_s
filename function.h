#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>
#include "account.h"

namespace Ui {
class function;
}

class function : public QWidget
{
    Q_OBJECT

public:
    explicit function(QWidget *parent = 0);
    ~function();

public:
    void set_account(account&);

private slots:
    void on_check_balance_clicked();

    void on_deposit_Button_clicked();

    void on_withdraw_Button_clicked();

    void on_brower_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_transfer_Button_clicked();

    void on_transfer_ok_clicked();

    void on_loan_Button_clicked();

    void on_repayment_Button_clicked();

    void on_loan_OK_clicked();

    void on_button_payback_loan_clicked();

    void on_button_look_cur_loan_clicked();

private:
    Ui::function *ui;
    account _my_account;
};

#endif // FUNCTION_H
