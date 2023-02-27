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
*****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "../include/Contact.h"

#define test "\
#!/bin/bash \n\
cd python \n\
python3 test.py \n\
"
#define export "\
#!/bin/bash \n\
gedit fichier.txt \n\
"

GtkBuilder *builder;
GtkWidget  *MainWindow;
GtkWidget  *AddContactWindow;
GtkWidget  *AboutDialogWindow;
GtkWidget  *EditContactWindow;
GtkWidget  *ShowContactWindow;
GtkWidget  *ViewContactWindow;
GtkWidget  *AlertDeleteContactDialog;

GtkTreeIter iter;
GtkListStore *store;
GtkTreeView *treeview;

int count =0;

void loadbuilder(){
    builder = gtk_builder_new_from_file("glade/app.glade");
    gtk_builder_connect_signals(builder, NULL);
}

/*------------------------ Les fonctions appelées lorsque le visiteur clique sur un bouton----------------------------*/

void on_addContactBtn_clicked()
{   
    gtk_widget_hide(GTK_WIDGET(ViewContactWindow));
    gtk_widget_hide(GTK_WIDGET(MainWindow));
    gtk_widget_show_all(AddContactWindow);
}

void ViewContactShow(){   
    gtk_widget_hide(GTK_WIDGET(AddContactWindow));
    gtk_widget_hide(GTK_WIDGET(ShowContactWindow));
    gtk_widget_hide(GTK_WIDGET(EditContactWindow));
    gtk_widget_hide(GTK_WIDGET(MainWindow));
    gtk_widget_show_all(ViewContactWindow);
}

void on_viewContactBtn_clicked(){

    
    store = GTK_LIST_STORE(gtk_builder_get_object(builder,"liststore1"));
    show_contact_db(store,iter);

    ViewContactShow();
    count = count + 1;
}

void on_aboutBtn_clicked(){
    gtk_widget_show_all(AboutDialogWindow);
}

void on_ShowContactBtn_clicked(){

    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkTreeSelection *selection;

    char *noms, *prenoms, *num, *adress;

    GtkLabel *nomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNomContact"));
    GtkLabel *prenomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowPrenomContact"));
    GtkLabel *numeroContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNumeroContact"));
    GtkLabel *adresseContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowAdressContact"));

    treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder,"treeviewContact"));

    selection = gtk_tree_view_get_selection(treeview);
    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter);

    gtk_tree_model_get(model, &iter, COL_NOM, &noms,COL_PRENOM, &prenoms, COL_NUMERO, &num, COL_ADRESSE, &adress, -1);


    gtk_label_set_text(nomContact,noms);
    gtk_label_set_text(prenomContact,prenoms);
    gtk_label_set_text(numeroContact,num);
    gtk_label_set_text(adresseContact,adress);
    
    gtk_widget_hide(GTK_WIDGET(ViewContactWindow));
    gtk_widget_show_all(ShowContactWindow);
}

void on_searchContact_changed(){

    GtkSearchEntry *searchContact = GTK_SEARCH_ENTRY(gtk_builder_get_object(builder,"searchContact"));
    
    const gchar *srch;

    srch = gtk_entry_get_text(GTK_ENTRY(searchContact));
   
    store = GTK_LIST_STORE(gtk_builder_get_object(builder,"liststore1"));
    
    gtk_list_store_clear(store);

    search_contact_db(store,iter,srch);
}
void on_StatContactBtn_clicked(){
    system(test);
}
void on_AddViewContactBtn_clicked(){

    on_addContactBtn_clicked();
}

void on_EditContactBtn_clicked(){
    
    GtkLabel *nomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNomContact"));
    GtkLabel *prenomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowPrenomContact"));
    GtkLabel *numeroContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNumeroContact"));
    GtkLabel *adresseContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowAdressContact"));

    GtkEntry *entreeEditNom = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditNom"));
    GtkEntry *entreeEditPrenom = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditPrenom"));
    GtkEntry *entreeEditNumero = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditNumero"));
    GtkEntry *entreeEditAdresse = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditAdresse"));

    gtk_entry_set_text(entreeEditNom,gtk_label_get_text(nomContact));
    gtk_entry_set_text(entreeEditPrenom,gtk_label_get_text(prenomContact));
    gtk_entry_set_text(entreeEditNumero,gtk_label_get_text(numeroContact));
    gtk_entry_set_text(entreeEditAdresse,gtk_label_get_text(adresseContact));


    gtk_widget_hide(GTK_WIDGET(ShowContactWindow));
    gtk_widget_show_all(GTK_WIDGET(EditContactWindow));
}
void on_DeleteContactBtn_clicked(){

    gtk_widget_show_all(AlertDeleteContactDialog);

}

