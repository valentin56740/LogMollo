prog: test.o tree_etu.o  
	gcc -o prog test.o tree_etu.o -lm 

main.o: test.c tree_etu.h
	gcc -c test.c -o test.o

fonc.o: tree_etu.c tree_etu.o 
	gcc -c tree_etu.c -o tree_etu.o

clear:
	rm test.o tree_etu.o prog 
