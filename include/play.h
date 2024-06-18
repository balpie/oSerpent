#include <stdlib.h>
#include <cstdlib>
#include <ncurses.h>
#include <ctime>
#include <unistd.h>
#define ROW 23
#define COLUMN 40

struct position{
	unsigned int row;
	unsigned int column;
	position* next;
};

class Board{
	char board[ROW][COLUMN];
	position* snake;
	int mele;
	int points;
public:
	Board(int); //richiede il numero di mele, 0 <= nMele <= 5 
	position getInput(); //ritorna la nuova posizione della testa
	bool gameState(); 
	bool muovi(bool);
	void incrementa();
	void randomizzaMela();
	void print();
	void gameover();

	bool checksave(Board); //TODO
	void save(Board); //TODO
	
};


