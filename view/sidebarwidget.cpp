#include "sidebarwidget.h"

SidebarWidget::SidebarWidget(QWidget *parent) : WebViewWidget(QUrl("qrc:/web/sidebar.html"), parent) {
}

void SidebarWidget::onNavItemClicked(int item) {
    emit navItemClicked(item);
}
