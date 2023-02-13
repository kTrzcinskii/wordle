#include "TerminalManager.h"
#include <cstdlib>

namespace terminal_manager {
	void TerminalManager::change_color(Colors color)
	{
		SetConsoleTextAttribute(hConsole_, color);
	}

	void TerminalManager::clear_terminal()
	{
		system("CLS");
	}
}