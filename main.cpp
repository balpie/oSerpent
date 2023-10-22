#include "play.h"

int main()
{
	initscr();
	raw();
	timeout(150);
	noecho();
	srand(time(NULL));
	Board b(4);
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

