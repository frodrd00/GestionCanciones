#include "copiar.h"

Copiar::Copiar()
{

}

Copiar::~Copiar()
{

}

QString Copiar::crearCarpeta(QString dir)
{
    QString carpetaCopia = dir + "(copia)";

    if(!QDir(carpetaCopia).exists())
        QDir().mkdir(carpetaCopia);

    return carpetaCopia;
}

void Copiar::copiarCanciones(QString dirOrigen, QString dirDestino)
{
    QFile::copy(dirOrigen, dirDestino);
}

