#ifndef WALL_H
#define WALL_H

#include <QWidget>

class Wall : public QWidget {
    Q_OBJECT

public:
    Wall(QWidget *parent=0);
    ~Wall();

    void repairWall();
    void addLifeWall();

public slots:
    void setCurrentLife(int damage);

private:
    QString name;
    int fullLife;
    int currentLife;

signals:
    void lifeChanged(int newLife);
    void endGame();
};

#endif // WALL_H
