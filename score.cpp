#include "score.h"
//#include <QtWidgets>
#include <fstream>
#include <string>

#define FILENAME "C:/3P4Go_Score.txt"

using namespace std;

score::score(QWidget *parent) : QDialog (parent)
{
    qDebug()<<"score.score: constructing score class...";
    setWin(2);
    setLose(55);
    setTotalScore(-12);
    //
    readScore();
    this->resize(QSize(300,100));

    back = new QPushButton("Back (Alt+&b)");

    WinShow = new QLabel(tr("Wins: "));
    DrawShow = new QLabel(tr("Draw: "));
    LoseShow = new QLabel(tr("Lose: "));
    TotalShow = new QLabel(tr("Total Socre: "));
    TotalPlay = new QLabel(tr("Total Play: "));

    WinSocre = new QLabel(getWin());
    DrawScore = new QLabel(getDraw());
    LoseScore = new QLabel(getLose());
    TotalScore = new QLabel(getTotalScore());
    PlayTime = new QLabel(getTotalPlay());

    Win = new QHBoxLayout();
    Draw = new QHBoxLayout();
    Lose = new QHBoxLayout();
    Total = new QHBoxLayout();
    Play = new QHBoxLayout();
    Button = new QHBoxLayout();

    MainLayout = new QVBoxLayout();

    Win->addStretch();
    Win->addWidget(WinShow);
    Win->addWidget(WinSocre);
    Win->addStretch();
    Draw->addStretch();
    Draw->addWidget(DrawShow);
    Draw->addWidget(DrawScore);
    Draw->addStretch();
    Lose->addStretch();
    Lose->addWidget(LoseShow);
    Lose->addWidget(LoseScore);
    Lose->addStretch();
    Total->addStretch();
    Total->addWidget(TotalShow);
    Total->addWidget(TotalScore);
    Total->addStretch();
    Play->addStretch();
    Play->addWidget(TotalPlay);
    Play->addWidget(PlayTime);
    Play->addStretch();
    Button->addStretch();
    Button->addWidget(back);
    Button->addStretch();

    MainLayout->addLayout(Win);
    MainLayout->addLayout(Draw);
    MainLayout->addLayout(Lose);
    MainLayout->addLayout(Total);
    MainLayout->addLayout(Play);
    MainLayout->addLayout(Button);

    connect(back, SIGNAL(clicked()), this, SLOT(backClicked()));

    setLayout(MainLayout);
    setWindowTitle(tr("Checking score..."));
}

score::~score()
{
    delete back;    delete WinShow;     delete LoseShow;    delete TotalShow;
    delete WinSocre;delete LoseScore;   delete TotalScore;  delete Win;
    delete Lose;    delete Total;       delete Button;      delete MainLayout;
    delete DrawShow;delete TotalPlay;   delete DrawScore;   delete PlayTime;
    delete Draw;    delete Play;
}

void score::readScore()
{
    fstream file;
    string line, score;
    file.open(FILENAME, ios::in);

    /* If user play this game first time */
    if(!file)
    {
        file.open(FILENAME, ios::out);      //initialize the score record
        if(file.is_open())
        {
             file << "w 0\n";     //win
             file << "d 0\n";     //draw
             file << "l 0\n";     //lose
             file << "t 0\n";     //totalScore
             file << "p 0\n";     //totalPlay

             win = 0;
             draw = 0;
             lose = 0;
             totalScore = 0;
             totalPlay = 1;
        }
    }
    else
    {
        while(getline(file, line))
        {
            char Fchar = line[0];
            score = line.substr(2, line.length());
            switch (Fchar)
            {
            case 'w':
                win = stoi(score);
                break;
            case 'd':
                draw = stoi(score);
                break;
            case 'l':
                lose = stoi(score);
                break;
            case 't':
                totalScore = stoi(score);
                break;
            case 'p':
                totalPlay = stoi(score);
            }
        }
    }
    file.close();
}

QString score::getWin()
{
    QString str = QString::number(win);
    return str;
}

QString score::getDraw()
{
    QString str = QString::number(draw);
    return str;
}

QString score::getLose()
{
    QString str = QString::number(lose);
    return str;
}

QString score::getTotalScore()
{
    QString str = QString::number(totalScore);
    return str;
}

QString score::getTotalPlay()
{
    QString str = QString::number(totalPlay);
    return str;
}


