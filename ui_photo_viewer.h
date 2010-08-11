/********************************************************************************
** Form generated from reading UI file 'photo_viewer.ui'
**
** Created: Wed Aug 11 20:46:05 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHOTO_VIEWER_H
#define UI_PHOTO_VIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Photo_ViewerClass
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Photo_ViewerClass)
    {
        if (Photo_ViewerClass->objectName().isEmpty())
            Photo_ViewerClass->setObjectName(QString::fromUtf8("Photo_ViewerClass"));
        Photo_ViewerClass->resize(800, 600);
        centralwidget = new QWidget(Photo_ViewerClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Photo_ViewerClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Photo_ViewerClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        Photo_ViewerClass->setMenuBar(menubar);
        statusbar = new QStatusBar(Photo_ViewerClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Photo_ViewerClass->setStatusBar(statusbar);

        retranslateUi(Photo_ViewerClass);

        QMetaObject::connectSlotsByName(Photo_ViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *Photo_ViewerClass)
    {
        Photo_ViewerClass->setWindowTitle(QApplication::translate("Photo_ViewerClass", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Photo_ViewerClass: public Ui_Photo_ViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHOTO_VIEWER_H
