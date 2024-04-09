/********************************************************************************
** Form generated from reading UI file 'plot.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <mygraphicsscene.h>

QT_BEGIN_NAMESPACE

class Ui_plot
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    MyGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *plot)
    {
        if (plot->objectName().isEmpty())
            plot->setObjectName(QString::fromUtf8("plot"));
        plot->resize(1695, 1198);
        centralwidget = new QWidget(plot);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 20, 75, 23));
        graphicsView = new MyGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 60, 1571, 1031));
        plot->setCentralWidget(centralwidget);
        menubar = new QMenuBar(plot);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1695, 23));
        plot->setMenuBar(menubar);
        statusbar = new QStatusBar(plot);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        plot->setStatusBar(statusbar);

        retranslateUi(plot);

        QMetaObject::connectSlotsByName(plot);
    } // setupUi

    void retranslateUi(QMainWindow *plot)
    {
        plot->setWindowTitle(QCoreApplication::translate("plot", "plot", nullptr));
        pushButton->setText(QCoreApplication::translate("plot", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class plot: public Ui_plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
