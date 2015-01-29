#include "gameWidget.h"
#include "wall.h"
#include "ship.h"
#include "bullet.h"
#include "enemy.h"
#include "constants.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QList>
#include <QMovie>
#include <QLabel>
#include <QSettings>
#include "qdebug.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    QGridLayout *layout = new QGridLayout(this);

    layout->setMargin(0);
    layout->addWidget(view, 0, 0, 1, 1);   
}

GameWidget::~GameWidget() {
    delete wall;
    delete scene;
    delete view;
    bulletHero.clear();
    enemyBomb.clear();
    enemyShoot.clear();
    bulletEnemy.clear();
}

//Загрузка игрового экрана
void GameWidget::load() {
    scene->setSceneRect(0, 0, WIDTH_SCENE, HEIGHT_SCENE);
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/backgroundGame.png")));

    wall = new Wall();
    scene->addWidget(wall);
    wall->move(WALL_POS_X, WALL_POS_Y);

    hero = new Ship();
    hero->animation(":/images/shipHero.gif");
    scene->addWidget(hero);
    hero->move(1230, HEIGHT_SCENE/2 - HEIGHT_SHIP/2);

    currentWave = 1;
    enemyOfWave = 10;
    currentEnemyOfWave = enemyOfWave;
    money = 0;

    connect(wall, SIGNAL(lifeChanged(int)), this, SIGNAL(lifeChanged(int)));
    connect(wall, SIGNAL(endGame()), this, SLOT(endGame()));

    anim = new QPropertyAnimation(hero, "pos");
    logicTimer = new QTimer(this);
    connect(logicTimer, SIGNAL(timeout()), this, SLOT(logic()));
    logicTimer->start(LOGIC_TIMER);
    newWave();
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    if(anim->state() == 2)
        return;

    QPointF heroPos;
    heroPos = hero->pos();

    switch (event->nativeVirtualKey()) {
    case Qt::Key_W:
        heroPos.setY(heroPos.y() - 50);
        break;
    case Qt::Key_S:
        heroPos.setY(heroPos.y() + 50);
        break;
    case Qt::Key_Space:
        addHeroBullet();
        break;
    default:
        break;
    }

    if(heroPos.y() >= 0 && heroPos.y() < HEIGHT_SCENE - HEIGHT_SHIP) {
        anim->setDuration(200);
        anim->setStartValue(hero->pos());
        anim->setEndValue(heroPos);
        anim->start();
    }
}

void GameWidget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton)
        addHeroBullet();
    if(event->button() == Qt::RightButton) {
        if(logicTimer->isActive())
            gamePause();
        else
            gamePlay();
    }
}

//Добавление пули героя
void GameWidget::addHeroBullet() {
    Bullet *newBullet = new Bullet("bulletHero");
    bulletHero.push_back(newBullet);
    scene->addWidget(newBullet);
    newBullet->move(hero->pos().x(), hero->pos().y() + HEIGHT_SHIP/2 - 8);
    newBullet->raise();
}

//Добавление пули врага
void GameWidget::addEnemyBullet(QString nameEnemy, QPoint posEnemy, QSize sizeEnemy) {
    Bullet *newBullet = new Bullet("bullet" + nameEnemy);
    bulletEnemy.push_back(newBullet);
    scene->addWidget(newBullet);
    newBullet->move(posEnemy.x() + sizeEnemy.width(), posEnemy.y() + sizeEnemy.height()/2 + 7);
}

