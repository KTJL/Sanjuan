all:Play.o
	gcc main.c Play.o -o main

Play:
	gcc -c Play.c -o Play.o