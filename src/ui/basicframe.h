#ifndef BASICFRAME_H
#define BASICFRAME_H

#include <QFrame>
#include <QPushButton>

namespace Ui {
class BasicFrame;
}

class BasicFrame : public QFrame
{
    Q_OBJECT

public:
    explicit BasicFrame(QWidget *parent = nullptr);
    ~BasicFrame();

public slots:
    void calculate();
    void save();

private:

    Ui::BasicFrame *ui;
};

#endif // BASICFRAME_H