//Обработка логики игры
void GameWidget::logic() {
    //передвижение пули героя
    //Удаляется, если вылетела за пределы экрана
    for(int i=0; i<bulletHero.count(); i++) {
        bulletHero[i]->move(bulletHero[i]->x() - bulletHero[i]->getSpeed(), bulletHero[i]->y());
        if(bulletHero[i]->pos().x() < -44) {
            delete bulletHero.at(i);
            bulletHero.removeAt(i);
        }
    }

    //Передвижение взрывающихся врагов
    //Наносят урон и удаляются, если долетели до крепости
    for(int i=0; i<enemyBomb.count(); i++) {
        enemyBomb[i]->move(enemyBomb[i]->x() + enemyBomb[i]->getSpeed(), enemyBomb[i]->y());

        if(enemyBomb[i]->x() + enemyBomb[i]->width() > 1140) {
            wall->setCurrentLife(enemyBomb[i]->getDamage());
            bangEnemy(enemyBomb[i]->pos());
            delete enemyBomb.at(i);
            enemyBomb.removeAt(i);
        }
    }

    //Передвижение стреляющих врагов
    //Останавливаются если долетели до середины поля, чтобы начать стрелять
    for(int i=0; i<enemyShoot.count(); i++) {
        if(enemyShoot[i]->x() + enemyShoot[i]->width() > 600) {
            if(logicTimer->isActive())
                enemyShoot[i]->enemyStartShoot();
            continue;
        }
        enemyShoot[i]->move(enemyShoot[i]->x() + enemyShoot[i]->getSpeed(), enemyShoot[i]->y());
    }

    //Обработка попадания пули в корабль
    for(int i=0; i<bulletHero.count(); i++) {
        for(int j=0; j<enemyBomb.count(); j++) {
            if(i < bulletHero.count()) {
                bulletHeroHit(enemyBomb[j], bulletHero[i], i);
                if(isEnemyDied(enemyBomb[j], 0))
                    enemyBomb.removeAt(j);
            }
        }

        for(int j=0; j<enemyShoot.count(); j++) {
            if(i < bulletHero.count()) {
                bulletHeroHit(enemyShoot[j], bulletHero[i], i);
                if(isEnemyDied(enemyShoot[j], 1))
                    enemyShoot.removeAt(j);
            }
        }
    }

    //Передвижение пуль врагов
    //Наносят урон и удаляются, если долетели до крепости
    for(int i=0; i<bulletEnemy.count(); i++) {
        bulletEnemy[i]->move(bulletEnemy[i]->x() + bulletEnemy[i]->getSpeed(), bulletEnemy[i]->y());
        if(bulletEnemy[i]->pos().x() > 1100) {
            wall->setCurrentLife(bulletEnemy[i]->getDamage());
            bulletEnemyBang(bulletEnemy[i]->pos());
            delete bulletEnemy.at(i);
            bulletEnemy.removeAt(i);
        }
    }

    if(enemyBomb.isEmpty() && enemyShoot.isEmpty())
        newWave();
}

//действия при проигрыше
void GameWidget::endGame() {
    logicTimer->stop();
    QLabel *loseText = new QLabel();
    loseText->setText(tr("Конец игры!!!"));
    loseText->setAlignment(Qt::AlignCenter);
    loseText->setAttribute(Qt::WA_NoSystemBackground);
    loseText->setGeometry(0, 0, scene->sceneRect().width(), scene->sceneRect().height());
    loseText->setStyleSheet("font: bold 72px;"
                            "color: red");
    scene->addWidget(loseText);
}

//Анимация при уничтожении врага
void GameWidget::bangEnemy(QPoint pos) {
    QMovie *bang = new QMovie();
    QLabel *labelBang = new QLabel();
    labelBang->setMovie(bang);
    labelBang->resize(90, 90);
    labelBang->setAttribute(Qt::WA_NoSystemBackground);
    bang->setScaledSize(QSize(90, 90));
    scene->addWidget(labelBang);
    labelBang->move(pos);
    bang->setFileName(":/images/bang.gif");
    bang->start();
    QTimer::singleShot(600, bang, SLOT(stop()));
    QTimer::singleShot(600, labelBang, SLOT(hide()));
}

//Анимация при попадании пули врага в крепость
void GameWidget::bulletEnemyBang(QPoint pos) {
    QMovie *bang = new QMovie();
    QLabel *labelBang = new QLabel();
    labelBang->setMovie(bang);
    labelBang->resize(60, 60);
    labelBang->setAttribute(Qt::WA_NoSystemBackground);
    bang->setScaledSize(QSize(60, 60));
    scene->addWidget(labelBang);
    labelBang->move(pos.x(), pos.y()-30);
    bang->setFileName(":/images/bulletBang.gif");
    bang->start();
    QTimer::singleShot(800, bang, SLOT(stop()));
    QTimer::singleShot(800, labelBang, SLOT(hide()));
}

//Создает новую волну
void GameWidget::newWave() {
    QLabel *wave = new QLabel();
    wave->setText(tr("Волна: ") + QString::number(currentWave));
    wave->setAlignment(Qt::AlignCenter);
    wave->setAttribute(Qt::WA_NoSystemBackground);
    wave->setGeometry(0, 0, scene->sceneRect().width(), scene->sceneRect().height());
    wave->setStyleSheet("font: bold 72px;"
                            "color: red");
    scene->addWidget(wave);
    QTimer::singleShot(1000, wave, SLOT(hide()));

    addEnemy();
    currentWave++;
    if(currentWave%10 == 0) {
        enemyOfWave *= 1.1;
        currentEnemyOfWave = enemyOfWave;
    }
}

