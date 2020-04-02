#pragma once

#include "webviewwidget.h"

class SidebarWidget : public WebViewWidget {
    Q_OBJECT
public:
    explicit SidebarWidget(QWidget *parent = nullptr);

public: // intended to be used via QWebChannel
    Q_INVOKABLE void emitNavItemClicked(int index) {
        emit navItemClicked(index);
    }

signals:
    void navItemClicked(int index);
};
