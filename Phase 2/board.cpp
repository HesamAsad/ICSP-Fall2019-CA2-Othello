#include <stdio.h>
#include "graphics.h"

#include "logic.h"

#define SIZE 480

// Cursor position
int gCursorRow = 0, gCursorColumn = 0;

void DrawBoard()
{
	setbkcolor(BLUE);
	cleardevice();

	setcolor(BLACK);

	for (int i = 1; i <= 7; i++)
	{
		int x = i * 60; // SIZE / 8
		line(x, 0, x, SIZE);
	}

	for (int i = 1; i <= 7; i++)
	{
		int y = i * 60;
		line(0, y, SIZE, y);
	}
}

void PlaceDisk(int board[8][8], int row, int column, int player)
{
	int color;

	board[row][column] = player;

	color = (player == 1)? BLACK : (player == 2)? WHITE : BLUE; // 1 -> BLACK | 2 -> WHITE | 0 (else) -> GREEN

	setcolor(color);
	setfillstyle(SOLID_FILL, color);

	fillellipse(30 + (column * 60), 30 + (row * 60), 27, 27); // 27 -> radiusx == radiusy -> circle
}

void MoveCursor(int board[8][8], int row, int column, int player)
{
	int color = (player == 1)? DARKGRAY : LIGHTGRAY; // 1 -> DARKGRAY | 2 -> LIGHTGRAY

	if (row >= 8 || column >= 8 || row < 0 || column < 0 )
		return; // Out of boundary

	// Remove previous cursor, if any.
	PlaceDisk(board, gCursorRow, gCursorColumn, board[gCursorRow][gCursorColumn]);

	// Draw cursor
	setfillstyle(SOLID_FILL, color);
	bar(20 + (column * 60), 20 + (row * 60), 40 + (column * 60), 40 + (row * 60)); // 20 x 20 square

	// Update cursor position
	gCursorRow = row;
	gCursorColumn = column;
}

void HandleInput(int board[8][8], int player)
{
	int valid = 0;

	// Draw first cursor
	MoveCursor(board, gCursorRow, gCursorColumn, player);

	while (!valid)
	{
		switch(getchar()) // Get character
		{
		case 'w':
			MoveCursor(board, gCursorRow - 1, gCursorColumn, player);
			break;
		case 's':
			MoveCursor(board, gCursorRow + 1, gCursorColumn, player);
			break;
		case 'a':
			MoveCursor(board, gCursorRow, gCursorColumn - 1, player);
			break;
		case 'd':
			MoveCursor(board, gCursorRow, gCursorColumn + 1, player);
			break;
		case 'W':
			MoveCursor(board, gCursorRow - 1, gCursorColumn, player);
			break;
		case 'S':
			MoveCursor(board, gCursorRow + 1, gCursorColumn, player);
			break;
		case 'A':
			MoveCursor(board, gCursorRow, gCursorColumn - 1, player);
			break;
		case 'D':
			MoveCursor(board, gCursorRow, gCursorColumn + 1, player);
			break;
		case ' ':
			if (board[gCursorRow][gCursorColumn] != 0)
			{
				valid = 0;
				printf("Cell's taken!\n");
			}
			else if(!ProcessMove(board, player, gCursorRow, gCursorColumn))
			{
				valid = 0;
				printf("Invalid move!\n");
			}
			else
			{
				valid = 1;
			}
		}
	}
}

void InitializeBoard(int board[8][8])
{
	//Initialize WinBGIm window
	initwindow(SIZE + 10, SIZE + 10); // + 10 -> because of a WinBGIm bug

	DrawBoard();

	// Using 0 for empty cells, 1 for black and 2 for white
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
			board[row][column] = 0;

	// Place initial disks
	PlaceDisk(board, 3, 3, 2);
	PlaceDisk(board, 3, 4, 1);
	PlaceDisk(board, 4, 3, 1);
	PlaceDisk(board, 4, 4, 2);
}

void GetDiskNum(int board[8][8], int *black, int *white)
{
	*black = 0;
	*white = 0;

	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
			if (board[row][column] == 1)
				(*black)++;
			else if (board[row][column] == 2)
				(*white)++;
}