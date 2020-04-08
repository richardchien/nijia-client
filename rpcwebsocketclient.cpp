#include "rpcwebsocketclient.h"

#include <QJsonDocument>
#include <QJsonObject>

RpcWebSocketClient::RpcWebSocketClient(QObject *parent) : QObject(parent) {
    connect(&m_websocket, &QWebSocket::connected, this, &RpcWebSocketClient::connected);
    connect(&m_websocket, &QWebSocket::disconnected, this, &RpcWebSocketClient::disconnected);
    connect(&m_websocket, &QWebSocket::textMessageReceived, this, &RpcWebSocketClient::onTextMessageReceived);
}

void RpcWebSocketClient::open(const QUrl &url) {
    m_url = url;
    m_websocket.open(url);
}

void RpcWebSocketClient::invoke(const Request &request, Callback callback) {
    if (!m_websocket.isValid()) {
        return;
    }

    auto uid = ++m_invokeSequence;
    qDebug() << "request (uid = " << uid << "): " << request;

    QVariantMap reqData = request.toMap();
    reqData["uid"] = uid;
    if (callback) m_callbacks[uid] = callback;
    m_websocket.sendTextMessage(QJsonDocument(QJsonObject::fromVariantMap(reqData)).toJson());
}

void RpcWebSocketClient::onTextMessageReceived(QString message) {
    QVariantMap respData = QJsonDocument::fromJson(message.toUtf8()).object().toVariantMap();
    Response response{respData["result"], respData["error"]};
    auto uid = respData["uid"].toInt();
    qDebug() << "response (uid = " << uid << "): " << response;

    auto callback = m_callbacks.take(uid);
    if (callback) {
        callback(response);
    }
}
