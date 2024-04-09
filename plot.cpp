#include "plot.h"
#include "ui_plot.h"


plot::plot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::plot)
{
    ui->setupUi(this);
    //update();
    //connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
    //    
    //    });
}

plot::~plot()
{
    delete ui;
}

//void plot::paintEvent(QPaintEvent* event)
//{
//    if (!m_selecting)
//    {
//        MyGraphicsView* view = new MyGraphicsView;
//        //QGraphicsView* view = new QGraphicsView;
//        QGraphicsScene* scene = new QGraphicsScene;
//        int width = view->viewport()->width();
//        int height = view->viewport()->height();
//        QPixmap img_pix(width, height);
//        img_pix.fill(Qt::white);
//        QPainter painter(&img_pix);
//
//        //høÃ∂»œﬂ± À¢
//        QPen pen(Qt::black);
//        pen.setColor(QColor("#787878"));
//        QPen pen2(Qt::black);
//        QVector<qreal> dashes;
//        dashes << 9 << 5;
//        pen.setDashPattern(dashes);
//        painter.setPen(pen);
//        int width_each = img_pix.width() / 10;
//        int height_each = img_pix.height() / 10;
//        for (int i = height_each; i < height; i += height_each)
//        {
//            painter.drawLine(0, i, width, i);
//        }
//        pen2.setColor(QColor("#C0C0C0"));
//        painter.setPen(pen2);
//
//        int tick_interval = height_each / 5;
//        int tick_length = 1;
//        for (int i = width_each; i <= width; i += width_each)
//        {
//            for (int j = i - width_each / 5; j > i - width_each; j -= width_each / 5)
//            {
//                for (int k = 0; k < height; k += tick_interval)
//                {
//                    //painter.drawLine(j, k, j, k+tick_interval);
//                    painter.drawLine(j - tick_length, k, j + tick_length, k);
//                }
//            }
//            for (int j = 0; j < height; j += tick_interval)
//            {
//                painter.drawLine(i, j, i, j + tick_interval);
//                painter.drawLine(i - tick_length, j, i + tick_length, j);
//            }
//        }
//        scene->addPixmap(img_pix);
//        //scene->setSceneRect(0, 0, view->viewport()->width(), view->viewport()->height());
//        scene->setSceneRect(img_pix.rect());
//        view->setScene(scene);
//        view->setRenderHint(QPainter::Antialiasing, true);
//        view->setRenderHint(QPainter::SmoothPixmapTransform, true);
//        ui->scrollArea->setWidget(view);
//        ui->scrollArea->setWidgetResizable(true);
//        qDebug() << view->width() << " and " << view->height();
//        ui->graphicsView->setScene(scene);
//    }
//    else
//    {
//        QPainter paint_window(this);
//        if (!m_selectRect.isNull())
//        {
//            paint_window.setPen(Qt::red);
//            paint_window.drawRect(m_selectRect);
//        }
//    }
//
//}



void plot::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_selecting = true;
        m_selectPos = event->pos();
        m_selectRect.setTopLeft(m_selectPos);
        m_selectRect.setBottomRight(m_selectPos);
        update();
    }
}

void plot::mouseMoveEvent(QMouseEvent* event)
{
    if (m_selecting)
    {

        m_selectPos = event->pos();
        m_selectRect.setBottomRight(m_selectPos);
        update();
    }
}

void plot::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_selectRect = QRect();
        update();
    }
}