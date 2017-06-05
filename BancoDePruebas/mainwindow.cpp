#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//PARTE 1 LEER CANCIONES MP3 FICHERO ELEGIDO POR EL USUARIO
void MainWindow::on_botonLeer_clicked()
{

    //selecciona la carpeta
    QString dir = QFileDialog::getExistingDirectory(this, tr("Elige una carpeta"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                              | QFileDialog::DontResolveSymlinks);


    //se guarda el directorio
    setDirectorio(dir);

    //si no se ha elegido una carpeta, no se avanza
    if(dir != NULL){

            setListaLog("***REGISTRO INICIADO***");

            //muestra por pantalla dir
            ui->lineDir->setText(getDirectorio());

            //muesta por pantalla el dir de la informacion.txt
            ui->lineTxt->setText(getDirectorio() + "/Informacion.txt");


            //tiempo
            QTime time;
            time.start();

            escribirLog("LEER INICIADO",time.elapsed(),1);

            l = new  Leer();

            //Recorre el directorio seleccionado
            l->recorreDirectorio(dir);

            escribirLog("Se ha recorrido el directorio elegido",time.elapsed(),0);

            //recorre todos los paths archivos encontrados
            for (int i = 0; i < l->sizeListaPaths(); ++i) {

                QString path = l->getListaPaths(i);// coje un path

                QFileInfo file(path);//coje la informacion del path
                QString name = file.fileName();//coje el nombre del archivo
                QString ext = file.completeSuffix();//coje la extension

                if(ext == "mp3"){
                    //se lee la cancion
                     Song *s = l->leerMetadatos(path.toLatin1().data());

                    //se mete en el vector de canciones
                    l->setCancion(s);

                    //se mete en el vector de path de canciones
                    l->setListaPathsSongs(path);

                    escribirLog("El archivo " + name + " es correcto " + ext ,time.elapsed(),0);

                }else{
                   escribirLog("El archivo " + name + " no es correcto " + ext ,time.elapsed(),-1);
                }

            }

            //FOR QUE RECORRE LA LISTA DE CANCIONES Y LO MUESTRA POR PANTALLA
            for (int var = 0; var < l->sizeCanciones(); ++var) {

                string titulo = l->getCancion(var).getTitulo();
                string artista = l->getCancion(var).getArtista();
                string album = l->getCancion(var).getAlbum();
                int year = l->getCancion(var).getYear();

                //NUEVA FILA
                int fila = ui->tablaInfo->rowCount();

                ui->tablaInfo->insertRow(fila);
                ui->tablaInfo->setItem(fila , TITULO,
                                       new QTableWidgetItem(QString::fromStdString(titulo)));
                ui->tablaInfo->setItem(fila , ARTISTA,
                                       new QTableWidgetItem(QString::fromStdString(artista)));
                ui->tablaInfo->setItem(fila , ALBUM,
                                       new QTableWidgetItem(QString::fromStdString(album)));
                ui->tablaInfo->setItem(fila , ANHO,
                                       new QTableWidgetItem(QString::number(year)));
            }

             escribirLog("Se ha mostrado la información por pantalla", time.elapsed(),0);


             //para guardar informacion en txt
             l->guardarInformacionFichero(dir);

             escribirLog("Se ha guardado la información en el fichero", time.elapsed(),0);
             escribirLog("FIN: Se han leido " + QString::number(l->sizeCanciones()) + " canciones", time.elapsed(),1);

             int tiempoTotal = time.elapsed();

             ui->tiempo1->setText(QString::number(tiempoTotal) + " ms");

             ui->botonLeer->setDisabled(true);
             ui->botonCopiar->setDisabled(false);
             ui->abrirDir->setDisabled(false);
             ui->abrirTxt->setDisabled(false);

             QMessageBox msgBox;
             msgBox.setText("Carpeta leída, Tiempo: " + QString::number(tiempoTotal) + " ms");
             msgBox.setWindowTitle("Aviso");
             msgBox.exec();

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("No has seleccionado una carpeta");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }

}
/*****************************************************************************************/

//PARTE 2 COPIAR LAS CANCIONES A OTRA CARPETA
void MainWindow::on_botonCopiar_clicked()
{

    //muestra pantalla dir copia de las canciones
    ui->lineDirCopia->setText(getDirectorio() + "(copia)");

    QTime time;
    time.start();

    escribirLog("COPIAR INICIADO", time.elapsed(),1);

    c = new Copiar();

    QString carpeta = c->crearCarpeta(getDirectorio());

    escribirLog("Se ha creado la carpeta " + carpeta, time.elapsed(),0);

    for (int var = 0; var < l->sizeListaPathsSongs(); ++var) {

        QFileInfo file(l->getListaPathsSongs(var));//coje la informacion del path
        QString name = file.baseName();//coje el nombre del archivo
        QString ext = file.suffix();// coje la extension
        QString nuevo = carpeta + "/" + name + "(copia)." + ext;
        c->copiarCanciones(l->getListaPathsSongs(var), nuevo);

        escribirLog("La canción " + name + " se ha copiado a " + carpeta
                    , time.elapsed(),0);
    }

    escribirLog("FIN: Se han copiado " + QString::number(l->sizeListaPathsSongs()) + " canciones a " + carpeta
                , time.elapsed(),1);

    int tiempoTotal = time.elapsed();

    ui->tiempo2->setText(QString::number(tiempoTotal) +" ms");
    ui->botonCopiar->setDisabled(true);
    ui->botonOrganizar->setDisabled(false);
    ui->comboBox->setDisabled(false);
    ui->abrirDirCopia->setDisabled(false);

    QMessageBox msgBox;
    msgBox.setText("Canciones copiadas, Tiempo: " + QString::number(tiempoTotal) +" ms");
    msgBox.setWindowTitle("Aviso");
    msgBox.exec();

}
/*****************************************************************************************/

//PARTE 3 ORGANIZAR
void MainWindow::on_botonOrganizar_clicked()
{
    QTime time;
    time.start();

    escribirLog("ORGANIZAR INICIADO", time.elapsed(),1);

    o = new Organizar();

    //CREAR LAS SUBCARPETAS POR EL TIPO ELEGIDO
    QString tipoOrganizacion = ui->comboBox->currentText();

    int tam = l->sizeCanciones();

    if(tipoOrganizacion == "Album"){

        //CREAR SUBCARPETA CON EL NOMBRE DEL ALBUM
        for (int i = 0; i < tam; ++i) {
            QString album = QString::fromStdString(l->getCancion(i).getAlbum());
            o->crearSubCarpetas(album,getDirectorio());
        }

        //metodo para ordenar las columnas de la tabla
        pintarColumnaOrganizar(ALBUM);


    }else  if(tipoOrganizacion == "Artista"){

        for (int i = 1; i < tam ; ++i) {

            QString artista = QString::fromStdString(l->getCancion(i).getArtista());
            o->crearSubCarpetas(artista,getDirectorio());
        }

        //metodo para ordenar las columnas de la tabla
         pintarColumnaOrganizar(ARTISTA);


    }else{

        for (int i = 0; i < tam; ++i) {

            QString ano = QString::number(l->getCancion(i).getYear());
            o->crearSubCarpetas(ano,getDirectorio());
        }

        //metodo para ordenar las columnas de la tabla
        pintarColumnaOrganizar(ANHO);

    }

     escribirLog("Subcarpetas creadas", time.elapsed(),0);

    //busca las carpetas
     o->buscarSubcarpetas(getDirectorio() + "(copia)");

     escribirLog("Subcarpetas encontradas", time.elapsed(),0);

     //busca las canciones
     o->buscarCanciones(getDirectorio() + "(copia)");

     escribirLog("Canciones encontradas", time.elapsed(),0);

     //MUEVE LA CANCION A SU TIPO DE CARPETA
     o->buscarCarpetaCancion(tipoOrganizacion);

    escribirLog("FIN: Organización por " + tipoOrganizacion + " en subcarpetas terminado", time.elapsed(),1);

    int tiempoTotal = time.elapsed();

    ui->tiempo3->setText(QString::number(tiempoTotal) + " ms");
    ui->botonOrganizar->setDisabled(true);
    ui->comboBox->setDisabled(true);

    //log
    ui->lineLog->setText(getDirectorio() + "/log.txt");
    ui->botonGuardarLog->setDisabled(false);

    QMessageBox msgBox;
    msgBox.setText("Canciones organizadas, Tiempo: " + QString::number(tiempoTotal) + " ms");
    msgBox.setWindowTitle("Aviso");
    msgBox.exec();


}
/*****************************************************************************************/

//METODO PARA ESCRIBIR EN EL LOG
void MainWindow::escribirLog(QString m, int time, int aviso)
{
    int fila = ui->tablaLog->rowCount();

    ui->tablaLog->insertRow(fila);
    ui->tablaLog->setItem(fila , MENSAJE,
                           new QTableWidgetItem(m));
    ui->tablaLog->setItem(fila , TIEMPO,
                           new QTableWidgetItem(QString::number(time)));

    if(aviso == -1)//para mostrar los errores como al leer ficheros no validos
     {
          ui->tablaLog->item(fila,MENSAJE)->setBackgroundColor(Qt::red);
          ui->tablaLog->item(fila,TIEMPO)->setBackgroundColor(Qt::red);
     }

     if(aviso == 0){

         ui->tablaLog->item(fila,MENSAJE)->setBackgroundColor(Qt::yellow);
         ui->tablaLog->item(fila,TIEMPO)->setBackgroundColor(Qt::yellow);
     }

     if(aviso == 1){

         ui->tablaLog->item(fila,MENSAJE)->setBackgroundColor(Qt::green);
         ui->tablaLog->item(fila,TIEMPO)->setBackgroundColor(Qt::green);
     }

     //lo guarda en el archivo log
     QDateTime dt;
     QString st = dt.currentDateTime().toString() + " -> " + m + ", Tiempo invertido: " + QString::number(time) + " ms";
     setListaLog(st);

}


//BOTON PARA GUARDAR EL LOG DE LA TABLA AL ACABAR DE ORGANIZAR
void MainWindow::on_botonGuardarLog_clicked()
{
    QString outputFilename = getDirectorio() + "/log.txt";
    QFile outputFile(outputFilename);
    outputFile.open(QIODevice::WriteOnly);
    QTextStream stream(&outputFile);

    for (int var = 0; var < sizeListaLog(); ++var) {
        stream << "**********************" << endl;
        stream << getListaLog(var).toUtf8() << endl;
        stream << "**********************" << endl;
    }

        ui->abrirLog->setDisabled(false);

        QMessageBox msgBox;
        msgBox.setText("El registro(log) ha sido guardado");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();

}

//AYUDA PARA UTILIZAR EL PROGRAMA
void MainWindow::on_action_Click_para_ayuda_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("1.Pulsa LEER para empezar a leer las canciones.\n2.Pulsa COPIAR para iniciar la copia de las canciones a otra carpeta.\n3.Elige el tipo de organización y dale al boton ORGANIZAR para organizar las canciones por el tipo elegido.");
    msgBox.setWindowTitle("Ayuda");
    msgBox.exec();
}
//PARA ORGANIZAR LA TABLA DE INFO POR EL TIPO ELEGIDO
void MainWindow::pintarColumnaOrganizar(int columna)
{
    if(columna == ALBUM){
         ui->tablaInfo->sortItems(ALBUM, Qt::AscendingOrder);
    }
    else if(columna == ARTISTA){
         ui->tablaInfo->sortItems(ARTISTA, Qt::AscendingOrder);
    }
    else{
         ui->tablaInfo->sortItems(ANHO, Qt::AscendingOrder);
    }

    int numFilas = ui->tablaInfo->rowCount();

    for (int var = 0; var < numFilas; ++var) {
        ui->tablaInfo->item(var,columna)->setBackgroundColor(Qt::green);
   }

}

