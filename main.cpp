#include "mainwindow.h"  // Se incluye el archivo de encabezado "mainwindow.h" para usar la clase MainWindow.
#include <QApplication>  // Se incluye la clase QApplication para gestionar la ejecución de la aplicación Qt.

int main(int argc, char *argv[]) {  // Función principal que inicia la aplicación Qt. Recibe argumentos de línea de comandos.
    QApplication a(argc, argv);  // Se crea un objeto QApplication que gestiona la inicialización y ejecución de la aplicación Qt.

    MainWindow w;  // Se crea un objeto de la clase MainWindow, que es la ventana principal de la aplicación.
    w.show();  // Se muestra la ventana principal en la pantalla.

    return a.exec();  // Se entra en el ciclo de eventos de la aplicación, esperando interacciones del usuario, y se ejecuta hasta que la aplicación se cierre.
}
