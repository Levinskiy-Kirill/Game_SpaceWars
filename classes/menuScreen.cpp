#include "menuScreen.h"
#include <QPushButton>

MenuScreen::MenuScreen(QWidget *parent) : QWidget(parent) {
    newGameButton = new QPushButton(tr("Новая игра"), this);
    helpButton = new QPushButton(tr("Помощь"), this);
    exitButton = new QPushButton(tr("Выход"), this);

    newGameButton->setGeometry(608, 450, 150, 40);
    helpButton->setGeometry(608, 500, 150, 40);
    exitButton->setGeometry(608, 550, 150, 40);

    QPalette pal;
    pal.setBrush(this->backgroundRole(), QBrush(QPixmap(":/images/backgroundMenu.jpg")));
    setAutoFillBackground(true);
    setPalette(pal);

    connect(newGameButton, SIGNAL(clicked()), parent, SLOT(pushNewGameButton()));
    connect(helpButton, SIGNAL(clicked()), parent, SLOT(pushHelpButton()));
    connect(exitButton, SIGNAL(clicked()), parent, SLOT(close()));
}

MenuScreen::~MenuScreen() {
    delete newGameButton;
    delete helpButton;
    delete exitButton;
}
