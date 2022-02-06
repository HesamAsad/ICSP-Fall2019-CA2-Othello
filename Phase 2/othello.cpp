#include <stdio.h>
#include "graphics.h"

#include "board.h"
#include "logic.h"

int main()
{
	int board[8][8];
	int player = 1; // Black always starts first

	int black, white;
	int ongoing = 1, pass = 0;

	InitializeBoard(board); // Board *must* be initialized before use

	while (ongoing)
	{
		GetDiskNum(board, &black, &white);

		if (HasLegalMoves(board, player))
		{
			printf("\n[Black: %d - White: %d]\n", black, white);
			printf("%s's turn\n", (player == 1)? "Black" : "White");

			pass = 0;
			HandleInput(board, player);
		}
		else
		{
			pass++;
		}

		// 2 passes means that no player is capable of making a valid move, so it's game over!
		if (pass == 2)
		{
			printf("\nGame over.\n");

			if (black > white)
				printf("Black wins!\n");
			else if(black < white)
				printf("White wins!\n");
			else
				printf("It's a draw!\n");

			printf("[Black: %d - White: %d]\n", black, white);

			break;
		}

		player = (player == 1)? 2 : 1; // Switch turns
	}

	printf("Press any key to exit...\n");
	getch();

	closegraph();
	return 0;
}