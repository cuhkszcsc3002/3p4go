#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtWidgets>
#include <string>

namespace Ui {
class MainWindow;
}

/*/
class QLineEdit;
class QLabel;
class QPushButton;
/*/

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

    //void GetLocalIP(char *ip);

private slots:
    void inviteClicked();
    void exitClick();
    void checkScoreClick();
    void startReceived();

signals:
    void showTransfer();
    void showScore();

private:
    char *ip;
    std::string ipAddress = "";

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
