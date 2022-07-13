#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>

class account
{
public:
    account();
    account(QString id):_ID(id){}
    QString get_ID();
private:
    QString _ID;
};

#endif // ACCOUNT_H
