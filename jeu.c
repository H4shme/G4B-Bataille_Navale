
#include <stdbool.h>
#include <stdio.h>
#define TAILLE 10
#define QUANTITE 5

#define RATE 6
#define TOUCHE 10
#define COULE 20
#include <stdlib.h>
#include <time.h>

/**
 * @file jeu.c
 * @brief Implémentation d'un jeu de bataille navale à deux joueurs.
 *
 * Le plateau est représenté par une grille carrée de taille TAILLE.
 * Les bateaux sont placés avant que les joueurs tirent à tour de rôle.
 */

void afficherCase(int tab[TAILLE][TAILLE], int ligne, int colonne,
                  bool auCombat);

void afficherTable(int tab[TAILLE][TAILLE]);

void afficherDeuxTable(int tab1[TAILLE][TAILLE], int tab2[TAILLE][TAILLE]);

void afficherListeBateau(int bateau[QUANTITE]);

bool estVide(int tab[TAILLE][TAILLE], int ligne, int colonne);

bool lireChoix();

bool LireType(int* ptrT);

bool LirePosition(int* ptrP);

bool lireDirection(int* ptrD);

bool PlacerListe(int tab[TAILLE][TAILLE], int ligne, int colonne, int type);

bool TerminerPlacement(int bateau[QUANTITE]);

bool PlacementPossible(int tab[TAILLE][TAILLE], int ligne, int colonne,
                       int type, int direction);

bool DejaTire(int tirs[TAILLE][TAILLE], int ligne, int colonne);

bool estPertu(int bateau[QUANTITE]);

void AjouterCase(int tab[TAILLE][TAILLE], int ligne, int colonne, int type);

void AjouterBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE]);

void SupprimerCase(int tab[TAILLE][TAILLE], int ligne, int colonne);

void SupprimerBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE], int type);

void PlacerBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE], int ligne,
                  int colonne, int type, int direction);

void ModifierBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE]);

void rechargerVie(int* ptrB);

void tire(int tab[TAILLE][TAILLE], int tirs[TAILLE][TAILLE],
          int bateau[QUANTITE], int ligne, int colonne);

void seBattre(int tab1[TAILLE][TAILLE], int tab2[TAILLE][TAILLE],
              int bateau1[QUANTITE], int bateau2[QUANTITE],
              int tirs1[TAILLE][TAILLE], int tirs2[TAILLE][TAILLE]);

const char* nomBateau(int type);

bool dejaTire(int tab[TAILLE][TAILLE], int ligne, int colonne);

int compteType(int tab[TAILLE][TAILLE], int type);

void coulerBateau(int tab[TAILLE][TAILLE], int type);

bool flotteDetruite(int tab[TAILLE][TAILLE]);

void tirOrdinateur(int tab[TAILLE][TAILLE]);

int main() {
  int tab1[TAILLE][TAILLE] = {0};
  int tab2[TAILLE][TAILLE] = {0};
  int bateau1[QUANTITE] = {1, 2, 3, 4, 5};
  int bateau2[QUANTITE] = {1, 2, 3, 4, 5};

  printf("Joueur 1, placez vos bateaux :\n");
  ModifierBateau(tab1, bateau1);
  printf("Joueur 2, placez vos bateaux :\n");
  ModifierBateau(tab2, bateau2);

  rechargerVie(bateau1);
  rechargerVie(bateau2);
  int tirs1[TAILLE][TAILLE] = {0};
  int tirs2[TAILLE][TAILLE] = {0};

  seBattre(tab1, tab2, bateau1, bateau2, tirs1, tirs2);
  return 0;
}

/**
 * @brief Affiche le symbole correspondant à une case du plateau.
 * @param tab plateau de jeu
 * @param ligne indice de ligne de la case
 * @param colonne indice de colonne de la case
 * @param auCombat indique si l'affichage se fait pendant le combat
 */
void afficherCase(int tab[TAILLE][TAILLE], int ligne, int colonne,
                  bool auCombat) {
  if (auCombat) {
    switch (tab[ligne][colonne]) {
      case 0:
        printf("~ ");
        break;
      case 1:
        printf("X ");
        break;
      case 2:
        printf("O ");
        break;
      default:
        printf("  ");
        break;
    }
  } else {
    switch (tab[ligne][colonne]) {
      case 0:
        printf("~ ");
        break;
      case 1:
        printf("p ");
        break;
      case 2:
        printf("c ");
        break;
      case 3:
        printf("D ");
        break;
      case 4:
        printf("C ");
        break;
      case 5:
        printf("P ");
        break;
      default:
        printf("  ");
        break;
    }
  }
}