//Добавляет случайных врагов. Количество врагов равно количеству требуемых врагов в волне N
void GameWidget::addEnemy() {
    for(int i=0; i<enemyOfWave; i++) {
        int enemyType = qrand() % 6;
        Enemy *temp;

        switch (enemyType) {
        case 0:
            temp = new Enemy("enemyBombEasy");
            temp->animation(":/images/enemyBombEasy.gif");
            enemyBomb.push_back(temp);
            break;
        case 1:
            temp = new Enemy("enemyBombMedium");
            temp->animation(":/images/enemyBombMedium.gif");
            enemyBomb.push_back(temp);
            break;
        case 2:
            temp = new Enemy("enemyBombHard");
            temp->animation(":/images/enemyBombHard.gif");
            enemyBomb.push_back(temp);
            break;
        case 3:
            temp = new Enemy("enemyShootEasy");
            temp->animation(":/images/enemyShootEasy.gif");
            enemyShoot.push_back(temp);
            break;
        case 4:
            temp = new Enemy("enemyShootMedium");
            temp->animation(":/images/enemyShootMedium.gif");
            enemyShoot.push_back(temp);
            break;
        case 5:
            temp = new Enemy("enemyShootHard");
            temp->animation(":/images/enemyShootHard.gif");
            enemyShoot.push_back(temp);
            break;
        default:
            break;
        }

        scene->addWidget(temp);
        temp->move(qrand() % 400 - 600, qrand() % 620);
        if(enemyType >= 3 && enemyType <= 5)
            connect(temp, SIGNAL(shoot(QString,QPoint,QSize)), this, SLOT(addEnemyBullet(QString,QPoint,QSize)));
    }
}

//Определяет столкнулась ли пуля игрока с врагом
void GameWidget::bulletHeroHit(Enemy *enemy, Bullet *bullet, int numOfBullet) {

    if((bullet->x() > enemy->x()) && (bullet->x() < enemy->x() + enemy->width() - 30)
            && (bullet->y() > enemy->y() + 30) && (bullet->y() < enemy->y() + enemy->height())) {
        enemy->setCurrentLife(bullet->getDamage());
        delete bullet;
        bulletHero.removeAt(numOfBullet);
    }
}

//Проверяет уничтожен ли враг
//0-Взрывающийся враг, 1-Стреляющий враг
bool GameWidget::isEnemyDied(Enemy *enemy, int flag) {
    if(enemy->getCurrentLife() <= 0) {
        if(flag == 1)
            disconnect(enemy, SIGNAL(shoot(QString,QPoint,QSize)), this, SLOT(addEnemyBullet(QString,QPoint,QSize)));
        bangEnemy(enemy->pos());
        money += enemy->getCost();
        emit moneyChanged(money);
        delete enemy;
        return true;
    }

    return false;
}

void GameWidget::gamePause() {
    if(logicTimer->isActive())
        logicTimer->stop();
    for(int i=0; i<enemyShoot.count(); i++)
        enemyShoot[i]->enemyPauseShoot();
}

//Возобновление игрового процесса
void GameWidget::gamePlay() {
    if(!logicTimer->isActive())
        logicTimer->start(LOGIC_TIMER);
    for(int i=0; i<enemyShoot.count(); i++)
        if(enemyShoot[i]->x() + enemyShoot[i]->width() > 600)
            enemyShoot[i]->enemyStartShoot();
}

//Починка крепости
void GameWidget::repair() {
    if(money >= COST_REPAIR) {
        wall->repairWall();
        money -= COST_REPAIR;
        emit moneyChanged(money);
    }
}

//Увеличение урона игрока
void GameWidget::addDamage() {
    if(money >= COST_DAMAGE) {
        Bullet::addLevelDamage();
        money -= COST_DAMAGE;
        emit moneyChanged(money);
    }
}

//Увеличение жизни у крепости
void GameWidget::addLife() {
    if(money >= COST_LIFE) {
        wall->addLifeWall();
        money -= COST_LIFE;
        emit moneyChanged(money);
    }
}
