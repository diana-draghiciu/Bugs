#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Buguri.h"

class Buguri : public QMainWindow
{
    Q_OBJECT

public:
    Buguri(QWidget *parent = Q_NULLPTR);

private:
    Ui::BuguriClass ui;
};
