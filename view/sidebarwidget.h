#pragma once

#include "webviewwidget.h"

class SidebarWidget : public WebViewWidget {
    Q_OBJECT
public:
    explicit SidebarWidget(QWidget *parent = nullptr);

signals:
    void navItemClicked(int item);

public slots:
    void onNavItemClicked(int item);
};
