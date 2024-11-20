#include "mainwindow.h"
#include <QDoubleValidator>
#include <QGroupBox>
#include <QHBoxLayout>

MainWindow::MainWindow(TcpClient *otherTcpClient, QWidget *parent)
    : QMainWindow(parent)
    , tcpClient(otherTcpClient)
{
    setWindowTitle("Polynomial");
    setMinimumSize(400, 300);
    resize(600, 800);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setObjectName("centralWidget");

    applyStyles();

    setupAnSection(centralWidget, mainLayout, inputAnRe, inputAnIm, changeAn);
    setupRootSection(centralWidget,
                     mainLayout,
                     inputRootRe,
                     inputRootIm,
                     addRoot,
                     inputIndex,
                     changeRoot,
                     inputResize,
                     rootsResize);
    setupEvaluateSection(centralWidget,
                         mainLayout,
                         inputEvaluateRe,
                         inputEvaluateIm,
                         evaluate,
                         evaluateOutput);
    setupPolynomSection(centralWidget, mainLayout, polynomFirstForm, polynomSecondForm);
    setupChangeModeSection(centralWidget, mainLayout, changeDoubleRB, changeComplexRB);
    setupConnectToServerSection(centralWidget,
                                mainLayout,
                                inputAddress,
                                inputPort,
                                connectToServerButton);
    setupLastActionSection(centralWidget, mainLayout, lastAction);

    connectSignals(changeAn, addRoot, changeRoot, rootsResize, evaluate, connectToServerButton, changeDoubleRB, changeComplexRB);
}

MainWindow::~MainWindow() {}

void MainWindow::applyStyles()
{
    setStyleSheet("#centralWidget {"
                  "   background-color: #171717;"
                  "}"
                  "#centralWidget * {"
                  "   background-color: #222222;"
                  "   font-family: 'San Francisco'; font-size: 11pt; color: #CCCCCC;"
                  "}"
                  "#centralWidget QGroupBox {"
                  "   background-color: #222222;"
                  "   border: 1px solid #545454;"
                  "   border-radius: 10px;"
                  "   margin-top: 15px;"
                  "}"
                  "#centralWidget QGroupBox::title {"
                  "   color: #CCCCCC;"
                  "   background-color: #404248;"
                  "   padding: 1px;"
                  "   border: 1px solid #545454;"
                  "   border-radius: 5px;"
                  "   subcontrol-origin: margin;"
                  "   subcontrol-position: top left;"
                  "   margin-left: 10px;"
                  "   margin-top: 1px;"
                  "}"
                  "#centralWidget QPushButton {"
                  "   background-color: #464A54;"
                  "   color: #CCCCCC;"
                  "   border: 1px solid #545454;"
                  "   border-radius: 5px;"
                  "   padding: 3px;"
                  "}"
                  "#centralWidget QLineEdit, "
                  "#centralWidget QTextEdit {"
                  "   border: 1px solid #545454;"
                  "   background-color: #282828;"
                  "   color: #CCCCCC;"
                  "}"
                  "#centralWidget QRadioButton {"
                  "   background-color: transparent;"
                  "   color: #CCCCCC;"
                  //"   border: 1px solid #545454;"
                  //"   border-radius: 5px;"
                  "   padding: 3px;"
                  "}");
}

void MainWindow::setupAnSection(QWidget *parent,
                                QVBoxLayout *parentLayout,
                                QLineEdit *&inputAnRe,
                                QLineEdit *&inputAnIm,
                                QPushButton *&changeAn)
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox *addAnBox = new QGroupBox("Изменить An", parent);
    QHBoxLayout *addAnBoxLayout = new QHBoxLayout(addAnBox);

    addAnBoxLayout->addWidget(new QLabel("Корень: "));
    inputAnRe = new QLineEdit("0");
    inputAnRe->setValidator(doubleValidator);
    addAnBoxLayout->addWidget(inputAnRe);
    addAnBoxLayout->addWidget(new QLabel(" + "));
    inputAnIm = new QLineEdit("0");
    inputAnIm->setValidator(doubleValidator);
    addAnBoxLayout->addWidget(inputAnIm);
    addAnBoxLayout->addWidget(new QLabel("i"));
    changeAn = new QPushButton("Изменить An");
    addAnBoxLayout->addWidget(changeAn);

    addAnBox->setLayout(addAnBoxLayout);
    parentLayout->addWidget(addAnBox);
}

