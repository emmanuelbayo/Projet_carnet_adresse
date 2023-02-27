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
******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "../include/Database.h"
#include "../include/TypeDef.h"


int ajout_contact_db(Contact contact,gchar *genre){

    int res = 0;
   
    MYSQL *con = mysql_init(NULL);
    Connect_db(con);

    char requete[280];
    sprintf(requete,"INSERT INTO contact(nom,prenom,numero,genre,adresse) VALUES ('%s','%s','%s','%s','%s');",
            contact.nom,contact.prenom,contact.numero,genre,contact.adresse);
    if(mysql_query(con,requete)){
        finish_with_error(con);
        res =-1;
    }
    else{
        res = 1;
    }
    mysql_close(con);
    return res;
}

void show_contact_db(GtkListStore  *store,GtkTreeIter iter){

    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[100];
    sprintf(requete,"select * from contact;");
    if(mysql_query(con,requete)){
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if(result == NULL)
        {
            finish_with_error(con);
        }
        MYSQL_ROW row;
        while((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,COL_NOM,row[1],COL_PRENOM, row[2],COL_NUMERO, row[3],COL_ADRESSE,row[5],4,row[6],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

void show_last_contact_db(GtkListStore  *store,GtkTreeIter iter){
    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[100];
    sprintf(requete,"select * from contact order by id desc limit 1;");
    if(mysql_query(con,requete)){
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if(result == NULL)
        {
            finish_with_error(con);
        }
        MYSQL_ROW row = mysql_fetch_row(result);
        
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,COL_NOM,row[1],COL_PRENOM, row[2],COL_NUMERO, row[3],COL_ADRESSE,row[5],4,row[6],-1);
        
        mysql_free_result(result);
    }
    mysql_close(con);
}

void search_contact_db(GtkListStore *store,GtkTreeIter iter,const char *srch){

    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[250];
    sprintf(requete,"select * from contact where nom like '%c%s%c' or prenom like '%c%s%c' or numero like '%c%s%c';",37,srch,37,37,srch,37,37,srch,37);
    if(mysql_query(con,requete)){
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if(result == NULL){
            finish_with_error(con);
        }
        MYSQL_ROW row;
        while((row = mysql_fetch_row(result)))
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store,&iter,COL_NOM,row[1],COL_PRENOM, row[2],COL_NUMERO, row[3],COL_ADRESSE,row[5],4,row[6],-1);
        }
        mysql_free_result(result);
    }
    mysql_close(con);
}

int get_contact_id(const char *nom,const char *prenom,const char *num,const char *adresse){

    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[500];
    sprintf(requete,"select * from contact where nom ='%s' and prenom = '%s' and numero = '%s' and adresse = '%s' order by id limit 1;",nom,prenom,num,adresse);
    if(mysql_query(con,requete)){
        finish_with_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if(result == NULL){
        finish_with_error(con);
    }
    MYSQL_ROW row=mysql_fetch_row(result);
    int res = atoi(row[0]);
    return res;
}
void get_contact_db(Contact contact, int id){
    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[500];
    sprintf(requete,"select * from contact where id = %d;",id);
    if(mysql_query(con, requete))
    {
        finish_with_error(con);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(con);
        if(result == NULL){
            finish_with_error(con);
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        contact.nom = row[1];
        contact.prenom = row[2];
        contact.numero = row[3];
        contact.adresse = row[4];
        mysql_free_result(result);
    }
}

void delete_contact_db(Contact contact,int id){

    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[100];
    sprintf(requete,"delete from contact where id = %d;",id);
    if(mysql_query(con, requete)){
        finish_with_error(con);
    }
    mysql_close(con);
}

int update_contact_db(Contact contact, int id){
    int res = 0;
    MYSQL *con = mysql_init(NULL);
    Connect_db(con);
    char requete[350];
    sprintf(requete,"update contact set nom='%s', prenom='%s', numero='%s',adresse='%s',reg_date=current_timestamp where id=%d;",contact.nom,contact.prenom,contact.numero,contact.adresse,id);
    if(mysql_query(con,requete)){
        finish_with_error(con);
        res = -1;
    }
    else{
        res = 1;
    }
    mysql_close(con);
    return res;
}