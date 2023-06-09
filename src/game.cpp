#include "game.h"
#include "ui_game.h"
#include <iostream>
#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>
#include <QtTest/QtTest>

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Pairs");
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

Game::~Game()
{
    delete ui;
}

void Game::click(int button)
{
    if (button == -1) { // New Game button
        newGame();
        return;
    }
    if (states[button] != State::CLOSE) { // If the card is already open
        return;
    }
    if (currentButton == -1) { // If there are no open card
        currentButton = button;
        changeButton(button, State::WAITING);
        return;
    }
    else {
        if (buttons[currentButton] == buttons[button]) { // If the two cards match
            changeButton(button, State::OPEN);
            changeButton(currentButton, State::OPEN);
            score += 1;
            remaining -= 1;
            ui -> label -> setText("Score: " + QString::number(score));
            ui -> label_2 -> setText("Remaining: " + QString::number(remaining));
            if (score == 15) {
                ui -> label -> setText("Score: " + QString::number(score));
                ui -> label_2 -> setText("You Win");
                lockAllButtons();
                ui -> pushButton -> blockSignals(false);
                return;
            }
        } else { // If they do not match
            changeButton(button, State::WAITING);
            remaining -= 1;
            ui -> label -> setText("Score: " + QString::number(score));
            ui -> label_2 -> setText("Remaining: " + QString::number(remaining));
            lockAllButtons();
            QTest::qWait(1000);
            unlockAllButtons();
            changeButton(button, State::CLOSE);
            changeButton(currentButton, State::CLOSE);
            if (remaining < 15 - score) { // If the player has remaining moves less than close cards, game over
                ui -> label -> setText("Score: " + QString::number(score));
                ui -> label_2 -> setText("Game Over");
                setAllButtonsFail();
                lockAllButtons();
                ui -> pushButton -> blockSignals(false);
                return;
            }
        }
        currentButton = -1;
    }
}

void Game::newGame()
{
    srand(time(0));
    score = 0;
    remaining = 50;
    currentButton = -1;
    ui -> label -> setText("Score: " + QString::number(score));
    ui -> label_2 -> setText("Remaining: " + QString::number(remaining));
    buttons.resize(30);
    states.resize(30, State::CLOSE);
    std::vector<std::string> words = {
        "apple",
        "banana",
        "orange",
        "watermelon",
        "pear",
        "grape",
        "pineapple",
        "strawberry",
        "cherry",
        "mango",
        "lemon",
        "coconut",
        "pomegranate",
        "blueberry",
        "raspberry"
    };
    for (int i = 0; i < 15; i++) {
        buttons[2 * i] = buttons[2 * i + 1] = words[i];
    }
    for (int i = 0; i < 30; i++) { // Shuffle cards
        int j = rand() % 30;
        std::swap(buttons[i], buttons[j]);
    }
    for (int i = 0; i < 30; i++) {
        changeButton(i, State::CLOSE);
    }
    unlockAllButtons();
}

void Game::changeButton(int button, State state)
{
    states[button] = state;
    if (state == State::CLOSE) {
        buttonMap[button] -> setText("");
        buttonMap[button] -> setEnabled(true);
        buttonMap[button] -> setStyleSheet("background-color: rgb(131, 131, 131); border: none;");
    } else if (state == State::WAITING) {
        buttonMap[button] -> setText(QString::fromStdString(buttons[button]));
        buttonMap[button] -> setEnabled(false);
        buttonMap[button] -> setStyleSheet("background-color: rgb(200, 200, 0); border: none; color: black;");
    } else if (state == State::OPEN) {
        buttonMap[button] -> setText(QString::fromStdString(buttons[button]));
        buttonMap[button] -> setEnabled(false);
        buttonMap[button] -> setStyleSheet("background-color: rgb(0, 200, 0); border: none; color: black;");
    } else if (state == State::FAIL) {
        buttonMap[button] -> setText(QString::fromStdString(buttons[button]));
        buttonMap[button] -> setEnabled(false);
        buttonMap[button] -> setStyleSheet("background-color: rgb(200, 0, 0); border: none; color: black;");
    }
}

void Game::lockAllButtons() // The player should be not able to click buttons sometimes
{
    ui -> pushButton -> blockSignals(true);
    for (int i = 0; i < 30; i++) {
        buttonMap[i] -> blockSignals(true);
    }
}

void Game::unlockAllButtons()
{
    ui -> pushButton -> blockSignals(false);
    for (int i = 0; i < 30; i++) {
        buttonMap[i] -> blockSignals(false);
    }
}

void Game::setAllButtonsFail()
{
    for (int i = 0; i < 30; i++) {
        changeButton(i, State::FAIL);
    }
}
