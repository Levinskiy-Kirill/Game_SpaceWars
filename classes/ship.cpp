#include "ship.h"
#include "constants.h"
#include <QMovie>
#include <QLabel>
#include <QString>

Ship::Ship(QWidget *parent) : QWidget(parent) {
    load();
}

Ship::~Ship() {
    delete animationShip;
    delete labelShip;
}

void Ship::load() {
    setAttribute(Qt::WA_NoSystemBackground);
    animationShip = new QMovie(this);
    labelShip = new QLabel(this);
    labelShip->setMovie(animationShip);
    animationShip->setCacheMode(QMovie::CacheAll);

    resize(WIDTH_SHIP, HEIGHT_SHIP);
    animationShip->setScaledSize(size());
}

void Ship::animation(QString textureName) {
    animationShip->stop();
    animationShip->setFileName(textureName);
    animationShip->jumpToFrame(qrand() % animationShip->frameCount());
    animationShip->start();
}
