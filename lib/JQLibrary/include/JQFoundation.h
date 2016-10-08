/*
    This file is part of JQLibrary

    Copyright: Jason

    Contact email: 188080501@qq.com

    GNU Lesser General Public License Usage
    Alternatively, this file may be used under the terms of the GNU Lesser
    General Public License version 2.1 or version 3 as published by the Free
    Software Foundation and appearing in the file LICENSE.LGPLv21 and
    LICENSE.LGPLv3 included in the packaging of this file. Please review the
    following information to ensure the GNU Lesser General Public License
    requirements will be met: https://www.gnu.org/licenses/lgpl.html and
    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef __JQFoundation_h__
#define __JQFoundation_h__

#if ((__cplusplus < 201103) && !(defined _MSC_VER)) || ((defined _MSC_VER) && (_MSC_VER < 1800))
#   error("Plwase add c++11 config on pro file")
#endif

#ifndef QT_CORE_LIB
#   error("Plwaer add core in pro file")
#endif

#ifndef QT_GUI_LIB
#   error("Plwaer add gui in pro file")
#endif

// C++ lib import
#include <set>
#include <unordered_set>
#include <functional>

// Qt lib import
#include <QCoreApplication>
#include <QMutex>
#include <QCryptographicHash>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QTime>
#include <QVariant>
#include <QPointer>
#include <QFile>
#include <QDebug>

class QTableWidget;
class QTreeWidget;
class QTextEdit;
class QLineEdit;

// Macro define
#define SingleNew(p, ...)                                                           \
    if (p) { delete p;  }                                                           \
    p = new decltype(*p)(__VA_ARGS__);

#define PropertyDeclare(Type, name, setName, ...)                                   \
    private:                                                                        \
    Type name ## _ __VA_ARGS__;                                                     \
    public:                                                                         \
    inline const Type &name() const { return name ## _; }                           \
    inline void setName(const Type &name) { name ## _ = name; }                     \
    private:

#define PropertyDeclareWithSlot(Type, name, setName, ...)                           \
    private:                                                                        \
    Type name ## _ __VA_ARGS__;                                                     \
    public Q_SLOTS:                                                                 \
    Type name() const { return name ## _; }                                         \
    void setName(const Type &name) { name ## _ = name; }                            \
    private:

#define PtrPropertyDeclare(Type, name, setName, ...)                                \
    private:                                                                        \
    Type *name ## _ __VA_ARGS__;                                                    \
    public:                                                                         \
    inline const Type *name() const                                                 \
        { return name ## _; }                                                       \
    inline void setName(const Type &name)                                           \
        { if ( name ## _ ) { delete name ## _; }                                    \
        name ## _ = new Type( name ); }                                             \
    private:

#define PrimaryKeyPropertyDeclare(ClassName, Type, name, ...)                       \
    Type name __VA_ARGS__;                                                          \
    ClassName() = default;                                                          \
    ClassName(const Type &name ## _): name(name ## _) { }                           \
    operator QVariant() const { return name; }                                      \
    operator Type() const { return name; }

#define DeleteClassCopy(ClassName)                                                  \
    ClassName(const ClassName &) = delete;                                          \
    ClassName &operator=(const ClassName &) = delete;

#define ContainerToJsonArrayAndReturn(container, ...)                               \
    {                                                                               \
        QJsonArray buf;                                                             \
        for (const auto &data: container)                                           \
        {                                                                           \
            buf.append( { data __VA_ARGS__ } );                                     \
        }                                                                           \
        return buf;                                                                 \
    }

#define ContainerToJsonArray(container, ...)                                        \
    [ & ]()                                                                         \
    {                                                                               \
        QJsonArray buf;                                                             \
        for (const auto &data: container)                                           \
        {                                                                           \
            buf.append( { data __VA_ARGS__ } );                                     \
        }                                                                           \
        return buf;\
    }()

#define ContainerToJsonObjectMap(container, target, ...)                            \
    for (const auto &data: Array)                                                   \
    {                                                                               \
        target.insert(__VA_ARGS__(data.toObject()));                                \
    }

#define rforeach (variable, container)                                              \
for (RforeachContainer<__typeof__((container))> _container_((container));           \
    _container_.__howMuch__; _container_.__howMuch__--)                             \
    for (variable = *(--_container_.__now__); ; __extension__ ({ break;}))

template < typename T >
class RforeachContainer {
public:
    inline RforeachContainer(const T& t) : __now__(t.end()), __howMuch__(t.size()) { }
    typename T::const_iterator __now__;
    int __howMuch__;
};

template < typename T >
inline typename std::enable_if< !std::is_pod< T >::value >::type
memset( T*, int, size_t )
{
    static_assert( std::is_pod< T >::value, "memset error: target not pod" );
}

template < typename T >
inline typename std::enable_if< !std::is_pod< T >::value >::type
memcpy( T*, int, size_t )
{
    static_assert( std::is_pod< T >::value, "memcpy error: target not pod" );
}

namespace JQFoundation
{

void eventLoopSleep(const int &delay);

void foreachWidget(QWidget *parent, const std::function<void(QWidget *)> &each, const bool &recursive = false);

void tableWidgetSetHorizontalHeaderLabels(QTableWidget *tableWidget, const QStringList &stringList);

void tableWidgetSetColumnWidth(QTableWidget *tableWidget, const QVector<int> &columnWidth);

void tableWidgetAddString(QTableWidget *tablwWidget, const QStringList &string);

void treeWidgetSetHorizontalHeaderLabels(QTreeWidget *treeWidget, const QStringList &ttringList);

void treeWidgetSetColumnWidth(QTreeWidget *treeWidget, const QVector<int> &columnWidth);

void setWidgetColor(QWidget *label, const QColor &color);

void texetEditMoveCursorToEnd(QTextEdit *textEdit);

void textEditAppendTextToEnd(QTextEdit *textEdit, const QString &string);

QString hashString(const QString &key, const QCryptographicHash::Algorithm &algorithm = QCryptographicHash::Sha1);

QString hashString(const QByteArray &key, const QCryptographicHash::Algorithm &algorithm = QCryptographicHash::Sha1);

QString hashStringWithSalt(const QString &key);

QPoint getWidgetGlobalPos(const QWidget *widget);

QRect getWidgetGlobalGeometry(const QWidget *widget);

QWidget *topParentWidget(QWidget *widget);

const QWidget *topParentWidget(const QWidget *widget);

bool singleApplication(const QString &flag);

bool singleApplicationExist(const QString &flag);

QString byteArrayToHexString(const QByteArray &data);

QByteArray pixmapToByteArray(const QPixmap &pixmap, const QString &format);

QByteArray imageToByteArray(const QImage &image, const QString &format);

QPixmap byteArrayToPixmap(const QByteArray &byteArray);

void lineEditSetToIPLineEdit(QLineEdit *lineEdit);

void lineEditSetToazAZ09LineEdit(QLineEdit *lineEdit);

void lineEditSetTo09LineEdit(QLineEdit *lineEdit);

void widgetSetToTransparent(QWidget *target);

QString randString(const int &stringLength = 40, const bool &autoSetSeed = true);

void waitForSignal(const QObject *sender, const char *signal);

QJsonObject jsonFilter(const QJsonObject &source, const QStringList &leftKey, const QJsonObject &mix = QJsonObject());

QJsonObject jsonFilter(const QJsonObject &source, const char *leftKey, const QJsonObject &mix = QJsonObject());

void setTimerCallback(const int &interval, const std::function< void(const QPointer< QTimer > &) > &callback, const bool &callbackOnStart = false);

void setDebugOutput(const QString &targetFilePath, const bool &argDateFlag = false);

// Template funcation define
template <typename FunType>
bool waitBoolSignal(const typename QtPrivate::FunctionPointer<FunType>::Object *sender, FunType signal);

// Class define
class BeforMain
{
public:
    BeforMain(const std::function<void()> &funcation);
};

class ReadyExit
{
public:
    ReadyExit(const QString &message);

    inline const QString &message() const { return message_; }

    inline operator QString() const { return message_; }

private:
    QString message_;
};

class ShowInformationMessageBoxFromOtherThread: public QObject
{
    Q_OBJECT

public:
    ShowInformationMessageBoxFromOtherThread(const QString &title, const QString &message);

    static void show(const QString &title, const QString &message);

private:
    void readyShow();

private slots:
    void onShow();

private:
    const QString title_;
    const QString message_;
};

class ConnectionManage
{
public:
    ConnectionManage();

    ~ConnectionManage();

    void push(const QMetaObject::Connection &connection);

    void insert(const QString &key, const QMetaObject::Connection &connection);

    void remove(const QString &key);

    void disconnectAll();

    void deleteLater();

private:
    QVector<QMetaObject::Connection> *vectorData_ = nullptr;
    QMap<QString, QMetaObject::Connection> *mapData_ = nullptr;
};

class ThreadHelper: public QObject
{
    Q_OBJECT

public:
    ThreadHelper(QMutex *&mutexForWait);

    void run(const std::function<void()> &callback);

public slots:
    void onRun();

signals:
    void readyRun();

private:
    QMutex mutex_;
    QList< std::function<void()> > waitCallbacks_;
    QMutex *&mutexForWait_;
};

class Thread: public QThread
{
public:
    Thread();

    ~Thread();

    void start(const std::function< void() > &callback);

    void waitForStart(const std::function< void() > &callback);

    void waitForRunning();

private:
    void run();

private:
    ThreadHelper *helper_ = nullptr;
    QMutex *mutexForWait_ = nullptr;
};

class InvokeFromThreadHelper: public QObject
{
    Q_OBJECT

public:
    void addCallback(const std::function<void()> &callback);

public slots:
    void onRun();

private:
    QMutex mutex_;
    QList< std::function<void()> > waitCallbacks_;
};

class InvokeFromThread
{
public:
    static void invoke(QThread *thread, const std::function<void()> &callback);

    static void waitForInvoke(QThread *thread, const std::function<void()> &callback);

private:
    static QMutex mutex_;
    static QMap< QThread *, InvokeFromThreadHelper * > helpers_;
};

class WaitForOtherThread
{
public:
    int wait();

    void finish(const int &flag = 0);

private:
    QMutex mutex_;
    int flag_ = 0;
};

// Template define
template <typename Func1>
bool waitBoolSignal(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal)
{
    QEventLoop eventLoop;

    QObject::connect(
                sender,
                signal,
                sender,
                [&](const bool &flag)
    {
        eventLoop.exit(flag);
    },
    Qt::DirectConnection);

    return eventLoop.exec();
}

}

#endif//__JQFoundation_h__
