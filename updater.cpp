// Copyright (C) 2023 Jeremy Nieth

#include "updater.h"
#include "ui_updater.h"
#include <QStringList>

Updater::Updater(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Updater)
{
    ui->setupUi(this);
    setStyle(QStyleFactory::create("Fusion"));
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->textEdit->insertPlainText("### Starting updater...\n");

    process = new QProcess(this);
    process->setWorkingDirectory("/opt/shinygui/updater/compiled");
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(processOutput()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished()));

    //commands.append(QPair<QString, QString>("### Creating temporary update folder...\n", "mkdir /opt/shinygui/temp"));
    //commands.append(QPair<QString, QString>("### Downloading update files...\n",         "wget https://github.com/razorlikes/shinygui/archive/refs/heads/main.zip -O /opt/shinygui/temp/update_temp.zip --limit-rate=1M -nv"));
    //commands.append(QPair<QString, QString>("### Extracting update files...\n",          "unzip -q /opt/shinygui/temp/update_temp.zip -d /opt/shinygui/temp/"));
    //commands.append(QPair<QString, QString>("",                                          "mv /opt/shinygui/temp/shinygui/* /opt/shinygui/temp/"));
    //commands.append(QPair<QString, QString>("",                                          "rmdir /opt/shinygui/temp/shinygui"));
    commands.append(QPair<QString, QString>("### Running qmake...\n",                    "qmake /opt/shinygui/updater/"));
    commands.append(QPair<QString, QString>("### Compiling new files...\n",              "make -j 2"));
    //commands.append(QPair<QString, QString>("### Cleaning up...\n",                      "make -C /opt/shinygui/ clean"));
    //commands.append(QPair<QString, QString>("",                                          "rm /opt/shinygui/Makefile"));
    //commands.append(QPair<QString, QString>("",                                          "rm -rf /opt/shinygui/temp"));
    commands.append(QPair<QString, QString>("### Replacing files...\n",                  "cp -f ./shinygui /opt/shinygui/"));
    commands.append(QPair<QString, QString>("### Restarting GUI...",                     "sudo /etc/init.d/gui restart"));
}

Updater::~Updater()
{
    delete ui;
}

void Updater::processOutput()
{
    ui->textEdit->insertPlainText(process->readAll());
    ui->textEdit->ensureCursorVisible();
}

void Updater::processFinished()
{
    ui->textEdit->insertPlainText(commands[index].first);
    ui->textEdit->ensureCursorVisible();

    if (index + 1 < commands.size())
        process->start(commands[index++].second);
    else if (index + 1 == commands.size())
        process->startDetached(commands[index].second);
}

void Updater::on_pushButton_pressed()
{
    this->close();
}

void Updater::on_pushButton_2_pressed()
{
    processFinished();
}
