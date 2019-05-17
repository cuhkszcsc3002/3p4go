#ifndef REJECT_H
#define REJECT_H

#include <QtWidgets>
//#include <QDialog>
//#include <QLabel>

class reject : public QDialog
{
    Q_OBJECT

public:
    explicit reject(QWidget *parent = nullptr);
   ~reject();

private slots:
    //void receiveReject();
    void exitClicked();

private:
    QPushButton *exit;
    QLabel *message;
};

#endif // REJECT_H
