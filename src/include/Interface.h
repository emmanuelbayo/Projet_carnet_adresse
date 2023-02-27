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
*******************************************************************************/
#ifndef INTERFACE_INCLUDE_H
#define INTERFACE_INCLUDE_H
#include "../fonction/Interface.c"

void loadbuilder();
void on_MainWindow_destroy();
void on_AddContactWindow_destroy();
void on_ViewContactWindow_destroy();
void on_EditContactWindow_destroy();
void on_ShowContactWindow_destroy();
void on_addContactBtn_clicked();
void ViewContactShow();
void on_viewContactBtn_clicked();
void on_aboutBtn_clicked();
void on_ShowContactBtn_clicked();
void on_AddViewContactBtn_clicked();
void on_searchContact_changed();
void on_StatContactBtn_clicked();
void on_EditContactBtn_clicked();
void on_DeleteContactBtn_clicked();
void on_creeContact_clicked();
void on_ValidEditBtn_clicked();
void on_cancelBtnDeleteContact_clicked();
void on_confBtnDeleteContact_clicked();
void on_exportContact_clicked();

#endif