void MainWindow::setupRootSection(QWidget *parent,
                                  QVBoxLayout *parentLayout,
                                  QLineEdit *&inputRootRe,
                                  QLineEdit *&inputRootIm,
                                  QPushButton *&addRoot,
                                  QLineEdit *&inputIndex,
                                  QPushButton *&changeRoot,
                                  QLineEdit *&inputResize,
                                  QPushButton *&rootsResize)
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox *rootBox = new QGroupBox("Операции с корнями", parent);
    QVBoxLayout *rootBoxLayout = new QVBoxLayout(rootBox);

    QWidget *addRootBox = new QWidget(rootBox);
    QHBoxLayout *addRootBoxLayout = new QHBoxLayout(addRootBox);

    addRootBoxLayout->addWidget(new QLabel("Корень: "));
    inputRootRe = new QLineEdit("0");
    inputRootRe->setValidator(doubleValidator);
    addRootBoxLayout->addWidget(inputRootRe);
    addRootBoxLayout->addWidget(new QLabel(" + "));
    inputRootIm = new QLineEdit("0");
    inputRootIm->setValidator(doubleValidator);
    addRootBoxLayout->addWidget(inputRootIm);
    addRootBoxLayout->addWidget(new QLabel("i"));
    addRoot = new QPushButton("Добавить корень");
    addRootBoxLayout->addWidget(addRoot);

    addRootBox->setLayout(addRootBoxLayout);
    rootBoxLayout->addWidget(addRootBox);

    QWidget *changeRootBox = new QWidget(rootBox);
    QHBoxLayout *changeRootBoxLayout = new QHBoxLayout(changeRootBox);

    QIntValidator *intValidator = new QIntValidator(0, 999999999, parent);

    changeRootBoxLayout->addWidget(new QLabel("Индекс: "));
    inputIndex = new QLineEdit("0");
    inputIndex->setValidator(intValidator);
    changeRootBoxLayout->addWidget(inputIndex);
    changeRoot = new QPushButton("Изменить корень");
    changeRootBoxLayout->addWidget(changeRoot);

    changeRootBox->setLayout(changeRootBoxLayout);
    rootBoxLayout->addWidget(changeRootBox);

    QWidget *changeRootsSizeBox = new QWidget(rootBox);
    QHBoxLayout *changeRootsSizeBoxLayout = new QHBoxLayout(changeRootsSizeBox);

    changeRootsSizeBoxLayout->addWidget(new QLabel("Размер массива корней: "));
    inputResize = new QLineEdit("0");
    inputResize->setValidator(intValidator);
    changeRootsSizeBoxLayout->addWidget(inputResize);
    rootsResize = new QPushButton("Изменить размер");
    changeRootsSizeBoxLayout->addWidget(rootsResize);

    changeRootsSizeBox->setLayout(changeRootsSizeBoxLayout);
    rootBoxLayout->addWidget(changeRootsSizeBox);
    parentLayout->addWidget(rootBox);
}

