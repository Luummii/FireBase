#include "firebase.h"
#include <QDir>

FireBase::FireBase(QObject *parent) : QObject(parent)
{

}

FireBase::FireBase(QString &http, const QString &token)
{
    urlFireBase = http;
    this->token = token;    
}

FireBase::FireBase(QJsonObject &object) :document(object)
{

}

FireBase::FireBase(QJsonDocument &document) :document(document)
{

}

FireBase *FireBase::child(QString &childName)
{
    HTTP.clear();
    HTTP.append(urlFireBase).append(childName).append(".json?auth=").append(token);    
    FireBase *firebase = new FireBase();
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

FireBase *FireBase::value(QJsonObject &object)
{
    FireBase *firebase = new FireBase(object);
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);    
    return firebase;
}

FireBase *FireBase::value(QJsonDocument &document)
{
    FireBase *firebase = new FireBase(document);
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

void FireBase::push(){ connectFireBase(QByteArray("POST"));}

void FireBase::set(){ connectFireBase(QByteArray("PUT"));}

void FireBase::update(){ connectFireBase(QByteArray("PATCH"));}

void FireBase::remove(){ connectFireBase(QByteArray("DELETE"));}

QString FireBase::get()
{
    QUrl url = QUrl::fromUserInput(HTTP);    
    QNetworkRequest request;    
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Accept-Encoding","identity");
    request.setUrl(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(request);

    QEventLoop wait;
    connect(manager, &QNetworkAccessManager::finished,
            this, &FireBase::networkRequestResult);
    connect(manager, &QNetworkAccessManager::finished,
            manager, &QNetworkAccessManager::deleteLater);
    connect(manager, &QNetworkAccessManager::finished,
            this, &FireBase::destroyFireSlot);
    connect(manager, &QNetworkAccessManager::finished,
            &wait, &QEventLoop::quit);
    QTimer::singleShot(10000, &wait, &QEventLoop::quit);
    wait.exec();

    return result;
}

void FireBase::connectFireBase(QByteArray method)
{
    QNetworkRequest request;
    QUrl url(HTTP);    
    request.setUrl(url);

    QBuffer *buffer = new QBuffer();
    buffer->open((QBuffer::ReadWrite));
    buffer->write(document.toJson());
    buffer->seek(0);
    buffer->close();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->sendCustomRequest(request, method, buffer);

    connect(manager, &QNetworkAccessManager::finished,
            buffer, &QBuffer::deleteLater);
    connect(manager, &QNetworkAccessManager::finished,
            manager, &QNetworkAccessManager::deleteLater);
    connect(manager, &QNetworkAccessManager::finished,
            this, &FireBase::destroyFireSlot);
}

FireBase *FireBase::orderBy(QString &orderBy)
{
    QString str = QString("&orderBy=%22%1%22").arg(orderBy);
    HTTP.append(str);
    FireBase *firebase = new FireBase();
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

FireBase *FireBase::startAt(int start_at)
{
    QString str = QString("&startAt=%1").arg(start_at);
    HTTP.append(str);
    FireBase *firebase = new FireBase();
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

FireBase *FireBase::limitToFirst(int limit_to_first)
{    
    QString str = QString("&limitToFirst=%1").arg(limit_to_first);
    HTTP.append(str);
    FireBase *firebase = new FireBase();
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

FireBase *FireBase::endAt(int end_at)
{
    QString str = QString("&endAt=%1").arg(end_at);
    HTTP.append(str);
    FireBase *firebase = new FireBase();
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

FireBase *FireBase::limitToLast(int limit_to_last)
{
    QString str = QString("&limitToLast=%1").arg(limit_to_last);
    HTTP.append(str);
    FireBase *firebase = new FireBase();
    connect(this, &FireBase::destroyFire,
            firebase, &FireBase::deleteLater);
    return firebase;
}

void FireBase::networkRequestResult(QNetworkReply *reply)
{
    QString result = (QString)reply->readAll();
    this->result = result;
    reply->deleteLater();
}

void FireBase::destroyFireSlot()
{
    emit destroyFire();
}
