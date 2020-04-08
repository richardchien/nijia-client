#include "application.h"

Application *Application::s_instance = nullptr;

Application::Application(int &argc, char **argv) : QApplication(argc, argv) {
    connect(&timer, &QTimer::timeout, this, &Application::updateDeviceList);
    connect(&rpcClient, &RpcWebSocketClient::connected, this, [this] {
        updateDeviceList();
        timer.setInterval(3000);
        timer.start();
    });
    connect(&rpcClient, &RpcWebSocketClient::disconnected, this, [this] { timer.stop(); });
    rpcClient.open(QUrl("ws://127.0.0.1:6001/ws/client"));
}

void Application::updateDeviceList() {
    rpcClient.invoke({"get_device_list", {}}, [this](auto response) {
        if (!response.error.isNull()) return;
        globalData.setDeviceList(response.result.toList());
    });
}