void MainWindow::setupEvaluateSection(QWidget *parent,
                                      QVBoxLayout *parentLayout,
                                      QLineEdit *&inputEvaluateRe,
                                      QLineEdit *&inputEvaluateIm,
                                      QPushButton *&evaluate,
                                      QLabel *&evaluateOutput)
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox *evaluateBox = new QGroupBox("Вычислить в точке", parent);
    QVBoxLayout *evaluateBoxLayout = new QVBoxLayout(evaluateBox);

    QWidget *evaluateInputBox = new QWidget(evaluateBox);
    QHBoxLayout *evaluateInputBoxLayout = new QHBoxLayout(evaluateInputBox);

    evaluateInputBoxLayout->addWidget(new QLabel("Значение: "));
    inputEvaluateRe = new QLineEdit("0");
    inputEvaluateRe->setValidator(doubleValidator);
    evaluateInputBoxLayout->addWidget(inputEvaluateRe);
    evaluateInputBoxLayout->addWidget(new QLabel(" + "));
    inputEvaluateIm = new QLineEdit("0");
    inputEvaluateIm->setValidator(doubleValidator);
    evaluateInputBoxLayout->addWidget(inputEvaluateIm);
    evaluateInputBoxLayout->addWidget(new QLabel("i"));
    evaluate = new QPushButton("Вычислить");
    evaluateInputBoxLayout->addWidget(evaluate);

    evaluateInputBox->setLayout(evaluateInputBoxLayout);
    evaluateBoxLayout->addWidget(evaluateInputBox);

    QWidget *evaluateOutputBox = new QWidget(evaluateBox);
    QHBoxLayout *evaluateOutputBoxLayout = new QHBoxLayout(evaluateOutputBox);

    evaluateOutput = new QLabel("Результат: p(0) = 0");
    evaluateOutputBoxLayout->addWidget(evaluateOutput);

    evaluateOutputBox->setLayout(evaluateOutputBoxLayout);
    evaluateBoxLayout->addWidget(evaluateOutputBox);

    parentLayout->addWidget(evaluateBox);
}

void MainWindow::setupPolynomSection(QWidget *parent,
                                     QVBoxLayout *parentLayout,
                                     QLabel *&polynomFirstForm,
                                     QLabel *&polynomSecondForm)
{
    QGroupBox *polynomBox = new QGroupBox("Полином в двух формах", parent);
    QVBoxLayout *polynomBoxLayout = new QVBoxLayout(polynomBox);

    QWidget *polynomFirstBox = new QWidget(polynomBox);
    QHBoxLayout *polynomFirstBoxLayout = new QHBoxLayout(polynomFirstBox);

    polynomFirstForm = new QLabel("p(x) = 0");
    polynomFirstForm->setWordWrap(true);
    polynomFirstBoxLayout->addWidget(polynomFirstForm);

    polynomFirstBox->setLayout(polynomFirstBoxLayout);
    polynomBoxLayout->addWidget(polynomFirstBox);

    QWidget *polynomSecondBox = new QWidget(polynomBox);
    QHBoxLayout *polynomSecondBoxLayout = new QHBoxLayout(polynomSecondBox);

    polynomSecondForm = new QLabel("p(x) = 0");
    polynomSecondForm->setWordWrap(true);
    polynomSecondBoxLayout->addWidget(polynomSecondForm);

    polynomSecondBox->setLayout(polynomSecondBoxLayout);
    polynomBoxLayout->addWidget(polynomSecondBox);

    parentLayout->addWidget(polynomBox);
}

void MainWindow::setupLastActionSection(QWidget *parent,
                                        QVBoxLayout *parentLayout,
                                        QLabel *&lastAction)
{
    lastAction = new QLabel("Действий не было", parent);
    lastAction->setObjectName("lastAction");
    lastAction->setStyleSheet("#lastAction {"
                              "   background-color: #FA5D51;"
                              "   border: 2px solid black;"
                              "   border-radius: 15px;"
                              "   padding: 5px;"
                              "   margin-top: 15px;"
                              "   font-size: 16px;"
                              "   font-weight: bold;"
                              "   text-align: center;"
                              "   color: white;"
                              "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                              "   stop:0 #333333, stop:1 #444444);"
                              "   qproperty-alignment: AlignCenter;"
                              "}");
    parentLayout->addWidget(lastAction);
}

