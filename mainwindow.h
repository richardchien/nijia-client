#pragma once

#include "sidebarbridge.h"

#include <QStackedWidget>
#include <QWebEngineView>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initView();
    void initLogic();
    QWebEngineView *createWebEngineView();

private:
    QWebEngineView *sidebarContainer;
    SidebarBridge *sidebarBridge;
    QWebChannel *sidebarWebChannel;

    QWebEngineView *dataMonitorContainer;
    QWebEngineView *deviceListContainer;
    QWebEngineView *sceneListContainer;
    QWebEngineView *myAccountContainer;

    QStackedWidget *mainWidget;
};
