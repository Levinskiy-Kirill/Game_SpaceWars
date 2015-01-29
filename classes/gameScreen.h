#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>

class QPushButton;
class QLCDNumber;
class QLabel;
class GameWidget;
//class Wall;

class GameScreen : public QWidget {
    Q_OBJECT

public:
    GameScreen(QWidget *parent=0);
    ~GameScreen();

private:
    QPushButton *menuButton;
    QPushButton *shopButton;
    QLabel *moneyLabel;
    QLCDNumber *numOfMoney;
    QLabel *lifeLabel;
    QLCDNumber *numOfLife;
    GameWidget *gameScene;

signals:

};

#endif // GAMESCREEN_H
