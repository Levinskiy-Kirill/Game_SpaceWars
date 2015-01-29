#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <QWidget>

class QLabel;
class QPushButton;

class HelpScreen : public QWidget {
    Q_OBJECT

public:
    HelpScreen(QWidget *parent=0);
    ~HelpScreen();

private:
    QLabel *helpText;
    QPushButton *backToMenu;
};

#endif // HELPSCREEN_H
