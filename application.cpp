#include "application.h"

#include <QIcon>

Application *Application::s_instance = nullptr;

Application::Application(int &argc, char **argv) : QApplication(argc, argv) {
    setWindowIcon(QIcon(":/web/images/logo.png"));

    connect(&m_timer, &QTimer::timeout, this, &Application::updateDeviceList);
    connect(&rpcClient, &RpcWebSocketClient::connected, this, [this] {
        updateDeviceList();
        m_timer.setInterval(3000);
        m_timer.start();
    });
    connect(&rpcClient, &RpcWebSocketClient::disconnected, this, [this] { m_timer.stop(); });
    rpcClient.open(QUrl("ws://127.0.0.1:6001/ws/client"));
}

void Application::updateDeviceList() {
    rpcClient.invoke({"get_device_list", {}}, [this](auto response) {
        if (!response.error.isNull()) return;
        globalData.setDeviceList(response.result.toList());
    });
}
