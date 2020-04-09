#include "webviewwidget.h"

#include <QBoxLayout>
#include <QWebChannel>

#include "application.h"

WebViewWidget::WebViewWidget(QWidget *parent) : QWebEngineView(parent) {
    setStyleSheet("background-color: #F5F6F8");
    page()->setBackgroundColor(Qt::transparent);

    channel = new QWebChannel;
    channel->registerObject("thisWidget", this);
    channel->registerObject("globalData", &Application::instance()->globalData);
    page()->setWebChannel(channel);
}

WebViewWidget::WebViewWidget(QUrl url, QWidget *parent) : WebViewWidget(parent) {
    load(url);
}

WebViewWidget::~WebViewWidget() {
    if (channel) delete qExchange(channel, nullptr);
}

void WebViewWidget::showEvent(QShowEvent *event) {
    QWebEngineView::showEvent(event);
    if (!isFirstShown) page()->runJavaScript("window.scrollTo(0, 0)");
    isFirstShown = false;
}
