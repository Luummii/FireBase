#ifndef FIREBASE_H
#define FIREBASE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QBuffer>
#include <QDebug>
#include <QUrl>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

class FireBase : public QObject
{
    Q_OBJECT

public:
    explicit FireBase(QObject *parent = 0);
    explicit FireBase(QString &http, const QString &token);

public:
    void push();
    void set();
    void update();
    void remove();
    QString get();

public:
    FireBase *child(QString &childName);
    FireBase *value(QJsonObject &object);
    FireBase *value(QJsonDocument &document);
    FireBase *orderBy(QString &orderBy);
    FireBase *startAt(int start_at);
    FireBase *limitToFirst(int limit_to_first);
    FireBase *endAt(int end_at);
    FireBase *limitToLast(int limit_to_last);

private:
    QString urlFireBase = "";
    QString token = "";
    QString result = "";
    QString HTTP = "";
    QJsonDocument document;

signals:
    void sendData(QJsonObject &root);

private slots:
    void connectFireBase(QByteArray method);
    void networkRequestResult(QNetworkReply *reply);
};


#endif // FIREBASE_H
