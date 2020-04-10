#include "devicelistwidget.h"

#include "application.h"
#include "devicewidget.h"

DeviceListWidget::DeviceListWidget(QWidget *parent) : WebViewWidget(QUrl("qrc:/web/device-list.html"), parent) {
}

void DeviceListWidget::onDeviceClicked(QString uid) {
    qDebug() << "uid:" << uid;
    DeviceWidget *widget = nullptr;
    if (deviceWidgets.contains(uid)) {
        widget = deviceWidgets[uid];
        if (!widget) deviceWidgets.remove(uid);
    }
    if (!widget) {
        widget = new DeviceWidget(uid);
        deviceWidgets[uid] = widget;
        connect(widget, &DeviceWidget::aboutToClose, this, [this, uid] { deviceWidgets.remove(uid); });
    }
    widget->show();
    widget->activateWindow();
}

void DeviceListWidget::onDeviceSwitchClicked(QString uid, bool currOn) {
    Application::instance()->rpcClient.invoke(
        {"update_device_state", {{"uid", uid}, {"state", QVariantMap({{"on", !currOn}})}}}, [uid](auto response) {
            if (!response.error.isNull()) return;
            Application::instance()->globalData.setDevice(uid, response.result.toMap());
        });
}
