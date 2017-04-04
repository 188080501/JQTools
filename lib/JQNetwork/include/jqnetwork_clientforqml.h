/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CLIENGFORQML_H
#define JQNETWORK_INCLUDE_JQNETWORK_CLIENGFORQML_H

// Qt lib import
#include <QJSValue>
#include <QJSValueList>
#include <QDateTime>

// JQNetwork lib import
#include <JQNetworkFoundation>

#ifdef QT_QML_LIB
#   define JQNETWORKCLIENTFORQML_REGISTERTYPE( engine ) \
    qmlRegisterType< JQNetworkClientForQml >( "JQNetworkClientForQml", 1, 0, "JQNetworkClientForQml" ); \
    engine.addImportPath( ":/JQNetwork/" );
#endif

class JQNetworkClientForQml: public QObject
{
    Q_OBJECT

public:
    JQNetworkClientForQml();

    ~JQNetworkClientForQml() = default;

public slots:
    bool beginClient();

    QVariantMap test() { return { { "key", QDateTime::currentDateTime() }, { "key2", QByteArray::fromHex( "00112233" ) } }; }

    void print(const QVariant &d) { qDebug() << d; }

    void createConnect(const QString &hostName, const quint16 &port);

    void sendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QVariantMap &payloadData,
            QJSValue succeedCallback,
            QJSValue failCallback
        );

private Q_SLOTS:
    inline void runOnClientThread(const std::function<void()> &callback);

signals:
    void connectToHostError(const QString &hostName, const quint16 &port);

    void connectToHostTimeout(const QString &hostName, const quint16 &port);

    void connectToHostSucceed(const QString &hostName, const quint16 &port);

    void remoteHostClosed(const QString &hostName, const quint16 &port);

    void readyToDelete(const QString &hostName, const quint16 &port);

private:
    JQNetworkClientSharedPointer jqNetworkClient_;
};

// inc import
#include "jqnetwork_clientforqml.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_CLIENGFORQML_H