void on_creeContact_clicked(){

    GtkEntry *EntreeNom,*EntreePrenom,*EntreeNumero,*EntreeAdresse;
    GtkComboBoxText *EntreeGenre;
    Contact contact;
    gchar *genre;

    EntreeNom = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeNom"));
    EntreePrenom = GTK_ENTRY(gtk_builder_get_object(builder,"EntreePrenom"));
    EntreeNumero = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeNumero"));
    EntreeGenre = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,"EntreeGenre"));
    EntreeAdresse = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeAdresse"));

    contact.nom = gtk_entry_get_text(EntreeNom);
    contact.prenom = gtk_entry_get_text(EntreePrenom);
    contact.numero = gtk_entry_get_text(EntreeNumero);
    contact.adresse = gtk_entry_get_text(EntreeAdresse);
    genre = gtk_combo_box_text_get_active_text(EntreeGenre);

    FILE *fichier;
    fichier = fopen("fichier.txt","w");
    fprintf(fichier,"%s\n%s\n%s\n%s\n%s\n",contact.nom,contact.prenom,contact.numero,contact.adresse,genre);
    fclose(fichier);

    if(strcmp(contact.nom,"")==0 || strcmp(contact.prenom,"")==0 || strcmp(contact.numero,"")==0 || strcmp(contact.adresse,"")==0 ){
        printf("\n Veuillez remplir tous les champs !\n");
        on_addContactBtn_clicked();
    }
    else
    {
        int res = ajout_contact_db(contact,genre);
        if( res == -1){
            printf("\n Erreur ! Veuillez verifier les données !\n");
            on_addContactBtn_clicked();
        }
        else{
            if(count == 0){
                on_viewContactBtn_clicked();
            }
           else{
               store = GTK_LIST_STORE(gtk_builder_get_object(builder,"liststore1"));
               show_last_contact_db(store,iter);

               gtk_entry_set_text(EntreeNom,"");
               gtk_entry_set_text(EntreePrenom,"");
               gtk_entry_set_text(EntreeNumero,"");
               gtk_entry_set_text(EntreeAdresse,"");
               ViewContactShow();
           }
            
        }
    }

}
void on_ValidEditBtn_clicked(){

    Contact contact;

    const char *nomC,*prenomC,*numeroC, *adresseC;

    GtkLabel *nomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNomContact"));
    GtkLabel *prenomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowPrenomContact"));
    GtkLabel *numeroContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNumeroContact"));
    GtkLabel *adresseContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowAdressContact"));

    GtkEntry *entreeEditNom = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditNom"));
    GtkEntry *entreeEditPrenom = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditPrenom"));
    GtkEntry *entreeEditNumero = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditNumero"));
    GtkEntry *entreeEditAdresse = GTK_ENTRY(gtk_builder_get_object(builder,"EntreeEditAdresse"));

    nomC = gtk_label_get_text(nomContact);
    prenomC = gtk_label_get_text(prenomContact);
    numeroC = gtk_label_get_text(numeroContact);
    adresseC = gtk_label_get_text(adresseContact);

    contact.nom = gtk_entry_get_text(entreeEditNom);
    contact.prenom = gtk_entry_get_text(entreeEditPrenom);
    contact.numero = gtk_entry_get_text(entreeEditNumero);
    contact.adresse = gtk_entry_get_text(entreeEditAdresse);

   if(strcmp(contact.nom,"")==0 || strcmp(contact.prenom,"")==0 || strcmp(contact.numero,"")==0 || strcmp(contact.adresse,"")==0){
        printf("Veuillez remplir tous les champs! \n");
        on_EditContactBtn_clicked();
    }
    else{
        int res = update_contact_db(contact, get_contact_id(nomC,prenomC,numeroC,adresseC));
        if(res == -1){
            printf("Veuillez verifier vos données ! \n");
            on_EditContactBtn_clicked();
        }
        else{
            store = GTK_LIST_STORE(gtk_builder_get_object(builder,"liststore1"));
            gtk_list_store_clear(store);
            show_contact_db(store,iter);
            ViewContactShow();
        }
    }
}
void on_cancelBtnDeleteContact_clicked(){
    gtk_widget_hide(AlertDeleteContactDialog);
}
void on_confBtnDeleteContact_clicked(){
    
    gtk_widget_hide(AlertDeleteContactDialog);
    
    Contact contact;

    GtkLabel *nomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNomContact"));
    GtkLabel *prenomContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowPrenomContact"));
    GtkLabel *numeroContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowNumeroContact"));
    GtkLabel *adresseContact = GTK_LABEL(gtk_builder_get_object(builder,"ShowAdressContact"));

    contact.nom = gtk_label_get_text(nomContact);
    contact.prenom = gtk_label_get_text(prenomContact);
    contact.numero = gtk_label_get_text(numeroContact);
    contact.adresse = gtk_label_get_text(adresseContact);

    delete_contact_db(contact,get_contact_id(contact.nom,contact.prenom,contact.numero,contact.adresse));

    store = GTK_LIST_STORE(gtk_builder_get_object(builder,"liststore1"));

    gtk_list_store_clear(store);

    show_contact_db(store,iter);

    ViewContactShow();
}
void on_exportContact_clicked(){
    system(export);
}


/* ----------------Les fonctions appelées lors la fermeture des fenêtres.-------------------------------- */

void on_MainWindow_destroy()
{
    gtk_main_quit();
}
void on_AddContactWindow_destroy()
{
   gtk_main_quit();
}
void on_ViewContactWindow_destroy(){
   gtk_main_quit();
}
void on_EditContactWindow_destroy(){
   gtk_main_quit();
}
void on_ShowContactWindow_destroy(){
    gtk_main_quit();
}

