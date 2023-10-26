#include "core/score.h"
#include "score.h"

Score::Score()
{
    m_info = new ScoreInfo;
    m_info->maxScore = 0;
    m_info->time = 0;
}

Score::~Score()
{
    m_info = nullptr;
    delete m_info;
}

void Score::writeToJson(int score)
{
#if 1
    // 修改json文件
    QFile file("score.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = file.readAll();
        QJsonObject root = QJsonDocument::fromJson(data).object();
        int maxScore = root["MaxScore"].toInt(); // json文件中的最高分
        int time = root["Time"].toInt();         // json文件中的闯关次数
        if (score >= maxScore)
        {
            root["MaxScore"] = score; // 写入最高分
        }
        root["Time"] = time + 1; // 写入闯关次数
        file.close();

        // 写入json文件
        QJsonDocument doc;
        doc.setObject(root);
        QByteArray byteArray = doc.toJson(QJsonDocument::Indented);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(byteArray);
        file.close();
    }
#endif
}

void Score::readFromJson()
{
    QFile file("score.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();
        m_info->maxScore = root["MaxScore"].toInt();
        m_info->time = root["Time"].toInt();
        file.close();
    }
}

ScoreInfo *Score::getValues()
{
    return m_info;
}
