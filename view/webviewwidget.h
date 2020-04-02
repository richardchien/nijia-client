#pragma once

#include <QWebChannel>
#include <QWebEngineView>

class WebViewWidget : public QWebEngineView {
    Q_OBJECT
public:
    explicit WebViewWidget(QWidget *parent = nullptr);
    explicit WebViewWidget(QUrl url, QWidget *parent = nullptr);
    virtual ~WebViewWidget();

protected:
    QWebChannel *channel;
    bool isFirstShown = true;

    void showEvent(QShowEvent *event) override;
};