//BORRAR CONTENIDO MAIN WINDOW
void MainWindow::on_action_Empezar_de_nuevo_triggered()
{
    ui->tablaInfo->clearContents();
    ui->tablaInfo->setRowCount(0);
    ui->tablaLog->clearContents();
    ui->tablaLog->setRowCount(0);

    ui->lineDir->clear();
    ui->lineDirCopia->clear();
    ui->lineTxt->clear();
    ui->lineLog->clear();
    ui->tiempo1->setText("0 ms");
    ui->tiempo2->setText("0 ms");
    ui->tiempo3->setText("0 ms");

    ui->botonLeer->setDisabled(false);
    ui->botonCopiar->setDisabled(true);
    ui->botonOrganizar->setDisabled(true);
    ui->comboBox->setDisabled(true);

    ui->abrirDir->setDisabled(true);
    ui->abrirDirCopia->setDisabled(true);
    ui->abrirTxt->setDisabled(true);
    ui->abrirLog->setDisabled(true);
    ui->botonGuardarLog->setDisabled(true);

}
//abrir archivo informacion txt
void MainWindow::on_abrirTxt_clicked()
{
    QString ruta = getDirectorio()+"/Informacion.txt";
    QFile file(ruta);
    if(file.exists(ruta))
        QDesktopServices::openUrl(ruta);
    else{
        QMessageBox msgBox;
        msgBox.setText("La ruta ha sido modificada");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();
    }


}
//abrir directorio elegido
void MainWindow::on_abrirDir_clicked()
{
    QString ruta = getDirectorio();
    QFile file(ruta);
    if(file.exists(ruta))
        QDesktopServices::openUrl(ruta);
    else{
        QMessageBox msgBox;
        msgBox.setText("La ruta ha sido modificada");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();
    }

}
//abrir directorio copia
void MainWindow::on_abrirDirCopia_clicked()
{
    QString ruta = getDirectorio()+"(copia)";
    QFile file(ruta);
    if(file.exists(ruta))
        QDesktopServices::openUrl(ruta);
    else{
        QMessageBox msgBox;
        msgBox.setText("La ruta ha sido modificada");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();
    }
}
//abrir el log
void MainWindow::on_abrirLog_clicked()
{
    QString ruta = getDirectorio()+"/log.txt";
    QFile file(ruta);
    if(file.exists(ruta))
        QDesktopServices::openUrl(ruta);
    else{
        QMessageBox msgBox;
        msgBox.setText("La ruta ha sido modificada");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();
    }
}


//directorio elegido
QString MainWindow::getDirectorio()
{
    return directorio;
}

void MainWindow::setDirectorio(QString d)
{
    directorio = d;
}

//vector de registro log
QString MainWindow::getListaLog(int i)
{
    return mensajesLog[i];
}

void MainWindow::setListaLog(QString s)
{
    mensajesLog.push_back(s);
}

int MainWindow::sizeListaLog()
{
    return mensajesLog.size();
}
