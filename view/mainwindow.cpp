#include "mainwindow.h"

#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QWebChannel>

#include "datamonlistwidget.h"
#include "devicelistwidget.h"
#include "myaccountwidget.h"
#include "scenelistwidget.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("NIJIA 智能家居");
    setStyleSheet("background-color: #F5F6F8");
    setFixedSize(900, 580);

    initView();
    initLogic();
}

MainWindow::~MainWindow() {
}

void MainWindow::initView() {
    sidebarWidget = new SidebarWidget;
    mainContainer = new QStackedWidget;
    mainContainer->addWidget(new DataMonListWidget);
    mainContainer->addWidget(new DeviceListWidget);
    mainContainer->addWidget(new SceneListWidget);
    mainContainer->addWidget(new MyAccountWidget);

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(3);
    sidebarWidget->setSizePolicy(sp);
    sp.setHorizontalStretch(7);
    mainContainer->setSizePolicy(sp);

    auto boxLayout = new QHBoxLayout;
    boxLayout->setSpacing(0);
    boxLayout->setMargin(0);
    boxLayout->addWidget(sidebarWidget);
    boxLayout->addWidget(mainContainer);
    setLayout(boxLayout);
}

void MainWindow::initLogic() {
    connect(sidebarWidget, &SidebarWidget::navItemClicked, this, [this](auto index) {
        if (index < 0 || index >= mainContainer->count()) return;
        auto wv = dynamic_cast<QWebEngineView *>(mainContainer->currentWidget());
        wv->page()->runJavaScript("window.scrollTo(0, 0)");
        mainContainer->setCurrentIndex(index);
    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QApplication::quit();
}
