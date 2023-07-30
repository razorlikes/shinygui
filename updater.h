// Copyright (C) 2023 Jeremy Nieth

#ifndef UPDATER_H
#define UPDATER_H

#include <QFrame>
#include <QProcess>
#include <QStyleFactory>
#include <QString>
#include <QList>
#include <QPair>

namespace Ui {
class Updater;
}

class Updater : public QFrame
{
    Q_OBJECT

public:
    explicit Updater(QWidget *parent = nullptr);
    ~Updater();

private:
    Ui::Updater *ui;
    QProcess *process;
    int index = 0;
    QList<QPair<QString, QString>> commands;


private slots:
    void processOutput();
    void processFinished();
    void on_pushButton_pressed();
    void on_pushButton_2_pressed();
};

#endif // UPDATER_H
