#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <string>
#include <map>

enum class State {
    CLOSE,
    WAITING,
    OPEN
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int currentButton = -1;
    int score = 0;
    int remaining = 50;
    std::vector<std::string> buttons;
    std::map<int, QPushButton*> buttonMap;
    std::vector<State> states;

private slots:
    void click(int button);
    void newGame();
    void changeButton(int button, State state);
};
#endif // MAINWINDOW_H
