#include "leer.h"
#include "mainwindow.h"



Leer::Leer()
{

}

Leer::~Leer()
{

}

//RECORRE EL DIRECTORIO SELECCIONADO
void Leer::recorreDirectorio(QString dir)
{
    QString nombre;
    QDirIterator dirIt(dir);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
              nombre = QFileInfo(dirIt.filePath()).completeBaseName();
                if(nombre.contains('.')){
                    QMessageBox msgBox;
                    msgBox.setText("El fichero" + nombre + "contiene caracteres no validos '.', no será leido");
                    msgBox.setWindowTitle("Error nombre fichero");
                    msgBox.exec();
                }
               else{
                  QString ruta = dirIt.filePath();
                  QFileInfo file(ruta);//coje la informacion del path
                  QString name = file.fileName();//coje el nombre del archivo
                 // QString ext = file.completeSuffix();//coje la extension
                if(name != ".." && name != ".")
                    setListaPaths(ruta);

                }
    }
}


//LEE LOS METADATOS DE LA CANCION PASADA COMO rutaCancion
Song* Leer::leerMetadatos(const char* rutaCancion)
{
    TagLib::FileRef cancion (rutaCancion);
    TagLib::String artista = cancion.tag()->artist();
    TagLib::String album = cancion.tag()->album();
    TagLib::String titulo = cancion.tag()->title();
    uint anho = cancion.tag()->year();

    Song *s = new Song(artista.to8Bit(true),album.to8Bit(true),titulo.to8Bit(true),anho);

    return s;
}

//CREAR ARCHIVO DE TEXTO y GUARDAR INFORMACION DE LOS METADATOS EN LA CARPETA SELECCIONADA
void Leer::guardarInformacionFichero(QString dir)
{
       QString outputFilename = dir + "/Informacion.txt";
       QFile outputFile(outputFilename);

       outputFile.open(QIODevice::WriteOnly);

       QTextStream stream(&outputFile);

       stream << "**********************" << endl;
       stream << QString::fromUtf8("Información de las canciones:\n");
       stream << "**********************" << endl;

       for (int var = 0; var < sizeCanciones(); ++var) {
          stream << QString::fromUtf8("Canción ")
                                      <<  var + 1 << endl;
          stream << QString::fromUtf8("Título: ")
                                      << QString::fromStdString(getCancion(var).getTitulo()) << endl;
          stream << QString::fromUtf8("Artista: ")
                                      << QString::fromStdString(getCancion(var).getArtista()) << endl;
          stream << QString::fromUtf8("Album: ")
                                      << QString::fromStdString(getCancion(var).getAlbum()) << endl;
          stream << QString::fromUtf8("Año: ")
                                      << QString::number(getCancion(var).getYear()) << endl;
          stream << "**********************" << endl;

       }

         outputFile.close();

}

//GETTERS AND SETTERS
Song Leer::getCancion(int i)
{
    return *listaCanciones[i];
}

void Leer::setCancion(Song *s)
{
    listaCanciones.push_back(s);
}

int Leer::sizeCanciones()
{
    return listaCanciones.size();
}

QString Leer::getListaPaths(int i)
{
    return listaPaths[i];
}

void Leer::setListaPaths(QString s)
{
    listaPaths.push_back(s);
}

int Leer::sizeListaPaths()
{
    return listaPaths.size();
}

QString Leer::getListaPathsSongs(int i)
{
    return listaPathsSongs[i];
}

void Leer::setListaPathsSongs(QString s)
{
    listaPathsSongs.push_back(s);
}

int Leer::sizeListaPathsSongs()
{
    return listaPathsSongs.size();
}






