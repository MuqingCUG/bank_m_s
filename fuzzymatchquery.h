#ifndef FUZZYMATCHQUERY_H
#define FUZZYMATCHQUERY_H

#include <QWidget>

namespace Ui {
class fuzzymatchquery;
}

class fuzzymatchquery : public QWidget
{
    Q_OBJECT

public:
    explicit fuzzymatchquery(QWidget *parent = 0);
    ~fuzzymatchquery();

private slots:
    void on_pushButton_clicked();

private:
    Ui::fuzzymatchquery *ui;
};

#endif // FUZZYMATCHQUERY_H
