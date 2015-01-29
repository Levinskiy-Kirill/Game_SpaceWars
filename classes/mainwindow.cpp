#include "mainwindow.h"
#include "menuScreen.h"
#include "gameScreen.h"
#include "helpScreen.h"
#include "constants.h"
#include "shopScreen.h"
#include <QStackedWidget>
#include <QSettings>

#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(WIDTH_SCREEN, HEIGHT_SCREEN);
    setWindowFlags(Qt::FramelessWindowHint);
    stackWidget = new QStackedWidget(this);
    menu = new MenuScreen(this);
    game = new GameScreen(this);
    shop = new ShopScreen(this);
    help = new HelpScreen(this);

    stackWidget->addWidget(menu);
    stackWidget->addWidget(game);
    stackWidget->addWidget(shop);
    stackWidget->addWidget(help);
    stackWidget->setCurrentWidget(menu);
    setCentralWidget(stackWidget);

    setStyleSheet(
              "QPushButton { "
              "  background-color: rgba(255, 153, 102, 200); "
              "  border-style: outset;"
              "  border-width: 2px;"
              "  border-radius: 10px;"
              "  border-color: rgba(176, 196, 222, 255);"
              "  font: bold 14px;"
              "  width: 3em;"
              "}"
              "QPushButton:hover {"
                "background-color: rgba(255, 102, 0, 200);"
              "}"
              "QPushButton:pressed {"
                "background-color: rgba(255, 0, 0, 200);"
              "}"
              "QLabel {"
                "background-color: rgba(102, 204, 102, 200);"
                "  border-style: outset;"
                "  border-width: 0px;"
                "  border-radius: 10px;"
                "  width: 3em;"
                "  padding-right: 20px;"
                "  font: bold 14px"
              "}"
              "QLCDNumber {"
                "background-color: rgba(255, 153, 102, 200);"
              "}"
              "QLayout {"
                "background-color: rgba(176, 196, 222, 255);"
              "}"
    );
}

MainWindow::~MainWindow()
{
    if(menu)
        delete menu;
    if(game)
        delete game;
    if(shop)
        delete shop;
    if(help)
        delete help;
    if(stackWidget)
        delete stackWidget;
}

void MainWindow::pushNewGameButton() {
    if(game) {
        stackWidget->removeWidget(game);
        delete game;
    }
    game = new GameScreen(this);
    stackWidget->addWidget(game);
    stackWidget->setCurrentWidget(game);

}

void MainWindow::pushHelpButton() {
    stackWidget->setCurrentWidget(help);
}

void MainWindow::pushMenuButton() {
    stackWidget->setCurrentWidget(menu);
}

void MainWindow::pushShopButton() {
    stackWidget->setCurrentWidget(shop);
}

void MainWindow::pushBackToGameButton() {
    stackWidget->setCurrentWidget(game);
    emit gameContinuePlay();
}
