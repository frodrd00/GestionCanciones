#ifndef LEER_H
#define LEER_H

#include <QString>
#include <QFileDialog>
#include <QDirIterator>

//archivo texto
#include <QTextStream>

//taglib
#include <taglib/taglib.h>
#include <taglib/fileref.h>

//vector de canciones
#include <vector>

//clase cancion
#include "song.h"

using namespace std;

//structura para guardar lso datos de la cancion

class Leer
{
public:
    Leer();
    ~Leer();

   Song *leerMetadatos(const char *rutaCancion);
   void recorreDirectorio(QString dir);
   void guardarInformacionFichero(QString dir);


   //songs
   Song getCancion(int i);
   void setCancion(Song *s);
   int sizeCanciones();

   //files
   QString getListaPaths(int i);
   void setListaPaths(QString s);
   int sizeListaPaths();

   //files songs
   QString getListaPathsSongs(int i);
   void setListaPathsSongs(QString s);
   int sizeListaPathsSongs();

 private:
   vector<Song*> listaCanciones;//vector con las canciones
   vector<QString> listaPaths;//vector con todas las direcciones
   vector<QString> listaPathsSongs;//vector con solo direcciones de las canciones
};

#endif // LEER_H
