# Lem-in

Ce projet a pour bût de nous faire coder une fourmillière...

Notre programme va prendre en paramètre des salles (sous forme de nom avec des coord x y)
ainsi que les liaisons entre ces diffèrentes salles.

le programme doit : pour les 'n' fourmis données en paramètre trouver le ou les chemins les plus courts
permettant à toutes les fourmis d'aller de la salle ##start à la salle ##end et ce, en utilisant le moins de tour possible.

Tout en respectant les règles suivantes : 
  - il ne peux y avoir plus d'une fourmi par salle (sauf 'start' et 'end')
  - On considère que les fourmis sont toutes dans la salle ##start au démarrage
  - À chaque tour vous pouvez déplacer chaque fourmi une seule fois et ce suivant une liaison (la salle réceptrice doit être libre).
  
ex. de fichier valide :
  
```
5         //nombre de fourmis
1 0 2     ///////////////
##start   //
0 2 0     //  Declaration des salles (nom x y)
##end     //  ##start et ##end défini un status à la salle défini à la ligne suivante
4 2 6     //  ici la salle nommé '0' sera la salle start
2 4 2     //
3 4 4     ////////////////
0-1       ////////////////
0-2       //
2-3       //  Declaration des liaison entre les salles (nom_salle1 - nom_salle2)
3-4       //
4-1       ////////////////
```

un makefile permet de compiler le programme.

les fichiers permettant de definir les salles sont disponible dans le dossier 'maps_test'
lancer le programme comme ceci : "./lem-in < maps_test/nc"

Pour rendre le rendu un peu plus comprehensible humainement, un visu est disponible avec ce projet (avec un thème particulier)!

Avant tout lancer la commande : "sh brew_check.sh" ce script va installer le necessaire au bon fonctionnement du visu (ca peut prendre un moment)

un petit : "make re" pour remettre tout bien comme il faut

puis lancer la même commande que precedement suivi d'un pipe '|' et de l'executable './display' (attention il y'a du son!)
ce qui nous donne avec tout : "./lem-in < maps_test/nc | ./display"

les touches '+' et '-' de votre pavé numérique permettent de monter et diminuer la vitesse.

Musique de menu : Propellerheads - Spybreak (Bullet time !!)

Musique de visu : Deftones - My Own Summer (instru only)

Quelques screens de rendu :

Menu :
![image1](https://github.com/ncoursol/Lem-in/blob/master/img/screenshot/image1.png)

Representation graphique de la methode algorithmique utilisée :
![image1](https://github.com/ncoursol/Lem-in/blob/master/img/screenshot/image2.png)

Les fourmis (oui c'est des fourmis) partant de start à end suivant le/les chemins trouvés
![image1](https://github.com/ncoursol/Lem-in/blob/master/img/screenshot/image3.png)
