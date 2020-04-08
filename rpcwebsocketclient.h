#pragma once

#include <QDebug>
#include <QObject>
#include <QUrl>
#include <QVariantMap>
#include <QtWebSockets/QWebSocket>

class RpcWebSocketClient : public QObject {
    Q_OBJECT

public:
    explicit RpcWebSocketClient(QObject *parent = nullptr);

    void open(const QUrl &url);

    struct Request {
        QString method;
        QVariantMap params;

        QVariantMap toMap() const {
            return {
                {"method", method},
                {"params", params},
            };
        }
    };

    struct Response {
        QVariant result;
        QVariant error;

        QVariantMap toMap() const {
            return {
                {"result", result},
                {"error", error},
            };
        }
    };

    using Callback = std::function<void(const Response &)>;

    void invoke(const Request &request, Callback callback);

public slots:
    void onTextMessageReceived(QString message);

signals:
    void connected();
    void disconnected();

private:
    QUrl m_url;
    QWebSocket m_websocket;
    QMap<int, Callback> m_callbacks;
    int m_invokeSequence = 0;
};

inline QDebug operator<<(QDebug debug, const RpcWebSocketClient::Request &request) {
    debug << request.toMap();
    return debug;
}

inline QDebug operator<<(QDebug debug, const RpcWebSocketClient::Response &response) {
    debug << response.toMap();
    return debug;
}
