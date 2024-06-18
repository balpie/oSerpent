#include "play.h"


position operator+(const position &p1, const position &p2)
{
	position res;
	res.next = (p1.next == nullptr) ? p2.next : p1.next;
	res.row = p1.row + p2.row;
	res.column = p1.column + p2.column;
	return res;
}

bool checkInbound(position p)
{
	if (p.row >= ROW || p.column >= COLUMN 
		|| p.row <= 0 || p.column <= 0)
	{
		return false;
	}
	return true;
}

Board::Board(int nMele = 1){
	//Mele:
	nMele = (nMele > 5) ? (5) : (nMele);
	mele = nMele;
	for (int i = 0; i < ROW; i++) //init board
		for (int j = 0; j < COLUMN; j++)
			board[i][j] = ' ';
	points = 1; //dimensione serpente
	for (int i = 0; i < nMele; i++) //randomizzazione mele/a
	{ 
		int R;
		int C;
		do
		{	
			R = rand() % ROW;
			C = rand() % (COLUMN - 2);
		}
		while (board[R][C] == '+' || (R == ROW/2 && C == (COLUMN - 2)/2) || (R == 1 + ROW/2 && C == (COLUMN - 2)/2));
		board[R][C] = '+';
	}
	//disegno la testa del serpente
	board[ROW/2][(COLUMN - 2)/2] = '@'; 
	//alloco la testa del serpente
	snake = new position;
	snake->row = ROW/2;
	snake->column = (COLUMN - 2)/2;
	snake->next = new position;
	snake->next->row = 1 + ROW/2;
	snake->next->column = (COLUMN - 2)/2;
	board[1 + ROW/2][(COLUMN - 2)/2] = '#';
}

void Board::print()
{
	erase();
	//int y, x;
	//y = x = 1;
	for (int i = 1; i <= ROW; i++)
		for (int j = 1; j <= COLUMN * 2; j++)
		{
			if (j % 2)
				mvaddch(i - 1, j - 1, board[i - 1][(j - 1) / 2]);
			else 
				mvaddch(i - 1, j - 1, ' ');
		}
	wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
	refresh();
}

position Board::getInput()
{ 
	char dir;
	position nHeadPos;
	nHeadPos.row = nHeadPos.column = 0; 
	nHeadPos.next = nullptr; //Posizione relativa alla vecchia posizione
	dir = getch();
	switch (dir)
	{
		case 'w':
			nHeadPos.row--;
			break;
		case 'a':
			nHeadPos.column--;
			break;
		case 's':
			nHeadPos.row++;
			break;
		case 'd':
			nHeadPos.column++;
			break;
		default:
			nHeadPos.row = snake->row - snake->next->row;
			nHeadPos.column= snake->column - snake->next->column;
	}
	nHeadPos = nHeadPos + *snake;
	if (nHeadPos.row == snake->row// "se ha provato a tornare indietro"
		&& nHeadPos.column == snake->column) 
	{
		nHeadPos.row = snake->row - snake->next->row;
		nHeadPos.column= snake->column - snake->next->column;
	}
	return nHeadPos;
}

//ritorna true se va aggiunta la testa
bool Board::muovi(bool aggiungiTesta) //controlla anche se 
{ 
	position newHead = getInput();
	position *p = snake;
	if (!aggiungiTesta) //caso in cui nel tick precedente
					//non ha mangiato una mela
	{
		if (snake->next == nullptr) //serpente con solo testa
		{
			delete snake;
			snake = nullptr;
		}
		else
		{
		position* q;
		while (p->next != nullptr) //rimuovi la coda
			{
				q = p;
				p = p->next;
			}
		delete p;
		q->next = nullptr;
		}
	}
	//aggiungi la testa di posizione newHead
	p = new position;
	p->row = newHead.row;
	p->column = newHead.column;
	p->next = snake;
	snake = p;
	if (checkInbound(newHead) 
		&& board[newHead.row][newHead.column] == '+')
	{
		points++;
		return true;
	}
	return false;
}

bool Board::gameState()
{
	if (!checkInbound(*snake))
		return false;
	position *p = snake->next; //scorro la lista
	for (int i = 0; i < ROW; i++) //tolgo tutto quello che non è mela
		for (int j = 0; j < COLUMN; j++)
			if (board[i][j] != '+')
				board[i][j] = ' ';
	board[snake->row][snake->column] = '@';
	while (p != nullptr)
	{
		if (p != snake && 
			p->row == snake->row && p->column == snake->column)
			return false;
		board[p->row][p->column] = '#';
		p = p->next;
	}
	return true;
}

void Board::randomizzaMela()
{
	int row, column;
	do
	{
		row = rand() % (ROW-1);
		column = rand() % (COLUMN-1);
        row++; column++;
	}while (board[row][column] == '+' || 
			board[row][column] == '#' ||
			board[row][column] == '@');
	board[row][column] = '+';
}

void Board::gameover()
{
	int y, x;
	getyx(stdscr, y, x);
	mvprintw(y/2, x/2 + 10, "game over :(");
	mvprintw(y/2 + 1, x/2 + 10, "pija varkosa");
	mvprintw(y/2 + 2, x/2 + 10, "%d", points);

	//TODO stampa i gazzoz di punti dioboia
    
	timeout(5000); //5 sec
    usleep(500000);
	refresh();
	getch();
}
