#include "organizar.h"


Organizar::Organizar()
{

}

Organizar::~Organizar()
{

}
//CREA SUBCARPETAS DE TIPO ELEGIDO: ALBUM, ARTISTA O AÑO
void Organizar::crearSubCarpetas(QString tipo, QString dirOrig)
{
    tipo = tipo.replace("/","y");

    QString dirDest = dirOrig + "(copia)/" + tipo;

    //se crea la carpeta
    QString carpetaCopia = dirDest;
    if(!QDir(carpetaCopia).exists())
        QDir().mkdir(carpetaCopia);

}
//BUSCA LAS SUBCARPETAS DEL DIR COPIA
void Organizar::buscarSubcarpetas(QString dir)
{
    QDirIterator dirIt(dir);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isDir())
               setPathSubCarpetas(dirIt.filePath());
    }
}
//BUSCA LAS CANCIONES DEL DIR COPIA
void Organizar::buscarCanciones(QString dir)
{
    QDirIterator dirIt(dir);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
               setPathCancionesCopia(dirIt.filePath());
    }
}

//BUSCA EL SUBDIRECTORIO A LA QUE HAY QUE MOVER LA CANCION
void Organizar::buscarCarpetaCancion(QString tipo)
{
    bool encontrada = false;
    int tam1 = sizePathCancionesCopia();
    int tam2 = sizePathSubCarpetas();
    //recorre canciones
    for (int i = 0; i < tam1; ++i) {
        encontrada = false;
        QString pathSong = getPathCancionesCopia(i);
        QString metadato = leerMetadato(pathSong.toLatin1().data(), tipo);
        metadato = metadato.replace("/","y");
        //recorre carpetas
        for (int j = 0; j < tam2 && encontrada == false; ++j) {
                QString pathDir = getPathSubcarpetas(j);
                QString nameDir = QDir(pathDir).dirName();
                if(nameDir == metadato){
                    moverCancion(pathSong, pathDir);
                    encontrada = true;
                }
        }
    }

}

//para leer el metadato de cada cancion copia
QString Organizar::leerMetadato(const char *rutaCancion, QString tipo)
{
    TagLib::FileRef cancion (rutaCancion);
    TagLib::String album = cancion.tag()->album();
    TagLib::String artista = cancion.tag()->artist();
    uint anho = cancion.tag()->year();

    if(tipo == "Album"){
        QString retorno = QString::fromStdString(album.to8Bit());
        return retorno;
    }
    else if(tipo == "Artista"){
        QString retorno = QString::fromStdString(artista.to8Bit());
        return retorno;
    }
    else{
        QString retorno = QString::number(anho);
        return retorno;
    }


}
//para mover la cancion
void Organizar::moverCancion(QString dirOrig, QString dirDest)
{

    QFileInfo file(dirOrig);//coje la informacion del path
    QString name = file.baseName();//coje el nombre del archivo
    QString ext = file.completeSuffix();//coje la extension

    dirDest = dirDest + "/" + name + "." + ext;

    //dirOrg: /home/carpeta(copia)/1(copia).mp3 -> dirDest: /home/carpeta(copia)/album/1(copia).mp3

    QFile::rename(dirOrig , dirDest);

    //renombra la cancion
    renombrarCancion(dirDest);

}
//para renombrar la cancion  Artista-Álbum-Título(año).mp3
void Organizar::renombrarCancion(QString dirDest)
{
    const char* rutaCancion = dirDest.toLatin1().data();

    TagLib::FileRef cancion (rutaCancion);
    TagLib::String artista = cancion.tag()->artist();
    TagLib::String album = cancion.tag()->album();
    TagLib::String titulo = cancion.tag()->title();
    uint anho = cancion.tag()->year();

    QFileInfo file(dirDest);//coje la informacion del path
    QString dir =  file.absolutePath();//coje la carpeta en la que esta
    QString ext = file.completeSuffix();//coje la extension

    QString artist = QString::fromStdString(artista.to8Bit());
    artist = artist.replace("/","y");
    artist = artist.replace("-"," ");
    QString albu = QString::fromStdString(album.to8Bit());
    albu = albu.replace("/","y");
    albu = albu.replace("-"," ");
    QString title = QString::fromStdString(titulo.to8Bit());
    title = title.replace("/","y");
    title = title.replace("-"," ");
    QString year = QString::number(anho);

    QString nuevoNombre = dir + "/" + artist +
                          "-" + albu +
                          "-" + title +
                          "(" + year + ")." + ext;

    //por si hay canciones repetidas
    QString ruta = nuevoNombre;
    QFile fileNew(ruta);
    srand(time(NULL));//semilla
    //si ya esite la cancion le pone un num rand a la otra
    if(fileNew.exists()){
        int randNumber = rand() % (100 - 1 ) + 1;//num entre 1-100

        nuevoNombre = dir + "/" + artist +
                                  "-" + albu +
                                  "-" + title +
                                  "(" + year + ")" + "(" +
                                    QString::number(randNumber) + ")." + ext;

        QFile::rename(dirDest , nuevoNombre);
    }
    else
        QFile::rename(dirDest , nuevoNombre);


}

//getters and setters
QString Organizar::getPathSubcarpetas(int i)
{
    return pathSubcarpetas[i];
}

void Organizar::setPathSubCarpetas(QString s)
{
    pathSubcarpetas.push_back(s);
}

int Organizar::sizePathSubCarpetas()
{
    return pathSubcarpetas.size();
}

QString Organizar::getPathCancionesCopia(int i)
{
    return pathCancionesCopia[i];
}

void Organizar::setPathCancionesCopia(QString s)
{
    pathCancionesCopia.push_back(s);
}

int Organizar::sizePathCancionesCopia()
{
    return pathCancionesCopia.size();
}

