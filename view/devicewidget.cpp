#include "devicewidget.h"

#include <QCloseEvent>

#include "application.h"

DeviceWidget::DeviceWidget(const QString &uid, QWidget *parent) : WebViewWidget(parent) {
    const auto device = Application::instance()->globalData.device(uid);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("NIJIA 智能家居 - " + device["name"].toString());
    setFixedSize(360, 460);

    m_uid = uid;
    m_model = device["model"].toString();
    load(QString("qrc:/web/devices/%1.html?uid=%2").arg(m_model, m_uid));

    connect(&m_timer, &QTimer::timeout, this, &DeviceWidget::updateHistoryStateList);
}

void DeviceWidget::updateHistoryStateList() {
    Application::instance()->rpcClient.invoke({"get_history_state_list", {{"device_uid", m_uid}, {"count", 20}}},
                                              [this](auto response) {
                                                  if (!response.error.isNull()) return;
                                                  m_historyStateList = response.result.toList();
                                                  emit historyStateListChanged();
                                              });
}

void DeviceWidget::startTimer() {
    updateHistoryStateList();
    m_timer.setInterval(5000);
    m_timer.start();
}

void DeviceWidget::changeState(QVariantMap state) {
    Application::instance()->rpcClient.invoke(
        {"update_device_state", {{"uid", m_uid}, {"state", state}}}, [uid = m_uid](auto response) {
            if (!response.error.isNull()) return;
            Application::instance()->globalData.setDevice(uid, response.result.toMap());
        });
}

void DeviceWidget::closeEvent(QCloseEvent *event) {
    m_timer.stop();
    emit aboutToClose();
    event->accept();
}
