// Copyright (C) 2023 Jeremy Nieth

#ifndef EPDCONTROL_H
#define EPDCONTROL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QVector>
#include <QRect>

#ifdef Q_OS_LINUX
#include <sys/ioctl.h>
#include <iostream>
#include <fcntl.h>
#include "include/mxcfb.h"
#include <linux/fb.h>
#include <unistd.h>
#endif

class EPDControl : public QObject
{
    Q_OBJECT
public:
    explicit EPDControl(QObject *parent = nullptr);
    int getBrightness();
    bool getBLStatus();
    QVector<QRect> *updateQueue;
    QTimer *screenRefreshTimer;

private:
    int currentBrightness;
    int lastBrightness;
    QFile* brightnessFile;

public slots:
    void setBrightness(int level);
    void decBrightness();
    void incBrightness();
    void toggleBacklight();
    void queueScreenUpdate(QRect rect);

private slots:
    void updateScreen(QRect rect);
    void refreshScreen();

signals:
    void brightnessChanged(int level);
};

#endif // EPDCONTROL_H
