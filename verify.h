#ifndef VERIFY_H
#define VERIFY_H

#include <QWidget>

namespace Ui {
class verify;
}

class verify : public QWidget
{
    Q_OBJECT

public:
    explicit verify(QWidget *parent = 0);
    ~verify();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::verify *ui;
};

#endif // VERIFY_H
