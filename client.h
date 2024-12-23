#ifndef CLIENT_H  // Se verifica si no se ha definido previamente el archivo de encabezado "CLIENT_H".
#define CLIENT_H  // Se define "CLIENT_H" para evitar la inclusión múltiple del archivo de encabezado.

#include <QString>  // Se incluye la clase QString de Qt para manejar cadenas de texto.
#include <QList>    // Se incluye la clase QList de Qt para manejar listas (colecciones de objetos).
#include "account.h"  // Se incluye el archivo de encabezado "account.h", que probablemente contiene la definición de la clase Account.

class Client {  // Se define la clase Client, que representa a un cliente de la aplicación.
public:
    Client(const QString& id, const QString& name);  // Constructor de la clase Client, que toma un ID y un nombre para crear un cliente.
    void addAccount(Account* account);  // Método para agregar una cuenta a la lista de cuentas del cliente.
    QList<Account*> getAccounts() const;  // Método para obtener una lista de todas las cuentas asociadas al cliente.
    QString getId() const;  // Método que retorna el ID del cliente.
    QString getName() const;  // Método que retorna el nombre del cliente.

private:
    QString id;  // Atributo que guarda el ID del cliente.
    QString name;  // Atributo que guarda el nombre del cliente.
    QList<Account*> accounts;  // Atributo que guarda una lista de punteros a las cuentas asociadas al cliente.
};

#endif  // Fin de la declaración del encabezado "CLIENT_H".
