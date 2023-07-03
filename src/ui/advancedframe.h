#ifndef ADVANCEDFRAME_H
#define ADVANCEDFRAME_H

#include <QFrame>
#include <QPushButton>
#include "subnet.h"
#include "iptablemodel.h"

namespace Ui {
class AdvancedFrame;
}

class AdvancedFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdvancedFrame(QWidget *parent = nullptr);
    ~AdvancedFrame();

public slots:
    void calculate();
    void save();

private:
    void setup();
    Ui::AdvancedFrame *ui;

    QList<subnetv4> list;
    IpTableModel * model;
};

#endif // ADVANCEDFRAME_H
