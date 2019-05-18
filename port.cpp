#include "port.h"

port::port(QWidget *parent) : QWidget(parent)
{
    exit = new QPushButton(tr("Exit (Alt+&e)"));
    save = new QPushButton(tr("Save (Alt+&s)"));
    message = new QLabel(tr("Enter your port here: "));
    lineEdit = new QLineEdit;
    labelLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;

    labelLayout->addWidget(message);
    labelLayout->addStretch();

    buttonLayout->addStretch();
    buttonLayout->addWidget(save);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exit);

    mainLayout->addLayout(labelLayout);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(buttonLayout);


    connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));

    setLayout(mainLayout);
    setFixedWidth(sizeHint().width());
    setFixedHeight(sizeHint().height());
    setWindowTitle(tr("Please proveide your port"));
}

port::~port()
{
    delete exit;
    delete save;
    delete message;
    delete lineEdit;
    delete labelLayout;
    delete buttonLayout;
    delete mainLayout;
}

void port::exitClicked(){
    this->close();
}

void port::savePortClicked()
{
    QString strPort = lineEdit->text();
    int intPort;
    intPort = strPort.toInt();
    qDebug() << "port.savePortClicked: Send user enter port" << intPort << endl;
    emit emitPort(intPort);
    this->close();
}

