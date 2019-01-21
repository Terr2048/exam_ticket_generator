/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_4;
    QWidget *centralWidget;
    QTextBrowser *header;
    QTextBrowser *examined;
    QTextBrowser *affirim;
    QTextBrowser *chairperson;
    QTextBrowser *input_deputy_director;
    QTextBrowser *by_discipline;
    QTextBrowser *input_discipline;
    QTextBrowser *by_spicility;
    QTextBrowser *input_specialty;
    QTextBrowser *teacher;
    QPushButton *button_open_file;
    QPushButton *button_ready;
    QTextBrowser *protocol_id;
    QScrollArea *scrollArea;
    QWidget *scrollContents;
    QLabel *count_ticket;
    QSpinBox *spin_box_count_ticket;
    QTextBrowser *input_teacher;
    QLabel *progress;
    QTextBrowser *date_apporval;
    QTextBrowser *review_date;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(788, 620);
        MainWindow->setMinimumSize(QSize(788, 620));
        MainWindow->setMaximumSize(QSize(788, 620));
        MainWindow->setBaseSize(QSize(788, 620));
        MainWindow->setMouseTracking(true);
        MainWindow->setAutoFillBackground(true);
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_4->setCheckable(false);
        action_4->setEnabled(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        header = new QTextBrowser(centralWidget);
        header->setObjectName(QStringLiteral("header"));
        header->setGeometry(QRect(20, 10, 741, 91));
        QFont font;
        font.setPointSize(12);
        header->setFont(font);
        header->setLayoutDirection(Qt::LeftToRight);
        header->setReadOnly(false);
        header->setAcceptRichText(false);
        examined = new QTextBrowser(centralWidget);
        examined->setObjectName(QStringLiteral("examined"));
        examined->setGeometry(QRect(20, 100, 371, 51));
        examined->setFont(font);
        examined->setAcceptDrops(false);
        examined->setAutoFillBackground(false);
        examined->setReadOnly(false);
        examined->setAcceptRichText(false);
        affirim = new QTextBrowser(centralWidget);
        affirim->setObjectName(QStringLiteral("affirim"));
        affirim->setGeometry(QRect(390, 100, 371, 51));
        affirim->setFont(font);
        affirim->setReadOnly(false);
        affirim->setAcceptRichText(false);
        chairperson = new QTextBrowser(centralWidget);
        chairperson->setObjectName(QStringLiteral("chairperson"));
        chairperson->setGeometry(QRect(20, 210, 371, 31));
        chairperson->setFont(font);
        chairperson->setReadOnly(false);
        chairperson->setAcceptRichText(false);
        input_deputy_director = new QTextBrowser(centralWidget);
        input_deputy_director->setObjectName(QStringLiteral("input_deputy_director"));
        input_deputy_director->setGeometry(QRect(390, 180, 371, 31));
        input_deputy_director->setFont(font);
        input_deputy_director->setReadOnly(false);
        input_deputy_director->setAcceptRichText(false);
        by_discipline = new QTextBrowser(centralWidget);
        by_discipline->setObjectName(QStringLiteral("by_discipline"));
        by_discipline->setGeometry(QRect(20, 248, 161, 35));
        by_discipline->setReadOnly(true);
        input_discipline = new QTextBrowser(centralWidget);
        input_discipline->setObjectName(QStringLiteral("input_discipline"));
        input_discipline->setGeometry(QRect(180, 248, 581, 35));
        input_discipline->setFont(font);
        input_discipline->setReadOnly(false);
        input_discipline->setAcceptRichText(false);
        by_spicility = new QTextBrowser(centralWidget);
        by_spicility->setObjectName(QStringLiteral("by_spicility"));
        by_spicility->setGeometry(QRect(20, 282, 161, 35));
        by_spicility->setReadOnly(true);
        input_specialty = new QTextBrowser(centralWidget);
        input_specialty->setObjectName(QStringLiteral("input_specialty"));
        input_specialty->setGeometry(QRect(180, 282, 581, 35));
        input_specialty->setFont(font);
        input_specialty->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        input_specialty->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        input_specialty->setReadOnly(false);
        input_specialty->setAcceptRichText(false);
        teacher = new QTextBrowser(centralWidget);
        teacher->setObjectName(QStringLiteral("teacher"));
        teacher->setGeometry(QRect(20, 316, 161, 35));
        teacher->setReadOnly(true);
        button_open_file = new QPushButton(centralWidget);
        button_open_file->setObjectName(QStringLiteral("button_open_file"));
        button_open_file->setGeometry(QRect(600, 530, 161, 41));
        button_ready = new QPushButton(centralWidget);
        button_ready->setObjectName(QStringLiteral("button_ready"));
        button_ready->setGeometry(QRect(20, 530, 161, 41));
        protocol_id = new QTextBrowser(centralWidget);
        protocol_id->setObjectName(QStringLiteral("protocol_id"));
        protocol_id->setGeometry(QRect(20, 150, 371, 31));
        protocol_id->setFont(font);
        protocol_id->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        protocol_id->setReadOnly(false);
        protocol_id->setAcceptRichText(false);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 390, 741, 131));
        scrollArea->setFont(font);
        scrollArea->setWidgetResizable(true);
        scrollContents = new QWidget();
        scrollContents->setObjectName(QStringLiteral("scrollContents"));
        scrollContents->setGeometry(QRect(0, 0, 739, 129));
        scrollArea->setWidget(scrollContents);
        count_ticket = new QLabel(centralWidget);
        count_ticket->setObjectName(QStringLiteral("count_ticket"));
        count_ticket->setGeometry(QRect(250, 360, 231, 21));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        count_ticket->setFont(font1);
        spin_box_count_ticket = new QSpinBox(centralWidget);
        spin_box_count_ticket->setObjectName(QStringLiteral("spin_box_count_ticket"));
        spin_box_count_ticket->setGeometry(QRect(430, 360, 41, 21));
        spin_box_count_ticket->setFont(font);
        spin_box_count_ticket->setMaximum(2147483647);
        input_teacher = new QTextBrowser(centralWidget);
        input_teacher->setObjectName(QStringLiteral("input_teacher"));
        input_teacher->setGeometry(QRect(180, 316, 581, 35));
        input_teacher->setFont(font);
        input_teacher->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        input_teacher->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        input_teacher->setReadOnly(false);
        input_teacher->setAcceptRichText(false);
        progress = new QLabel(centralWidget);
        progress->setObjectName(QStringLiteral("progress"));
        progress->setGeometry(QRect(200, 540, 381, 21));
        progress->setFont(font);
        date_apporval = new QTextBrowser(centralWidget);
        date_apporval->setObjectName(QStringLiteral("date_apporval"));
        date_apporval->setGeometry(QRect(390, 150, 371, 31));
        date_apporval->setFont(font);
        date_apporval->setReadOnly(false);
        date_apporval->setAcceptRichText(false);
        review_date = new QTextBrowser(centralWidget);
        review_date->setObjectName(QStringLiteral("review_date"));
        review_date->setGeometry(QRect(20, 180, 371, 31));
        review_date->setFont(font);
        review_date->setReadOnly(false);
        review_date->setAcceptRichText(false);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 788, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_4);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_4->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", Q_NULLPTR));
        header->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\232\320\270\321\200\320\276\320\262\321\201\320\272\320\276\320\265 \320\276\320\261\320\273\320\260\321\201\321\202\320\275\320\276\320\265 \320\263\320\276\321\201\321\203\320\264\320\260\321\200\321\201\321\202\320\262\320\265\320\275\320\275\320\276\320\265 \320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\320\276\320\265</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block"
                        "-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\261\321\216\320\264\320\266\320\265\321\202\320\275\320\276\320\265 \321\203\321\207\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265 \321\201\321\200\320\265\320\264\320\275\320\265\320\263\320\276 \320\277\321\200\320\276\321\204\320\265\321\201\321\201\320\270\320\276\320\275\320\260\320\273\321\214\320\275\320\276\320\263\320\276 \320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\320\275\320\270\321\217</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\302\253\320\232\320\270\321\200\320\276\320\262\321\201\320\272\320\270\320\271 \320\260\320\262\320\270\320\260\321\206\320\270\320\276\320\275\320\275\321\213\320\271 \321\202\320\265\321\205\320\275\320\270\320\272\321\203\320\274\302\273</span></p></body></html>", Q_NULLPTR));
        examined->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\240\320\260\321\201\321\201\320\274\320\276\321\202\321\200\320\265\320\275\320\276 \321\206\320\270\320\272\320\273\320\276\320\262\320\276\320\271 \320\272\320\276\320\274\320\270\321\201\321\201\320\270\320\265\320\271<br />\320\262\321\213\321\207\320\270\321\201\320\273\320\270\321\202\320\265\320\273\321\214\320\275\321\213\321\205 \321\201\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\320\276\321\201\321\202\320\265\320\271</p></body></html>", Q_NULLPTR));
        affirim->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\243\320\242\320\222\320\225\320\240\320\226\320\224\320\220\320\256:</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\227\320\260\320\274. \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\260 \321\202\320\265\321\205\320\275\320\270\320\272\321\203\320\274\320\260</p></body></html>", Q_NULLPTR));
        chairperson->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\321\200\320\265\320\264\321\201\320\265\320\264\320\260\321\202\320\265\320\273\321\214: <span style=\" font-family:'MS Shell Dlg 2,sans-serif';\">_______</span></p></body></html>", Q_NULLPTR));
        input_deputy_director->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2,sans-serif';\">________</span></p></body></html>", Q_NULLPTR));
        by_discipline->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\320\237\320\276 \320\264\320\270\321\201\321\206\320\270\320\277\320\273\320\270\320\275\320\265</span></p></body></html>", Q_NULLPTR));
        by_spicility->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\320\224\320\273\321\217 \321\201\320\277\320\265\321\206\320\270\320\260\320\273\321\214\320\275\320\276\321\201\321\202\320\270</span></p></body></html>", Q_NULLPTR));
        input_specialty->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        teacher->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\214 </span></p></body></html>", Q_NULLPTR));
        button_open_file->setText(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", Q_NULLPTR));
        button_ready->setText(QApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\320\276", Q_NULLPTR));
        protocol_id->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273 \342\204\226 _</p></body></html>", Q_NULLPTR));
        count_ticket->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\270\320\273\320\265\321\202\320\276\320\262:", Q_NULLPTR));
        input_teacher->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        progress->setText(QString());
        date_apporval->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2,sans-serif';\">\302\253____\302\273 ___________ 201_ \320\263.</span> </p></body></html>", Q_NULLPTR));
        review_date->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2,sans-serif';\">\302\253____\302\273 ___________ 201_ \320\263.</span> </p></body></html>", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
