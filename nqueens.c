#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int clauses = 0;
FILE *f;
FILE *f2;

int ligne(int c, int N){
    return ((c-1)/N);
}

int col(int c, int N){
    return ((c-1)%N);
}
//fonction qui renvoie la case du tableau [x,y] comme entier
int reine(x, y, N){
    return ((x)*N +(y) + 1);
}


void diagonale_bas(int x, int y, int N) {
  int i, j;
  for (; x < N - 1 && y < N - 1; x++, y++)
    for (i = x + 1, j = y + 1; i < N && j < N; i++, j++) {
      fprintf(f, "-%d -%d 0\n", reine(x, y, N), reine(i, j, N));
      clauses++;
    }
}

void diagonale_haut(int x, int y, int N) {
  int i, j;
  for (; x > 0 && y < N - 1; x--, y++)
    for (i = x - 1, j = y + 1; i >= 0 && j < N; i--, j++) {
      fprintf(f, "-%d -%d 0\n", reine(x, y, N), reine(i, j, N));
      clauses++;
    }
}

int main() {
  int a, b, d, k, value;
  int c, N;
  printf("\nSaisir N le nombre de reines(N>=4) ou entrez 0 pour quitter:   ");
  scanf("%d",&N);
  while(N > 0){
  if (N<4){
    printf("\nN doit être supérieur à 4 \n");
    printf("\nSaisir N le nombre de reines(N>=4) ou entrez 0 pour quitter:   ");
    scanf("%d",&N);
    continue;
  }
  char table[N][N];
  //ouverture du fichier pour la creation des clauses
  f = fopen("clauses_seuls.txt", "w");

  for (k = 0; k < N; k++) {
    for (a = 0; a < N - 1; a++)
      for (b = a + 1; b < N; b++) {
        fprintf(f, "-%d -%d 0\n", reine(k, a, N), reine(k, b, N));
        clauses++;
        fprintf(f, "-%d -%d 0\n", reine(a, k, N), reine(b, k, N));
        clauses++;
      }

    for (a = 0; a < N; a++)
      fprintf(f, "%d ", reine(k, a, N));
    fprintf(f, "0\n");
    clauses++;
  }

  for (a = 0; a < N - 1; a++){
    diagonale_bas(0, a, N);
  }
  for (a = 1; a < N - 1; a++){
    diagonale_bas(a, 0, N);
  }
  for (a = 1; a < N; a++){
    diagonale_haut(a, 0, N);
  }
  for (a = 1; a < N - 1; a++){
    diagonale_haut(N - 1, a, N);

  }
  fclose(f);
  //ouverture du fichier pour la transformation des clauses en format DIMACS
   f = fopen("clauses.cnf", "w");
  fprintf(f, "p cnf %d %d\n", N * N, clauses);
  fclose(f);
  system("cat clauses_seuls.txt >> clauses.cnf");
  //Appel du SAT Solveur cryptominisat5 sur le fichier DIMACS
  //et stockage du résultat du solveur dans le fichier resultat.txt
  system("cryptominisat5 --verb 0 clauses.cnf > resultat.txt");

  f = fopen("resultat.txt", "r");
  if ((c = fgetc(f)) == EOF || c != 's'){
    exit(1);
  }

  //On remplit d'abord la table par des points partout
  for (a = 0; a < N; a++){
    for (b = 0; b < N; b++){
        table[a][b] = '.';
    }
  }
  while((c = fscanf(f, "%d", &d)) != EOF){
    if (c == 0) {
        fgetc(f);
        continue;
    }
    //On met 'R' (reine) dans la table là où la variable booléene est vrai (d>0)
    if (d > 0){
        table[ligne(d,N)][col(d,N)] = 'R';
    }
  }
  f2 = fopen("BOARD.txt", "w");
    //On affiche la table finale avec les reines aux bons endroits
  for (a = 0; a < N; a++) {
        for (b = 0; b < N; b++){
            fprintf(f2, "%c ", table[a][b]);
        }
        fprintf(f2, "\n");
  }
  fclose(f2);
  if(N<20){
  printf("\n");
  system("cat BOARD.txt");
  }
  else{
  printf("\nLe résultat est dans le fichier BOARD.txt");
  }
  printf("\n");
  fclose(f);
  clauses=0;
  printf("\nSaisir N le nombre de reines(N>=4) ou entrez 0 pour quitter:   ");
  scanf("%d",&N);
  }
}