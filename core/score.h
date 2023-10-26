#ifndef SCORE_H
#define SCORE_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

/*
    {
        "MaxSocre" : xxxx,
        "Time" : 1,
    }
*/

// 结构体
struct ScoreInfo
{
    int maxScore;
    int time;
};

class Score
{
public:
    Score();
    ~Score();

    void writeToJson(int score);
    void readFromJson();
    ScoreInfo *getValues();

private:
    ScoreInfo *m_info;
};

#endif // SCORE_H