/**
 * @brief Affiche le plateau de jeu avec les coordonnées.
 * @param tab plateau à afficher
 */
void afficherTable(int tab[TAILLE][TAILLE]) {
  puts("");
  puts("  0 1 2 3 4 5 6 7 8 9");
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    printf("%c ", ligne + 'A');
    for (int colonne = 0; colonne < TAILLE; colonne++) {
      afficherCase(tab, ligne, colonne, false);
    }
    puts("");
  }
  puts("");
}

/**
 * @brief Affiche côte à côte deux tableaux de tirs.
 * @param tab1 tableau de tirs du premier joueur
 * @param tab2 tableau de tirs du second joueur
 */
void afficherDeuxTable(int tab1[TAILLE][TAILLE], int tab2[TAILLE][TAILLE]) {
  puts("");
  puts("  0 1 2 3 4 5 6 7 8 9        0 1 2 3 4 5 6 7 8 9");
  for (int ligne = 0; ligne < TAILLE; ligne++) {
    printf("%c ", ligne + 'A');
    for (int colonne1 = 0; colonne1 < TAILLE; colonne1++) {
      afficherCase(tab1, ligne, colonne1, true);
    }
    printf("     ");
    printf("%c ", ligne + 'A');
    for (int colonne2 = 0; colonne2 < TAILLE; colonne2++) {
      afficherCase(tab2, ligne, colonne2, true);
    }
    puts("");
  }
}

/**
 * @brief Affiche les bateaux qui peuvent encore être placés.
 * @param bateau tableau indiquant les bateaux restant à placer
 */
void afficherListeBateau(int bateau[QUANTITE]) {
  puts("");
  if (bateau[0]) puts("Patrouilleur : Entrez 1 (2 cases)");
  if (bateau[1]) puts("Croiseur     : Entrez 2 (3 cases)");
  if (bateau[2]) puts("Destroyer    : Entrez 3 (3 cases)");
  if (bateau[3]) puts("Cuirassé     : Entrez 4 (4 cases)");
  if (bateau[4]) puts("Porte-avions : Entrez 5 (5 cases)");
  puts("");
}

/**
 * @brief Indique si une case du plateau est vide.
 * @param tab plateau de jeu
 * @param ligne indice de ligne
 * @param colonne indice de colonne
 */
bool estVide(int tab[TAILLE][TAILLE], int ligne, int colonne) {
  return tab[ligne][colonne] == 0;
}

/**
 * @brief Vérifie si tous les bateaux ont été placés.
 * @param bateau tableau indiquant les bateaux restant à placer
 */
bool TerminerPlacement(int bateau[QUANTITE]) {
  int somme = 0;
  for (int i = 0; i < QUANTITE; i++) {
    somme += bateau[i];
  }
  return (somme == 0) ? true : false;
}

/**
 * @brief Demande à l'utilisateur de répondre par oui ou non.
 */
bool lireChoix() {
  char choix;
  printf("(Y/N) : ");
  scanf(" %c", &choix);
  while (choix != 'Y' && choix != 'y' && choix != 'N' && choix != 'n') {
    printf("Confirme avec Y ou N : ");
    scanf(" %c", &choix);
  }
  return (choix == 'Y' || choix == 'y');
}

/**
 * @brief Ajoute un bateau dans une case si celle-ci est vide.
 * @param tab plateau de jeu
 * @param ligne indice de ligne
 * @param colonne indice de colonne
 * @param type type du bateau à placer
 */
void AjouterCase(int tab[TAILLE][TAILLE], int ligne, int colonne, int type) {
  if (estVide(tab, ligne, colonne)) tab[ligne][colonne] = type;
}

/**
 * @brief Vide une case du plateau.
 * @param tab plateau de jeu
 * @param ligne indice de ligne
 * @param colonne indice de colonne
 */
void SupprimerCase(int tab[TAILLE][TAILLE], int ligne, int colonne) {
  tab[ligne][colonne] = 0;
}

/**
 * @brief Vérifie si un bateau peut être placé dans une direction donnée.
 * @param tab plateau de jeu
 * @param ligne ligne de départ
 * @param colonne colonne de départ
 * @param type type du bateau
 * @param direction direction (1 haut, 2 droite, 3 bas, 4 gauche)
 */
