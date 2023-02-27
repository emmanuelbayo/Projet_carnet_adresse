/*****************************************************************************************************
*
*  Nom du projet  :   Mon carnet d'adresse
*  Code Version   :   1.0
* Développé par   :   BAYO Patrick - ESATIC, Côte d'ivoire - Mai 2020
*        GitHub   :   https://github.com/emmanuelbayo
*
*  Note1 : Ce programme a été Developpé sur Linux (Ubuntu 18.04 LTS) avec "Gtk+ 3.12" et "Glade 3.22.1".
*          Vous pouvez démarrer ce programme avec cette version ou une version supérieur.
*          Si vous voulez démarrer le programme avec un autre système d'exploitation, veuillez
*          consulter : https://www.gtk.org/download/ 
*
*  Note2 : Le fichier makefile est un fichier utilisé par le programme make pour exécuter un ensemble 
*          d'action comme la compilation d'un programme,l'archivage de document, la mise à jour 
*          de site. Ici, nous l'utilisons pour compiler le projet.          
*
*           Compilation (Linux)  :  Pour compiler, utilisez la commande "make"
*
*            Exécutable (Linux)  :  ./carnet
*
* Le code source disponible sur  :  https://github.com/emmanuelbayo
*
***********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "include/Database.h"
#include "include/Interface.h"

GtkBuilder *builder;
GtkWidget  *MainWindow;
GtkWidget  *AddContactWindow;
GtkWidget  *AboutDialogWindow;
GtkWidget  *EditContactWindow;
GtkWidget  *ShowContactWindow;
GtkWidget  *ViewContactWindow;
GtkWidget  *AlertDeleteContactDialog;


int main(int argc, char *argv[]){

    gtk_init(&argc, &argv);

    loadbuilder();

    MainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
    AddContactWindow = GTK_WIDGET(gtk_builder_get_object(builder, "AddContactWindow"));
    AboutDialogWindow = GTK_WIDGET(gtk_builder_get_object(builder,"AboutDialogWindow"));
    EditContactWindow = GTK_WIDGET(gtk_builder_get_object(builder,"EditContactWindow"));
    ShowContactWindow =GTK_WIDGET(gtk_builder_get_object(builder,"ShowContactWindow"));
    ViewContactWindow =GTK_WIDGET(gtk_builder_get_object(builder,"ViewContactWindow"));
    AlertDeleteContactDialog = GTK_WIDGET(gtk_builder_get_object(builder,"AlertDeleteContactDialog"));

    
    GtkLabel *TimeLabel = GTK_LABEL(gtk_builder_get_object(builder, "date_lbl"));
    GDateTime *datetime = g_date_time_new_now_local ();


    char *Time;
    Time = g_date_time_format (datetime, "%d-%m-%Y --- %H:%M ");
    gtk_label_set_text (TimeLabel, Time);

    gtk_widget_show(MainWindow);                
    gtk_main();

    return 0;
}
