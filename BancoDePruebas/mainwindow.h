#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QMainWindow>
#include <QMessageBox>
#include "leer.h"
#include "copiar.h"
#include "organizar.h"
#include "song.h"

//Tiempo
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     void escribirLog(QString m, int time, int aviso);
     void pintarColumnaOrganizar(int columna);

     QString getDirectorio();
     void setDirectorio(QString d);

     //log
     QString getListaLog(int i);
     void setListaLog(QString s);
     int sizeListaLog();

private slots:
    void on_botonLeer_clicked();
    void on_botonCopiar_clicked();
    void on_botonOrganizar_clicked();
    void on_action_Click_para_ayuda_triggered();
    void on_action_Empezar_de_nuevo_triggered();
    void on_abrirTxt_clicked();
    void on_abrirDir_clicked();
    void on_abrirDirCopia_clicked();
    void on_abrirLog_clicked();
    void on_botonGuardarLog_clicked();

private:
    Ui::MainWindow *ui;

    //enumeracion para la tabla de info
    enum Tabla1
    {
      TITULO, ARTISTA, ALBUM, ANHO, PLAY
      // 0 1 2 3
    };

    //enumeracion para la tabla de log
    enum Tabla2
    {
      MENSAJE, TIEMPO
      // 0 1
    };

    QString directorio;

    Leer *l ;
    Copiar *c;
    Organizar *o;

    //mensajes del log
    vector<QString> mensajesLog ;

};

#endif // MAINWINDOW_H
