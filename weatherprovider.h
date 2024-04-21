// Copyright (C) 2023 Jeremy Nieth

#ifndef WEATHERPROVIDER_H
#define WEATHERPROVIDER_H

#include <QObject>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QPixmap>
#include <QTimer>

class WeatherProvider : public QObject
{
    Q_OBJECT

    typedef struct {
        QString curTemp;
        QString curWeather;
        QString curHigh;
        QString curLow;
        QPixmap curIcon;
    } _weatherShort;

    typedef struct {

    } _weatherDetailed;

public:
    explicit WeatherProvider(QObject *parent = nullptr);

    _weatherShort getWeatherCurrent() const;

    _weatherDetailed getWeather5Days() const;

private:
    QNetworkAccessManager *net;

    QTimer *requestTimer;

    _weatherShort weatherCurrent;
    _weatherDetailed weather5Days;

signals:
    void weatherReady();

private slots:
    void updateWeather();
    void requestFinished(QNetworkReply* apiReply);

};

#endif // WEATHERPROVIDER_H
