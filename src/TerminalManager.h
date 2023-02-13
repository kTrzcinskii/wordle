#pragma once

#include <Windows.h>

namespace terminal_manager {
	class TerminalManager {
	public:
		enum Colors {
			White = 15,
			Green = 2,
			Yellow = 14,
			Red = 12,
			Cyan = 3,
			Violet = 9,
		};

		void change_color(Colors color);
		void clear_terminal();
		void sleep_for(unsigned int miliseconds);
		void pause();

	private:
		HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
	};
}