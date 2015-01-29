#include "bullet.h"
#include "constants.h"
#include <QPixmap>
#include <QLabel>
#include <QSettings>

#include "qDebug"

int Bullet::levelDamage;

Bullet::Bullet(QString nameBullet, QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_NoSystemBackground);
    QSettings bulletSettings(":/text/bullet.txt", QSettings::IniFormat);
    name = bulletSettings.value(nameBullet + "/name").toString();
    speed = bulletSettings.value(nameBullet + "/speed").toInt();
    speed *= (double)LOGIC_TIMER/1000;
    damage = bulletSettings.value(nameBullet + "/damage").toInt();
    if(nameBullet == "bulletHero")
        damage += levelDamage*5;

    labelBullet = new QLabel(this);
    pixBullet = new QPixmap();
    pixBullet->load(":/images/" + name + ".png");
    labelBullet->setPixmap(*pixBullet);
    resize(pixBullet->width(), pixBullet->height());
}

Bullet::~Bullet() {
    delete labelBullet;
    delete pixBullet;
}

int Bullet::getSpeed() {
    return speed;
}

int Bullet::getDamage() {
    return damage;
}

void Bullet::addLevelDamage() {
    levelDamage++;
}

QString Bullet::getName() {
    return name;
}