bool PlacementPossible(int tab[TAILLE][TAILLE], int ligne, int colonne,
                       int type, int direction) {
  int longueur;
  if (type <= 2)
    longueur = type + 1;
  else
    longueur = type;

  switch (direction) {
    case 1:
      for (int i = 0; i < longueur; i++) {
        if (ligne - i < 0 || !estVide(tab, ligne - i, colonne)) return false;
      }
      return true;

    case 2:
      for (int i = 0; i < longueur; i++) {
        if (colonne + i > 9 || !estVide(tab, ligne, colonne + i)) return false;
      }
      return true;

    case 3:
      for (int i = 0; i < longueur; i++) {
        if (ligne + i > 9 || !estVide(tab, ligne + i, colonne)) return false;
      }
      return true;

    case 4:
      for (int i = 0; i < longueur; i++) {
        if (colonne - i < 0 || !estVide(tab, ligne, colonne - i)) return false;
      }
      return true;

    default:
      return false;
  }
}

/**
 * @brief Affiche les directions dans lesquelles un bateau peut être placé.
 * @param tab plateau de jeu
 * @param ligne ligne de départ
 * @param colonne colonne de départ
 * @param type type du bateau
 */
bool PlacerListe(int tab[TAILLE][TAILLE], int ligne, int colonne, int type) {
  bool liste[4];
  for (int i = 1; i <= 4; i++) {
    liste[i - 1] = PlacementPossible(tab, ligne, colonne, type, i);
  }
  int somme = 0;
  for (int j = 0; j < 4; j++) {
    somme += liste[j];
  }
  puts("");
  if (somme != 0) {
    if (liste[0]) printf("HAUT   : 1\n");
    if (liste[1]) printf("DROITE : 2\n");
    if (liste[2]) printf("BAS    : 3\n");
    if (liste[3]) printf("GAUCHE : 4\n");
    puts("");
    return true;
  } else {
    puts("Choisir une autre position !");
    puts("");
    return false;
  }
}

/**
 * @brief Place un bateau sur le plateau et le marque comme placé.
 * @param tab plateau de jeu
 * @param bateau tableau des bateaux disponibles
 * @param ligne ligne de départ
 * @param colonne colonne de départ
 * @param type type du bateau
 * @param direction direction du placement
 */
void PlacerBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE], int ligne,
                  int colonne, int type, int direction) {
  int longueur;
  if (type <= 2)
    longueur = type + 1;
  else
    longueur = type;

  bateau[type - 1] = 0;
  switch (direction) {
    case 1:
      for (int i = 0; i < longueur; i++) {
        AjouterCase(tab, ligne - i, colonne, type);
      }
      break;

    case 2:
      for (int i = 0; i < longueur; i++) {
        AjouterCase(tab, ligne, colonne + i, type);
      }
      break;

    case 3:
      for (int i = 0; i < longueur; i++) {
        AjouterCase(tab, ligne + i, colonne, type);
      }
      break;

    case 4:
      for (int i = 0; i < longueur; i++) {
        AjouterCase(tab, ligne, colonne - i, type);
      }
      break;

    default:
      break;
  }
}

/**
 * @brief Supprime du plateau toutes les cases d'un bateau donné.
 * @param tab plateau de jeu
 * @param bateau tableau des bateaux disponibles
 * @param type type du bateau à supprimer
 */
void SupprimerBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE], int type) {
  bateau[type - 1] = type;
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      if (tab[i][j] == type) SupprimerCase(tab, i, j);
    }
  }
}

/**
 * @brief Lit et valide une position sur le plateau.
 * @param ptrP tableau recevant l'indice de ligne puis celui de colonne
 */
bool LirePosition(int* ptrP) {
  char ligne = 'A' - 1;
  int colonne = -1;
  printf("Entrez position (ex: A0) : ");
  scanf(" %c%d", &ligne, &colonne);
  if (ligne >= 'a' && ligne <= 'z') {
    ligne = ligne - 'a' + 'A';
  }
  ligne -= 'A';
  if (ligne < 0 || ligne >= TAILLE || colonne < 0 || colonne >= TAILLE) {
    return false;
  }
  ptrP[0] = ligne;
  ptrP[1] = colonne;
  return true;
}

/**
 * @brief Lit et valide le type de bateau choisi.
 * @param ptrT adresse où stocker le type choisi
 */
bool LireType(int* ptrT) {
  int type = -1;
  printf("Indiquez un numéro de bateau (1-5) : ");
  scanf("%d", &type);
  if (type < 1 || type > QUANTITE) return false;
  *ptrT = type;
  return true;
}

/**
 * @brief Lit et valide la direction de placement d'un bateau.
 * @param ptrD adresse où stocker la direction choisie
 */
