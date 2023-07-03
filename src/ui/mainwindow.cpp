#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setup();
    ui->statusbar->showMessage("IP-TOOL by @Danofred00");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    ui->setupUi(this);
    // add some widgets
    basicFrame = new BasicFrame;
    advancedFrame = new AdvancedFrame;
    // add frames to tab
    ui->tabWidget->addTab(basicFrame, "Basic");
    ui->tabWidget->addTab(advancedFrame, "Subnet");
    // do connections
    connect(ui->actionExit, &QAction::triggered, [&](){
        QCoreApplication::exit();
    });

    connect(ui->actionAbout_Qt, &QAction::triggered, [&](){
        QApplication::aboutQt();
    });
}