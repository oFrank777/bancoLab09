#include "mainwindow.h"  // Se incluye el archivo de encabezado "mainwindow.h" para usar la clase MainWindow.
#include "ui_mainwindow.h"  // Se incluye el archivo de encabezado "ui_mainwindow.h" generado por Qt para interactuar con la interfaz de usuario.
#include <QMessageBox>  // Se incluye QMessageBox para mostrar mensajes emergentes de alerta.

MainWindow::MainWindow(QWidget *parent) :  // Constructor de la clase MainWindow que se llama al crear la ventana principal.
    QMainWindow(parent),  // Se llama al constructor de la clase base QMainWindow.
    ui(new Ui::MainWindow),  // Se inicializa el puntero 'ui' para la interfaz gráfica.
    accountManager(AccountManager::getInstance())  // Se inicializa el puntero 'accountManager' con la instancia única de AccountManager.
{
    ui->setupUi(this);  // Se configura la interfaz de usuario definida en Qt Designer.

    // Configurar tipos de cuenta en el combo box para seleccionar el tipo de cuenta.
    ui->accountTypeCombo->addItem("Ahorro", static_cast<int>(AccountType::SAVINGS));  // Se agrega "Ahorro" con el valor correspondiente del enum AccountType.
    ui->accountTypeCombo->addItem("Joven", static_cast<int>(AccountType::YOUTH));  // Se agrega "Joven" con el valor correspondiente del enum AccountType.
    ui->accountTypeCombo->addItem("Plus", static_cast<int>(AccountType::PLUS));  // Se agrega "Plus" con el valor correspondiente del enum AccountType.
    ui->accountTypeCombo->addItem("Empresarial", static_cast<int>(AccountType::BUSINESS));  // Se agrega "Empresarial" con el valor correspondiente del enum AccountType.
    ui->accountTypeCombo->addItem("Crédito", static_cast<int>(AccountType::CREDIT));  // Se agrega "Crédito" con el valor correspondiente del enum AccountType.

    // Configurar tipos de transacción en el combo box para seleccionar el tipo de transacción.
    ui->transactionTypeCombo->addItem("Depósito", static_cast<int>(TransactionType::DEPOSIT));  // Se agrega "Depósito" con el valor correspondiente del enum TransactionType.
    ui->transactionTypeCombo->addItem("Retiro", static_cast<int>(TransactionType::WITHDRAWAL));  // Se agrega "Retiro" con el valor correspondiente del enum TransactionType.
    ui->transactionTypeCombo->addItem("Préstamo Personal", static_cast<int>(TransactionType::PERSONAL_LOAN));  // Se agrega "Préstamo Personal" con el valor correspondiente del enum TransactionType.
    ui->transactionTypeCombo->addItem("Transferencia Nacional", static_cast<int>(TransactionType::NATIONAL_TRANSFER));  // Se agrega "Transferencia Nacional" con el valor correspondiente del enum TransactionType.
    ui->transactionTypeCombo->addItem("Compra con Tarjeta", static_cast<int>(TransactionType::CREDIT_PURCHASE));  // Se agrega "Compra con Tarjeta" con el valor correspondiente del enum TransactionType.

    // Configurar las fechas de inicio y fin para el rango de estado de cuenta.
    ui->fromDateEdit->setDate(QDate::currentDate().addMonths(-1));  // Establece la fecha de inicio al mes pasado.
    ui->toDateEdit->setDate(QDate::currentDate());  // Establece la fecha de fin a la fecha actual.

    // Deshabilitar pestañas de la interfaz de usuario hasta que se inicie sesión.
    ui->tabWidget->setTabEnabled(1, false);  // Deshabilita la segunda pestaña (crear cuenta).
    ui->tabWidget->setTabEnabled(2, false);  // Deshabilita la tercera pestaña (realizar transacción).
    ui->tabWidget->setTabEnabled(3, false);  // Deshabilita la cuarta pestaña (generar estado de cuenta).
}

MainWindow::~MainWindow() {  // Destructor de la clase MainWindow.
    delete ui;  // Se libera la memoria utilizada por la interfaz gráfica.
}

