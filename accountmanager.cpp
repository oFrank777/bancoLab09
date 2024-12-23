// accountmanager.cpp
#include "accountmanager.h"  // Se incluye el archivo de encabezado "accountmanager.h" para usar la clase AccountManager y sus métodos.
#include <QDateTime>  // Se incluye la clase QDateTime para trabajar con fechas y horas.


// Inicialización del singleton
AccountManager* AccountManager::instance = nullptr;  // Se inicializa el puntero estático a nullptr para implementar el patrón Singleton.

AccountManager* AccountManager::getInstance() {  // Método estático que devuelve la instancia única de AccountManager (Singleton).
    if (instance == nullptr) {  // Si no existe una instancia, se crea una nueva.
        instance = new AccountManager();  // Se crea una nueva instancia de AccountManager.
    }
    return instance;  // Se retorna la instancia de AccountManager.
}

AccountManager::AccountManager(QObject *parent) : QObject(parent) {  // Constructor privado de la clase AccountManager para evitar instanciaciones externas (público solo para Singleton).
    // El constructor está vacío porque se utiliza para inicializar los miembros del singleton.
}

void AccountManager::createAccount(const QString& clientId, AccountType type) {  // Método para crear una nueva cuenta para un cliente.
    // Generar un ID único para la cuenta usando timestamp
    QString accountId = QString("%1-%2").arg(clientId).arg(QDateTime::currentMSecsSinceEpoch());  // Se genera un ID único para la cuenta con el ID del cliente y el timestamp actual.

    // Crear la nueva cuenta con saldo inicial de 0
    Account* newAccount = new Account(accountId, type);  // Se crea la cuenta con el ID generado y el tipo de cuenta especificado.
    accounts[accountId] = newAccount;  // Se agrega la cuenta al mapa de cuentas, usando el ID como clave.

    // Crear el cliente si no existe
    if (!clients.contains(clientId)) {  // Si no existe el cliente, se crea uno nuevo.
        clients[clientId] = new Client(clientId, "Cliente " + clientId);  // Se crea un nuevo cliente con el ID proporcionado.
    }

    // Asignar la cuenta al cliente
    clients[clientId]->addAccount(newAccount);  // Se asigna la cuenta al cliente creado o ya existente.
}

QList<Account*> AccountManager::getClientAccounts(const QString& clientId) {  // Método para obtener todas las cuentas asociadas a un cliente.
    if (clients.contains(clientId)) {  // Si el cliente existe en el mapa.
        return clients[clientId]->getAccounts();  // Se devuelve la lista de cuentas del cliente.
    }
    return QList<Account*>();  // Si el cliente no existe, se retorna una lista vacía.
}

bool AccountManager::executeTransaction(const QString& accountId, double amount, TransactionType type) {  // Método para ejecutar una transacción en una cuenta.
    if (!accounts.contains(accountId)) {  // Si la cuenta no existe.
        return false;  // La transacción no se puede ejecutar.
    }

    Account* account = accounts[accountId];  // Se obtiene la cuenta asociada al ID proporcionado.
    double interestRate = calculateInterest(account->getType(), type);  // Se calcula la tasa de interés basada en el tipo de cuenta y el tipo de transacción.
    double totalAmount = amount * (1 + interestRate);  // Se calcula el monto total de la transacción incluyendo la tasa de interés.

    // Validaciones específicas por tipo de transacción
    switch (type) {  // Se verifica el tipo de transacción y se aplica la lógica correspondiente.
    case TransactionType::DEPOSIT:  // Para depósitos.
        // No hay restricciones para depósitos
        return account->executeTransaction(amount, type);  // Se ejecuta la transacción de depósito.

    case TransactionType::WITHDRAWAL:  // Para retiros.
        // Verificar que haya saldo suficiente
        if (account->getBalance() >= totalAmount) {  // Si el saldo es suficiente.
            return account->executeTransaction(totalAmount, type);  // Se ejecuta la transacción de retiro.
        }
        return false;  // Si no hay saldo suficiente, la transacción no se puede ejecutar.

    case TransactionType::PERSONAL_LOAN:  // Para préstamos personales.
        // Verificar que el tipo de cuenta permita préstamos
        if (account->getType() == AccountType::PLUS ||
            account->getType() == AccountType::BUSINESS) {  // Si la cuenta es de tipo PLUS o BUSINESS.
            return account->executeTransaction(totalAmount, type);  // Se ejecuta la transacción de préstamo.
        }
        return false;  // Si la cuenta no permite préstamos, la transacción no se puede ejecutar.

    case TransactionType::NATIONAL_TRANSFER:  // Para transferencias nacionales.
        // Verificar saldo suficiente incluyendo comisión
        if (account->getBalance() >= totalAmount) {  // Si el saldo es suficiente para cubrir la transferencia y la comisión.
            return account->executeTransaction(totalAmount, type);  // Se ejecuta la transacción de transferencia.
        }
        return false;  // Si no hay saldo suficiente, la transacción no se puede ejecutar.

    case TransactionType::CREDIT_PURCHASE:  // Para compras a crédito.
        // Solo permitir en tarjetas de crédito
        if (account->getType() == AccountType::CREDIT) {  // Si la cuenta es de tipo crédito.
            return account->executeTransaction(totalAmount, type);  // Se ejecuta la transacción de compra a crédito.
        }
        return false;  // Si la cuenta no es de tipo crédito, la transacción no se puede ejecutar.

    default:
        return false;  // Si el tipo de transacción no es reconocido, la transacción no se puede ejecutar.
    }
}

