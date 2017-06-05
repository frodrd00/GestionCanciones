#ifndef SONG_H
#define SONG_H

#include <string>

using namespace std;


class Song
{
public:

    Song();
    ~Song();

    //constructor sobrecargado;
    Song(string artista, string album, string titulo, int year);

    //getters pora obtener la informacion de las canciones
    string getArtista();
    string getAlbum();
    string getTitulo();
    int getYear();

    //setter por si se quiere cambiar algun atributo de la cancion
    void setArtista(string artista);
    void setAlbum(string album);
    void setTitulo(string titulo);
    void setYear(int year);



//atributos de la cancion
private:
    string artista;//nombre del artista
    string album; //nombre del album
    string titulo; //titulo de la cancion
    int year;//año de la cancion
};

#endif // SONG_H
