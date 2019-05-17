#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtWidgets>
#include <string>

namespace Ui {
class MainWindow;
}


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
    void startReceived();

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
    void showTransfer();
    void showScore();
    void emitInvit(QString myIP, QString p1IP, QString p2IP);

private:
    char *ip;
    std::string ipAddress = "";
    QString myIP;

    QLineEdit *player1IP;
    QLineEdit *player2IP;
    QLineEdit *hostIP;

    QLabel *p1;
    QLabel *p2;
    QLabel *host;

    QPushButton *invite;
    QPushButton *exit;
    QPushButton *check;

    QHBoxLayout *p1Layout;
    QHBoxLayout *p2Layout;
    QHBoxLayout *hostLayout;

    QHBoxLayout *p1IPLayout;
    QHBoxLayout *p2IPLayout;
    QHBoxLayout *hostIPLayout;

    QHBoxLayout *editorLayout;
    QHBoxLayout *buttonLayout;

    QVBoxLayout *ipLayout;
    QVBoxLayout *userLayout;
    QVBoxLayout *mainLayout;

};

#endif // MAINWINDOW_H
