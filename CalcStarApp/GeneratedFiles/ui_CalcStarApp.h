/********************************************************************************
** Form generated from reading UI file 'CalcStarApp.ui'
**
** Created: Wed Mar 19 21:19:56 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCSTARAPP_H
#define UI_CALCSTARAPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalcStarAppClass
{
public:
    QAction *actionExit;
    QAction *actionTokenize;
    QAction *actionCompile;
    QAction *actionEvaluate;
    QAction *actionRunAllTests;
    QWidget *centralWidget;
    QTabWidget *tabCtrlMain;
    QWidget *tab_Variables;
    QTableWidget *grd_Variables;
    QLabel *lbl_Variables;
    QPushButton *cmd_SaveVariables;
    QWidget *tab_Tokens;
    QLabel *lbl_Tokens;
    QTableWidget *grd_Tokens;
    QWidget *tab_RPN;
    QLabel *lbl_RPN;
    QTableWidget *grd_RPNStack;
    QWidget *tab_Output;
    QLabel *lbl_Output;
    QTextEdit *txt_Output;
    QWidget *tabTests;
    QTextEdit *txtTestResults;
    QTextEdit *txt_Expression;
    QLabel *lbl_strExpression;
    QMenuBar *menuBar;
    QMenu *mnu_File;
    QMenu *mnu_Expression;
    QMenu *menuTest;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalcStarAppClass)
    {
        if (CalcStarAppClass->objectName().isEmpty())
            CalcStarAppClass->setObjectName(QString::fromUtf8("CalcStarAppClass"));
        CalcStarAppClass->resize(512, 617);
        actionExit = new QAction(CalcStarAppClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionTokenize = new QAction(CalcStarAppClass);
        actionTokenize->setObjectName(QString::fromUtf8("actionTokenize"));
        actionCompile = new QAction(CalcStarAppClass);
        actionCompile->setObjectName(QString::fromUtf8("actionCompile"));
        actionEvaluate = new QAction(CalcStarAppClass);
        actionEvaluate->setObjectName(QString::fromUtf8("actionEvaluate"));
        actionRunAllTests = new QAction(CalcStarAppClass);
        actionRunAllTests->setObjectName(QString::fromUtf8("actionRunAllTests"));
        centralWidget = new QWidget(CalcStarAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabCtrlMain = new QTabWidget(centralWidget);
        tabCtrlMain->setObjectName(QString::fromUtf8("tabCtrlMain"));
        tabCtrlMain->setGeometry(QRect(20, 120, 471, 441));
        tab_Variables = new QWidget();
        tab_Variables->setObjectName(QString::fromUtf8("tab_Variables"));
        grd_Variables = new QTableWidget(tab_Variables);
        grd_Variables->setObjectName(QString::fromUtf8("grd_Variables"));
        grd_Variables->setGeometry(QRect(20, 30, 421, 361));
        lbl_Variables = new QLabel(tab_Variables);
        lbl_Variables->setObjectName(QString::fromUtf8("lbl_Variables"));
        lbl_Variables->setGeometry(QRect(20, 10, 61, 16));
        cmd_SaveVariables = new QPushButton(tab_Variables);
        cmd_SaveVariables->setObjectName(QString::fromUtf8("cmd_SaveVariables"));
        cmd_SaveVariables->setGeometry(QRect(350, 0, 91, 23));
        tabCtrlMain->addTab(tab_Variables, QString());
        tab_Tokens = new QWidget();
        tab_Tokens->setObjectName(QString::fromUtf8("tab_Tokens"));
        lbl_Tokens = new QLabel(tab_Tokens);
        lbl_Tokens->setObjectName(QString::fromUtf8("lbl_Tokens"));
        lbl_Tokens->setGeometry(QRect(20, 10, 61, 16));
        grd_Tokens = new QTableWidget(tab_Tokens);
        grd_Tokens->setObjectName(QString::fromUtf8("grd_Tokens"));
        grd_Tokens->setGeometry(QRect(20, 30, 421, 361));
        grd_Tokens->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabCtrlMain->addTab(tab_Tokens, QString());
        tab_RPN = new QWidget();
        tab_RPN->setObjectName(QString::fromUtf8("tab_RPN"));
        lbl_RPN = new QLabel(tab_RPN);
        lbl_RPN->setObjectName(QString::fromUtf8("lbl_RPN"));
        lbl_RPN->setGeometry(QRect(20, 10, 81, 16));
        grd_RPNStack = new QTableWidget(tab_RPN);
        grd_RPNStack->setObjectName(QString::fromUtf8("grd_RPNStack"));
        grd_RPNStack->setGeometry(QRect(20, 31, 421, 361));
        grd_RPNStack->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabCtrlMain->addTab(tab_RPN, QString());
        tab_Output = new QWidget();
        tab_Output->setObjectName(QString::fromUtf8("tab_Output"));
        lbl_Output = new QLabel(tab_Output);
        lbl_Output->setObjectName(QString::fromUtf8("lbl_Output"));
        lbl_Output->setGeometry(QRect(20, 10, 131, 16));
        txt_Output = new QTextEdit(tab_Output);
        txt_Output->setObjectName(QString::fromUtf8("txt_Output"));
        txt_Output->setGeometry(QRect(20, 30, 251, 61));
        tabCtrlMain->addTab(tab_Output, QString());
        tabTests = new QWidget();
        tabTests->setObjectName(QString::fromUtf8("tabTests"));
        txtTestResults = new QTextEdit(tabTests);
        txtTestResults->setObjectName(QString::fromUtf8("txtTestResults"));
        txtTestResults->setGeometry(QRect(10, 10, 441, 401));
        tabCtrlMain->addTab(tabTests, QString());
        txt_Expression = new QTextEdit(centralWidget);
        txt_Expression->setObjectName(QString::fromUtf8("txt_Expression"));
        txt_Expression->setGeometry(QRect(20, 30, 471, 81));
        lbl_strExpression = new QLabel(centralWidget);
        lbl_strExpression->setObjectName(QString::fromUtf8("lbl_strExpression"));
        lbl_strExpression->setGeometry(QRect(20, 0, 91, 21));
        CalcStarAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalcStarAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 512, 21));
        mnu_File = new QMenu(menuBar);
        mnu_File->setObjectName(QString::fromUtf8("mnu_File"));
        mnu_Expression = new QMenu(menuBar);
        mnu_Expression->setObjectName(QString::fromUtf8("mnu_Expression"));
        menuTest = new QMenu(menuBar);
        menuTest->setObjectName(QString::fromUtf8("menuTest"));
        CalcStarAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CalcStarAppClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CalcStarAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CalcStarAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CalcStarAppClass->setStatusBar(statusBar);

        menuBar->addAction(mnu_File->menuAction());
        menuBar->addAction(mnu_Expression->menuAction());
        menuBar->addAction(menuTest->menuAction());
        mnu_File->addAction(actionExit);
        mnu_Expression->addAction(actionTokenize);
        mnu_Expression->addAction(actionCompile);
        mnu_Expression->addAction(actionEvaluate);
        menuTest->addAction(actionRunAllTests);

        retranslateUi(CalcStarAppClass);

        tabCtrlMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CalcStarAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalcStarAppClass)
    {
        CalcStarAppClass->setWindowTitle(QApplication::translate("CalcStarAppClass", "FrmMain", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("CalcStarAppClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionTokenize->setText(QApplication::translate("CalcStarAppClass", "Tokenize", 0, QApplication::UnicodeUTF8));
        actionCompile->setText(QApplication::translate("CalcStarAppClass", "Compile", 0, QApplication::UnicodeUTF8));
        actionEvaluate->setText(QApplication::translate("CalcStarAppClass", "Evaluate", 0, QApplication::UnicodeUTF8));
        actionRunAllTests->setText(QApplication::translate("CalcStarAppClass", "Run All Tests", 0, QApplication::UnicodeUTF8));
        lbl_Variables->setText(QApplication::translate("CalcStarAppClass", "Variables", 0, QApplication::UnicodeUTF8));
        cmd_SaveVariables->setText(QApplication::translate("CalcStarAppClass", "Save Variables", 0, QApplication::UnicodeUTF8));
        tabCtrlMain->setTabText(tabCtrlMain->indexOf(tab_Variables), QApplication::translate("CalcStarAppClass", "VARIABLES", 0, QApplication::UnicodeUTF8));
        lbl_Tokens->setText(QApplication::translate("CalcStarAppClass", "Tokens List", 0, QApplication::UnicodeUTF8));
        tabCtrlMain->setTabText(tabCtrlMain->indexOf(tab_Tokens), QApplication::translate("CalcStarAppClass", "TOKENS", 0, QApplication::UnicodeUTF8));
        lbl_RPN->setText(QApplication::translate("CalcStarAppClass", "RPN Stack List", 0, QApplication::UnicodeUTF8));
        tabCtrlMain->setTabText(tabCtrlMain->indexOf(tab_RPN), QApplication::translate("CalcStarAppClass", "RPN", 0, QApplication::UnicodeUTF8));
        lbl_Output->setText(QApplication::translate("CalcStarAppClass", "Expression Parser Output", 0, QApplication::UnicodeUTF8));
        tabCtrlMain->setTabText(tabCtrlMain->indexOf(tab_Output), QApplication::translate("CalcStarAppClass", "OUTPUT", 0, QApplication::UnicodeUTF8));
        tabCtrlMain->setTabText(tabCtrlMain->indexOf(tabTests), QApplication::translate("CalcStarAppClass", "TEST RESULTS", 0, QApplication::UnicodeUTF8));
        lbl_strExpression->setText(QApplication::translate("CalcStarAppClass", "strExpression", 0, QApplication::UnicodeUTF8));
        mnu_File->setTitle(QApplication::translate("CalcStarAppClass", "File", 0, QApplication::UnicodeUTF8));
        mnu_Expression->setTitle(QApplication::translate("CalcStarAppClass", "Expression", 0, QApplication::UnicodeUTF8));
        menuTest->setTitle(QApplication::translate("CalcStarAppClass", "Test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalcStarAppClass: public Ui_CalcStarAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCSTARAPP_H
