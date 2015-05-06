#include <iostream>
using namespace std;
#include <conio.h>

#include "Console.h"
using namespace System;

#include "globals.h"

// Reset the console's cursor to bottom of screen.
void ResetCursor()
{
	Console::SetCursorPosition(0, Console::WindowHeight() - 1);
}

// TODO Part 3: Check collision function

int main()
{
#pragma region Look Nice
	// Get the handle of the console window.
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set font size/properties so the maze fits.
	CONSOLE_FONT_INFOEX font;
	font.nFont = 0;
	font.dwFontSize.X = 10;
	font.dwFontSize.Y = 20;
	font.FontFamily = 48;
	font.FontWeight = 400;
	font.cbSize = sizeof(font);
	SetCurrentConsoleFontEx(consoleHandle, false, &font);

	// What are our current properties?
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	GetConsoleScreenBufferInfoEx(consoleHandle, &info);

	// Correctly colored critters.
	info.ColorTable[DarkYellow] = RGB(246, 130, 31);
	info.ColorTable[Cyan] = RGB(27, 177, 230);
	info.ColorTable[Red] = RGB(237, 27, 36);
	info.ColorTable[Magenta] = RGB(245, 153, 178);
	info.ColorTable[Yellow] = RGB(254, 242, 0);

	// Set proper dimensions with no scroll bars.
	COORD winSize = CreateCoord(MAZE_COLS, MAZE_ROWS + 2);
	info.dwSize.X = info.dwMaximumWindowSize.X = info.srWindow.Right = winSize.X;
	info.dwSize.Y = info.dwMaximumWindowSize.Y = info.srWindow.Bottom = winSize.Y;
	SetConsoleScreenBufferInfoEx(consoleHandle, &info);
	SetConsoleScreenBufferSize(consoleHandle, winSize);

	// How large are we and the entire screen?
	HWND hwnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int	w  = rect.right - rect.left,
		h  = rect.bottom - rect.top,
		sw = GetSystemMetrics(SM_CXSCREEN),
		sh = GetSystemMetrics(SM_CYSCREEN);

	// Center us.
	MoveWindow(hwnd, (sw - w) >> 1, (sh - h) >> 1, w, h, TRUE);

	SetConsoleTitle(L"Pac-Man"); // Unicode string!
#pragma endregion

	// TODO Part 2: Memory Leak Detection

	// TODO Part 2: Seed random
	// NOTE: Commenting-out the seeding of random can make it easier to test your code

	// TODO Part 1: Name entry

	char maze[MAZE_ROWS][MAZE_COLS] =
	{
		// 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54
		{ MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, '0', ' ', MUD, ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', MUD, ' ', '0', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MUD, ' ', ' ', ' ', MUD, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MGD, MGD, MGD, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MBR, ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', ' ', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', ' ', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', MUD, ' ', 'o', ' ', MUD, ' ', MUD, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MUD, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
		{ MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', ' ', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MTR, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MTL, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, '0', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', '0', MUD, },
		{ MBL, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MTL, MLR, MTR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MBR, },
		{ MTL, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', ' ', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', MBL, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MTR, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', MUD, ' ', MUD, ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', MBL, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', ' ', MUD, ' ', ' ', ' ', MUD, ' ', 'o', ' ', MTL, MLR, MLR, MLR, MLR, MLR, MBR, ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MTR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MBR, ' ', 'o', ' ', MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, ' ', 'o', MUD, },
		{ MUD, 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', ' ', 'o', MUD, },
		{ MBL, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MLR, MBR, },
	};

	// Draw the maze.
	for (int i = 0; i < MAZE_ROWS; i++)
	{
		for (int j = 0; j < MAZE_COLS; j++)
		{
			if (MPP == maze[i][j])
				Console::ForegroundColor(Green);
			else if (MDOT == maze[i][j] || MGD == maze[i][j])
				Console::ForegroundColor(White);
			else
				Console::ForegroundColor(Blue);
			cout << maze[i][j];
		}
	}

#pragma region Example Code
#if !0
	/*****************************************************************/
	/*****************************************************************/
	// EXAMPLE CODE - None of this code belongs in the final game, so
	//	make sure to disable it when you start writing the game code.
	/*****************************************************************/
	/*****************************************************************/

	// COORD structure:
	//  - 2 short data members: X and Y
	//  - no constructor, so initially both are set to garbage
	//  - helper function CreateCoord can be used to make a coord and assign it good starting values
	COORD temp = CreateCoord(5, 5);
	Console::SetCursorPosition(temp.X, temp.Y);

	Console::ForegroundColor(Yellow);
	cout << PAC;

	// ResetCursor - written at top of main.cpp (resets the cursor to the bottom of the game).
	ResetCursor();

	Console::ResetColor();
	cout << "Press 'd' to move Pac-Man right: ";
	while (true)
	{
		// _getch() - from <conio.h>
		//  - reads a single character
		//  - doesn't print the input to the screen
		//  - DON'T use cin.ignore with this, not needed and will force the player to press enter
		char letter = _getch();
		if (cin.good() && 'd' == letter)
			break;
		cin.clear();
	}
	ResetCursor();

	// Clear-out Pac-Man's last spot by printing a space.
	Console::SetCursorPosition(temp.X, temp.Y);
	cout << ' ';

	// Update Pac-Man's position.
	temp.X += 2;

	// Draw at new spot.
	Console::SetCursorPosition(temp.X, temp.Y);
	Console::ForegroundColor(Yellow);
	cout << PAC;

	/*****************************************************************/
	/*****************************************************************/
	// END OF EXAMPLE CODE
	/*****************************************************************/
	/*****************************************************************/
#endif
#pragma endregion

	// TODO Part 1: Create player
	COORD playerStart = CreateCoord(27, 23);

	// TODO Part 2: Create ghosts
	COORD startPos[NUM_GHOSTS] = { { 27, 11 }, { 23, 14 }, { 27, 14 }, { 31, 14 } };
	ConsoleColor startColor[NUM_GHOSTS] = { Red, Cyan, Magenta, DarkYellow };

	// TODO Part 1: Display HUD and reset cursor

	// TODO Part 1: Game loop
	// Inside game loop:
	//	TODO Part 1: Player input
	//	TODO Part 1: Move player
	//	TODO Part 3: Check collision
	//	TODO Part 2: Move ghosts
	//	TODO Part 3: Check collision
	//	TODO Part 3: Handle player death
	//	TODO Part 1: Display HUD and reset cursor

	// After game loop:
	// TODO Part 1 & 2: Free memory

	Console::ResetColor();
	ResetCursor();
	system("pause");
	return 0;
}