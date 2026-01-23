#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "grafo.h"

void loadNodes(const QString& filePath, Grafo& grafo){
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject raiz = doc.object();

    QJsonArray elementos = raiz["elementos"].toArray();

    for(const auto& item : elementos){
        QJsonObject obj = item.toObject();
        long long id = obj["id"].toVariant().toLongLong();
        //...logica para latitude e longitude
    }
}
