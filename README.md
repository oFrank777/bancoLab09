# Sistema Bancario - Proyecto de Gestión de Cuentas y Transacciones
![SistemaBancario_EstadodeCuenta](https://github.com/oFrank777/bancoLab09/blob/main/SistemaBancario_EstadodeCuenta.png)
## Descripción

El **Sistema Bancario** es una aplicación que permite a los clientes gestionar sus cuentas bancarias, realizar transacciones y consultar estados de cuenta. El sistema permite crear cuentas de diferentes tipos (Ahorro, Joven, Plus, Empresarial, Crédito), realizar depósitos, retiros, transferencias nacionales, compras con tarjeta, y generar estados de cuenta con transacciones realizadas durante un periodo.

Este sistema simula las operaciones básicas de un banco con un enfoque en la gestión de cuentas y transacciones utilizando una interfaz gráfica construida con **Qt**.

## Funcionalidades Principales

- **Inicio de sesión de cliente**: Los clientes pueden iniciar sesión en el sistema utilizando su ID de cliente.
- **Gestión de cuentas**: Los clientes pueden crear nuevas cuentas bancarias de diferentes tipos.
- **Transacciones**: El sistema permite realizar depósitos, retiros, transferencias nacionales, préstamos personales y compras con tarjeta.
- **Estados de cuenta**: Los clientes pueden consultar un estado de cuenta con todas las transacciones realizadas dentro de un rango de fechas específico.

## Diagrama UML

A continuación se presenta el diagrama UML del sistema, que describe la estructura de las clases involucradas:

![Diagrama UML del Sistema Bancario](https://github.com/oFrank777/bancoLab09/blob/main/uml.png)  

> **Nota**: El diagrama UML describe las relaciones entre las principales clases del sistema: `Client`, `Account`, `Transaction`, `AccountManager` y `MainWindow`.

## Tecnologías Usadas

- **Qt**: Para el desarrollo de la interfaz gráfica de usuario.
- **C++**: Para la implementación de la lógica del sistema.
- **Git**: Para el control de versiones del código fuente.

## Requisitos

- **Sistema Operativo**: Windows, Linux o macOS (sin embargo, el archivo ejecutable actual es solo para Windows).
- **No se requiere compilación**: El proyecto tiene un archivo ejecutable listo para usar.

## Instrucciones de Ejecución

Para ejecutar el sistema, sigue estos pasos:

1. **Descargar el archivo ejecutable**:
    - Dirígete a la página de **releases** del proyecto en GitHub y descarga el archivo ejecutable (`.exe`).
    
    [Descargar Release](https://github.com/oFrank777/bancoLab09/releases)

2. **Ejecutar el archivo**:
    - Una vez descargado el archivo `.exe`, simplemente haz doble clic sobre él para iniciar el sistema.
    - La aplicación se abrirá y podrás interactuar con la interfaz gráfica para iniciar sesión, gestionar cuentas, realizar transacciones y generar estados de cuenta.

3. **Interacción con la interfaz**:
    - **Inicio de sesión**: Ingresa el ID del cliente para acceder a las funcionalidades del sistema.
    - **Gestión de cuentas**: Crea nuevas cuentas bancarias y visualiza las cuentas existentes.
    - **Realizar transacciones**: Realiza depósitos, retiros, transferencias nacionales, y más.
    - **Generar estados de cuenta**: Consulta las transacciones realizadas durante un rango de fechas.
