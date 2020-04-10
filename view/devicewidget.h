#pragma once

#include <QTimer>

#include "webviewwidget.h"

class DeviceWidget : public WebViewWidget {
    Q_OBJECT

    Q_PROPERTY(QVariantList historyStateList MEMBER m_historyStateList NOTIFY historyStateListChanged)

public:
    explicit DeviceWidget(const QString &uid, QWidget *parent = nullptr);

public slots:
    void updateHistoryStateList();

public: // intended to be used via QWebChannel
    Q_INVOKABLE void startTimer();
    Q_INVOKABLE void changeState(QVariantMap state);

signals:
    void aboutToClose();
    void historyStateListChanged();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QString m_uid;
    QString m_model;
    QVariantList m_historyStateList;
    QTimer m_timer;
};