void MainWindow::setupConnectToServerSection(QWidget *parent,
                                             QVBoxLayout *parentLayout,
                                             QLineEdit *&inputAddress,
                                             QLineEdit *&inputPort,
                                             QPushButton *&connectToServerButton)
{
    QGroupBox *connectToServerBox = new QGroupBox("Подключиться к серверу", parent);
    QHBoxLayout *connectToServerBoxLayout = new QHBoxLayout(connectToServerBox);

    connectToServerBoxLayout->addWidget(new QLabel("IP Адресс: "));
    inputAddress = new QLineEdit("0");
    connectToServerBoxLayout->addWidget(inputAddress);
    connectToServerBoxLayout->addWidget(new QLabel("Порт: "));
    inputPort = new QLineEdit("0");
    connectToServerBoxLayout->addWidget(inputPort);

    connectToServerBox->setLayout(connectToServerBoxLayout);
    parentLayout->addWidget(connectToServerBox);

    connectToServerButton = new QPushButton("Подключиться");
    parentLayout->addWidget(connectToServerButton);
}

void MainWindow::setupChangeModeSection(QWidget *parent,
                                        QVBoxLayout *parentLayout,
                                        QRadioButton *&changeDoubleRB,
                                        QRadioButton *&changeComplexRB)
{
    QDoubleValidator *doubleValidator = new QDoubleValidator(parent);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    QGroupBox *changeModeBox = new QGroupBox("Изменить множество", parent);
    QHBoxLayout *changeModeBoxLayout = new QHBoxLayout(changeModeBox);

    changeDoubleRB = new QRadioButton("Вещественные числа");
    changeModeBoxLayout->addWidget(changeDoubleRB);
    changeComplexRB = new QRadioButton("Комплексные числа");
    changeModeBoxLayout->addWidget(changeComplexRB);

    changeModeBox->setLayout(changeModeBoxLayout);
    parentLayout->addWidget(changeModeBox);

    changeDoubleRB->setChecked(true);
}

void MainWindow::connectSignals(QPushButton *changeAn,
                                QPushButton *addRoot,
                                QPushButton *changeRoot,
                                QPushButton *rootsResize,
                                QPushButton *evaluate,
                                QPushButton *connectToServerButton,
                                QRadioButton *changeDoubleRB,
                                QRadioButton *changeComplexRB
                                )
{
    connect(changeAn, &QPushButton::clicked, this, &MainWindow::onChangeAnClicked);
    connect(addRoot, &QPushButton::clicked, this, &MainWindow::onAddRootClicked);
    connect(changeRoot, &QPushButton::clicked, this, &MainWindow::onChangeRootClicked);
    connect(rootsResize, &QPushButton::clicked, this, &MainWindow::onRootsResizeClicked);
    connect(evaluate, &QPushButton::clicked, this, &MainWindow::onEvaluateClicked);
    connect(changeDoubleRB, &QRadioButton::toggled, this, &MainWindow::onChangeDoubleRBClicked);
    connect(changeComplexRB, &QRadioButton::toggled, this, &MainWindow::onChangeComplexRBClicked);
    connect(connectToServerButton, &QPushButton::clicked, this, &MainWindow::onChangeConnectionToServerClicked);
    connect(tcpClient, &TcpClient::messageReceived, this, &MainWindow::onMessageReceived);
}

void MainWindow::onChangeAnClicked()
{
    lastAction->setText("Отправлен запрос на изменение An");
    tcpClient->sendData("changeAn " + (inputAnRe->text().isEmpty() ? "0" : inputAnRe->text()) + ' '
                        + (inputAnIm->text().isEmpty() ? "0" : inputAnIm->text()));
}

void MainWindow::onAddRootClicked()
{
    lastAction->setText("Отправлен запрос на добавление корня");
    tcpClient->sendData("addRoot " + (inputRootRe->text().isEmpty() ? "0" : inputRootRe->text())
                        + ' ' + (inputRootIm->text().isEmpty() ? "0" : inputRootIm->text()));
}

