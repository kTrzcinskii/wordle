#include "Wordle.h"
#include "TerminalManager.h"
#include <iostream>
#include <fstream>

namespace wordle {
	terminal_manager::TerminalManager tm;

	Wordle::Wordle()
	{
		tm.change_color(tm.Cyan);
		std::cout << "Loading data...\n";
		tm.sleep_for(300);
		std::ifstream file("./res/words.txt");
		std::string temp;
		while (std::getline(file, temp))
		{
			all_words_.push_back(temp);
			all_words_number_++;
		}
		file.close();
		tm.change_color(tm.Green);
		std::cout << "Data loaded successfully!\n";
		tm.sleep_for(500);
		tm.clear_terminal();
	}

	void Wordle::welcome_user()
	{
		tm.change_color(tm.White);
		std::cout << "\nWelcome to Worlde - terminal version!\n\n";
		tm.change_color(tm.Cyan);
		std::cout << "Enter your name to continue: ";
		tm.change_color(tm.Violet);
		std::getline(std::cin, user_);
		tm.sleep_for(500);
		tm.clear_terminal();
		tm.change_color(tm.White);
		std::cout << "\nHello ";
		tm.change_color(tm.Violet);
		std::cout << user_;
		tm.change_color(tm.White);
		std::cout << "\nLet the game begin!\n";
 	}

	void Wordle::set_new_word()
	{
		std::cout << "ALL WORDS: " << all_words_number_;
	}

	void Wordle::start()
	{
		welcome_user();
		set_new_word();
	}
}