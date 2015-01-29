#include "helpScreen.h"
#include "constants.h"
#include <QLabel>
#include <QPushButton>

HelpScreen::HelpScreen(QWidget *parent) : QWidget(parent) {
    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(Qt::gray));
    setAutoFillBackground(true);
    setPalette(pal);

    helpText = new QLabel(this);
    helpText->setText(tr("Правила игры\n"
                         "Летай и уничтожай врагов.\nКаждые 10 уровней количество врагов увеличивается\n\n\n\n\n"
                         "Перемещение корабля вверх: W\n"
                         "Перемещение корабля вниз: S\n"
                         "Выстрел: ЛКМ"));
    helpText->setGeometry(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN);
    helpText->setAttribute(Qt::WA_NoSystemBackground);
    helpText->setAlignment(Qt::AlignCenter);

    backToMenu = new QPushButton(tr("Назад"), this);
    backToMenu->setGeometry(1100, 650, 150, 40);
    connect(backToMenu, SIGNAL(clicked()), parent, SLOT(pushMenuButton()));
}

HelpScreen::~HelpScreen() {
    delete helpText;
    delete backToMenu;
}
