#include "client.h"  // Se incluye el archivo de encabezado "client.h" para usar la clase Client y sus métodos.

Client::Client(const QString& id, const QString& name)  // Constructor de la clase Client que inicializa el ID y el nombre del cliente.
    : id(id), name(name) {}  // Se inicializan las variables miembro id y name con los valores proporcionados en el constructor.

void Client::addAccount(Account* account) {  // Método que agrega una cuenta a la lista de cuentas del cliente.
    accounts.append(account);  // Se agrega la cuenta proporcionada a la lista de cuentas del cliente.
}

QList<Account*> Client::getAccounts() const {  // Método que devuelve todas las cuentas asociadas al cliente.
    return accounts;  // Se retorna la lista de cuentas del cliente.
}

QString Client::getId() const {  // Método que obtiene el ID del cliente.
    return id;  // Se retorna el ID del cliente.
}

QString Client::getName() const {  // Método que obtiene el nombre del cliente.
    return name;  // Se retorna el nombre del cliente.
}
