#include "shopScreen.h"
#include <QPushButton>
#include <QLabel>

ShopScreen::ShopScreen(QWidget *parent) : QWidget(parent) {
    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(Qt::gray));
    setAutoFillBackground(true);
    setPalette(pal);

    setStyleSheet("QLabel {"
                  "  padding: 0;"
                  "}");

    repair = new QPushButton(tr("Чинить"), this);
    addDamage = new QPushButton(tr("Увеличить урон +5"), this);
    addLife = new QPushButton(tr("Увеличить прочность +50"), this);
    backToGame = new QPushButton(tr("Назад"), this);
    costRepair = new QLabel(tr("Цена: 500"), this);
    costRepair->setAlignment(Qt::AlignCenter);

    costDamage = new QLabel(tr("Цена: 2000"), this);
    costDamage->setAlignment(Qt::AlignCenter);

    costLife = new QLabel(tr("Цена: 3000"), this);
    costLife->setAlignment(Qt::AlignCenter);

    repair->setGeometry(483, 200, 250, 40);
    costRepair->setGeometry(783, 200, 100, 40);

    addDamage->setGeometry(483, 300, 250, 40);
    costDamage->setGeometry(783, 300, 100, 40);

    addLife->setGeometry(483, 400, 250, 40);
    costLife->setGeometry(783, 400, 100, 40);
    backToGame->setGeometry(1100, 650, 150, 40);

    connect(backToGame, SIGNAL(clicked()), parent, SLOT(pushBackToGameButton()));
    connect(repair, SIGNAL(clicked()), parent, SIGNAL(repairBuy()));
    connect(addDamage, SIGNAL(clicked()), parent, SIGNAL(damageBuy()));
    connect(addLife, SIGNAL(clicked()), parent, SIGNAL(lifeBuy()));
}

ShopScreen::~ShopScreen() {
    delete repair;
    delete addDamage;
    delete addLife;
    delete backToGame;
    delete costRepair;
    delete costDamage;
    delete costLife;
}
