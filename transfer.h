#ifndef TRANSFER_H
#define TRANSFER_H

#include <QtWidgets>

class transfer : public QDialog
{
    Q_OBJECT

public:
    explicit transfer(QWidget *parent = nullptr);
    ~transfer();

private slots:
    void receiveInvite();

signals:
    void comfirmReceived();

private:
    QLabel *message;
    QVBoxLayout *layout;
};

#endif // TRANSFER_H
