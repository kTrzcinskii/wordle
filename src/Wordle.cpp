#include "Wordle.h"
#include "TerminalManager.h"
#include <iostream>

namespace wordle {
	terminal_manager::TerminalManager tm;

	void Wordle::welcome_user()
	{
		std::cout << "\nWelcome to Worlde - terminal version!\n\n";
		tm.change_color(tm.Cyan);
		std::cout << "Enter your name to continue: ";
		tm.change_color(tm.Violet);
		getline(std::cin, user_);
		tm.sleep_for(500);
		tm.clear_terminal();
		tm.change_color(tm.White);
		std::cout << "\nHello ";
		tm.change_color(tm.Violet);
		std::cout << user_;
		tm.change_color(tm.White);
		std::cout << "\nLet the game begin!\n";
 	}

	void Wordle::start()
	{
		welcome_user();
	}
}