#include "gameScreen.h"
#include "gameWidget.h"
//#include "wall.h"
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "qdebug.h"

GameScreen::GameScreen(QWidget *parent) : QWidget(parent) {
    menuButton = new QPushButton(tr("Меню"));
    shopButton = new QPushButton(tr("Магазин"));
    moneyLabel = new QLabel(tr("Деньги:"));
    moneyLabel->setAlignment(Qt::AlignRight);
    numOfMoney = new QLCDNumber();

    numOfMoney->setSegmentStyle(QLCDNumber::Flat);
    lifeLabel = new QLabel("Жизни:");

    lifeLabel->setAlignment(Qt::AlignRight);
    numOfLife = new QLCDNumber();

    numOfLife->setSegmentStyle(QLCDNumber::Flat);
    gameScene = new GameWidget(this);

    QHBoxLayout *header = new QHBoxLayout();
    header->addWidget(menuButton);
    header->addWidget(shopButton);
    header->addWidget(moneyLabel);
    header->addWidget(numOfMoney);
    header->addWidget(lifeLabel);
    header->addWidget(numOfLife);

    QVBoxLayout *screen = new QVBoxLayout();
    screen->addLayout(header);
    screen->addWidget(gameScene);
    screen->setMargin(0);

    setLayout(screen);

    numOfLife->display(100);

    gameScene->load();

    connect(menuButton, SIGNAL(clicked()), parent, SLOT(pushMenuButton()));
    connect(gameScene, SIGNAL(lifeChanged(int)), numOfLife, SLOT(display(int)));
    connect(gameScene, SIGNAL(moneyChanged(int)), numOfMoney, SLOT(display(int)));
    connect(shopButton, SIGNAL(clicked()), parent, SLOT(pushShopButton()));
    connect(shopButton, SIGNAL(clicked()), gameScene, SLOT(gamePause()));
    connect(parent, SIGNAL(gameContinuePlay()), gameScene, SLOT(gamePlay()));
    connect(parent, SIGNAL(repairBuy()), gameScene, SLOT(repair()));
    connect(parent, SIGNAL(damageBuy()), gameScene, SLOT(addDamage()));
    connect(parent, SIGNAL(lifeBuy()), gameScene, SLOT(addLife()));
}

GameScreen::~GameScreen() {
    delete menuButton;
    delete shopButton;
    delete moneyLabel;
    delete numOfMoney;
    delete lifeLabel;
    delete numOfLife;
    delete gameScene;
}

