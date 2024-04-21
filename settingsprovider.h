#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

class settingsprovider : public QObject
{
    Q_OBJECT
public:
    explicit settingsprovider(QObject *parent = nullptr);

signals:

};

#endif // SETTINGSPROVIDER_H
