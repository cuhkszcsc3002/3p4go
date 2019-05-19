#include "port.h"

port::port(QWidget *parent) : QWidget(parent)
{
    exit = new QPushButton(tr("Exit (Alt+&e)"));
    save = new QPushButton(tr("Save (Alt+&s)"));
    message = new QLabel(tr("Enter your port here: "));
    lineEdit = new QLineEdit;
    labelLayout = new QHBoxLayout;
    lineEditLayout = new QVBoxLayout;
    buttonLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;

    QPalette pal;
    pal.setColor(QPalette::Text,QColor(0,0,0));
    lineEdit->setPalette(pal);
    lineEdit->setMaxLength(25);

    labelLayout->addWidget(message);
    labelLayout->addStretch();

    lineEditLayout->addLayout(labelLayout);
    lineEditLayout->addWidget(lineEdit);

    buttonLayout->addStretch();
    buttonLayout->addWidget(save);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exit);

    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(lineEditLayout);
    mainLayout->addLayout(buttonLayout);


    connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));
    connect(save, SIGNAL(clicked()), this, SLOT(savePortClicked()));

    setLayout(mainLayout);
    setFixedWidth(sizeHint().width()+300);
    setFixedHeight(sizeHint().height()+300);
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
    delete lineEditLayout;
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

