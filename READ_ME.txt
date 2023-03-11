groupe projet: EL BOUCHRIFI Anas - EZAROUALI Abdelkader - AIT-ALI Amine - GHERBI Amayas 

Le but de notre programme est de résoudre le problème de N reines dans un échiquier de N*N cases 
en formalisant les contraintes en forme normale conjonctive puis les convertir en fichier format
DIMACS qu'on donnera au SAT Solveur 'cryptominisat5' qui va résoudre les clauses et affecter aux 
variables des cases une valeur x ( x>0 -> la case contient une reine et x<0 -> la case ne contient pas une reine )


Méthode d'utilisation :

+ Compilation: make compiler 

+ Exécution : make execute

+ Clean : make clean 

Exemple d'exécution :

Saisir N le nombre de reines(N>=4) ou entrez 0 pour quitter:   4
. . R . 
R . . . 
. . . R 
. R . . 

Remarque :
Si vous entrez N>=20 le résultat ne s'affiche pas sur le terminal pour question de lisibilité 
mais il est écrit dans le fichier BOARD.txt que vous pouvez ouvrir et voir la table d'échiquier bien lisible.

