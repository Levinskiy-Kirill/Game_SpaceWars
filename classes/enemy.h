#ifndef ENEMY_H
#define ENEMY_H

#include "ship.h"
#include <QWidget>

class QProgressBar;
class QLabel;
class QTimer;

class Enemy : public Ship {
    Q_OBJECT

public:
    Enemy(QString nameEnemy, QWidget *parent=0);
    ~Enemy();

    int getDamage();
    int getCurrentLife();
    int getSpeed();
    int getCost();
    QString getName();
    void setCurrentLife(int bulletDamage);
    void enemyStartShoot();
    void enemyPauseShoot();

private:
    int fullLife;
    int currentLife;
    int damage;
    int speed;
    int cost;
    QString name;
    QLabel *lifeEdit;
    QTimer *shootTimer;

private slots:
    void enemyShoot();

signals:
    void shoot(QString nameEnemy, QPoint posEnemy, QSize sizeEnemy);
};

#endif // ENEMY_H
