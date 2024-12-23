// account.h
#ifndef CUENTA_H
#define CUENTA_H

#include <QString>
#include <QList>
#include "transaction.h"

enum class AccountType {
    SAVINGS,
    YOUTH,
    PLUS,
    BUSINESS,
    CREDIT,
    ALL
};

class Account {
public:
    Account(const QString& id, AccountType type, double balance = 0.0);
    bool executeTransaction(double amount, TransactionType type);
    QString generateStatement(const QDate& fromDate, const QDate& toDate);
    double getBalance() const;
    AccountType getType() const;
    QString getId() const;

private:
    QString id;
    AccountType type;
    double balance;
    QList<Transaction> transactions;
};

#endif