bool lireDirection(int* ptrD) {
  int direction = -1;
  printf("Saisissez un nombre pour sélectionner l'orientation du placement : ");
  scanf("%d", &direction);
  if (direction < 1 || direction > 4) return false;
  *ptrD = direction;
  return true;
}

/**
 * @brief Guide l'utilisateur pour ajouter un bateau au plateau.
 * @param tab plateau de jeu
 * @param bateau tableau des bateaux restant à placer
 */
void AjouterBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE]) {
  int type;
  int direction;
  int position[2];
  int* ptrT = &type;
  int* ptrD = &direction;
  int* ptrP = position;
  bool impossiblePlace;
  do {
    impossiblePlace = false;
    afficherTable(tab);
    if (!LirePosition(ptrP)) {
      puts("Position invalide.");
      impossiblePlace = true;
      continue;
    }
    afficherListeBateau(bateau);
    if (!LireType(ptrT)) {
      puts("Type invalide.");
      impossiblePlace = true;
      continue;
    }
    if (bateau[type - 1] == 0) {
      puts("Ce bateau est déjà placé.");
      impossiblePlace = true;
      continue;
    }
    if (!PlacerListe(tab, position[0], position[1], type))
      impossiblePlace = true;
    else {
      if (!lireDirection(ptrD)) {
        puts("Direction invalide.");
        impossiblePlace = true;
        continue;
      }
      if (!PlacementPossible(tab, position[0], position[1], type, direction)) {
        puts("Placement impossible dans cette direction.");
        impossiblePlace = true;
        continue;
      }
      PlacerBateau(tab, bateau, position[0], position[1], type, direction);
      afficherTable(tab);
    }
  } while (impossiblePlace);
}

/**
 * @brief Permet d'ajouter ou de supprimer des bateaux avant de commencer.
 * @param tab plateau de jeu
 * @param bateau tableau des bateaux disponibles
 */
void ModifierBateau(int tab[TAILLE][TAILLE], int bateau[QUANTITE]) {
  int mode;
  bool termine = false;
  afficherTable(tab);
  while (!termine) {
    printf("Ajouter (1), supprimer (2), terminer (3) (temporaire): ");
    scanf("%d", &mode);
    switch (mode) {
      case 1:
        AjouterBateau(tab, bateau);
        break;
      case 2:
        int type;
        if (!LireType(&type)) {
          puts("Numéro invalide.");
          break;
        }
        if (bateau[type - 1] != 0) {
          puts("Ce bateau n'est pas placé.");
          break;
        }
        SupprimerBateau(tab, bateau, type);
        break;
      case 3:
        if (TerminerPlacement(bateau)) {
          termine = true;
          for (int i = 0; i < 300; i++) {
            puts("");
          }
        } else
          puts("Tous les bateaux ne sont pas encore placés.");
        break;
      default:
        printf("Cette option n'est pas disponible.");
        break;
    }
  }
}

/**
 * @brief Réinitialise les points de vie des cinq bateaux.
 * @param ptrB tableau des points de vie des bateaux
 */
void rechargerVie(int* ptrB) {
  for (int i = 0; i < QUANTITE; i++) {
    ptrB[i] = i + 1;
    if (i < 2) ptrB[i] += 1;
  }
}

/**
 * @brief Indique si une position a déjà été visée.
 * @param tirs tableau des tirs effectués
 * @param ligne indice de ligne
 * @param colonne indice de colonne
 */
bool DejaTire(int tirs[TAILLE][TAILLE], int ligne, int colonne) {
  return tirs[ligne][colonne];
}

/**
 * @brief Enregistre un tir et met à jour les points de vie du bateau touché.
 * @param tab plateau contenant les bateaux
 * @param tirs tableau des tirs effectués
 * @param bateau tableau des points de vie des bateaux
 * @param ligne indice de ligne visée
 * @param colonne indice de colonne visée
 */
void tire(int tab[TAILLE][TAILLE], int tirs[TAILLE][TAILLE],
          int bateau[QUANTITE], int ligne, int colonne) {
  if (tab[ligne][colonne]) {
    tirs[ligne][colonne] = 1;
    bateau[tab[ligne][colonne] - 1] -= 1;
  } else
    tirs[ligne][colonne] = 2;
}

/**
 * @brief Vérifie si tous les bateaux de la flotte sont détruits.
 * @param bateau tableau des points de vie des bateaux
 */
bool estPertu(int bateau[QUANTITE]) {
  int nombre = 0;
  for (int i = 0; i < QUANTITE; i++) {
    if (bateau[i]) nombre++;
  }
  return nombre == 0;
}

