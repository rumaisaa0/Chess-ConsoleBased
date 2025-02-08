#include<iostream>
#include<conio.h>
#include<cstring>
#include<string>
#include<math.h>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
#include<fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;
void start(char board[][8])
{
	for (int i = 0; i < 8; i++)
		board[1][i] = 'p';
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			board[i][j] = ' ';
	}
	for (int i = 0; i < 8; i++)
		board[6][i] = 'P';
	board[7][0] = 'R';
	board[7][1] = 'H';
	board[7][2] = 'B';
	board[7][3] = 'Q';
	board[7][4] = 'K';
	board[7][5] = 'B';
	board[7][6] = 'H';
	board[7][7] = 'R';
	board[0][0] = 'r';
	board[0][1] = 'h';
	board[0][2] = 'b';
	board[0][3] = 'q';
	board[0][4] = 'k';
	board[0][5] = 'b';
	board[0][6] = 'h';
	board[0][7] = 'r';
}
void outboard(char board[][8])
{
	cout << "   a   b   c   d   e   f   g   h" << endl;
	cout << "   --------------------------------" << endl;
	for (int i = 0, r = 8; i < 8; i++, r--)
	{
		int c = 0;
		cout << r << " |";
		for (int j = 0; j < 8; j++, c++)
		{
			if (c % 2 == 0)
			{
				cout << board[i][j] << "  |";
			}
			else if (c % 2 != 0)
			{
				cout << board[i][j] << "  |";
			}
		}
		cout << " " << r << endl;
		cout << "   --------------------------------" << endl;
	}
	cout << "   a   b   c   d   e   f   g   h" << endl;
}
void validmove(int afrow, int b4row, int afcol, int b4col, char board[][8])
{
	board[afrow][afcol] = board[b4row][b4col];
	board[b4row][b4col] = ' ';
}
bool bpawn(int afrow, int brow, int afcol, int bcol, char board[][8], bool enpassantw)
{
	bool val = false;
	 //to move downwards and sideways left
	if ((afrow == brow + 1) && (afcol == bcol - 1))
	{
		if (board[afrow][afcol] != ' ')
			val = true;
	}
	 //to move downwards and sideways right
	else if ((afrow == brow + 1) && (afcol == bcol + 1))
	{
		if (board[afrow][afcol] != ' ')
			val = true;
	}
	// to move forward
	else if ((afrow == brow + 1) && afcol == bcol)
	{
		if (board[afrow][afcol] == ' ')
			val = true;
	}
	 //to move 2 steps forward
	else if ((afrow == brow + 2) && afcol == bcol && brow == 1)
	{
		if (board[afrow][afcol] == ' ' && board[afrow - 1][afcol] == ' ')
			val = true;
	}
	//en passant
	if (brow == 4 && afrow == 5 && (bcol == (afcol - 1) || afcol == (bcol - 1)) && enpassantw == true && board[4][afcol] == 'P')
	{
		val = true;
		board[4][afcol] = ' ';
		cout << "enpassant by black!" << endl;
	}
	return val;
}
bool rook(int bfrow, int afrow, int bfcol, int afcol, char board[][8])
{
	if (bfrow == afrow && bfcol == afcol)
		return false;
	else if (bfrow == afrow)
	{

		if (bfcol < afcol)//to move right
		{
			for (int i = bfcol + 1; i <= afcol; i++)
			{
				if (board[bfrow][i] != ' ')
					return false;
			}
		}
		else if (bfcol > afcol)//to move left
		{
			for (int i = bfcol - 1; i > afcol; i--)
			{
				if (board[bfrow][i] != ' ')
					return false;
			}
		}
		return true;
	}
	else if (bfcol == afcol) //to move up
	{
		if (bfrow < afrow)
		{
			for (int i = bfrow + 1; i < afrow; i++)
			{
				if (board[i][bfcol] != ' ')
					return false;
			}
		}
		if (bfrow > afrow)//to move down
		{
			for (int i = bfrow - 1; i > afrow; i--)
			{
				if (board[i][bfcol] != ' ')
					return false;
			}
		}
		return true;
	}
	return false;
}
bool bishop(int bfrow, int afrow, int bfcol, int afcol, char board[][8])
{
	if (bfrow == afrow || bfcol == afcol)
		return false;
	 //lower left diagonal
	else if (bfrow <afrow && bfcol >afcol)
	{
		if ((afrow - bfrow) == (bfcol - afcol))
		{
			int j = bfcol - 1;
			for (int i = bfrow + 1; i < afrow && j>afcol; i++, j--)
			{
				if (board[i][j] != ' ')
					return false;
			}
			return true;
		}
		else
			return false;
	}
	 //upper right diagonal
	else if (bfrow > afrow && bfcol < afcol)
	{
		if ((bfrow - afrow) == (afcol - bfcol))
		{
			int j = bfcol + 1;
			for (int i = bfrow - 1; i > afrow && j < afcol; i--, j++)
			{
				if (board[i][j] != ' ')
					return false;
			}
			return true;
		}
		else
			return false;
	}
	// upper left diagonal
	else if (bfrow > afrow && bfcol > afcol)
	{
		if ((bfrow - afrow) == (bfcol - afcol))
		{
			int j = bfcol - 1;
			for (int i = bfrow - 1; i > afrow && j > afcol; i--, j--)
			{
				if (board[i][j] != ' ')
					return false;
			}
			return true;
		}
		else
			return false;
	}
	 //lower right diagonal
	else if (bfrow < afrow && bfcol < afcol)
	{
		if ((afrow - bfrow) == (afcol - bfcol))
		{
			int j = bfcol + 1;
			for (int i = bfrow + 1; i < afrow && j < afcol; i++, j++)
			{
				if (board[i][j] != ' ')
					return false;
			}
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
bool king(int bfrow, int afrow, int bfcol, int afcol, char board[][8])
{
	if (bfrow == afrow && bfcol == afcol)
		return false;
	else if (bfrow == afrow - 1 && bfcol == afcol + 1)// move upward left
		return true;
	else if (bfrow == afrow + 1 && bfcol == afcol - 1)// move downward right
		return true;
	else if (bfrow == afrow - 1 && bfcol == afcol - 1)// move upward right
		return true;
	else if (bfrow == afrow + 1 && bfcol == afcol + 1)// move downward left
		return true;
	else if (bfrow == afrow - 1 && bfcol == afcol)// move upwards straight
		return true;
	else if (bfrow == afrow + 1 && bfcol == afcol)// move downwards straight
		return true;
	else if (bfrow == afrow && bfcol == afcol + 1)// move left straight
		return true;
	else if (bfrow == afrow && bfcol == afcol - 1)// move right straight
		return true;
	else if (bfrow == afrow && bfcol == 4 && afcol == 2)//castling 1
	{
		if (bfrow == 0 && (board[0][0] == 'r') && board[0][1] == ' ' && board[0][2] == ' ' && board[0][3] == ' ')
		{
			board[0][0] = ' ';
			board[0][3] = 'r';
			return true;
		}
		else if (bfrow == 7 && (board[7][0] == 'R') && board[7][1] == ' ' && board[7][2] == ' ' && board[7][3] == ' ')
		{
			board[7][0] = ' ';
			board[7][3] = 'r';
			return true;
		}
	}
	else if (bfrow == afrow && bfcol == 4 && afcol == 6)//castling 2
	{
		if (bfrow == 0 && (board[0][7] == 'r') && board[0][5] == ' ' && board[0][6] == ' ')
		{
			board[0][7] = ' ';
			board[0][5] = 'r';
			return true;
		}
		else if (bfrow == 7 && (board)[7][7] == 'R' && board[7][5] == ' ' && board[7][6] == ' ')
		{
			board[7][7] = ' ';
			board[7][5] = 'r';
			return true;
		}
	}
	return false;
}
bool horse(int afrow, int b4row, int afcol, int b4col, char board[][8])
{
	if (b4col + 1 == afcol)
	{
		if (b4row + 2 == afrow)
			return true;
		else if (b4row - 2 == afrow)
			return true;
	}
	else if (b4col - 1 == afcol)
	{
		if (b4row + 2 == afrow)
			return true;
		else if (b4row - 2 == afrow)
			return true;
	}
	else if (b4col - 2 == afcol)
	{
		if (b4row + 1 == afrow)
			return true;
		else if (b4row - 1 == afrow)
			return true;
	}
	else if (b4col + 2 == afcol)
	{
		if (b4row + 1 == afrow)
			return true;
		else if (b4row - 1 == afrow)
			return true;
	}
	return false;
}
bool queen(int b4row, int afrow, int b4col, int afcol, char board[][8])
{
	bool roo, bish;
	roo = rook(b4row, afrow, b4col, afcol, board);
	bish = bishop(b4row, afrow, b4col, afcol, board);
	if (bish == false && roo == false)
		return false;
	else
		return true;
}
bool wpawn(int afrow, int b4row, int afcol, int b4col, char board[][8], bool enpassantb)
{
	bool val = false;
	if ((afrow == b4row - 1) && (afcol == b4col - 1))// to move downwards and sideways left
	{
		if (board[afrow][afcol] != ' ')
			val = true;
	}
	else if ((afrow == b4row - 1) && (afcol == b4col + 1))// to move downwards and sideways right
	{
		if (board[afrow][afcol] != ' ')
			val = true;
	}
	else if ((afrow == b4row - 1) && afcol == b4col)// to move forward
	{
		if (board[afrow][afcol] == ' ')
			val = true;
	}
	else if ((afrow == b4row - 2) && afcol == b4col && b4row == 6)// to move 2 steps forward
	{
		if (board[afrow][afcol] == ' ' && board[afrow + 1][afcol] == ' ')
			val = true;
	}
	//en passant
	if (b4row == 3 && afrow == 2 && (b4col == (afcol - 1) || afcol == (b4col - 1)) && enpassantb == true && board[3][afcol] == 'p')
	{
		val = true;
		board[3][afcol] = ' ';
		cout << "enpassant by white!" << endl;
	}
	return val;
}
bool check2(char board[][8], int movenum)
{
	int cr, cc;
	char element;
	bool check = false, enpassant = false;
	if (movenum % 2 == 0)//white
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'K')
				{
					cr = i;
					cc = j;
					i = 8;
					j = 8;
				}
			}
		}
	}
	else if (movenum % 2 != 0)//black
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'k')
				{
					cr = i;
					cc = j;
					i = 8;
					j = 8;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != ' ')
			{
				check = false;
				element = board[i][j];
				if (element == 'p')
				{
					check = bpawn(cr, i, cc, j, board, enpassant);
				}
				else if (element == 'k' || element == 'K')
				{
					check = king(i, cr, j, cc, board);
				}
				else if (element == 'b' || element == 'B')
				{
					check = bishop(i, cr, j, cc, board);
				}
				else if (element == 'h' || element == 'H')
				{
					check = horse(cr, i, cc, j, board);
				}
				else if (element == 'q' || element == 'Q')
				{
					check = queen(i, cr, j, cc, board);
				}
				else if (element == 'r' || element == 'R')
				{
					check = rook(i, cr, j, cc, board);
				}
				else if (element == 'P')
				{
					check = wpawn(cr, i, cc, j, board, enpassant);
				}
				if (check == true && movenum % 2 == 0 && board[i][j] > 83)
				{
					cout << i << " " << j << endl;
					cout << "check by own white invalid " << endl;
					j = 8;
					i = 8;
					return false;
				}if (check == true && movenum % 2 != 0 && board[i][j] < 83)
				{
					cout << "check by own black invalid " << endl;
					j = 8;
					i = 8;
					return false;
				}
			}
		}
	}
	return true;
}
bool checkmate3i(int afrow, int afcol, char board[][8], int movenum)
{
	int kill = 0;
	bool check3 = false;
	bool enpassantw = false, enpassantb = false;
	for (int i = 0; i < 8; i++)//for black king//kill attack
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 'p')
				check3 = bpawn(afrow, i, afcol, j, board, enpassantw);
			if (board[i][j] == 'b')
				check3 = bishop(i, afrow, j, afcol, board);
			if (board[i][j] == 'h')
				check3 = horse(afrow, i, afcol, j, board);
			if (board[i][j] == 'q')
				check3 = queen(i, afrow, j, afcol, board);
			if (board[i][j] == 'r')
				check3 = rook(i,afrow,j, afcol, board);
			if (check3 == true && movenum % 2 == 0 && board[i][j] > 83)
			{
				kill++;
			}
		}
	}
	for (int i = 0; i < 8; i++)//for white king//kill attack
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 'P')
				check3 = wpawn(afrow, i, afcol, j, board, enpassantb);
			if (board[i][j] == 'B')
				check3 = bishop(i,afrow, j, afcol, board);
			if (board[i][j] == 'H')
				check3 = horse(afrow, i, afcol, j, board);
			if (board[i][j] == 'Q')
				check3 = queen(i,afrow, j, afcol, board);
			if (board[i][j] == 'R')
				check3 = rook(i,afrow, j, afcol, board);
			if (check3==true && movenum % 2 != 0 && board[i][j] < 83)
			{
				kill++;
			}
		}
	}
	if (kill == 0)
	{
		bool killattack, possiblek = false, checkm8b = false, enpass = false;
		char attackelement, kingbw, temp;
		int kingrow, kingcol;
		attackelement = board[afrow][afcol];
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'k' && movenum % 2 == 0)
				{
					kingrow = i;
					kingcol = j;
					kingbw = 'k';
					i = 8;
					j = 8;
				}if (board[i][j] == 'K' && movenum % 2 != 0)
				{
					kingrow = i;
					kingcol = j;
					kingbw = 'K';
					i = 8;
					j = 8;
				}
			}
		}
		while (possiblek == false)
		{
			if (board[kingrow + 1][kingcol - 1] == ' ' || (movenum % 2 == 0 && board[kingrow + 1][kingcol - 1] > 83) || (movenum % 2 != 0 && board[kingrow + 1][kingcol - 1] < 83))
			{
				temp = board[kingrow + 1][kingcol - 1];
				board[kingrow + 1][kingcol - 1] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow + 1][kingcol - 1] = temp;
				if (possiblek == true)
					break;
			}
			if (board[kingrow - 1][kingcol + 1] == ' ' || (movenum % 2 == 0 && board[kingrow - 1][kingcol + 1] > 83) || (movenum % 2 != 0 && board[kingrow - 1][kingcol + 1] < 83))
			{
				temp = board[kingrow - 1][kingcol + 1];
				board[kingrow - 1][kingcol + 1] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow - 1][kingcol + 1] = temp;
				if (possiblek == true)
					break;
			}
			if (board[kingrow + 1][kingcol + 1] == ' ' || (movenum % 2 == 0 && board[kingrow + 1][kingcol + 1] > 83) || (movenum % 2 != 0 && board[kingrow + 1][kingcol + 1] < 83))
			{
				temp = board[kingrow + 1][kingcol + 1];
				board[kingrow + 1][kingcol + 1] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow + 1][kingcol + 1] = temp;
				if (possiblek == true)
					break;
			}
			if (board[kingrow - 1][kingcol - 1] == ' ' || (movenum % 2 == 0 && board[kingrow - 1][kingcol - 1] > 83) || (movenum % 2 != 0 && board[kingrow - 1][kingcol - 1] < 83))
			{
				temp = board[kingrow - 1][kingcol - 1];
				board[kingrow - 1][kingcol - 1] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow - 1][kingcol - 1] = temp;
				if (possiblek == true)
					break;
			}
			if (board[kingrow + 1][kingcol] == ' ' || (movenum % 2 == 0 && board[kingrow + 1][kingcol] > 83) || (movenum % 2 != 0 && board[kingrow + 1][kingcol] < 83))
			{
				temp = board[kingrow + 1][kingcol];
				board[kingrow + 1][kingcol] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow + 1][kingcol] = temp;
				if (possiblek == true)
					break;
			}
			if (board[kingrow - 1][kingcol] == ' ' || (movenum % 2 == 0 && board[kingrow - 1][kingcol] > 83) || (movenum % 2 != 0 && board[kingrow - 1][kingcol] < 83))
			{
				temp = board[kingrow - 1][kingcol];
				board[kingrow - 1][kingcol] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				temp = board[kingrow - 1][kingcol];
				if (possiblek == true)
					break;
			}
			if (board[kingrow][kingcol - 1] == ' ' || (movenum % 2 == 0 && board[kingrow][kingcol - 1] > 83) || (movenum % 2 != 0 && board[kingrow][kingcol - 1] < 83))
			{
				temp = board[kingrow][kingcol - 1];
				board[kingrow][kingcol - 1] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow][kingcol - 1] = temp;
				if (possiblek == true)
					break;
			}
			if (board[kingrow][kingcol + 1] == ' ' || (movenum % 2 == 0 && board[kingrow][kingcol + 1] > 83) || (movenum % 2 != 0 && board[kingrow][kingcol + 1] < 83))
			{
				temp = board[kingrow][kingcol + 1];
				board[kingrow][kingcol + 1] = kingbw;
				board[kingrow][kingcol] = ' ';
				possiblek = check2(board, movenum);
				board[kingrow][kingcol] = kingbw;
				board[kingrow][kingcol + 1] = temp;
				if (possiblek == true)
					break;
			}
			break;
		}
		if (possiblek == false)
			return true;
	}
	return false;
}
void check1(char board[][8], int movenum,bool &checkm,bool& checkb, bool& checkw)
{
	int cr, cc;
	char element;
	bool check = false, enpassant = false;
	if (movenum % 2 == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'k')
				{
					cr = i;
					cc = j;
					i = 8;
					j = 8;
				}
			}
		}
	}
	else if (movenum % 2 != 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'K')
				{
					cr = i;
					cc = j;
					i = 8;
					j = 8;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			element = board[i][j];
			if (element != ' ')
			{
				if (element == 'p')
					check = bpawn(cr, i, cc, j, board, enpassant);
				else if (element == 'k' || element == 'K')
					check = king(i, cr, j, cc, board);
				else if (element == 'b' || element == 'B')
					check = bishop(i, cr, j, cc, board);
				else if (element == 'h' || element == 'H')
					check = horse(cr, i, cc, j, board);
				else if (element == 'q' || element == 'Q')
					check = queen(i, cr, j, cc, board);
				else if (element == 'r' || element == 'R')
					check = rook(i, cr, j, cc, board);
				else if (element == 'P')
					check = wpawn(cr, i, cc, j, board, enpassant);
				if (check == true && movenum % 2 == 0 && board[i][j] < 83)
				{
					checkb = true;
					check = false;
					if (checkmate3i(i, j, board, movenum))
					{
						cout << "checkmate by white" << endl;
						checkm = true;
						break;
					}
					cout << "check! black save ur king " << endl;
					j = 8;
					i = 8;
				}if (check == true && movenum % 2 != 0 && board[i][j] > 83)
				{
					checkw = true;
					check = false;
					if (checkmate3i(i, j, board, movenum))
					{
						cout << "checkmate by black" << endl;
						checkm = true;
						break;
					}
					cout << "check! white save ur king " << endl;
					j = 8;
					i = 8;

				}
			}
		}
	}
}
//void stalemate(char board[][8], int movenum)
//{
//	int countw = 0, countb = 0;
//	bool stalemove;
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (board[i][j] != 32 && movenum % 2 == 0 && board[i][j] < 83)//white stalemate
//			{
//				if (board[i][j] == 'P')
//				{
//					stalemove = wpawn(afrow, i, afcol, j, board, enpassantw);
//				}
//				else if (board[i][j] == 'K')
//				{
//					stalemove = king(i, afrow, j, afcol, board);
//				}
//				else if (board[i][j] == 'B')
//				{
//					stalemove = bishop(i, afrow, j, afcol, board);
//				}
//				else if (board[i][j] == 'H')
//				{
//					stalemove = horse(afrow, i, afcol, j, board);
//				}
//				else if (board[i][j] == 'Q')
//				{
//					stalemove = queen(i, afrow, j, afcol, board);
//				}
//				else if (board[i][j] == 'R')
//				{
//					stalemove = rook(i, afrow, j, afcol, board);
//				}
//			}
//			else	if (board[i][j] != 32 && movenum % 2 != 0 && board[i][j] > 83)//black stalemate
//			{
//				if (board[i][j] == 'p')
//				{
//					stalemove = bpawn(afrow, i, afcol, j, board, enpassantw);
//				}
//				else if (board[i][j] == 'k')
//				{
//					stalemove = king(i, afrow, j, afcol, board);
//				}
//				else if (board[i][j] == 'b')
//				{
//					stalemove = bishop(i, afrow, j, afcol, board);
//				}
//				else if (board[i][j] == 'h')
//				{
//					stalemove = horse(afrow, i, afcol, j, board);
//				}
//				else if (board[i][j] == 'q')
//				{
//					stalemove = queen(i, afrow, j, afcol, board);
//				}
//				else if (board[i][j] == 'r')
//				{
//					stalemove = rook(i, afrow, j, afcol, board);
//				}
//			}
//		}
//	}
//}
bool handshakeandresignfunc(int movenum, float timew, float timeb, int mode)
{
	char choice = 'n';
	while (choice != 'c' && choice != 'C' && choice != 'r' && choice != 'R' && choice != 'h' && choice != 'H')
	{
		cout << "enter r to resign" << endl;
		cout << "enter h to handshake" << endl;
		cout << "enter c to continue" << endl;
		cin >> choice;
	}
	if (choice == 'c' || choice == 'C')
		return false;
	if (movenum % 2 == 0)
	{
		if (choice == 'r' || choice == 'R')
		{
			cout << "black wins!" << endl;
			return true;
		}
		else if (choice == 'h' || choice == 'H')
		{
			cout << "black do you accept handshake?" << endl;
			cout << "enter a to accept handshake" << endl;
			cin >> choice;
			if (choice == 'a' || choice == 'A')
			{
				cout << "handshaken!" << endl;
				if (mode == 1)
				{
					if (timew < timeb)
						cout << "white has the advantage" << endl;
					else
						cout << "black has the advantage" << endl;
				}
				return true;
			}
		}
	}
	if (movenum % 2 != 0)
	{
		if (choice == 'r' || choice == 'R')
		{
			cout << "white wins!" << endl;
			return true;
		}
		else if (choice == 'h' || choice == 'H')
		{
			cout << "white do you accept handshake?" << endl;
			cout << "enter a to accept handshake" << endl;
			cin >> choice;
			if (choice == 'a' || choice == 'A')
			{
				cout << "handshaken!" << endl;
				if (mode == 1)
				{
					if (timew < timeb)
						cout << "white has the advantage" << endl;
					else
						cout << "black has the advantage" << endl;
				}
				return true;
			}
		}

	}
	return false;
}
int main()
{
	int b4row, b4col, afrow, afcol;
	char element, promotion = 'p', again = 'a';
	char before[3], after[3], board[8][8];
	ofstream game;
	game.open("chess.txt");
	for (int gamenum = 1; gamenum <= 3; )
	{
		start(board);
		outboard(board);
		cout << "game number: " << gamenum << endl;
		game << "game number: " << gamenum << endl;
		int movenum = 0, mode = 0;
		float timew = 0, timeb = 0;
		bool checkb=false, checkw=false, end = false, enpassantb = false, enpassantw = false, move = false,checkm=false;
		do
		{
			if (mode != 1 && mode != 2 && mode != 3 && mode != 4)//mode choice
			{
				cout << "press 1 for classic mode" << endl;
				cout << "press 2 for Rapid mode" << endl;
				cout << "press 3 for Blitz mode" << endl;
				cout << "press 4 for Lightning mode" << endl;
				cout << "enter your choice" << endl;
				cin >> mode;
				if (mode != 1 && mode != 2 && mode != 3 && mode != 4)
				{
					cout << "invalid choice" << endl;
					continue;
				}
				else if (mode == 2)
				{
					game << "rapid mode" << endl;
					timew = 600;
					timeb = 600;
				}
				else if (mode == 3)
				{
					game << "Blitz mode" << endl;
					timew = 300;
					timeb = 300;
				}
				else if (mode == 4)
				{
					game << "lightning mode" << endl;
					timew = 15;
					timeb = 15;
				}
				else if (mode == 1)
					game << "Classic mode" << endl;
			}
			game << endl;
			if (movenum % 2 == 0)
			{
				cout << "white move" << endl;
				game << "white move" << endl;
			}
			if (movenum % 2 != 0)
			{
				cout << "black move" << endl;
				game << "black move" << endl;
			}
			cout << "move:" << movenum + 1 << endl;
			move = false;
			auto start = high_resolution_clock::now();
			cout << "enter before position: " << endl;
			cin >> before;
			b4row = abs(before[1] - 56);
			b4col = before[0] - 97;
			cout << "enter after position: " << endl;
			cin.ignore();
			cin.get(after, 3);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<seconds>(stop - start);
			game << before << "  " << after << endl;
			game << "move number: " << movenum + 1 << endl;
			afrow = abs((after[1]) - 56);
			afcol = after[0] - 97;
			cout << b4col << " " << b4row << " " << afcol << " " << afrow << endl;
			system("CLS");
			element = board[b4row][b4col];
			if (board[b4row][b4col] == 'p')
			{
				move = bpawn(afrow, b4row, afcol, b4col, board, enpassantw);
				if (b4row == 1 && afrow == 3 && move == true)
					enpassantb = true;
				cout << enpassantb << endl;
			}
			else if (board[b4row][b4col] == 'k' || board[b4row][b4col] == 'K')
			{
				move = king(b4row, afrow, b4col, afcol, board);
				if (b4row == afrow && b4col == 4 && afcol == 2)//castling
				{
					if (b4row == 0 && board[0][0] == 'r' && board[0][1] == ' ' && board[0][2] == ' ' && board[0][3] == ' ' && checkb == false && board[b4row][b4col] == 'k')
					{
						board[0][0] = ' ';
						board[0][3] = 'r';
						move = true;
					}
					else if (b4row == 7 && board[7][0] == 'R' && board[7][1] == ' ' && board[7][2] == ' ' && board[7][3] == ' ' && checkw == false && board[b4row][b4col] == 'K')
					{
						board[7][0] = ' ';
						board[7][3] = 'R';
						move = true;
					}
				}
				else if (b4row == afrow && b4col == 4 && afcol == 6)
				{
					if (b4row == 0 && board[0][7] == 'r' && board[0][5] == ' ' && board[0][6] == ' ' && checkb == false && board[b4row][b4col] == 'k')
					{
						board[0][7] = ' ';
						board[0][5] = 'r';
						move = true;
					}
					else if (b4row == 7 && (board)[7][7] == 'R' && board[7][5] == ' ' && board[7][6] == ' ' && checkw == false && board[b4row][b4col] == 'K')
					{
						board[7][7] = ' ';
						board[7][5] = 'R';
						move = true;
					}
				}
			}
			else if (board[b4row][b4col] == 'b' || board[b4row][b4col] == 'B')
				move = bishop(b4row, afrow, b4col, afcol, board);
			else if (board[b4row][b4col] == 'h' || board[b4row][b4col] == 'H')
				move = horse(afrow, b4row, afcol, b4col, board);
			else if (board[b4row][b4col] == 'q' || board[b4row][b4col] == 'Q')
				move = queen(b4row, afrow, b4col, afcol, board);
			else if (board[b4row][b4col] == 'r' || board[b4row][b4col] == 'R')
				move = rook(b4row, afrow, b4col, afcol, board);
			else if (board[b4row][b4col] == ' ')
				move = false;
			else if (board[b4row][b4col] == 'P')
			{
				move = wpawn(afrow, b4row, afcol, b4col, board, enpassantb);
				if (b4row == 6 && afrow == 4 && move == true)
					enpassantw = true;
				cout << enpassantw << endl;
			}
			if (movenum % 2 == 0)//white move first
			{
				if (board[b4row][b4col] > 83)
					move = false;
				if (board[afrow][afcol] < 83 && board[afrow][afcol] != 32)
					move = false;
			}
			else if (movenum % 2 != 0)//black move second
			{
				if (board[b4row][b4col] < 83)
					move = false;
				if (board[afrow][afcol] > 83 && board[afrow][afcol] != 32)
					move = false;
			}
			if (move == true)//checking ownself
			{
				element = board[afrow][afcol];
				board[afrow][afcol] = board[b4row][b4col];
				board[b4row][b4col] = ' ';
				move = check2(board, movenum);
				board[b4row][b4col] = board[afrow][afcol];
				board[afrow][afcol] = element;
			}
			if (movenum % 2 == 0)//timing white
			{
				if (mode == 1)
					timew += duration.count();
				if (mode == 2)
				{
					timew -= duration.count();
					if (move == true)
						timew += 10;
				}
				if (mode == 3 || mode == 4)
					timew -= duration.count();
			}
			if (movenum % 2 != 0)//timing black
			{
				if (mode == 1)
					timeb += duration.count();
				if (mode == 2)
				{
					timeb -= duration.count();
					if (move == true)
						timeb += 10;
				}
				if (mode == 3 || mode == 4)
					timeb -= duration.count();
			}
			cout << "whites time: " << timew << endl;
			cout << "blacks time: " << timeb << endl;
			if (move == true)
			{
				if (b4row == 6 && afrow == 7 && board[b4row][b4col] == 'p')//pawn promotion of black
				{
					while (promotion != 'q' && promotion != 'r' && promotion != 'b' && promotion != 'h' && promotion != 'k')
					{
						cout << "oppurtunity to promote your pawn" << endl;
						cout << "enter element you want to promote to: ";
						cin >> promotion;
						if (promotion == 'q' || promotion == 'r' || promotion == 'b' || promotion == 'h' || promotion == 'k')
							board[b4row][b4col] = promotion;
					}
				}
				if (b4row == 1 && afrow == 0 && board[b4row][b4col] == 'P')//pawn promotion of white
				{
					while (promotion != 'Q' && promotion != 'R' && promotion != 'B' && promotion != 'H' && promotion != 'K')
					{
						cout << "oppurtunity to promote your pawn" << endl;
						cout << "enter element you want to promote to: ";
						cin >> promotion;
					}
					if (promotion == 'Q' || promotion == 'R' || promotion == 'B' || promotion == 'H' || promotion == 'K')
						board[b4row][b4col] = promotion;
				}
				cout << "move number: " << movenum + 1 << endl;
				game << "valid move " << endl;
				validmove(afrow, b4row, afcol, b4col, board);
				outboard(board);
				check1(board, movenum,checkm,checkb,checkw);
				if (movenum % 2 != 0)
				{
					enpassantw = false;
					checkb = false;
				}
				if (movenum % 2 == 0)
				{
					enpassantb = false;
					checkw = false;
				}
				if (checkm == true)
					break;
				if ((mode == 2 || mode == 3 || mode == 4) && (timew <= 0 || timeb <= 0))
					break;
			}
			else if (move == false)
			{
				cout << "invalid move" << endl;
				game << "invalid move" << endl;
				outboard(board);
				if ((mode == 2 || mode == 3 || mode == 4) && (timew <= 0 || timeb <= 0))
					break;
				cout << "enter move again" << endl;
				game << "entered move again below" << endl;
				continue;
			}
			if (mode != 4&&checkm==false)
				end = handshakeandresignfunc(movenum, timew, timeb, mode);
			if (mode == 4)
			{
				timew = 15;
				timeb = 15;
			}
			movenum++;
		} while (end == false);
		if ((mode == 2 || mode == 3 || mode == 4) && end == false)
		{
			if (timeb < timew)
			{
				cout << "white wins" << endl;
				game << "white wins" << endl;
			}
			else
			{
				cout << "black wins" << endl;
				game << "black wins" << endl;
			}
		}
		if (gamenum < 3)
		{
			again = 'a';
			while (again != 'n' && again != 'y' && again != 'Y' && again != 'N')
			{
				cout << "enter y to play again" << endl;
				cout << "enter n to exit" << endl;
				cin >> again;
			}
			if (again == 'n' || again == 'N')
				break;
			else if (again == 'y' || again == 'Y')
				gamenum++;
		}
		game << endl;
		game << endl;
		/*system("CLS");*/
	}
	game.close();
	system("pause");
	return 0;
}