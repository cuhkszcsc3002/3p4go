#ifndef SCORE_H
#define SCORE_H

#include <QtWidgets>

class score : public QDialog
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = nullptr);
    ~score();

    void readScore();
    QString getWin();
    QString getLose();
    QString getTotalScore();
    void setWin(int w);
    void setLose(int l);
    void setTotalScore(int t);

private slots:
    void backClicked();
    void checkReceived();

signals:
    //void ComfirmReceived();

private:
    int win;
    int lose;
    int totalScore;

    QPushButton *back;

};

#endif // SCORE_H
