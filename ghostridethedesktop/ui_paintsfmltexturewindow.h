/********************************************************************************
** Form generated from reading UI file 'paintsfmltexturewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTSFMLTEXTUREWINDOW_H
#define UI_PAINTSFMLTEXTUREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintSFMLTextureWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PaintSFMLTextureWindow)
    {
        if (PaintSFMLTextureWindow->objectName().isEmpty())
            PaintSFMLTextureWindow->setObjectName(QStringLiteral("PaintSFMLTextureWindow"));
        PaintSFMLTextureWindow->resize(400, 300);
        centralWidget = new QWidget(PaintSFMLTextureWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 321, 141));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 130, 113, 32));
        PaintSFMLTextureWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PaintSFMLTextureWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 22));
        PaintSFMLTextureWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PaintSFMLTextureWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PaintSFMLTextureWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PaintSFMLTextureWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PaintSFMLTextureWindow->setStatusBar(statusBar);

        retranslateUi(PaintSFMLTextureWindow);

        QMetaObject::connectSlotsByName(PaintSFMLTextureWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PaintSFMLTextureWindow)
    {
        PaintSFMLTextureWindow->setWindowTitle(QApplication::translate("PaintSFMLTextureWindow", "PaintSFMLTextureWindow", Q_NULLPTR));
        label->setText(QApplication::translate("PaintSFMLTextureWindow", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PaintSFMLTextureWindow", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PaintSFMLTextureWindow: public Ui_PaintSFMLTextureWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTSFMLTEXTUREWINDOW_H
