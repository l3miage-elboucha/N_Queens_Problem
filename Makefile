CC=clang
N_REINES=8  # Default value -DN=$(N_REINES)

execute: nqueens
	./nqueens

compiler: nqueens.c
	$(CC) -o nqueens nqueens.c 

clean:
	rm -f nqueens clauses_seuls.txt clauses.cnf resultat.txt BOARD.txt