/*****************************************************************************************************
*
*  Nom du projet  :   Mon carnet d'adresse.
*  Code Version   :   1.0
*  Développé par  :   BAYO Patrick - ESATIC, Côte d'ivoire - Mai 2020
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
****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con){
    fprintf(stderr,"\nError %s [%d] \n",mysql_error(con),mysql_errno(con));
    mysql_close(con);
    exit(1);
}

void Connect_db(MYSQL *con){
  
    static char *host = "localhost";
    static char *dbuser = "Patrick";
    static char *dbpassw = "password";

    if(con == NULL){
        fprintf(stderr,"mysql_init() a échoué. \n");
        exit(1);
    }   

    if(!(mysql_real_connect(con,host,dbuser,dbpassw,"testmysql",3306,NULL,0))){
        finish_with_error(con);
    }
    
}