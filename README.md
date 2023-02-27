# Projet_carnet_adresse

Il s'agit d'un repertoire de contact devéloppé en C avec la librairie gtk et mysql dans le cadre d'un projet académique.

## Note 1

Ce programme a été Developpé sur Linux (Ubuntu 18.04 LTS) avec "Gtk+ 3.12" et "Glade 3.22.1".
Vous pouvez démarrer ce programme avec cette version ou une version supérieur.
Si vous voulez démarrer le programme avec un autre système d'exploitation, veuillez
consulter [Ici](https://www.gtk.org/docs/installations/windows/)

## Note 2 

Le fichier makefile est un fichier utilisé par le programme make pour exécuter un ensemble 
d'action comme la compilation d'un programme,l'archivage de document, la mise à jour 
de site. Ici, nous l'utilisons pour compiler le projet. 

## Compilation 

Ce projet contient le fichier makefile qui permet de compiler le projet.
On utilise la commande
   ```sh
   make
   ```
Puis on lance l'executable  du programme
Sur windows,
   ```sh
   > carnet
   ```
Sur Linux
   ```sh
   $ ./carnet
   ```