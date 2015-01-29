#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QWidget>

class QPushButton;

class MenuScreen : public QWidget {
    Q_OBJECT

public:
    MenuScreen(QWidget *parent=0);
    ~MenuScreen();

private:
    QPushButton *newGameButton;
    QPushButton *helpButton;
    QPushButton *exitButton;
};

#endif // MENUSCREEN_H
