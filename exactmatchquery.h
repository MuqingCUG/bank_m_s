#ifndef EXACTMATCHQUERY_H
#define EXACTMATCHQUERY_H

#include <QWidget>

namespace Ui {
class exactmatchQuery;
}

class exactmatchQuery : public QWidget
{
    Q_OBJECT

public:
    explicit exactmatchQuery(QWidget *parent = 0);
    ~exactmatchQuery();

private slots:
    void on_Button_deposit_inquire_clicked();

    void on_deposit_inquire_clicked();

private:
    Ui::exactmatchQuery *ui;
};

#endif // EXACTMATCHQUERY_H
