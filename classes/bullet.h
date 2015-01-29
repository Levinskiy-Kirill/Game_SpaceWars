#ifndef BULLET_H
#define BULLET_H

#include <QWidget>

class QPixmap;
class QLabel;

class Bullet : public QWidget {
    Q_OBJECT

public:
    Bullet(QString nameBullet, QWidget *parent=0);
    ~Bullet();

    int getSpeed();
    int getDamage();
    static void addLevelDamage();
    QString getName();

private:
    QString name;
    int speed;
    int damage;
    int static levelDamage; //Используется для увеличения урона пули героя

    QPixmap *pixBullet;
    QLabel *labelBullet;
};

#endif // BULLET_H
