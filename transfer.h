#ifndef TRANSFER_H
#define TRANSFER_H

#include <QtWidgets>
//#include <QDialog>
//#include <QLabel>

class transfer : public QDialog
{
    Q_OBJECT

public:
    explicit transfer(QWidget *parent = nullptr);
    ~transfer();

private slots:
    void receiveInvite();
    void comfirmClicked();

signals:
    void comfirmReceived();

private:
    QPushButton *comfirm;
};


#endif // TRANSFER_H
