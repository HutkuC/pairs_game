#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonMap[0] = ui -> pushButton_2;
    buttonMap[1] = ui -> pushButton_3;
    buttonMap[2] = ui -> pushButton_4;
    buttonMap[3] = ui -> pushButton_5;
    buttonMap[4] = ui -> pushButton_6;
    buttonMap[5] = ui -> pushButton_7;
    buttonMap[6] = ui -> pushButton_8;
    buttonMap[7] = ui -> pushButton_9;
    buttonMap[8] = ui -> pushButton_10;
    buttonMap[9] = ui -> pushButton_11;
    buttonMap[10] = ui -> pushButton_12;
    buttonMap[11] = ui -> pushButton_13;
    buttonMap[12] = ui -> pushButton_14;
    buttonMap[13] = ui -> pushButton_15;
    buttonMap[14] = ui -> pushButton_16;
    buttonMap[15] = ui -> pushButton_17;
    buttonMap[16] = ui -> pushButton_18;
    buttonMap[17] = ui -> pushButton_19;
    buttonMap[18] = ui -> pushButton_20;
    buttonMap[19] = ui -> pushButton_21;
    buttonMap[20] = ui -> pushButton_22;
    buttonMap[21] = ui -> pushButton_23;
    buttonMap[22] = ui -> pushButton_24;
    buttonMap[23] = ui -> pushButton_25;
    buttonMap[24] = ui -> pushButton_26;
    buttonMap[25] = ui -> pushButton_27;
    buttonMap[26] = ui -> pushButton_28;
    buttonMap[27] = ui -> pushButton_29;
    buttonMap[28] = ui -> pushButton_30;
    buttonMap[29] = ui -> pushButton_31;
    for (int i = 0; i < 30; i++) {
        connect(buttonMap[i], &QPushButton::clicked, [=](){click(i);});
    }
    newGame();
    connect(ui -> pushButton, &QPushButton::clicked, [=](){click(-1);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click(int button)
{
    if (button == -1) {
        newGame();
    }
}

void MainWindow::newGame()
{
    srand(time(0));
    score = 0;
    remaining = 50;
    buttons.resize(30);
    isOpen.resize(30, false);
    for (int i = 0; i < 15; i++) {
        buttons[2 * i] = buttons[2 * i + 1] = std::to_string(i);
    }
    for (int i = 0; i < 30; i++) {
        int j = rand() % 30;
        std::swap(buttons[i], buttons[j]);
    }
    for (int i = 0; i < 30; i++) {
        buttonMap[i] -> setText(QString::fromStdString(buttons[i]));
        buttonMap[i] -> setEnabled(true);
    }
}



