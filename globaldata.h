#pragma once

#include <QDebug>
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

    Q_INVOKABLE QVariantMap device(QString uid) const {
        for (const auto &dev : m_deviceList) {
            if (dev.toMap()["uid"].toString() == uid) {
                return dev.toMap();
            }
        }
        return QVariantMap();
    }

    void setDevice(QString uid, QVariantMap val) {
        for (auto &dev : m_deviceList) {
            if (dev.toMap()["uid"] == uid) {
                dev = qMove(val);
                emit deviceListChanged();
                break;
            }
        }
    }

signals:
    void deviceListChanged();

private:
    // TODO
    QString m_username;
    QString m_token;

    QVariantList m_deviceList;
};
