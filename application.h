#pragma once

#include <QApplication>
#include <QTimer>

#include "globaldata.h"
#include "rpcwebsocketclient.h"

class Application : public QApplication {
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);

    static void setInstance(Application *app) {
        s_instance = app;
    }

    static Application *instance() {
        return s_instance;
    }

    GlobalData globalData;
    RpcWebSocketClient rpcClient;

private:
    static Application *s_instance;

    QTimer m_timer;

    void updateDeviceList();
};
