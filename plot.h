#ifndef PLOT_H
#define PLOT_H

#include <QMainWindow>
#include <iostream>
#include <cmath>
#include <qtmath>
#include <qdebug.h>
#include <qpainter.h>
#include <qpaintdevice.h>
#include <qlabel.h>
#include <qgraphicsview.h>
#include <qmouseeventtransition.h>
#include <QMouseEvent>
#include <qlayout.h>
#include <qpixmap.h>

#include "MyGraphicsScene.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class plot; }
QT_END_NAMESPACE

class plot : public QMainWindow
{
    Q_OBJECT

public:
    plot(QWidget *parent = nullptr);
    ~plot();
    //void paintEvent(QPaintEvent*) override;

    
private:
    Ui::plot *ui;
    QRect m_selectRect;
    QPoint m_selectPos;
    bool m_selecting = false;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};
#endif // PLOT_H
