/*
 * File: finish.h
 *
 * This program configurate a window that shows up when one of the three
 * players beats other two players. The window provides two options buttons
 * for the players: restart the game or exit the game. When player clicks
 * the restart button, the window will tell game.cpp to call game initializer.
 * When player clicks the exit button, the window will tell game.cpp to call
 * game terminator.
 *
 */

#ifndef FINISH_H
#define FINISH_H

#include <QtWidgets>

class finish : public QDialog
{
    Q_OBJECT

public:
    explicit finish(QWidget *parent = nullptr);
    ~finish();

private slots:
    //void receiveInvite();
    void exitClicked();
    void restartClicked();

signals:
    void restart();
    void gameEixt();

private:
    QPushButton *again;
    QPushButton *exit;
    QLabel *message;
};

#endif // FINISH_H
