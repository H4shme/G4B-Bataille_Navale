# Changelog

Toutes les évolutions notables du projet, semaine par semaine, la plus
récente en haut. Format inspiré de
[Keep a Changelog](https://keepachangelog.com/fr/1.1.0/). Chaque changement
précise qui l'a réalisé avec une mention `@prénom` ; un changement
réalisé à plusieurs cite tous ses auteurs : `(@prénom1, @prénom2)`.

## Semaine 3 -- 16/10/26

### Ajouté

- Description de la représentation du plateau dans le README (@Aurelien, @Momcilo)
- Section "Comment jouer" dans le README (@Aurelien, @Momcilo)
- Fonctions pas encore utilisées ajoutées au schéma de décomposition (@Aurelien)
- Structures `Bateau`, `Coup` et `Joueur` et énumération `TypeBateau` pour remplacer les tableaux d'entiers (@Han Tao, @Youssef, @Momcilo)
- Fonction `initialiserJoueur` qui prépare la grille, les bateaux, et le compteur de coups d'un joueur (@Iesin, @Han Tao, @Youssef)
- Noms des joueurs (`Joueur 1` et `Joueur 2`) affichés au-dessus des grilles (@Iesin)
- Fonction `afficherDeuxTables` : le joueur 1 est toujours à gauche et le joueur 2 toujours à droite (@Iesin)
- Fonction `cls` qui efface l'écran entre les tours (@Iesin)
- Constante `RATE` (`-10`) pour représenter un tir raté dans la grille (@Iesin)
- Constante `AUTO_PLACEMENT` et fonction `placerAuto` pour placer automatiquement les bateaux pendant les tests (@Iesin)
- Commentaires Doxygen mis à jour pour les structures et les nouvelles fonctions (@Momcilo )

### Modifié

- Section "Compilation" et tableau "Organisation du projet" du README remplis (@Aurelien)
- README réécrit pour la version à structures : données, schéma de décomposition, limites et jeux d'essais à refaire (@Iesin)
- Le combat JcJ fonctionne avec deux `Joueur` : `tire` prend un tireur et une cible, `seBattre` alterne les deux joueurs (@Iesin, @Han Tao, @Youssef)
- Les bateaux restent cachés pendant le combat : les deux joueurs peuvent regarder le même écran (@Iesin)
- `dejaTire` et `verifierCoulance` travaillent sur la grille de la cible (@Iesin, @Aurelien, @Han Tao)
- La suppression d'un bateau utilise la position et la direction mémorisées (@Iesin, @Youssef)
- Menu de placement : la saisie du choix est redemandée tant qu'elle n'est pas valide, et une case de départ occupée est refusée (@Han Tao, @Youssef)

### Corrigé

- Ordre des semaines dans le CHANGELOG, mentions `@prénom` et virgules (@Aurelien)
- Un tir touché sur le patrouilleur ressemblait à un tir raté : le bateau pouvait être coulé à tort (@Iesin)
- En-tête de grille décalé : saut de ligne ajouté et colonnes alignées avec les cases (@Iesin)
- Le joueur 2 ne tire plus après la destruction de la flotte du joueur 2 par le joueur 1 (@Han Tao)
- Le vainqueur est affiché à la fin de la partie (@Youssef)

### Supprimé

- Structure `Partie` remplacée par `Joueur` (@Momcilo)
- Tableaux d'entiers `tirs` et `bateau` et leurs fonctions associées (`rechargerVie`, `estPertu`, `DejaTire`...) (@Iesin)
- Fonctions préparatoires de l'ordinateur (`tirOrdinateur`, `compteType`, `coulerBateau`, `nomBateau`, `flotteDetruite`, `lireChoix`), à réécrire avec les structures (@Momcilo)


## Semaine 2 -- 09/10/26

### Ajouté

- Placement des bateaux avec le choix de la position et orientation (@Iesin)
- Ajout et suppression des bateaux avant le début de la partie (@Youssef)
- Systeme de combat JcJ (PVP) avec gestion des tours et des tirs (@Han Tao)
- Suivi des tirs déjà effectués et detection de la victoire (@Aurelien)
- Fonctions préparatoires pour les tirs de l'ordinateur et la détection des bateaux coulés (@Momcilo)
- Ajout des commentaires format doxygen (@Youssef, @Iesin, @Han Tao, @Aurelien, @Momcilo)

### Modifié

- Amélioration de l'affichage des grilles et des bateaux (@Youssef, @Iesin, @Han Tao, @Aurelien, @Momcilo)
- Ajout de controles sur les positions, les types de bateaux et les directions (@Youssef, @Iesin, @Han Tao, @Aurelien, @Momcilo)
- Organisation et développement des fonctions de placement et de combat (@Youssef, @Iesin, @Han Tao, @Aurelien, @Momcilo)