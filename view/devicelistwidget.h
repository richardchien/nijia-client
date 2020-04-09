#pragma once

#include "devicewidget.h"
#include "webviewwidget.h"

class DeviceListWidget : public WebViewWidget {
    Q_OBJECT
public:
    explicit DeviceListWidget(QWidget *parent = nullptr);

public: // intended to be used via QWebChannel
    Q_INVOKABLE void onDeviceClicked(QString uid);
    Q_INVOKABLE void onDeviceSwitchClicked(QString uid);

signals:

private:
    QMap<QString, DeviceWidget *> deviceWidgets;
};
