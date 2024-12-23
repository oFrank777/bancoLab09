#ifndef ACCOUNTMANAGER_H  // Se verifica si no se ha definido previamente el archivo de encabezado "ACCOUNTMANAGER_H".
#define ACCOUNTMANAGER_H  // Se define "ACCOUNTMANAGER_H" para evitar la inclusión múltiple del archivo de encabezado.

#include <QObject>   // Se incluye la clase QObject de Qt, que es la clase base para todos los objetos que requieren capacidades de señal y ranura.
#include <QMap>      // Se incluye la clase QMap de Qt para manejar mapas (asociaciones clave-valor).
#include "account.h" // Se incluye el archivo de encabezado "account.h", que probablemente contiene la definición de la clase Account.
#include "client.h"  // Se incluye el archivo de encabezado "client.h", que probablemente contiene la definición de la clase Client.

class AccountManager : public QObject {  // Se define la clase AccountManager, que hereda de QObject para usar las señales y ranuras de Qt.
    Q_OBJECT  // Macro de Qt que permite la gestión de señales y ranuras en la clase.

public:
    static AccountManager* getInstance();  // Método estático para obtener la única instancia de la clase AccountManager (patrón Singleton).
    void createAccount(const QString& clientId, AccountType type);  // Método para crear una cuenta asociada a un cliente con un tipo específico.
    QList<Account*> getClientAccounts(const QString& clientId);  // Método que devuelve una lista de las cuentas asociadas a un cliente dado su ID.
    bool executeTransaction(const QString& accountId, double amount, TransactionType type);  // Método para ejecutar una transacción en una cuenta especificada.
    QString generateStatement(const QString& clientId, const QDate& fromDate, const QDate& toDate, AccountType type = AccountType::ALL);  // Método para generar un estado de cuenta de un cliente para un rango de fechas y tipo de cuenta (por defecto, todos los tipos).

private:
    AccountManager(QObject *parent = nullptr);  // Constructor privado para evitar la creación directa de instancias (usando el patrón Singleton).
    static AccountManager* instance;  // Atributo estático que guarda la única instancia de la clase AccountManager.
    QMap<QString, Client*> clients;  // Mapa que asocia el ID de un cliente con un puntero a su objeto Client.
    QMap<QString, Account*> accounts;  // Mapa que asocia el ID de una cuenta con un puntero a su objeto Account.

    double calculateInterest(AccountType type, TransactionType transType);  // Método privado para calcular el interés basado en el tipo de cuenta y tipo de transacción.
};

#endif  // Fin de la declaración del encabezado "ACCOUNTMANAGER_H".
