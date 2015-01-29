#ifndef SHIP_H
#define SHIP_H

#include <QWidget>

class QMovie;
class QLabel;
class QString;

class Ship : public QWidget {
    Q_OBJECT

public:
    Ship(QWidget *parent=0);
    ~Ship();
    void animation(QString textureName);

private:
    void load();

protected:
    QMovie *animationShip;
    QLabel *labelShip;
};

#endif // SHIP_H
