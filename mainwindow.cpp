// Copyright (C) 2023 Jeremy Nieth

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "updater.h"
#include "weatherprovider.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clockUpdate();
    setStyle(QStyleFactory::create("Fusion"));
    setAttribute(Qt::WA_AcceptTouchEvents);

    clockTimer = new QTimer(this);
    clockTimer->setInterval(1000);
    clockTimer->start();
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockUpdate()));

    hourlyTimer = new QTimer(this);
    hourlyTimer->setInterval(3600000);
    hourlyTimer->start();
    connect(hourlyTimer, SIGNAL(timeout()), this, SLOT(eink_full_update()));

    epdControl = new EPDControl(this);
    connect(epdControl, SIGNAL(brightnessChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(ui->btnBLightMinus, SIGNAL(pressed()), epdControl, SLOT(decBrightness()));
    connect(ui->btnBLightPlus, SIGNAL(pressed()), epdControl, SLOT(incBrightness()));
    connect(ui->btnBLightToggle, SIGNAL(pressed()), epdControl, SLOT(toggleBacklight()));

    ui->label_6->setAttribute(Qt::WA_TranslucentBackground);

    prov = new WeatherProvider();
    connect(prov, SIGNAL(weatherReady()), this, SLOT(weatherUpdate()));

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    static int i = 0;
    qDebug("paintEvent no %d at rect %dx%d, %dx%d", i++, e->rect().topLeft().x(), e->rect().topLeft().y(), e->rect().width(), e->rect().height());
    epdControl->queueScreenUpdate(e->rect());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clockUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    ui->lblClock->setText(time.toString("HH"));
    ui->lblClock_2->setText(time.toString("mm"));
    ui->lblDate->setText(time.toString("dddd, dd.MM.yyyy"));
}

void MainWindow::weatherUpdate()
{
    ui->label_6->setPixmap(prov->getWeatherCurrent().curIcon);
    ui->label_7->setText(prov->getWeatherCurrent().curTemp + " °C\n" + prov->getWeatherCurrent().curWeather);
    ui->label_8->setText("˄ " + prov->getWeatherCurrent().curHigh + "°C\n˅ " + prov->getWeatherCurrent().curLow + "°C");
}

void MainWindow::on_pushButton_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("QPushButton {border-width: 14px;}");
    ui->pushButton_2->setStyleSheet("QPushButton {border-width: 7px;}");
    ui->pushButton_3->setStyleSheet("QPushButton {border-width: 7px;}");
    ui->pushButton_4->setStyleSheet("QPushButton {border-width: 7px;}");
    ui->pushButton_5->setStyleSheet("QPushButton {border-width: 7px;}");
}

void MainWindow::on_pushButton_2_pressed()
{
     ui->stackedWidget->setCurrentIndex(1);
     ui->pushButton->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_2->setStyleSheet("QPushButton {border-width: 14px;}");
     ui->pushButton_3->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_4->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_5->setStyleSheet("QPushButton {border-width: 7px;}");
}

void MainWindow::on_pushButton_3_pressed()
{
     ui->stackedWidget->setCurrentIndex(2);
     ui->pushButton->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_2->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_3->setStyleSheet("QPushButton {border-width: 14px;}");
     ui->pushButton_4->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_5->setStyleSheet("QPushButton {border-width: 7px;}");
}

void MainWindow::on_pushButton_4_pressed()
{
     ui->stackedWidget->setCurrentIndex(3);
     ui->pushButton->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_2->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_3->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_4->setStyleSheet("QPushButton {border-width: 14px;}");
     ui->pushButton_5->setStyleSheet("QPushButton {border-width: 7px;}");
}

void MainWindow::on_pushButton_5_pressed()
{
     ui->stackedWidget->setCurrentIndex(4);
     ui->pushButton->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_2->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_3->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_4->setStyleSheet("QPushButton {border-width: 7px;}");
     ui->pushButton_5->setStyleSheet("QPushButton {border-width: 14px;}");
}

void MainWindow::on_pushButton_6_pressed()
{
    Updater *updater = new Updater(this);
    updater->move(50, 100);
    updater->show();
}
