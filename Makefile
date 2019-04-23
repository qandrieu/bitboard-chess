all : main.o game.o view.o legalmove.o attack.o pile.o bboard.o
	gcc main.o game.o view.o legalmove.o attack.o pile.o bboard.o -o ChessGame

main.o: main.c game.h view.h
	gcc -c main.c -o main.o -Wall -O

game.o: game.c legalmove.h
	gcc -c game.c -o game.o -Wall -O

view.o: view.c legalmove.h
	gcc -c view.c -o view.o -Wall -O

legalmove.o: legalmove.c attack.h pile.h
	gcc -c legalmove.c -o legalmove.o -Wall -O

attack.o: attack.c bboard.h
	gcc -c attack.c -o attack.o -Wall -O

pile.o: pile.c
	gcc -c pile.c -o pile.o -Wall -O

bboard.o: bboard.c
	gcc -c bboard.c -o bboard.o -Wall -O

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ChessGame