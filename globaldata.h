#pragma once

#include <QObject>
#include <QVariantList>

class GlobalData : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList deviceList READ deviceList WRITE setDeviceList NOTIFY deviceListChanged)

public:
    using QObject::QObject;

    QVariantList deviceList() const {
        return m_deviceList;
    }

    void setDeviceList(QVariantList val) {
        m_deviceList = qMove(val);
        emit deviceListChanged();
    }

signals:
    void deviceListChanged();

private:
    // TODO
    QString m_username;
    QString m_token;

    QVariantList m_deviceList;
};
