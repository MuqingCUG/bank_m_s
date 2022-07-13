#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QWidget>

namespace Ui {
class userlogin;
}

class userlogin : public QWidget
{
    Q_OBJECT

public:
    explicit userlogin(QWidget *parent = 0);
    ~userlogin();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::userlogin *ui;
};

#endif // USERLOGIN_H
