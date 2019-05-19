#ifndef PORT_H
#define PORT_H

#include <QtWidgets>
//#include <QDialog>
//#include <QLabel>

class port : public QWidget
{
    Q_OBJECT

public:
    explicit port(QWidget *parent = nullptr);
   ~port();


private slots:
    void exitClicked();
    void savePortClicked();

signals:
    void emitPort(int port);

private:
    QLineEdit *lineEdit;
    QLabel *message;
    QPushButton *exit;
    QPushButton *save;

    QHBoxLayout *labelLayout;
    QVBoxLayout *lineEditLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};


#endif // PORT_H
