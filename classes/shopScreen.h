#ifndef SHOPSCREEN_H
#define SHOPSCREEN_H

#include <QWidget>

class QPushButton;
class QLabel;

class ShopScreen : public QWidget {
    Q_OBJECT

public:
    ShopScreen(QWidget *parent=0);
    ~ShopScreen();

private:
    QPushButton *repair;
    QPushButton *addDamage;
    QPushButton *addLife;
    QPushButton *backToGame;
    QLabel *costRepair;
    QLabel *costDamage;
    QLabel *costLife;
};

#endif // SHOPSCREEN_H
