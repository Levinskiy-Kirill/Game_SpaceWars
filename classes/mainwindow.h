#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MenuScreen;
class QStackedWidget;
class GameScreen;
class ShopScreen;
class HelpScreen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void pushNewGameButton();
    void pushHelpButton();
    void pushMenuButton();
    void pushShopButton();
    void pushBackToGameButton();

private:
    QStackedWidget *stackWidget;
    MenuScreen *menu;
    GameScreen *game;
    ShopScreen *shop;
    HelpScreen *help;

signals:
    void gameContinuePlay();
    void repairBuy();
    void damageBuy();
    void lifeBuy();
};

#endif // MAINWINDOW_H
