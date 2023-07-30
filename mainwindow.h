// Copyright (C) 2023 Jeremy Nieth

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QDateTime>
#include <QString>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QPaintEvent>
#include <QDebug>

#include <epdcontrol.h>
#include <updater.h>
#include <weatherprovider.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent * e);

private:
    Ui::MainWindow *ui;
    QTimer *hourlyTimer;
    QTimer *clockTimer;
    EPDControl *epdControl;
    QRect lastUpdateRect;

    WeatherProvider *prov;

private slots:
    void on_pushButton_pressed();
    void on_pushButton_2_pressed();
    void on_pushButton_3_pressed();
    void on_pushButton_4_pressed();
    void on_pushButton_5_pressed();

    void clockUpdate();
    void on_pushButton_6_pressed();

    void weatherUpdate();
};
#endif // MAINWINDOW_H