void MainWindow::on_loginButton_clicked() {  // Método que se ejecuta cuando se hace clic en el botón de login.
    QString clientId = ui->clientIdInput->text();  // Se obtiene el ID del cliente desde el campo de texto.
    if (!clientId.isEmpty()) {  // Si el campo de texto no está vacío.
        currentClientId = clientId;  // Se guarda el ID del cliente en la variable miembro 'currentClientId'.
        updateAccountList();  // Se actualiza la lista de cuentas del cliente.
        ui->tabWidget->setTabEnabled(1, true);  // Se habilita la pestaña de crear cuenta.
        ui->tabWidget->setTabEnabled(2, true);  // Se habilita la pestaña de realizar transacciones.
        ui->tabWidget->setTabEnabled(3, true);  // Se habilita la pestaña de generar estado de cuenta.
        ui->tabWidget->setCurrentIndex(1);  // Se cambia a la pestaña de crear cuenta.
        showMessage("Sesión iniciada correctamente");  // Se muestra un mensaje de éxito.
    } else {
        showMessage("Por favor ingrese un ID de cliente válido");  // Si el campo está vacío, se muestra un mensaje de error.
    }
}

void MainWindow::on_createAccountButton_clicked() {  // Método que se ejecuta cuando se hace clic en el botón para crear cuenta.
    AccountType type = static_cast<AccountType>(ui->accountTypeCombo->currentData().toInt());  // Se obtiene el tipo de cuenta seleccionado en el combo box.
    accountManager->createAccount(currentClientId, type);  // Se llama al método de AccountManager para crear la cuenta.
    updateAccountList();  // Se actualiza la lista de cuentas.
    showMessage("Cuenta creada exitosamente");  // Se muestra un mensaje de éxito.
}

void MainWindow::on_executeTransactionButton_clicked() {  // Método que se ejecuta cuando se hace clic en el botón para ejecutar una transacción.
    QString accountId = ui->transactionAccountCombo->currentText();  // Se obtiene la cuenta seleccionada para la transacción.
    double amount = ui->amountSpinBox->value();  // Se obtiene el monto de la transacción desde el campo de entrada.
    TransactionType type = static_cast<TransactionType>(ui->transactionTypeCombo->currentData().toInt());  // Se obtiene el tipo de transacción seleccionado.

    if (accountManager->executeTransaction(accountId, amount, type)) {  // Se ejecuta la transacción a través de AccountManager.
        showMessage("Transacción ejecutada exitosamente");  // Se muestra un mensaje de éxito si la transacción fue exitosa.
        updateAccountList();  // Se actualiza la lista de cuentas.
    } else {
        showMessage("Error al ejecutar la transacción");  // Si hubo un error, se muestra un mensaje de error.
    }
}

void MainWindow::on_generateStatementButton_clicked() {  // Método que se ejecuta cuando se hace clic en el botón para generar un estado de cuenta.
    QDate fromDate = ui->fromDateEdit->date();  // Se obtiene la fecha de inicio del rango para el estado de cuenta.
    QDate toDate = ui->toDateEdit->date();  // Se obtiene la fecha de fin del rango.
    AccountType type = static_cast<AccountType>(ui->statementAccountTypeCombo->currentData().toInt());  // Se obtiene el tipo de cuenta seleccionado.

    QString statement = accountManager->generateStatement(currentClientId, fromDate, toDate, type);  // Se genera el estado de cuenta a través de AccountManager.
    ui->statementText->setText(statement);  // Se muestra el estado de cuenta en el área de texto.
}

void MainWindow::updateAccountList() {  // Método que actualiza la lista de cuentas en la interfaz gráfica.
    ui->accountsList->clear();  // Se limpia la lista de cuentas antes de actualizarla.
    ui->transactionAccountCombo->clear();  // Se limpia el combo box de cuentas para las transacciones.

    QList<Account*> accounts = accountManager->getClientAccounts(currentClientId);  // Se obtienen todas las cuentas del cliente actual.
    for (Account* account : accounts) {  // Se itera sobre todas las cuentas.
        QString accountInfo = QString("Cuenta %1 - Saldo: $%2")
                                  .arg(account->getId())  // Se obtiene el ID de la cuenta.
                                  .arg(account->getBalance(), 0, 'f', 2);  // Se obtiene el saldo de la cuenta y se formatea.
        ui->accountsList->addItem(accountInfo);  // Se agrega la información de la cuenta a la lista de cuentas.
        ui->transactionAccountCombo->addItem(account->getId());  // Se agrega el ID de la cuenta al combo box para las transacciones.
    }
}

void MainWindow::showMessage(const QString& message) {  // Método que muestra un mensaje en la barra de estado.
    ui->statusbar->showMessage(message, 3000);  // Se muestra el mensaje en la barra de estado durante 3 segundos.
}
