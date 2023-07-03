#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "basicframe.h"
#include "advancedframe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void setup();

    Ui::MainWindow *ui;
    BasicFrame * basicFrame;
    AdvancedFrame * advancedFrame;
};

#endif // MAINWINDOW_H
