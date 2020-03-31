#include "mainwindow.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QWebChannel>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("NIJIA 智能家居");
    setWindowIcon(QIcon(":/web/images/logo.png"));
    setFixedSize(900, 580);

    initView();
    initLogic();
}

MainWindow::~MainWindow() {
    delete qExchange(sidebarBridge, nullptr);
    delete qExchange(sidebarWebChannel, nullptr);
}

void MainWindow::initView() {
    sidebarContainer = createWebEngineView();
    dataMonitorContainer = createWebEngineView();
    deviceListContainer = createWebEngineView();
    sceneListContainer = createWebEngineView();
    myAccountContainer = createWebEngineView();

    mainWidget = new QStackedWidget;
    mainWidget->addWidget(dataMonitorContainer);
    mainWidget->addWidget(deviceListContainer);
    mainWidget->addWidget(sceneListContainer);
    mainWidget->addWidget(myAccountContainer);

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(3);
    sidebarContainer->setSizePolicy(sp);
    sp.setHorizontalStretch(7);
    mainWidget->setSizePolicy(sp);

    auto *boxLayout = new QHBoxLayout;
    boxLayout->setSpacing(0);
    boxLayout->setMargin(0);
    boxLayout->addWidget(sidebarContainer);
    boxLayout->addWidget(mainWidget);
    setLayout(boxLayout);
}

void MainWindow::initLogic() {
    sidebarBridge = new SidebarBridge;
    sidebarWebChannel = new QWebChannel;
    sidebarWebChannel->registerObject("bridge", sidebarBridge);
    sidebarContainer->page()->setWebChannel(sidebarWebChannel);

    sidebarContainer->load(QUrl("qrc:/web/sidebar.html"));
    dataMonitorContainer->load(QUrl("qrc:/web/data-mon-list.html"));
    deviceListContainer->load(QUrl("qrc:/web/device-list.html"));
    sceneListContainer->load(QUrl("qrc:/web/scene-list.html"));
    myAccountContainer->load(QUrl("qrc:/web/my-account.html"));

    connect(sidebarBridge, &SidebarBridge::navItemClicked, mainWidget, &QStackedWidget::setCurrentIndex);
}

QWebEngineView *MainWindow::createWebEngineView() {
    auto view = new QWebEngineView;
    view->setStyleSheet("border: none;");
    return view;
}
