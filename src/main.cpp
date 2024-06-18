#include "play.h"

int main()
{
    int curry, currx;

	initscr();
	raw();
	timeout(150);
        //DEBUG
        //timeout(15000);
        //DEBUG
	noecho();
	srand(time(NULL));
	Board b(4);
    getmaxyx(stdscr, curry, currx); //controllo che la finestra sia abbastanza grande
    if(curry < 24 || currx < 80) 
    {
        erase();
        mvprintw(2, 1, "Finestra troppo piccola");
        refresh();
        timeout(5000); //5 sec
        usleep(500000);
        refresh();
        getch();
        endwin();
        return 0;
    }
    resize_term(24, 80);
	b.print();
	bool mela = false;
	do
	{
		if (mela) //prima perchè così so già dov'è il coso
			b.randomizzaMela();
		b.print();
		mela = b.muovi(mela);
	}
	while(b.gameState());
	b.gameover();
	endwin();
	return 0;
}