void score::setWin(int w)
{
    ifstream inFile;
    ofstream outFile;
    string tempStr, line;

    inFile.open(FILENAME, ios::in);
    if(!inFile)
    {
        outFile.open(FILENAME, ios::out);      //if the file is not exist, create a new file
        if(outFile.is_open())
        {
             outFile << "w " << w << "\n";  //win
             outFile << "d 0\n";            //draw
             outFile << "l 0\n";            //lose
             outFile << "t 0\n";            //total
             outFile << "p 0\n";            //play
             outFile.close();

             win = w;
             draw = 0;
             lose = 0;
             totalScore = 0;
             totalPlay = 0;
        }
    }
    else
    {
        int i=0;
        while(getline(inFile, line))
        {
            if(i == 0)
                tempStr = tempStr + string("w ") + to_string(w) + string("\n");
            else
                tempStr = tempStr + line + string("\n");
            i++;
        }
        inFile.close();

        outFile.open(FILENAME, ios::out);
        outFile<<tempStr;
        outFile.close();
    }
}

void score::setDraw(int d)
{
    ifstream inFile;
    ofstream outFile;
    string tempStr, line;

    inFile.open(FILENAME, ios::in);
    if(!inFile)
    {
        outFile.open(FILENAME, ios::out);      //if the file is not exist, create a new file
        if(outFile.is_open())
        {
             outFile << "w 0\n";            //lose
             outFile << "d " << d << "\n";  //win
             outFile << "l 0\n";            //lose
             outFile << "t 0\n";            //total
             outFile << "p 0\n";
             outFile.close();

             win = 0;
             draw = d;
             lose = 0;
             totalScore = 0;
             totalPlay = 0;
        }
    }
    else
    {
        int i=0;
        while(getline(inFile, line))
        {
            if(i == 1)
                tempStr = tempStr + string("d ") + to_string(d) + string("\n");
            else
                tempStr = tempStr + line + string("\n");
            i++;
        }
        inFile.close();

        outFile.open(FILENAME, ios::out);
        outFile<<tempStr;
        outFile.close();
    }
}

void score::setLose(int l)
{
    ifstream inFile;
    ofstream outFile;
    string tempStr, line;

    inFile.open(FILENAME, ios::in);
    if(!inFile)
    {
        outFile.open(FILENAME, ios::out);      //if the file is not exist, create a new file
        if(outFile.is_open())
        {
             outFile << "w 0\n";            //win
             outFile << "d 0\n";            //draw
             outFile << "l " << l << "\n";  //lose
             outFile << "t 0\n";            //total
             outFile << "p 0\n";            //play
             outFile.close();

             win = 0;
             draw = 0;
             lose = l;
             totalScore = 0;
             totalPlay = 0;
        }
    }
    else
    {
        int i=0;
        while(getline(inFile, line))
        {
            if(i == 2)
                tempStr = tempStr + string("l ") + to_string(l) + string("\n");
            else
                tempStr = tempStr + line + string("\n");
            i++;
        }
        inFile.close();

        outFile.open(FILENAME, ios::out);
        outFile<<tempStr;
        outFile.close();
    }
}

void score::setTotalScore(int t)
{
    ifstream inFile;
    ofstream outFile;
    string tempStr, line;

    inFile.open(FILENAME, ios::in);
    if(!inFile)
    {
        outFile.open(FILENAME, ios::out);      //if the file is not exist, create a new file
        if(outFile.is_open())
        {
             outFile << "w 0\n";            //win
             outFile << "d 0\n";            //draw
             outFile << "l 0\n";            //lose
             outFile << "t " << t << "\n";  //total
             outFile << "p 0\n";
             outFile.close();

             win = 0;
             draw = 0;
             lose = 0;
             totalScore = t;
             totalPlay = 0;
        }
    }
    else
    {
        int i=0;
        while(getline(inFile, line))
        {
            if(i == 3)
                tempStr = tempStr + string("t ") + to_string(t) + string("\n");
            else
                tempStr = tempStr + line + string("\n");
            i++;
        }
        inFile.close();

        outFile.open(FILENAME, ios::out);
        outFile<<tempStr;
        outFile.close();
    }
}

void score::setTotalPlay(int p)
{
    ifstream inFile;
    ofstream outFile;
    string tempStr, line;

    inFile.open(FILENAME, ios::in);
    if(!inFile)
    {
        outFile.open(FILENAME, ios::out);      //if the file is not exist, create a new file
        if(outFile.is_open())
        {
             outFile << "w 0\n";            //win
             outFile << "d 0\n";            //draw
             outFile << "l 0\n";            //lose
             outFile << "t 0\n";            //total
             outFile << "p " << p << "\n";  //play
             outFile.close();

             win = 0;
             draw = 0;
             lose = 0;
             totalScore = 0;
             totalPlay = p;
        }
    }
    else
    {
        int i=0;
        while(getline(inFile, line))
        {
            if(i == 4)
                tempStr = tempStr + string("p ") + to_string(p) + string("\n");
            else
                tempStr = tempStr + line + string("\n");
            i++;
        }
        inFile.close();

        outFile.open(FILENAME, ios::out);
        outFile<<tempStr;
        outFile.close();
    }
}

void score::backClicked()
{
    this->close();
}

void score::checkReceived()
{
    this->show();
}