void MainWindow::onChangeRootClicked()
{
    lastAction->setText("Отправлен запрос на изменение корня по индексу");
    tcpClient->sendData("changeRoot " + (inputRootRe->text().isEmpty() ? "0" : inputRootRe->text())
                        + ' ' + (inputRootIm->text().isEmpty() ? "0" : inputRootIm->text()) + ' '
                        + (inputIndex->text().isEmpty() ? "0" : inputIndex->text()));
}

void MainWindow::onRootsResizeClicked()
{
    lastAction->setText("Отправлен запрос на изменение размера массива корней");
    tcpClient->sendData("rootsResize "
                        + (inputResize->text().isEmpty() ? "0" : inputResize->text()));
}

void MainWindow::onEvaluateClicked()
{
    lastAction->setText("Отправлен запрос на вычисление в точке");
    tcpClient->sendData("evaluate "
                        + (inputEvaluateRe->text().isEmpty() ? "0" : inputEvaluateRe->text()) + ' '
                        + (inputEvaluateIm->text().isEmpty() ? "0" : inputEvaluateIm->text()));
}

void MainWindow::onChangeConnectionToServerClicked()
{
    if (!(tcpClient->isConnected())) {
        if (tcpClient->connectToServer(inputAddress->text(), inputPort->text().toInt())) {
            lastAction->setText("Подключён к серверу");
            connectToServerButton->setText("Отключиться");
        } else {
            lastAction->setText("Подключиться не удалось");
        }
    } else {
        tcpClient->disconnectFromServer();
        lastAction->setText("Отключён от сервера");
        connectToServerButton->setText("Подключиться");
    }
}

void MainWindow::onChangeDoubleRBClicked()
{
    if (changeDoubleRB->isChecked()) {
        lastAction->setText("Отправлен запрос на изменение множества чисел на вещественное");
        tcpClient->sendData("changeDouble");
    }
}

void MainWindow::onChangeComplexRBClicked()
{
    if (changeComplexRB->isChecked()) {
        lastAction->setText("Отправлен запрос на изменение множества чисел на комплексное");
        tcpClient->sendData("changeComplex");
    }
}

void MainWindow::onMessageReceived(const QString &response)
{
    if (lastAction->text() == "Отправлен запрос на изменение An") {
        lastAction->setText("Получен результат изменения An");
        polynomFirstForm->setText(response.section('\n', 0, 0));
        polynomSecondForm->setText(response.section('\n', 1, 1));
    }
    else if (lastAction->text() == "Отправлен запрос на добавление корня") {
        lastAction->setText("Получен результат добавления корня");
        polynomFirstForm->setText(response.section('\n', 0, 0));
        polynomSecondForm->setText(response.section('\n', 1, 1));
    }
    else if (lastAction->text() == "Отправлен запрос на изменение корня по индексу") {
        lastAction->setText("Получен результат изменения корня");
        polynomFirstForm->setText(response.section('\n', 0, 0));
        polynomSecondForm->setText(response.section('\n', 1, 1));
    }
    else if (lastAction->text() == "Отправлен запрос на изменение размера массива корней") {
        lastAction->setText("Получен результат изменения размера массива корней");
        polynomFirstForm->setText(response.section('\n', 0, 0));
        polynomSecondForm->setText(response.section('\n', 1, 1));
    }
    else if (lastAction->text() == "Отправлен запрос на вычисление в точке") {
        lastAction->setText("Получен результат вычисления в точке");
        evaluateOutput->setText("Результат: " + response);
    }
    else if (response.startsWith("changedModeToDouble")) {
        lastAction->setText("Множество чисел было изменено на вещественное");
        polynomFirstForm->setText(response.section('\n', 1, 1));
        polynomSecondForm->setText(response.section('\n', 2, 2));
    }
    else if (response.startsWith("changedModeToComplex")) {
        lastAction->setText("Множество чисел было изменено на комплексное");
        polynomFirstForm->setText(response.section('\n', 1, 1));
        polynomSecondForm->setText(response.section('\n', 2, 2));
    }
    else {
        lastAction->setText("Ответ сервера: " + response);
    }
}
