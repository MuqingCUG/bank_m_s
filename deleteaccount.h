#ifndef DELETEACCOUNT_H
#define DELETEACCOUNT_H

#include <QWidget>

namespace Ui {
class deleteAccount;
}

class deleteAccount : public QWidget
{
    Q_OBJECT

public:
    explicit deleteAccount(QWidget *parent = 0);
    ~deleteAccount();

private slots:
    void on_pushButton_clicked();

    void on_close_delete_windows_clicked();

private:
    Ui::deleteAccount *ui;
};

#endif // DELETEACCOUNT_H
