#include <stdio.h>
#include "logic.h"

void InitializeBoard(char board[8][8])
{
	// Using '.' as the placeholder
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
			board[row][column] = '.';

	// Place initial disks
	board[3][3] = 'w';
	board[3][4] = 'b';
	board[4][3] = 'b';
	board[4][4] = 'w';
}

void DrawBoard(char board[8][8])
{
	int black = 0, white = 0;

	printf("\n    1  2  3  4  5  6  7  8\n");

	for (int row = 0; row < 8; row++)
	{
		printf(" %d ", (row + 1) * 10);

		for (int column = 0; column < 8; column++)
		{
			printf("%c  ", board[row][column]);

			if (board[row][column] == 'w')
				white++;
			else if (board[row][column] == 'b')
				black++;
		}

		printf("\n");
	}

	printf("\t[B: %d | W: %d]\n\n", black, white);
}

void PlaceDisk(char board[8][8], char player)
{
	int choice, column, row;

	for (;;) // Loop endlessly
	{
		printf("%s's turn: ", (player == 'w')? "White" : "Black");
		scanf("%d", &choice);

		// 12, 2 is column and 1 is row
		column = choice % 10; // 2
		row = choice / 10; // 1

		// Array indices start from 0 not 1
		row--;
		column--;

		if (row >= 8 || column >= 8 || row < 0 || column < 0 )
			printf("Invalid choice!\n");
		else if (board[row][column] != '.')
			printf("Cell's already filled!\n");
		else if (ProcessMove(board, player, row, column))
			break;
		else
			printf("Invalid move!\n");
	}
}

void GetDiskNum(char board[8][8], int *black, int *white)
{
	*black = 0;
	*white = 0;

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
			if (board[row][column] == 'b')
				(*black)++;
			else if (board[row][column] == 'w')
				(*white)++;
}
