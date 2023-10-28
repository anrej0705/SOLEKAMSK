#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_main_app.h"

class main_app : public QMainWindow
{
    Q_OBJECT

public:
    main_app(QWidget *parent = nullptr);
    ~main_app();

private:
    Ui::main_appClass ui;
};
