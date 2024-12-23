#ifndef TRANSACTION_H  // Se verifica si no se ha definido previamente el archivo de encabezado "TRANSACTION_H".
#define TRANSACTION_H  // Se define "TRANSACTION_H" para evitar la inclusión múltiple del archivo de encabezado.

#include <QDateTime>  // Se incluye la clase QDateTime de Qt, que se utiliza para manejar fechas y horas.

enum class TransactionType {  // Se define un tipo de enumeración para los diferentes tipos de transacciones.
    DEPOSIT,        // Depósito de dinero en la cuenta.
    WITHDRAWAL,     // Retiro de dinero de la cuenta.
    PERSONAL_LOAN,  // Préstamo personal.
    NATIONAL_TRANSFER,  // Transferencia nacional entre cuentas.
    CREDIT_PURCHASE  // Compra a crédito utilizando la cuenta.
};

class Transaction {  // Se define la clase Transaction, que representa una transacción realizada en una cuenta.
public:
    Transaction(double amount, TransactionType type, const QDateTime& dateTime);  // Constructor de la clase Transaction, que toma el monto, el tipo y la fecha/hora de la transacción.
    double getAmount() const;  // Método que retorna el monto de la transacción.
    TransactionType getType() const;  // Método que retorna el tipo de la transacción.
    QDateTime getDateTime() const;  // Método que retorna la fecha y hora en que ocurrió la transacción.

private:
    double amount;  // Atributo que guarda el monto de la transacción.
    TransactionType type;  // Atributo que guarda el tipo de transacción (de tipo enumerado TransactionType).
    QDateTime dateTime;  // Atributo que guarda la fecha y hora en que se realizó la transacción.
};

#endif  // Fin de la declaración del encabezado "TRANSACTION_H".
