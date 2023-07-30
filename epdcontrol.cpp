// Copyright (C) 2023 Jeremy Nieth

#include "epdcontrol.h"
#include <QDebug>

#define BRIGHTNESS_STEP_SIZE 10
#define REFRESH_RATE 30

EPDControl::EPDControl(QObject *parent) : QObject(parent)
{
    brightnessFile = new QFile("/sys/class/backlight/mxc_msp430_fl.0/brightness", this);
    brightnessFile->open(QIODevice::ReadOnly);
    QTextStream instream(brightnessFile);
    currentBrightness = instream.readLine().toInt();
    brightnessFile->close();
    emit brightnessChanged(currentBrightness);

    screenRefreshTimer = new QTimer(this);
    screenRefreshTimer->setInterval(1000 / REFRESH_RATE);
    screenRefreshTimer->setSingleShot(true);
    connect(screenRefreshTimer, SIGNAL(timeout()), this, SLOT(refreshScreen()));

    updateQueue = new QVector<QRect>();
}

void EPDControl::setBrightness(int level)
{
    if (level > 100)
        level = 100;
    else if (level < 0)
        level = 0;

    brightnessFile->open(QIODevice::WriteOnly);
    QTextStream outstream(brightnessFile);
    outstream << level;
    brightnessFile->close();
    currentBrightness = level;
    emit brightnessChanged(level);
}

int EPDControl::getBrightness()
{
    return currentBrightness;
}

bool EPDControl::getBLStatus()
{
    return (bool)currentBrightness;
}

void EPDControl::decBrightness()
{
    setBrightness(currentBrightness - BRIGHTNESS_STEP_SIZE);
}

void EPDControl::incBrightness()
{
    setBrightness(currentBrightness + BRIGHTNESS_STEP_SIZE);
}

void EPDControl::toggleBacklight()
{
    if (currentBrightness != 0)
    {
        lastBrightness = currentBrightness;
        setBrightness(0);
    }
    else if (currentBrightness == 0)
        setBrightness(lastBrightness); 
}

void EPDControl::queueScreenUpdate(QRect rect)
{
    updateQueue->append(rect);
    screenRefreshTimer->start();
}

void EPDControl::refreshScreen()
{
    if (updateQueue->size() > 1)
    {
        QRect temp = updateQueue->takeFirst();

        while (!updateQueue->isEmpty())
            temp = temp.united(updateQueue->takeFirst());

        updateScreen(temp);
    }
    else
        updateScreen(updateQueue->takeFirst());
}

using namespace std;
void EPDControl::updateScreen(QRect rect)
{
    #ifdef Q_OS_LINUX
    mxcfb_update_data update_data = {
        rect.y(), rect.x(), rect.width(), rect.height(),
        WAVEFORM_MODE_AUTO,
    };
    update_data.flags = EPDC_FLAG_FORCE_MONOCHROME;

    int framebuffer = open("/dev/fb0", O_RDWR);
    if (framebuffer != -1)
    {
        ioctl(framebuffer, MXCFB_SET_UPDATE_SCHEME, UPDATE_SCHEME_SNAPSHOT);
        ioctl(framebuffer, MXCFB_SEND_UPDATE, &update_data);
        close(framebuffer);
    }
    #endif

    qDebug("Received coords %dx%d, %dx%d", rect.x(), rect.y(), rect.width(), rect.height());
}
