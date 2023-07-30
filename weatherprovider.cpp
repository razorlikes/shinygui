// Copyright (C) 2023 Jeremy Nieth

#include "weatherprovider.h"

#include <QDebug>

#define OWM_LINK "http://api.openweathermap.org/data/2.5/onecall?lat=50.3569&lon=7.5890&appid=07312a06b36faeafee340310f879d749&units=metric&exclude=minutely,hourly,alerts&lang=de"
#define UPDATE_INTERVAL 300000

WeatherProvider::WeatherProvider(QObject *parent)
    : QObject{parent}
{
    mngr = new QNetworkAccessManager(this);
    mngr->get(QNetworkRequest(QUrl(OWM_LINK)));

    connect(mngr, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

    requestTimer = new QTimer(this);
    requestTimer->setInterval(UPDATE_INTERVAL);
    requestTimer->start();
    connect(requestTimer, SIGNAL(timeout()), this, SLOT(updateWeather()));
}

void WeatherProvider::updateWeather()
{
    qDebug() << "updateWeather called";
    mngr->get(QNetworkRequest(QUrl(OWM_LINK)));
}

void WeatherProvider::requestFinished(QNetworkReply *apiReply)
{
    qDebug() << "requestFinished called";
    QJsonDocument replyJSON = QJsonDocument::fromJson(apiReply->readAll());

    weatherCurrent.curTemp = QString::number(replyJSON.object()["current"].toObject()["temp"].toDouble());
    weatherCurrent.curWeather = replyJSON.object()["current"].toObject()["weather"].toArray().at(0).toObject()["description"].toString();
    weatherCurrent.curHigh = QString::number(replyJSON.object()["daily"].toArray().at(0).toObject()["temp"].toObject()["max"].toDouble());
    weatherCurrent.curLow = QString::number(replyJSON.object()["daily"].toArray().at(0).toObject()["temp"].toObject()["min"].toDouble());

    switch (replyJSON.object()["current"].toObject()["weather"].toArray().at(0).toObject()["icon"].toString().first(2).toInt()) {
    case 1:
        weatherCurrent.curIcon = QPixmap("icons/weather/01d.png");
        break;
    case 2:
        weatherCurrent.curIcon =  QPixmap("icons/weather/02d.png");
        break;
    case 3:
        weatherCurrent.curIcon =  QPixmap("icons/weather/03d.png");
        break;
    case 4:
        weatherCurrent.curIcon =  QPixmap("icons/weather/04d.png");
        break;
    case 9:
        weatherCurrent.curIcon =  QPixmap("icons/weather/09d.png");
        break;
    case 10:
        weatherCurrent.curIcon =  QPixmap("icons/weather/10d.png");
        break;
    case 11:
        weatherCurrent.curIcon =  QPixmap("icons/weather/11d.png");
        break;
    case 13:
        weatherCurrent.curIcon =  QPixmap("icons/weather/13d.png");
        break;
    case 50:
        weatherCurrent.curIcon =  QPixmap("icons/weather/50d.png");
        break;
    default:
        weatherCurrent.curIcon =  QPixmap("icons/weather/01d.png");
        break;
    }

    emit weatherReady();
}

WeatherProvider::_weatherShort WeatherProvider::getWeatherCurrent() const
{
    return weatherCurrent;
}

WeatherProvider::_weatherDetailed WeatherProvider::getWeather5Days() const
{
    return weather5Days;
}
