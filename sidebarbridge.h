#pragma once

#include <QObject>

class SidebarBridge : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;

public slots:
    void emitNavItemClicked(int index) {
        emit navItemClicked(index);
    }

signals:
    void navItemClicked(int index);
};
