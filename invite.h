#ifndef INVITERECEIVE_H
#define INVITERECEIVE_H

#include <QtWidgets>

class inviteReceive : public QDialog
{
    Q_OBJECT

public:
    explicit inviteReceive(QWidget *parent = nullptr);
    ~inviteReceive();
    void receiveInvite(const QString ipAddress);


private slots:
    void acceptClick();
    void rejectClick();

public:
signals:
    void inviteAccept();
    void inviteReject();

private:
    QLabel *info;
    QPushButton *acceptInvite;
    QPushButton *rejectInvite;

    QHBoxLayout *button;
    QHBoxLayout *information;
    QVBoxLayout *mainLayout;


};


#endif // INVITERECEIVE_H
