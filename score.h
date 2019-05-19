#ifndef SCORE_H
#define SCORE_H

#include <QtWidgets>

class score : public QDialog
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = nullptr);
    ~score();

    int win;
    int lose;
    int draw;
    int totalScore;
    int totalPlay;

    void readScore();
    QString getWin();
    QString getDraw();
    QString getLose();
    QString getTotalScore();
    QString getTotalPlay();
    void setWin(int w);
    void setDraw(int d);
    void setLose(int l);
    void setTotalScore(int t);
    void setTotalPlay(int p);

private slots:
    void backClicked();
    void checkReceived();

signals:
    //void ComfirmReceived();

private:
    QPushButton *back;
    QLabel *WinShow;
    QLabel *DrawShow;
    QLabel *LoseShow;
    QLabel *TotalShow;
    QLabel *TotalPlay;

    QLabel *WinSocre;
    QLabel *DrawScore;
    QLabel *LoseScore;
    QLabel *TotalScore;
    QLabel *PlayTime;

    QHBoxLayout *Win;
    QHBoxLayout *Draw;
    QHBoxLayout *Lose;
    QHBoxLayout *Total;
    QHBoxLayout *Play;
    QHBoxLayout *Button;

    QVBoxLayout *MainLayout;

};

#endif // SCORE_H