QString AccountManager::generateStatement(const QString& clientId, const QDate& fromDate,
                                          const QDate& toDate, AccountType type) {  // Método para generar un estado de cuenta para un cliente en un período determinado.
    QString statement = "=======================================\n";
    statement += "           ESTADO DE CUENTA                \n";  // Encabezado del estado de cuenta.
    statement += "=======================================\n\n";

    if (!clients.contains(clientId)) {  // Si el cliente no existe en el sistema.
        return "Error: Cliente no encontrado";  // Se retorna un mensaje de error.
    }

    Client* client = clients[clientId];  // Se obtiene el cliente.
    statement += QString("Cliente ID: %1\n").arg(clientId);  // Se agrega el ID del cliente al estado de cuenta.
    statement += QString("Nombre: %1\n").arg(client->getName());  // Se agrega el nombre del cliente al estado de cuenta.
    statement += QString("Período: %1 al %2\n\n")
                     .arg(fromDate.toString("dd/MM/yyyy"))
                     .arg(toDate.toString("dd/MM/yyyy"));  // Se agrega el período de tiempo del estado de cuenta.

    QList<Account*> clientAccounts = client->getAccounts();  // Se obtiene la lista de cuentas del cliente.
    double totalBalance = 0;  // Variable para calcular el balance total de todas las cuentas del cliente.

    for (Account* account : clientAccounts) {  // Se recorre cada cuenta del cliente.
        // Filtrar por tipo de cuenta si se especifica
        if (type != AccountType::ALL && account->getType() != type) {  // Si se especifica un tipo de cuenta y no coincide, se omite.
            continue;
        }

        statement += "\n----------------------------------------\n";  // Se agrega un separador para cada cuenta.
        statement += QString("Cuenta ID: %1\n").arg(account->getId());  // Se agrega el ID de la cuenta al estado de cuenta.

        // Convertir el tipo de cuenta a texto
        QString accountType;  // Variable para almacenar el tipo de cuenta en formato de texto.
        switch (account->getType()) {
        case AccountType::SAVINGS: accountType = "Ahorro"; break;
        case AccountType::YOUTH: accountType = "Joven"; break;
        case AccountType::PLUS: accountType = "Plus"; break;
        case AccountType::BUSINESS: accountType = "Empresarial"; break;
        case AccountType::CREDIT: accountType = "Tarjeta de Crédito"; break;
        default: accountType = "Desconocido"; break;
        }

        statement += QString("Tipo de Cuenta: %1\n").arg(accountType);  // Se agrega el tipo de cuenta al estado de cuenta.
        statement += account->generateStatement(fromDate, toDate);  // Se agrega el estado de cuenta generado para esa cuenta.
        totalBalance += account->getBalance();  // Se suma el balance de la cuenta al balance total.
    }

    statement += "\n=======================================\n";  // Fin del estado de cuenta.
    statement += QString("BALANCE TOTAL: $%1\n").arg(totalBalance, 0, 'f', 2);  // Se agrega el balance total de todas las cuentas.
    statement += "=======================================\n";

    return statement;  // Se retorna el estado de cuenta completo.
}

double AccountManager::calculateInterest(AccountType type, TransactionType transType) {  // Método para calcular la tasa de interés según el tipo de cuenta y transacción.
    // Tasas de interés según tipo de cuenta y transacción
    switch (transType) {
    case TransactionType::PERSONAL_LOAN:  // Para préstamos personales.
        switch (type) {
        case AccountType::PLUS: return 0.08;      // 8% para cuentas PLUS.
        case AccountType::BUSINESS: return 0.085;  // 8.5% para cuentas BUSINESS.
        default: return 0.10;                      // 10% para otros tipos de cuenta.
        }

    case TransactionType::NATIONAL_TRANSFER:  // Para transferencias nacionales.
        switch (type) {
        case AccountType::BUSINESS: return 0.005;  // 0.5% para cuentas BUSINESS.
        case AccountType::PLUS: return 0.02;       // 2% para cuentas PLUS.
        default: return 0.04;                      // 4% para otros tipos de cuenta.
        }

    case TransactionType::CREDIT_PURCHASE:  // Para compras a crédito.
        switch (type) {
        case AccountType::CREDIT:
            return 0.15;  // 15% para tarjetas de crédito.
        default:
            return 0.25;  // 25% para otros tipos (aunque no deberían permitirse).
        }

    case TransactionType::DEPOSIT:  // Para depósitos.
        // Intereses ganados por depósitos
        switch (type) {
        case AccountType::SAVINGS: return 0.02;   // 2% para cuentas de ahorro.
        case AccountType::PLUS: return 0.025;     // 2.5% para cuentas PLUS.
        case AccountType::BUSINESS: return 0.03;  // 3% para cuentas BUSINESS.
        default: return 0.015;                    // 1.5% para otros tipos de cuenta.
        }

    default:
        return 0.0;  // Sin interés para otros tipos de transacciones.
    }
}
