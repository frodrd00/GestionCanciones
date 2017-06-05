#ifndef ORGANIZAR_H
#define ORGANIZAR_H

#include "song.h"
#include "vector"
#include "leer.h"
#include <QFile>
#include <QDir>

#include <stdlib.h>


class Organizar
{
public:
    Organizar();
    ~Organizar();

    void crearSubCarpetas(QString tipo, QString dirOrig);
    void buscarSubcarpetas(QString dir);
    void buscarCanciones(QString dir);
    void buscarCarpetaCancion(QString tipo);
    QString leerMetadato(const char* rutaCancion, QString tipo);
    void moverCancion(QString dirOrig, QString dirDest);
    void renombrarCancion(QString dirDest);

    //setters & getters
    QString getPathSubcarpetas(int i);
    void setPathSubCarpetas(QString s);
    int sizePathSubCarpetas();

    QString getPathCancionesCopia(int i);
    void setPathCancionesCopia(QString s);
    int sizePathCancionesCopia();


private:
    vector<QString> pathSubcarpetas;
    vector<QString> pathCancionesCopia;


};

#endif // ORGANIZAR_H
