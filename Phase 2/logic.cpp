#include "board.h"

int TraceBlank(int board[8][8], int row, int column, int offsetX, int offsetY)
{
	int player = board[row][column];

	column += offsetX;
	row += offsetY;

	if (board[row][column] == 0)
		return 0;

	while((column >= 0 && column <= 7) && (row >= 0 && row <= 7) && board[row][column] != player)
	{
		if (board[row][column] == 0)
			return 1;

		column += offsetX;
		row += offsetY;
	}

	return 0;
}

int TraceDisk(int board[8][8], int player, int row, int column, int offsetX, int offsetY)
{
	int origRow, origColumn;
	int opponent;

	origRow = row;
	origColumn = column;

	opponent = (player == 1)? 2 : 1;

	column += offsetX;
	row += offsetY;

	if (board[row][column] == 0 || board[row][column] == player)
		return 0;

	while((column >= 0 && column <= 7) && (row >= 0 && row <= 7) && board[row][column] == opponent)
	{
		column += offsetX;
		row += offsetY;
	}

	// Trace back
	if (board[row][column] == player)
	{
		// Flip rival disks
		while (row != origRow || column != origColumn)
		{
			//board[row][column] = player;
			PlaceDisk(board, row, column, player);

			column -= offsetX;
			row -= offsetY;
		}

		//board[row][column] = player; // Place the disk in the cell player has selected
		PlaceDisk(board, row, column, player);

		return 1;
	}

	return 0;
}

// Return 1 if the move is valid and is processed, otherwise, return 0
int ProcessMove(int board[8][8], int player, int row, int column)
{
	int scenario[8] = {0};

	// We must check each possible scenario seperately. Why? Because the compiler will skip checking other scenarios if one of them is possible
	scenario[0] = TraceDisk(board, player, row, column, -1, 0); // left
	scenario[1] = TraceDisk(board, player, row, column, +1, 0); // right
	scenario[2] = TraceDisk(board, player, row, column, 0, +1); // up
	scenario[3] = TraceDisk(board, player, row, column, 0, -1); // down
	scenario[4] = TraceDisk(board, player, row, column, +1, +1); // bottom-right corner
	scenario[5] = TraceDisk(board, player, row, column, -1, -1); // upper-left corner
	scenario[6] = TraceDisk(board, player, row, column, +1, -1); // upper-right corner
	scenario[7] = TraceDisk(board, player, row, column, -1, +1); // bottom-left corner

	return scenario[0] || scenario[1] || scenario[2] || scenario[3] || scenario[4] || scenario[5] || scenario[6] || scenario[7];
}

// Return 1 if the player can make a legal move, otherwise, return 0
int HasLegalMoves(int board[8][8], int player)
{
	for (int row = 0; row < 8; row++)
		for (int column = 0; column < 8; column++)
		{
			if (board[row][column] == player)
			{
				if (TraceBlank(board, row, column, -1, 0) || TraceBlank(board, row, column, +1, 0) // left and right
				|| TraceBlank(board, row, column, 0, +1) || TraceBlank(board, row, column, 0, -1) // up and down
				|| TraceBlank(board, row, column, +1, +1) || TraceBlank(board, row, column, -1, -1) // bottom-right corner and upper-left corner
				|| TraceBlank(board, row, column, +1, -1) || TraceBlank(board, row, column, -1, +1)) // upper-right corner and bottom-left corner
					return 1;
			}
		}

	return 0;
}
