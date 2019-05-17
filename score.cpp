#include "score.h"
//#include <QtWidgets>
#include <fstream>
#include <string>

#define FILENAME "F:\\3P4Go_Score.txt"

using namespace std;

score::score(QWidget *parent) : QDialog (parent)
{
    //
    setWin(2);
    setLose(55);
    setTotalScore(-12);
    //
    readScore();
    this->resize(QSize(300,100));

    back = new QPushButton("Back (Alt+&b)");

    QLabel *WinShow = new QLabel(tr("Wins: "));
    QLabel *LoseShow = new QLabel(tr("Lose: "));
    QLabel *TotalShow = new QLabel(tr("Total Socre: "));

    QLabel *WinSocre = new QLabel(getWin());
    QLabel *LoseScore = new QLabel(getLose());
    QLabel *TotalScore = new QLabel(getTotalScore());

    QHBoxLayout *Win = new QHBoxLayout();
    QHBoxLayout *Lose = new QHBoxLayout();
    QHBoxLayout *Total = new QHBoxLayout();
    QHBoxLayout *Button = new QHBoxLayout();

    QVBoxLayout *MainLayout = new QVBoxLayout();

    Win->addStretch();
    Win->addWidget(WinShow);
    Win->addWidget(WinSocre);
    Win->addStretch();
    Lose->addStretch();
    Lose->addWidget(LoseShow);
    Lose->addWidget(LoseScore);
    Lose->addStretch();
    Total->addStretch();
    Total->addWidget(TotalShow);
    Total->addWidget(TotalScore);
    Total->addStretch();
    Button->addStretch();
    Button->addWidget(back);
    Button->addStretch();

    MainLayout->addLayout(Win);
    MainLayout->addLayout(Lose);
    MainLayout->addLayout(Total);
    MainLayout->addLayout(Button);

    connect(back, SIGNAL(clicked()), this, SLOT(backClicked()));

    setLayout(MainLayout);
    setWindowTitle(tr("Checking score..."));
}

score::~score()
{}

void score::readScore()
{
    fstream file;
    string line, score;
    file.open(FILENAME, ios::in);

    if(!file)
    {
        file.open(FILENAME, ios::out);      //initialize the score record
        if(file.is_open())
        {
             file << "w 0\n";     //win
             file << "l 0\n";     //lose
             file << "t 0\n";     //total

             win = 0;
             lose = 0;
             totalScore = 0;
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
            case 'l':
                lose = stoi(score);
                break;
            case 't':
                totalScore = stoi(score);
                break;
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
             outFile << "l 0\n";            //lose
             outFile << "t 0\n";            //total
             outFile.close();

             win = w;
             lose = 0;
             totalScore = 0;
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
             outFile << "l " << l << "\n";  //lose
             outFile << "t 0\n";            //total
             outFile.close();

             win = 0;
             lose = l;
             totalScore = 0;
        }
    }
    else
    {
        int i=0;

        while(getline(inFile, line))
        {
            if(i == 1)
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
             outFile << "l 0\n";            //lose
             outFile << "t " << t << "\n";  //total
             outFile.close();

             win = 0;
             lose = 0;
             totalScore = t;
        }
    }
    else
    {
        int i=0;

        while(getline(inFile, line))
        {
            if(i == 2)
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

void score::backClicked()
{
    this->close();
}

void score::checkReceived()
{
    this->show();
}

