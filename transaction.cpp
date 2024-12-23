#include "transaction.h"  // Se incluye el archivo de encabezado "transaction.h" para usar la clase Transaction.

Transaction::Transaction(double amount, TransactionType type, const QDateTime& dateTime)  // Constructor de la clase Transaction.
    : amount(amount), type(type), dateTime(dateTime) {}  // Inicialización de los miembros de la clase con los valores recibidos.

double Transaction::getAmount() const {  // Método para obtener el monto de la transacción.
    return amount;  // Devuelve el monto de la transacción.
}

TransactionType Transaction::getType() const {  // Método para obtener el tipo de transacción.
    return type;  // Devuelve el tipo de transacción.
}

QDateTime Transaction::getDateTime() const {  // Método para obtener la fecha y hora de la transacción.
    return dateTime;  // Devuelve la fecha y hora de la transacción.
}
