#include "mainwindow.h"

#include <QBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("NIJIA 智能家居");
    setFixedSize(900, 580);

    sidebarContainer = new QWebEngineView;
    sidebarContainer->setStyleSheet("border: none;");
    mainContainer = new QWebEngineView;
    mainContainer->setStyleSheet("border: none");

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(3);
    sidebarContainer->setSizePolicy(sp);
    sp.setHorizontalStretch(8);
    mainContainer->setSizePolicy(sp);

    sidebarContainer->setContextMenuPolicy(Qt::PreventContextMenu);
    mainContainer->setContextMenuPolicy(Qt::PreventContextMenu);

    sidebarContainer->load(QUrl("qrc:/web/sidebar.html"));
    sidebarContainer->show();

    auto *lo = new QHBoxLayout;
    lo->setSpacing(0);
    lo->setMargin(0);
    lo->addWidget(sidebarContainer);
    lo->addWidget(mainContainer);
    setLayout(lo);
}

MainWindow::~MainWindow() {
}
