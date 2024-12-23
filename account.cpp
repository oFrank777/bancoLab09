#include "account.h"  // Se incluye el archivo de encabezado "account.h" para usar la clase Account y sus métodos.

Account::Account(const QString& id, AccountType type, double balance)  // Constructor de la clase Account que inicializa el ID, tipo de cuenta y balance de la cuenta.
    : id(id), type(type), balance(balance) {}  // Inicialización de los atributos de la clase con los valores proporcionados en el constructor.

bool Account::executeTransaction(double amount, TransactionType type) {  // Método para ejecutar una transacción en la cuenta. Recibe el monto y el tipo de transacción.
    bool success = false;  // Variable que indica si la transacción fue exitosa (inicialmente se establece como falsa).
    switch (type) {  // Se verifica el tipo de transacción.
    case TransactionType::DEPOSIT:  // Si es un depósito.
        balance += amount;  // Se incrementa el balance con el monto del depósito.
        success = true;  // La transacción fue exitosa.
        break;
    case TransactionType::WITHDRAWAL:  // Si es un retiro.
        if (balance >= amount) {  // Si hay suficiente saldo en la cuenta.
            balance -= amount;  // Se decrementa el balance con el monto del retiro.
            success = true;  // La transacción fue exitosa.
        }
        break;
    case TransactionType::PERSONAL_LOAN:  // Si es un préstamo personal.
    case TransactionType::NATIONAL_TRANSFER:  // Si es una transferencia nacional.
    case TransactionType::CREDIT_PURCHASE:  // Si es una compra a crédito.
        if (type != TransactionType::CREDIT_PURCHASE || this->type == AccountType::CREDIT) {  // Verifica que la cuenta sea de tipo crédito si la transacción es de compra a crédito.
            balance -= amount;  // Se decrementa el balance con el monto de la transacción.
            success = true;  // La transacción fue exitosa.
        }
        break;
    }

    if (success) {  // Si la transacción fue exitosa.
        transactions.append(Transaction(amount, type, QDateTime::currentDateTime()));  // Se agrega la transacción a la lista de transacciones con el monto, tipo y la fecha/hora actual.
    }
    return success;  // Se devuelve si la transacción fue exitosa o no.
}

QString Account::generateStatement(const QDate& fromDate, const QDate& toDate) {  // Método para generar un estado de cuenta entre dos fechas dadas.
    QString statement = QString("Estado de cuenta - ID: %1\n").arg(id);  // Se inicia el estado de cuenta con el ID de la cuenta.
    statement += QString("Período: %1 - %2\n\n").arg(fromDate.toString("dd/MM/yyyy")).arg(toDate.toString("dd/MM/yyyy"));  // Se agrega el período de tiempo.

    double totalDeposits = 0;  // Variable para almacenar el total de los depósitos.
    double totalWithdrawals = 0;  // Variable para almacenar el total de los retiros.

    for (const Transaction& trans : transactions) {  // Se recorre cada transacción realizada en la cuenta.
        QDateTime transDate = trans.getDateTime();  // Se obtiene la fecha y hora de la transacción.
        if (transDate.date() >= fromDate && transDate.date() <= toDate) {  // Si la transacción está dentro del rango de fechas especificado.
            statement += QString("%1 - %2: $%3\n")  // Se agrega la información de la transacción (fecha, tipo y monto).
                             .arg(transDate.toString("dd/MM/yyyy hh:mm"))
                             .arg(trans.getType() == TransactionType::DEPOSIT ? "Depósito" : "Retiro")
                             .arg(trans.getAmount(), 0, 'f', 2);  // El monto se muestra con dos decimales.

            if (trans.getType() == TransactionType::DEPOSIT) {  // Si la transacción es un depósito.
                totalDeposits += trans.getAmount();  // Se suma al total de depósitos.
            } else {  // Si la transacción es un retiro.
                totalWithdrawals += trans.getAmount();  // Se suma al total de retiros.
            }
        }
    }

    statement += QString("\nResumen:\n");  // Se agrega el resumen de la cuenta.
    statement += QString("Total depósitos: $%1\n").arg(totalDeposits, 0, 'f', 2);  // Se muestra el total de depósitos.
    statement += QString("Total retiros: $%1\n").arg(totalWithdrawals, 0, 'f', 2);  // Se muestra el total de retiros.
    statement += QString("Saldo actual: $%1\n").arg(balance, 0, 'f', 2);  // Se muestra el saldo actual.

    return statement;  // Se retorna el estado de cuenta generado.
}

double Account::getBalance() const {  // Método que retorna el balance actual de la cuenta.
    return balance;  // Se devuelve el valor del balance.
}

AccountType Account::getType() const {  // Método que retorna el tipo de cuenta.
    return type;  // Se devuelve el tipo de cuenta.
}

QString Account::getId() const {  // Método que retorna el ID de la cuenta.
    return id;  // Se devuelve el ID de la cuenta.
}
