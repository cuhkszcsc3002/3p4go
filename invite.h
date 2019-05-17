#ifndef INVITERECEIVE_H
#define INVITERECEIVE_H

#include <QtWidgets>

class inviteReceive : public QDialog
{
    Q_OBJECT

public:
    explicit inviteReceive(QWidget *parent = nullptr);
    ~inviteReceive();

private slots:
    void receiveInvite(const QString ipAddress);
    void acceptClick();
    void rejectClick();

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
