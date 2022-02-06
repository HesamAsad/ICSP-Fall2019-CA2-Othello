#include <stdio.h>
#include "board.h"
#include "logic.h"

int main()
{
	char board[8][8];
	char player = 'b'; // Black always starts first
	int black, white;
	int ongoing = 1, pass = 0;

	InitializeBoard(board); // Board *must* be initialized before use

	while (ongoing)
	{
		if (!pass)
			DrawBoard(board);

		if (HasLegalMoves(board, player))
		{
			pass = 0;
			PlaceDisk(board, player);
		}
		else
			pass++;

		// 2 passes means that no player is capable of making a valid move, so it's game over!
		if (pass == 2)
		{
			printf("Game over.\n");

			GetDiskNum(board, &black, &white);

			if (black > white)
				printf("Black wins!\n");
			else if(black < white)
				printf("White wins!\n");
			else
				printf("It's a draw!\n");

			break;
		}

		player = (player == 'b')? 'w' : 'b'; // Switch players
	}

	return 0;
}
