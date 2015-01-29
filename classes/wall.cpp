#include "wall.h"
#include <QPaintEvent>

Wall::Wall(QWidget *parent) : QWidget(parent) {
    name = "Wall";
    fullLife = 100;
    currentLife = fullLife;
    QPixmap *pixWall = new QPixmap(":/images/wall.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(*pixWall));

    setPalette(palette);
    resize(pixWall->size());
    emit lifeChanged(fullLife);
}

Wall::~Wall() {

}

void Wall::setCurrentLife(int damage) {
    currentLife -=damage;
    emit lifeChanged(currentLife);
    if(currentLife <= 0)
        emit endGame();
}

void Wall::repairWall() {
    currentLife = fullLife;
    emit lifeChanged(currentLife);
}

void Wall::addLifeWall() {
    fullLife += 50;
    currentLife = fullLife;
    emit lifeChanged(currentLife);
}
