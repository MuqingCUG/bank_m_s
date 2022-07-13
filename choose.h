#ifndef CHOOSE_H
#define CHOOSE_H

#include <QMainWindow>

namespace Ui {
class Choose;
}

class Choose : public QMainWindow
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = 0);
    ~Choose();

private slots:
    void on_administer_clicked();

    void on_client_clicked();

private:
    Ui::Choose *ui;
};

#endif // CHOOSE_H
