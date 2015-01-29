#include "enemy.h"
#include "constants.h"
#include <QLineEdit>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QSettings>
#include <QTimer>
#include "qDebug"

Enemy::Enemy(QString nameEnemy, QWidget *parent) : Ship(parent) {

    QSettings enemySettings(":/text/enemies.txt", QSettings::IniFormat);
    name = enemySettings.value(nameEnemy + "/name").toString();
    fullLife = enemySettings.value(nameEnemy + "/fullLife").toInt();
    currentLife = fullLife;
    damage = enemySettings.value(nameEnemy + "/damage").toInt();
    speed = enemySettings.value(nameEnemy + "/speed").toInt();
    speed *= (double)LOGIC_TIMER/1000;
    cost = enemySettings.value(nameEnemy + "/cost").toInt();

    shootTimer = new QTimer(this);
    lifeEdit = new QLabel(this);
    lifeEdit = new QLabel(this);
    lifeEdit->setText(QString::number((currentLife*100)/fullLife) + "%");
    lifeEdit->setAlignment(Qt::AlignCenter);
    lifeEdit->setStyleSheet("font: bold 14px;"
                            "color: green");

    //resize(500, 500);
    QVBoxLayout *layoutShip = new QVBoxLayout;

    layoutShip->addWidget(lifeEdit);
    layoutShip->addWidget(labelShip);

    setLayout(layoutShip);
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(enemyShoot()));
}

Enemy::~Enemy() {
    delete lifeEdit;
    delete shootTimer;
}

void Enemy::setCurrentLife(int bulletDamage) {
    currentLife -= bulletDamage;
    lifeEdit->setText(QString::number((currentLife*100)/fullLife) + "%");
}

int Enemy::getDamage() {
    return damage;
}

int Enemy::getCurrentLife() {
    return currentLife;
}

int Enemy::getSpeed() {
    return speed;
}

int Enemy::getCost() {
    return cost;
}

QString Enemy::getName() {
    return name;
}

void Enemy::enemyStartShoot() {
    if(!shootTimer->isActive())
        shootTimer->start(2000);
}

void Enemy::enemyShoot() {
    emit shoot(name, pos(), size());
}

void Enemy::enemyPauseShoot() {
    if(shootTimer->isActive())
        shootTimer->stop();
}