/**
 * @brief Gère les tours de tir des deux joueurs jusqu'à la fin de la partie.
 * @param tab1 plateau du premier joueur
 * @param tab2 plateau du second joueur
 * @param bateau1 points de vie des bateaux du premier joueur
 * @param bateau2 points de vie des bateaux du second joueur
 * @param tirs1 tirs effectués par le premier joueur
 * @param tirs2 tirs effectués par le second joueur
 */
void seBattre(int tab1[TAILLE][TAILLE], int tab2[TAILLE][TAILLE],
              int bateau1[QUANTITE], int bateau2[QUANTITE],
              int tirs1[TAILLE][TAILLE], int tirs2[TAILLE][TAILLE]) {
  int tour = 1;
  int position[2];
  bool partieFinie = false;
  while (!partieFinie) {
    afficherDeuxTable(tirs1, tirs2);
    printf("\n--- Joueur %d, a vous de tirer ---\n", tour);
    if (!LirePosition(position)) {
      puts("Position invalide, reessayez.");
      continue;
    }

    if (tour == 1) {
      if (DejaTire(tirs2, position[0], position[1])) {
        puts("Vous avez deja tire ici !");
        continue;
      }
      tire(tab2, tirs2, bateau2, position[0], position[1]);
      if (estPertu(bateau2))
        partieFinie = true;
      else
        tour = 2;
    } else {
      if (DejaTire(tirs1, position[0], position[1])) {
        puts("Vous avez deja tire ici !");
        continue;
      }
      tire(tab1, tirs1, bateau1, position[0], position[1]);
      if (estPertu(bateau1))
        partieFinie = true;
      else
        tour = 1;
    }
  }
  if (estPertu(bateau2))
    puts("\nJoueur 1 a gagne !");
  else
    puts("\nJoueur 2 a gagne !");
}

/**
 * @brief Renvoie le nom correspondant à un type de bateau.
 * @param type type du bateau (1 à 5)
 * @return le nom du bateau
 */
const char* nomBateau(int type) {
  switch (type) {
    case 1:
      return "Patrouilleur";
    case 2:
      return "Croiseur";
    case 3:
      return "Destroyer";
    case 4:
      return "Cuirasse";
    default:
      return "Porte-avions";
  }
}

/**
 * @brief Vérifie si une case a déjà été visée selon son état.
 * @param tab plateau du joueur
 * @param ligne indice de ligne
 * @param colonne indice de colonne
 * @return true si la condition est vérifiée, sinon false
 */
bool dejaTire(int tab[TAILLE][TAILLE], int ligne, int colonne) {
  return tab[ligne][colonne] == RATE || tab[ligne][colonne] > TOUCHE;
}

/**
 * @brief Compte les cases intactes d'un type de bateau.
 * @param tab plateau du joueur
 * @param type type du bateau
 * @return le nombre de cases intactes
 */
int compteType(int tab[TAILLE][TAILLE], int type) {
  int compte = 0;
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      if (tab[i][j] == type) compte++;
    }
  }
  return compte;
}

/**
 * @brief Marque comme coulées les cases touchées du bateau indiqué.
 * @param tab plateau du joueur
 * @param type type du bateau
 */
void coulerBateau(int tab[TAILLE][TAILLE], int type) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      if (tab[i][j] == type + TOUCHE) tab[i][j] = type + COULE;
    }
  }
}

/**
 * @brief Vérifie si la flotte ne contient plus de case de bateau intacte.
 * @param tab plateau du joueur
 * @return true si la condition est vérifiée, sinon false
 */
bool flotteDetruite(int tab[TAILLE][TAILLE]) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      if (tab[i][j] >= 1 && tab[i][j] <= QUANTITE) return false;
    }
  }
  return true;
}

/**
 * @brief Fait tirer l'ordinateur sur une case qui n'a pas encore été visée.
 * @param tab plateau du joueur
 */
void tirOrdinateur(int tab[TAILLE][TAILLE]) {
  int ligne;
  int colonne;
  do {
    ligne = rand() % TAILLE;
    colonne = rand() % TAILLE;
  } while (dejaTire(tab, ligne, colonne));

  printf("\nL'ordinateur tire en %c%d : ", ligne + 'A', colonne);

  int type = tab[ligne][colonne];
  if (type == 0) {
    tab[ligne][colonne] = RATE;
    puts("rate !");
  } else {
    tab[ligne][colonne] = type + TOUCHE;
    if (compteType(tab, type) == 0) {
      coulerBateau(tab, type);
      printf("COULE ! (%s)\n", nomBateau(type));
    } else {
      printf("touche (%s)\n", nomBateau(type));
    }
  }
}
