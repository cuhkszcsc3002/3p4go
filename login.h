#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtWidgets>
#include <string>

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

    /* SLOT section:
     *
     * inviteClicked():
     * This slot will send the IP addresses that user enter to the processing
     * method in GAME class. Also, for the host, this slot will emit a signal to
     * tell the transfer message window to show
     *
     * exitClick():
     * This slot will close the current login window when triggered.
     *
     * checkScoreClick():
     * This slot will emit a signal to tell the check score window to show.
     *
     * startReceived():
     * This slot will hide the login window if the chess game start
     */
private slots:
    void inviteClicked();
    void exitClick();
    void checkScoreClick();

    /* Signal section:
     *
     * showTransfer():
     * This signal is used together with inviteClicked() slot, trigger the transfer
     * window.
     *
     * showScore():
     * This signal will close the current login window when triggered.
     *
     * checkScoreClick():
     * This slot will emit a signal to tell the check score window to show.
     *
     * startReceived():
     * This slot will hide the login window if the chess game start
     */
signals:
    void showScore();
    void emitInvite(QString p1IP, QString p2IP, QString p1Port, QString p2Port);

private:
    QLineEdit *player1IP;
    QLineEdit *player1Port;
    QLineEdit *player2IP;
    QLineEdit *player2Port;
    QLineEdit *hostIP;

    QLabel *p1ip;
    QLabel *p1port;
    QLabel *p2ip;
    QLabel *p2port;
    QLabel *host;

    QPushButton *invite;
    QPushButton *exit;
    QPushButton *check;

    QHBoxLayout *p1Layout;
    QHBoxLayout *p2Layout;
    QHBoxLayout *hostLayout;
    QHBoxLayout *port1Layout;
    QHBoxLayout *port2Layout;

    QHBoxLayout *p1IPLayout;
    QHBoxLayout *p2IPLayout;
    QHBoxLayout *p1PortLayout;
    QHBoxLayout *p2PortLayout;
    QHBoxLayout *hostIPLayout;

    QHBoxLayout *editorLayout;
    QHBoxLayout *buttonLayout;

    QVBoxLayout *ipLayout;
    QVBoxLayout *portLayout;
    QVBoxLayout *userLayout;
    QVBoxLayout *userPortlayout;
    QVBoxLayout *mainLayout;

};

#endif // MAINWINDOW_H
