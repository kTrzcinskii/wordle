#include "TerminalManager.h"
#include <cstdlib>
#include <thread>
#include <chrono>

namespace terminal_manager {
	void TerminalManager::change_color(Colors color)
	{
		SetConsoleTextAttribute(hConsole_, color);
	}

	void TerminalManager::clear_terminal()
	{
		system("CLS");
	}

	void TerminalManager::sleep_for(unsigned int miliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	}
}