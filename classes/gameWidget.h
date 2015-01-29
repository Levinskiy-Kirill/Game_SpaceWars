#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class QGraphicsScene;
class QGraphicsView;
class QPropertyAnimation;
class QMovie;
class QLabel;
class QTimer;
class Wall;
class Ship;
class Bullet;
class Enemy;

class GameWidget : public QWidget {
    Q_OBJECT

public:
    GameWidget(QWidget *parent=0);
    ~GameWidget();
    void load();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Wall *wall;
    Ship *hero;
    QList<Bullet*> bulletHero;
    QList<Bullet*> bulletEnemy;
    QList<Enemy*> enemyBomb;
    QList<Enemy*> enemyShoot;

    QPropertyAnimation *anim;
    QTimer *logicTimer;

    int currentWave;
    int enemyOfWave;
    int currentEnemyOfWave;
    int money;

    void addHeroBullet();
    void bangEnemy(QPoint pos);
    void bulletEnemyBang(QPoint pos);
    void newWave();
    void addEnemy();
    bool isEnemyDied(Enemy *enemy, int flag); //0-Взрывающийся враг, 1-Стреляющий враг
    void bulletHeroHit(Enemy *enemy, Bullet *bullet, int numOfBullet);

public slots:
    void gamePause();
    void gamePlay();
    void repair();
    void addDamage();
    void addLife();

private slots:
    void logic();
    void endGame();
    void addEnemyBullet(QString nameEnemy, QPoint posEnemy, QSize sizeEnemy);

signals:
    void lifeChanged(int newLife);
    void moneyChanged(int newMoney);
};

#endif // GAMEWIDGET_H
