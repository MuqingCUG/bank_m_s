#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <QWidget>

namespace Ui {
class creditcard;
}

class creditcard : public QWidget
{
    Q_OBJECT

public:
    explicit creditcard(QWidget *parent = 0);
    ~creditcard();

private slots:
    void on_Button_credit_ok_clicked();

private:
    Ui::creditcard *ui;
};

#endif // CREDITCARD_H
