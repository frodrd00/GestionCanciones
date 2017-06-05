#ifndef COPIAR_H
#define COPIAR_H

#include <QString>
#include <QDir>


class Copiar
{
public:
    Copiar();
    ~Copiar();

    QString crearCarpeta(QString dir);
    void copiarCanciones(QString dirOrigen, QString dirDestino);

};

#endif // COPIAR_H
