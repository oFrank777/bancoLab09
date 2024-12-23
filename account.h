#ifndef ACCOUNT_H  // Se verifica si no se ha definido previamente el archivo de encabezado "ACCOUNT_H".
#define ACCOUNT_H  // Se define "ACCOUNT_H" para evitar la inclusión múltiple del archivo de encabezado.

#include <QString>  // Se incluye la clase QString de Qt para manejar cadenas de texto.
#include <QList>    // Se incluye la clase QList de Qt para manejar listas (colecciones de objetos).
#include "transaction.h"  // Se incluye el archivo de encabezado "transaction.h" que probablemente contiene la definición de la clase Transaction.

enum class AccountType {  // Se define un tipo de enumeración para los diferentes tipos de cuentas.
    SAVINGS,  // Tipo de cuenta de ahorros.
    YOUTH,    // Tipo de cuenta juvenil.
    PLUS,     // Tipo de cuenta Plus.
    BUSINESS, // Tipo de cuenta de negocios.
    CREDIT,   // Tipo de cuenta de crédito.
    ALL       // Tipo que engloba todos los tipos de cuenta.
};

class Account {  // Se define la clase Account que representa una cuenta bancaria.
public:
    Account(const QString& id, AccountType type, double balance = 0.0);  // Constructor de la clase, toma el ID de la cuenta, el tipo de cuenta y un balance opcional (0.0 por defecto).
    bool executeTransaction(double amount, TransactionType type);  // Método que ejecuta una transacción en la cuenta. Devuelve true si la transacción fue exitosa.
    QString generateStatement(const QDate& fromDate, const QDate& toDate);  // Método que genera un estado de cuenta para un rango de fechas específico.
    double getBalance() const;  // Método que retorna el balance actual de la cuenta.
    AccountType getType() const;  // Método que retorna el tipo de cuenta.
    QString getId() const;  // Método que retorna el ID de la cuenta.

private:
    QString id;  // Atributo que guarda el ID de la cuenta.
    AccountType type;  // Atributo que guarda el tipo de cuenta (de tipo enumerado AccountType).
    double balance;  // Atributo que guarda el balance de la cuenta.
    QList<Transaction> transactions;  // Atributo que guarda una lista de transacciones realizadas en la cuenta (de tipo Transaction, que probablemente esté definido en el archivo "transaction.h").
};

#endif  // Fin de la declaración del encabezado "ACCOUNT_H"
