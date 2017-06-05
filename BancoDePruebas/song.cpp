#include "song.h"

Song::Song()
{

}

Song::~Song()
{

}

Song::Song(string artista, string album, string titulo, int year)
{
    this->artista = artista;
    this->album = album;
    this->titulo = titulo;
    this->year = year;
}

string Song::getArtista()
{
    return artista;
}

string Song::getAlbum()
{
    return album;
}

string Song::getTitulo()
{
    return titulo;
}

int Song::getYear()
{
    return year;
}

void Song::setArtista(string artista)
{
    this->artista = artista;
}

void Song::setAlbum(string album)
{
    this->album = album;
}

void Song::setTitulo(string titulo)
{
    this->titulo = titulo;
}

void Song::setYear(int year)
{
    this->year = year;
}

