# Bataille Navale

**Groupe** : `G4B` -- Iesin Sab, Aurelien Salmon, Momcilo Uzelac, Youssef Zaghdoudi, Han Tao Zhao.

## Description

Ce Jeu est nommé "Bataille Navale", il se déroule sous forme de partie qui se termine uniquement quand un des joueurs a détruit tout les bateaux adverses (d'ailleurs, il n'y a pas d'égalité dans une partie).

Il existe deux modes de jeu : Le mode JcJ donc Joueur Contre Joueur & le mode JcE donc Joueur contre Robot 

Le jeu se déroule sous 3 phases principales les voici : 

-1ère phase : Phase d'initialisation {

  - On demande si le jeu doit se dérouler sous forme de JcJ ou JcE
  - Les joueurs placent le bateau de façon manuel ou automatique
}

- 2ème phase : Phase de jeu {
  - Le joueur 1 tire en premier 
  - Le joueur 2 tire ensuite
  - On boucle jusqu'a ce qu'un des joueurs n'a plus aucun bateau présent sur la grille
}
- 3ème phase : Phase finale {
  - On affiche le vainqueur et le nombre de bateaux qu'il lui reste
  - On réinitalise la grille
  - On propose soit de relancer soit de quitter  
}

Pour les fonctionnalités valorisée nous avons pris le choix d'ajouter un mode Joueur Contre Joueur et d'afficher les deux tableaux en meme temps et également d'ajouter des scores.

## Compilation et exécution

Sous VSCode, la touche `F5` compile le fichier actif (`jeu.c`) avec tous les
modules du dossier `lib/` et lance l'exécutable.

En ligne de commande :

```bash
# TODO: adaptez si votre point d'entrée ou vos options de compilation changent
gcc -std=c23 -Wall -Werror jeu.c lib/*.c -o jeu -lm
./jeu
```

[Précisez ici toute dépendance ou option particulière propre à votre projet :
bibliothèque externe, arguments de lancement, mode de jeu...]

## Schéma de décomposition

main
├── void ModifierBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE])
│   ├── void afficherTable(int tab[TAILLE][TAILLE])
│   │   └── void afficherCase(int tab[TAILLE][TAILLE], int ligne, int colonne, bool auCombat)
│   ├── void AjouterBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE])
│   │   ├── void afficherTable(int tab[TAILLE][TAILLE])
│   │   │   └── void afficherCase(int tab[TAILLE][TAILLE], int ligne, int colonne, bool auCombat)
│   │   ├── bool LirePosition(int* ptrP)
│   │   ├── void afficherListeBateau(int bateau[QUANTITE])
│   │   ├── bool LireType(int* ptrT)
│   │   ├── bool PlacerListe(int tab[TAILLE][TAILLE], int ligne, int colonne, int type)
│   │   │   └── bool PlacementPossible(int tab[TAILLE][TAILLE], int ligne, int colonne, int type, int direction)
│   │   │       └── bool estVide(int tab[TAILLE][TAILLE], int ligne, int colonne)
│   │   ├── bool lireDirection(int* ptrD)
│   │   ├── bool PlacementPossible(int tab[TAILLE][TAILLE], int ligne, int colonne, int type, int direction)
│   │   │   └── bool estVide(int tab[TAILLE][TAILLE], int ligne, int colonne)
│   │   ├── void PlacerBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE], int ligne, int colonne, int type, int direction)
│   │   │   └── void AjouterCase(int tab[TAILLE][TAILLE], int ligne, int colonne, int type)
│   │   │       └── bool estVide(int tab[TAILLE][TAILLE], int ligne, int colonne)
│   │   └── void afficherTable(int tab[TAILLE][TAILLE])
│   │       └── void afficherCase(int tab[TAILLE][TAILLE], int ligne, int colonne, bool auCombat)
│   ├── bool LireType(int* ptrT)
│   ├── bool TerminerPlacement(int bateau[QUANTITE])
│   └── void SupprimerBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE], int type)
│       └── void SupprimerCase(int tab[TAILLE][TAILLE], int ligne, int colonne)
├── void rechargerVie(int* ptrB)
└── void seBattre(int tab1[TAILLE][TAILLE], int tab2[TAILLE][TAILLE],
                  int bateau1[QUANTITE], int bateau2[QUANTITE],
                  int tirs1[TAILLE][TAILLE], int tirs2[TAILLE][TAILLE])
    ├── void afficherDeuxTable(int tab1[TAILLE][TAILLE], int tab2[TAILLE][TAILLE])
    │   └── void afficherCase(int tab[TAILLE][TAILLE], int ligne, int colonne, bool auCombat)
    ├── bool LirePosition(int* ptrP)
    ├── bool DejaTire(int tirs[TAILLE][TAILLE], int ligne, int colonne)
    ├── void tire(int tab[TAILLE][TAILLE], int tirs[TAILLE][TAILLE],
    │             int bateau[QUANTITE], int ligne, int colonne)
    └── bool estPertu(int bateau[QUANTITE])





## Organisation du projet


|-----------------------------------|
| Fichier | Rôle                    |
| ------- | ----------------------- |
| `jeu.c` | [point d'entrée du jeu] |
|-----------------------------------|

## Documentation

La documentation du code est générée par [Doxygen](https://www.doxygen.nl/)
dans le dossier `html/` :

```bash
doxygen Doxyfile
```

## Jeux d'essais

Les traces d'exécution (parties rejouées, résultats des mesures de
comparaison) se trouvent dans le dossier `output/`.

Vous devrez expliquer comment obtenir ces traces.

## Journal des changements

Voir [CHANGELOG.md](./CHANGELOG.md).

## Licences

Ce projet utilise deux licences libres pour son contenu.

* Le contenu écrit est sous licence
  [CC-BY-SA](https://creativecommons.org/licenses/by-sa/4.0/), voir le fichier
  [LICENCE-CONTENT](./LICENCE-CONTENT).
* Les programmes et exemples de code sont sous licence
  [unlicence](https://unlicense.org), voir le fichier
  [LICENCE](./LICENCE).
# G4B-Bataille_Navale
