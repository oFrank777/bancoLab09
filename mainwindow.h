#ifndef MAINWINDOW_H  // Se verifica si no se ha definido previamente el archivo de encabezado "MAINWINDOW_H".
#define MAINWINDOW_H  // Se define "MAINWINDOW_H" para evitar la inclusión múltiple del archivo de encabezado.

#include <QMainWindow>  // Se incluye la clase QMainWindow de Qt, que es la clase base para las ventanas principales de la aplicación.
#include "accountmanager.h"  // Se incluye el archivo de encabezado "accountmanager.h", que contiene la definición de la clase AccountManager.

namespace Ui {  // Se define el espacio de nombres Ui, donde se declaran las clases relacionadas con la interfaz de usuario generada por Qt Designer.
class MainWindow;  // Se declara la clase MainWindow dentro del espacio de nombres Ui (esto es una convención de Qt para separar la UI generada).
}

class MainWindow : public QMainWindow {  // Se define la clase MainWindow, que hereda de QMainWindow, y representa la ventana principal de la aplicación.
    Q_OBJECT  // Macro de Qt que permite la gestión de señales y ranuras en la clase.

public:
    explicit MainWindow(QWidget *parent = nullptr);  // Constructor de la clase MainWindow, toma un puntero al widget principal (por defecto nullptr).
    ~MainWindow();  // Destructor de la clase MainWindow.

private slots:  // Se definen las ranuras que responden a las señales de la interfaz de usuario.
    void on_loginButton_clicked();  // Ranura que se ejecuta cuando se hace clic en el botón de login.
    void on_createAccountButton_clicked();  // Ranura que se ejecuta cuando se hace clic en el botón de crear cuenta.
    void on_executeTransactionButton_clicked();  // Ranura que se ejecuta cuando se hace clic en el botón de ejecutar transacción.
    void on_generateStatementButton_clicked();  // Ranura que se ejecuta cuando se hace clic en el botón de generar estado de cuenta.

private:
    Ui::MainWindow *ui;  // Atributo que guarda un puntero a la interfaz de usuario generada por Qt Designer.
    AccountManager* accountManager;  // Atributo que guarda un puntero al administrador de cuentas, usado para interactuar con las cuentas.
    QString currentClientId;  // Atributo que guarda el ID del cliente actual, utilizado para realizar operaciones específicas.

    void updateAccountList();  // Método privado para actualizar la lista de cuentas en la interfaz de usuario.
    void showMessage(const QString& message);  // Método privado para mostrar un mensaje en la interfaz de usuario.
};

#endif  // Fin de la declaración del encabezado "MAINWINDOW_H".
